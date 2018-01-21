#include"PDESolver.h"

#ifndef IMPLICITMETHOD_H	//include guard
#define IMPLICITMETHOD_H 

/**
* ImplicitMethod is an abstract class for all of the implicit schemes.
*
* It inherits from PDESolver and contains all of the useful class for an implicit scheme.
* It has a few new class members that are related to the two matrixes needed in the solving
* of an implicit scheme.
*
* The explicit scheme will solve the equation : matrix * fTable[tWeWantToSolve] = matrix2 using 
* the LU decomposition. The value of matrix and matrix2 changes with the scheme we wish to use.
*/
class ImplicitMethod : public PDESolver {
protected:
	// CLASS MEMBERS
	vector< vector<double> > matrix;	///< Matrix in the left of the equation 
	vector< double > matrix2;			///< Matrix in the right of the equation
public:
	/**
	* ImplicitMethod's constructor
	*
	* @see PDESolver (same constructor)
	*/
	ImplicitMethod(Parameters parameters);
	//~ImplicitMethod();

	/**
	* Solve method to fill up fTable
	*
	* @see solve() function from PDESolver
	*/
	void solve();

	/**
	* Function that solves the equation matrix * ftable[t+1] = matrix2 once the thomas algorithm has been applied
	*/
	void solve_thomas(int t);

	/**
	* Function that creates matrix (3 diagonal matrix)
	*/
	void createMatrix();

	/**
	* Function that creates matrix2
	*
	* @param t for which time step we wish to create that matrix
	*/
	void createMatrix2(int t);

	/**
	* Pure virtual function that will give the value in the diagonal of matrix
	*
	* The way of creating matrix is always the same (thus the createMatrix() method here), 
	* only the value of the matrix changes with the scheme
	*
	* @return value of the diagonal of the matrix
	*/
	double virtual getDiagonalValue() = 0;

	/**
	* Pure virtual that gives the value outside of the diagonal of matrix
	*
	* @return value outside of the diagonal of matrix
	* @see getDiagonalValue() for some additional infos
	*/
	double virtual getOutOfDiagonalValue() = 0;

	/**
	* Pure virtual function that gets the values of matrix2
	*
	* @param time step 
	* @param space point
	* @return value of matrix2 for i and t 
	*/
	double virtual getMatrix2Values(int t, int i) = 0;

	/**
	* Method used in the constructor of implicit schemes
	*
	* It gets matrix2 for the first time step ready as well as matrix
	* and its' LU decomposition that will always be the same no matter
	* the time step and time point
	*/
	void initialization();
};

#endif