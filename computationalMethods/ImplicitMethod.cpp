#include"ImplicitMethod.h"
#include<iostream>

// CONSTRUCTOR
ImplicitMethod::ImplicitMethod(Parameters parameters): PDESolver(parameters), matrix(parameters.numberOfSpacePoints - 1, vector<double>(parameters.numberOfSpacePoints - 1)), matrix2(parameters.numberOfSpacePoints - 1) {
}

// Initialization method used in all implicit schemes' constructors
void ImplicitMethod::initialization() {
	// Get time step 0, needed to create matrix2
	for (int t = 0; t <= parameters.numberOfTimePoints; t++) {
		for (int i = 0; i <= parameters.numberOfSpacePoints; i++) {
			checkBundaries(i, t);
		}
	}
	// Creation of both matrix and applying the thomas algorithm right away
	createMatrix();
	createMatrix2(0);
}

// Function to fill up fTable for all the time steps we want
void ImplicitMethod::solve() {
	// For each time step, we solve the new equation matrix * fTable[t] = matrix2 to fill up fTable and then get the new matrix2 ready. (matrix1 doesn't change)
	for (int t = 1; t <= parameters.numberOfTimePoints; t++) {
		solve_thomas(t);
		createMatrix2(t);
	}
}

// Creates matrix as seen in the analysis (cf report) and applying the thomas algorithm directly on each value
void ImplicitMethod::createMatrix() {
	// Only zeros except at i-1, i and i+1 (3-diagonal matrix). For these points, the value change with the scheme we are using
	double diag = getDiagonalValue();
	double nonDiag = getOutOfDiagonalValue();
	for (int i = 0; i < parameters.numberOfSpacePoints - 1; i++) {
		if (i == 0) {
			matrix[i][i+1] = nonDiag / diag;
		}
		else if (i != parameters.numberOfSpacePoints - 2) {
			matrix[i][i+1] = nonDiag / (diag - nonDiag * matrix[i - 1][i]);
		}
		matrix[i][i] = 1;
	}
}

// Creates matrix2 as seen in the analysis (cf report) and applying the thomas algorithm directly on each value
void ImplicitMethod::createMatrix2(int t) {
	double diag = getDiagonalValue();
	double nonDiag = getOutOfDiagonalValue();
	for (int i = 0; i < parameters.numberOfSpacePoints - 1; i++) {
		if (i == 0) {
			matrix2[i] = getMatrix2Values(t, i) / diag;
		}else {
			matrix2[i] = (getMatrix2Values(t, i) - nonDiag*matrix2[i - 1]) / (diag - nonDiag*matrix[i - 1][i]);
		}
	}
}

// Getting the value for fTable[t+1] by solving the different equations
void ImplicitMethod::solve_thomas(int t) {
	for (int i = parameters.numberOfSpacePoints; i >= 0; i--) {
		if(!checkBundaries(i, t)) {
			if (i-1 == parameters.numberOfSpacePoints - 2) {
				fTable[t][i] = matrix2[i - 1];
			}
			else {
				fTable[t][i] = matrix2[i - 1] - matrix[i - 1][i] * fTable[t][i + 1];
			}
		}
	}
}