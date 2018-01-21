#include"FTCS.h"
#include<iostream>

// CONSTRUCTOR 
FTCS::FTCS(Parameters parameters): ExplicitMethod(parameters) {
	try {
		if (parameters.D*parameters.deltaT / (parameters.deltaX*parameters.deltaX) > 0.5) {
			throw domain_error("FTCS will be unstable with these parameters");
		}
	}
	catch (domain_error &error) {
		cout << "WARNING:" << endl;
		cout << error.what() << endl;
	}
}

// Get the next time step using FTCS's equation
double FTCS::getNextTimeStep(int i, int t) {
	return fTable[t - 1][i] + (parameters.D*parameters.deltaT / (parameters.deltaX*parameters.deltaX)) * (fTable[t - 1][i + 1] - 2 * fTable[t - 1][i] + fTable[t - 1][i - 1]);
}