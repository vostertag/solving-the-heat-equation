#include"ExplicitMethod.h"

#ifndef DUFORFRANKEL_H  //include guard
#define DUFORTFRANKEL_H 

/**
* DuFortFrankel is an explicit scheme that we are required to use in this assignement
*/
class DuFortFrankel : public ExplicitMethod {
	public:
		/**
		* DuFortFrankel's constructor
		*
		* @see PDESolver (same constructor)
		*/
		DuFortFrankel(Parameters parameters);
		//~DuFortFrankel();

		/**
		* Implementation of ExplicitMethod's getNextTimeStep
		*
		* @see getNextTimeStep() from ExplicitMethod
		*/
		double getNextTimeStep(int i, int t);
};

#endif