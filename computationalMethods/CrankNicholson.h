#include"ImplicitMethod.h"

#ifndef CRANKNICHOLSON_H	// include guard
#define CRANKNICHOLSON_H 

/**
* CrankNicholson implicit scheme that we are required to use in this assignement
*/
class CrankNicholson : public ImplicitMethod {
private:
	double c; 							///< Value of c in the matrix (found during the analysis of the method in the report)
public:
	/**
	* CrankNicholson's constructor
	* 
	* @see PDESolver 
	*/
	CrankNicholson(Parameters parameters);
	//~CrankNicholson();

	/**
	* Get the diagonal value for the CrankNicholson scheme
	*
	* @return value of the diagonal of matrix
	* @see getDiagonalValue() from ImplicitScheme
	*/
	double getDiagonalValue();

	/**
	* Get the values out of the diagonal for the CrankNicholson scheme
	*
	* @return value of the points out of the diagonal of matrix
	* @see getOutOfDiagonalValue() from ImplicitScheme
	*/
	double getOutOfDiagonalValue();

	/**
	* Get the values of matrix2
	*
	* @return value of matrix2 for t and i
	* @see getBoundaryValue() from ImplicitScheme
	*/
	double getMatrix2Values(int t, int i);
};

#endif