#include"ExplicitMethod.h"

#ifndef ANALYTICALSOLUTION_H	// include guard
#define ANALYTICALSOLUTION_H 

/**
* Analytical Solution to the problem
*
* It is not an explicit scheme but its' behaviour is pretty much the same as one, which is 
* why it inherits from ExplicitMethod
*/
class AnalyticalSolution : public ExplicitMethod {
private:
	// CLASS MEMBER

	const double PI = 3.141592653589793;	///< Approximate value of pi
public:
	/**
	* Analytical constructor
	*
	* @see PDESolver (same constructor)
	*/
	AnalyticalSolution(Parameters parameters);
	//~AnalyticalSolution();

	/**
	* Implementation of ExplicitMethod's getNextTimeStep
	*
	* @see getNextTimeStep() from ExplicitMethod
	*/
	double getNextTimeStep(int i, int t);

	/**
	* Function to get the analytical value of the solution f(t, x) with a given precision
	*
	* @param x, value of x
	* @param t, value of t
	* @param precision that we wish to have for the infinite for loop (that can't be infinite with a computer...)
	*/
	double getAnalyticalValue(double x, double t, int precision);
};

#endif