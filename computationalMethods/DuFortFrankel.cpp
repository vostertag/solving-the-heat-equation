#include"DuFortFrankel.h"
#include<iostream>
#include<math.h>

// CONSTRUCTOR
DuFortFrankel::DuFortFrankel(Parameters parameters): ExplicitMethod(parameters) {
	getFirstStrepFromFTCS();	// This scheme needs to have 2 time step to get the next one. Therefore we must get the first time step from an other scheme (FTCS here)
}

// Get the next time step using DuFortFrankel's equation
double DuFortFrankel::getNextTimeStep(int i, int t) {
	// If t > 1, we use the equation. Otherwise, we must use the result from FTCS as discussed in the comment of the constructor
	if (t > 1) {
		return ((1 - (2 * parameters.D*parameters.deltaT / pow(parameters.deltaX, 2))) * fTable[t - 2][i] +
			(2 * parameters.D*parameters.deltaT / pow(parameters.deltaX, 2)) * (fTable[t - 1][i + 1] + fTable[t - 1][i - 1])) *
			(1 / (1 + (2 * parameters.D*parameters.deltaT / pow(parameters.deltaX, 2))));
	}
	else {
		return fTable[t][i];
	}
}