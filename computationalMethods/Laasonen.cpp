#include"Laasonen.h"
#include<iostream>

// CONSTRUCTOR
Laasonen::Laasonen(Parameters parameters) :
	ImplicitMethod(parameters) {
	c = parameters.D*parameters.deltaT / (parameters.deltaX*parameters.deltaX);
	initialization();
}

// Gets the values of matrix2 for Laasonen (cf analysis in report)
double Laasonen::getMatrix2Values(int t, int i) {
	// Boundary value
	if (i == parameters.numberOfSpacePoints - 2 || i == 0) {
		return fTable[t][i + 1] + c*parameters.tSur;
	}
	// Other values
	else {
		return fTable[t][i + 1];
	}
}

// Gets the diagonal values of matrix for Laasonen (cf analysis in report)
double Laasonen::getDiagonalValue() {
	return (2 * c + 1);
}

// Gets the out of diagonal values of matrix for Laasonen (cf analysis in report)
double Laasonen::getOutOfDiagonalValue() {
	return -c;
}