#include"ExplicitMethod.h"

#ifndef RICHARDSON_H	//include guard
#define RICHARDSON_H 

/**
* Richardson is an explicit scheme that we are required to use in this assignement
*/
class Richardson : public ExplicitMethod {
public:
	/**
	* Richardson's constructor
	*
	* @see PDESolver (same constructor)
	*/
	Richardson(Parameters parameters);
	//~Richardson();

	/**
	* Implementation of ExplicitMethod's getNextTimeStep
	*
	* @see getNextTimeStep() from ExplicitMethod
	*/
	double getNextTimeStep(int i, int t);
};

#endif