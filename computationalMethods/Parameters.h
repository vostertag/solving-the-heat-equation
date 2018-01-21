#ifndef PARAMETERS_H	//include guard
#define PARAMETERS_H

/**
* Parameters is a structure that has all of the useful parameters of the problem to solve.
*
* It was created so that if a user uses multiple schemes, he wouldn't have to write each parameters
* again and again which is quite frustrating. Here, he'll just define them once.
*/
struct Parameters
{
	double D;							///< Diffusivity (in ft^2/hr)
	double deltaT;						///< deltaT (in hrs) 
	double deltaX;						///< deltaX (in ft) 
	double tIn;							///< Temperature of the inside of the wall 
	double tSur;						///< Temperature of the outside of the wall
	double L;							///< Size of the wall
	int numberOfTimePoints;				///< Number of points in time we will need to solve
	int numberOfSpacePoints;			///< Number of points in our grid that we will try to solve
};

#endif