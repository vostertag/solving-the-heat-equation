#include"ExplicitMethod.h"
#include"AnalyticalSolution.h"
#include"CrankNicholson.h"
#include"FTCS.h"
#include<iostream>

// Constructor (using PDESolver's constructor)
ExplicitMethod::ExplicitMethod(Parameters parameters): PDESolver(parameters) {
}

// Function to fill up fTable for all the time steps we want
void ExplicitMethod::solve() {
	// For each space point of each time step, we check if we are at a bundary (and use the bundary conditions if so)
	// If we are not, we get the value of the temperature for each point using the equation of whatever scheme we are using
	for (int t = 0; t <= parameters.numberOfTimePoints; t++) {
		for (int i = 0; i <= parameters.numberOfSpacePoints; i++) {
			if (!checkBundaries(i, t)) {
				fTable[t][i] = getNextTimeStep(i, t);
			}
		}
	}
}

// Fill up the first time step with the FTCS scheme
void ExplicitMethod::getFirstStrepFromFTCS() {
	// Create FTCS, solve for only 1 point, copy fTable[1]
	int temp = parameters.numberOfTimePoints;
	parameters.numberOfTimePoints = 1;
	FTCS ftcs = FTCS(parameters);
	parameters.numberOfTimePoints = temp;
	ftcs.solve();
	fTable[1] = ftcs.getFTable()[1];
}