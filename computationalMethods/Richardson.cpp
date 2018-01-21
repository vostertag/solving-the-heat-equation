#include"Richardson.h"
#include<iostream>

// CONSTRUCTOR 
Richardson::Richardson(Parameters parameters): ExplicitMethod(parameters) {
	getFirstStrepFromFTCS();	// This scheme needs to have 2 time step to get the next one. Therefore we must get the first time step from an other scheme (FTCS here)
}

// Get the next time step using Richardson's equation
double Richardson::getNextTimeStep(int i, int t) {
	// If t > 1, we use the equation. Otherwise, we must use the result from FTCS as discussed in the comment of the constructor
	if (t > 1) {
		return fTable[t-2][i] + parameters.D/(2* parameters.deltaT*parameters.deltaX*parameters.deltaX) * (fTable[t-1][i+1] - 2* fTable[t - 1][i] + fTable[t - 1][i - 1]);
	}
	else {
		return fTable[t][i];
	}
}