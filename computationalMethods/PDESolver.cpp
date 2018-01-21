#include"PDESolver.h"
#include<iostream>
#include <math.h>
#include<string>
#include<typeinfo>

using namespace std;

// CONSTRUCTOR
// initialisation de fTable et des paramètres
PDESolver::PDESolver(Parameters parameters) : parameters(parameters) {
	// catching exceptions
	try {
		if (parameters.L <= 0) {
			throw invalid_argument("The wall must have a length bigger than 0");
		}if (parameters.deltaT <= 0 || parameters.deltaX <= 0) {
			throw invalid_argument("The mesh sizes must be bigger than 0");
		}if (parameters.numberOfSpacePoints * parameters.deltaX != parameters.L) {
			throw invalid_argument("The mesh size times the number of space points should be equal to the length of the wall");
		}
	}
	catch (invalid_argument &error) {
		cout << "ERROR:" << endl;
		cout << error.what() << endl;
		abort();
	}
	this->fTable = vector< vector<double> >(parameters.numberOfTimePoints + 1, vector< double >(parameters.numberOfSpacePoints + 1));
}

// Function checking if we are the edge of the wall
bool PDESolver::checkBundaries(int i, int t) {
	if (i == 0 || i == parameters.numberOfSpacePoints) {
		fTable[t][i] = parameters.tSur;		// If we are at the edge (i=0 or i=last space point), we know the temperature is tSur
		return true;
	}
	else if (t == 0) {
		fTable[t][i] = parameters.tIn;
		return true;
	}
	return false;
}

// Function that returns the name of the class
string PDESolver::getClassName() {
	string className = typeid(*this).name();
	className.erase(0, 6);		// To remove the "class " part of typeid().name()
	return className;
}

// Calculating the L2 norm for each time step compared to PDESolver
vector< double > PDESolver::L2NormWith(PDESolver* pdeSolver) {
	vector< double > L2Norms(parameters.numberOfTimePoints+1);
	vector< vector<double> > fTable2 = pdeSolver->getFTable();
	try {
		// Making sure both schemes are solved, otherwise it is useless to compare them...
		if (fTable[0][0] != parameters.tSur || fTable2[0][0] != parameters.tSur) {
			throw invalid_argument("The two scheme should be solved in order to compare them");
		}
	}catch (invalid_argument &error) {
		cout << "ERROR:" << endl;
		cout << error.what() << endl;
		abort();
	}
	double sum, norm;
	for (int t = 0; t <= parameters.numberOfTimePoints; t++) {
		sum = 0;
		for (int i = 0; i <= parameters.numberOfSpacePoints; i++) {
			sum += sqrt(pow(fTable[t][i] - fTable2[t][i], 2));
		}
		// Using the norm L2 definition, best one for analysis (cf report)
		norm = sum;
		L2Norms[t] = norm;
	}
	return L2Norms;
}

// Getter for fTable
vector< vector<double> > PDESolver::getFTable() {
	return fTable;
}

// Getter for deltaT
Parameters PDESolver::getParameters() {
	return parameters;
}

void PDESolver::setParameters(Parameters parameters) {
	this->parameters = parameters;
}
