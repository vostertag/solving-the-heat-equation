#include"AnalyticalSolution.h"
#include"math.h"
#include<iostream>

// CONSTRUCTOR
AnalyticalSolution::AnalyticalSolution(Parameters parameters): ExplicitMethod(parameters) {

}

// Return the analytical value for x and t
double AnalyticalSolution::getAnalyticalValue(double x, double t, int precision) {
	double sum = 0;
	// The sum cannot be infinite like the analytical solution would want it to be. We have to stop at a number (precision)
	for (int m = 1; m < precision; m++) {
		sum += exp(-parameters.D*pow(m*PI / parameters.L, 2)*t) * ((1 - pow(-1, m)) / (m*PI)) * sin(m*PI*x / parameters.L);
	}
	return parameters.tSur + 2 * (parameters.tIn - parameters.tSur) * sum;	// Simply applying what's given in the subject of the assignement
}

// Get the next time step using the analytical solution given in the subject
double AnalyticalSolution::getNextTimeStep(int i, int t) {
	return getAnalyticalValue(i*parameters.deltaX, t*parameters.deltaT, 1000);
}