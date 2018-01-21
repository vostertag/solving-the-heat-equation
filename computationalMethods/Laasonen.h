#include"ImplicitMethod.h"

#ifndef LAASONEN_H	// include guard
#define LAASONEN_H 

/**
* Laasonen implicit scheme that we are required to use in this assignement
*/
class Laasonen : public ImplicitMethod {
private:
	double c; 							///< Value of c in the matrix (found during the analysis of the method in the report)
public:
	/**
	* Laasonen's constructor
	*
	* @see PDESolver (same constructor)
	*/
	Laasonen(Parameters parameters);
	//~Laasonen();

	/**
	* Get the diagonal value for the Laasonen scheme
	*
	* @return value of the diagonal of matrix
	* @see getDiagonalValue() from ImplicitScheme
	*/
	double getDiagonalValue();

	/**
	* Get the values out of the diagonal for the Laasonen scheme
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