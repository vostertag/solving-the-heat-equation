#include<vector>	
#include"Parameters.h"


using namespace std;

#ifndef PDESOLVER_H		// include guard
#define PDESOLVER_H

/**
* PDESolver is an abstract class that has all the required functions and members to solve the
* partial differential equations (PDE) from the subject. It will be the base for all the schemes.
*
* It provides a constructor that will be used by all of its' derived class to get all the
* variables needed for the solving of the equation.
* It also provides some useful functions that will often be used by its' derived class.
*/
class PDESolver {
	protected:
		// CLASS MEMBERS 
		Parameters parameters;					///< Structure Parameters, with all of the problem's parameters, to make it easier on the user to write when he uses the  same parameters again and again
		vector< vector<double> > fTable;		///< Vector of vectors that contains all the solutions f : fTable[1][10] is the temperature at the 1st time point of the 10th space point
	public:
		/**
		* PDESolver's constructor
		*
		* By providing all the wanted parameters, we can set up the solving of the equation.
		* This function also initialize fTable with the solutions of the time step 0 that we
		* already know and will always be the same, no matter the scheme used.
		* You probably noticed that we don't ask for numberOfSpacePoints, that is because we
		* can get it using the other parameters.
		*
		* This function also throws exceptions if the user's value can not be used
		* 
		* @param D the diffusivity (in ft^2/hr)
		* @param deltaT (in hrs)
		* @param deltaX (in ft)
		* @param tIn the temperature inside of the wall
		* @param tSur the temperature outside of the wall
		* @param L the size of the wall
		* @param numberOfTimePoints number of points in time we wish to solve
		*/
		PDESolver(Parameters parameters);

		//~PDESolver();

		/**
		* Function that checks if we are at an edge of the wall.
		*
		* If it's the case, it will also put the right value for that space point at that time step in fTable 
		* (which is the boundary condition, that is to say tSur)
		*
		* @param i space point that needs to be checked
		* @param t timepoint that we are at (useful to fill up fTable if needed)
		* @return true if we are at a bundary and false otherwise
		*/
		bool checkBundaries(int i, int t);

		/**
		* Pure virtual function that solves all the points that we desire and put their value in fTable
		*
		* Every type of scheme (implicit and explicit) will solve our equation, but they have different 
		* ways to do it, as we will see. Therefore, this is a pure virtual class.
		*/
		void virtual solve()=0;

		/**
		* Function that creates a vector with the L2 norm for each time step in comparison of an other PDESolver
		*
		* Mostly used with the analytic solution, to get the errors of the scheme
		* 
		* @param pdeSolver to do the L2 norm with
		* @return vector with the values of the norm for each time step of our scheme
		*/
		vector< double > L2NormWith(PDESolver* pdeSolver);

		/**
		* Getter for fTable (useful in the Printer class)
		*
		* @return fTable
		*/
		vector< vector<double> > getFTable();

		/**
		* Getter for Parameters
		* 
		* @return Parameters
		*/
		Parameters getParameters();

		/**
		* Setter for Parameters
		*/
		void setParameters(Parameters parameters);

		/**
		* Function that gives the name of the class (scheme) being used
		*
		* @return the name of the class
		*/
		string getClassName();
};

#endif
