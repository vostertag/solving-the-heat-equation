#include"PDESolver.h"

#ifndef EXPLICITMETHOD_H	//include guard
#define EXPLICITMETHOD_H 

/**
* ExplicitMethod is an abstract class for all of the explicit schemes.
*
* It inherits from PDESolver and contains all of the useful class for an explicit scheme.
*/
class ExplicitMethod : public PDESolver {
	public:
		/**
		* ExplicitMethod's constructor
		*
		* @see PDESolver (same constructor)
		*/
		ExplicitMethod(Parameters parameters);

		/**
		* Pure virtual function to get the next time step using the previous ones we already solved
	    *	
		* The only difference in each explicit scheme is the way to get the next time step, so this will
		* have to be implemented by all the explicit schemes.
		*
		* @param i which space point do we wish to solve
		* @param t at which time step are we
		* @return the value of the temperature for fTable[t][i]
		*/
		double virtual getNextTimeStep(int i, int t)=0;
		//~ExplicitMethod();

		/**
		* Solve method to fill up fTable
		* 
		* @see solve() function from PDESolver
		*/
		void solve();

		/**
		* Get the first time step using the FTCS method
		*
		* Some explicit schemes are using two time steps to solve the next one. This is a problem for
		* t = 1 and we therefore need to use an other explicit method to get all the points for the first
		* time step. In our case, we will be using the FTCS scheme.
		*
		* @see FTCS
		*/
		void getFirstStrepFromFTCS();
};

#endif