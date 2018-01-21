#include"ExplicitMethod.h"

#ifndef FTCS_H	// include guard
#define FTCS_H 

/**
* FTCS (Forward Time, Central Space) is an explicit scheme that was not required to use in the assignement.
*
* I implemented it because we need an explicit scheme that doesn't two time steps to get the 
* next one to initialize fTable[1][i] (for all i) for the other explicit schemes.
*/
class FTCS : public ExplicitMethod {
	public:
		/**
		* FTCS constructor
		*
		* @see PDESolver (same constructor)
		*/
		FTCS(Parameters parameters);
		//~FTCS();

		/**
		* Implementation of ExplicitMethod's getNextTimeStep
		*
		* @see getNextTimeStep() from ExplicitMethod
		*/
		double getNextTimeStep(int i, int t);
};

#endif