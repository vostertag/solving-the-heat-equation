#include"CrankNicholson.h"
#include<iostream>

// CONSTRUCTOR
CrankNicholson::CrankNicholson(Parameters parameters) :
	ImplicitMethod(parameters) {
	c = parameters.D*parameters.deltaT / (2 * parameters.deltaX*parameters.deltaX);
	initialization();
}

// Gets the values of matrix2 for CrankNicholson (cf analysis in report)
double CrankNicholson::getMatrix2Values(int t, int i) {
	// Boundary value
	if (i == parameters.numberOfSpacePoints - 2 || i == 0) {
		return (1 - 2 * c)*fTable[t][i + 1] + c*fTable[t][i + 2] + c*fTable[t][i] + c*parameters.tSur;
	}
	// Other values
	else {
		return (1 - 2 * c)*fTable[t][i + 1] + c*fTable[t][i + 2] + c*fTable[t][i];
	}
}

// Gets the diagonal values of matrix for CrankNicholson (cf analysis in report)
double CrankNicholson::getDiagonalValue() {
	return (2 * c + 1);
}

// Gets the out of diagonal values of matrix for CrankNicholson (cf analysis in report)
double CrankNicholson::getOutOfDiagonalValue() {
	return -c;
}