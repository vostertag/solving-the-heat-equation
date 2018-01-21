#include<vector>
#include"Parameters.h"
#include"PDESolver.h"

#ifndef PRINTER_H	// include guard
#define PRINTER_H 

using namespace std;

/**
* Printer class used to create all the datFiles as well as the gnuplot commands to do to get the graphs from the report
*/
class Printer{
private: 
	PDESolver* pdeSolver;				///< PDESolver we wish to print
	Parameters parameters;				///< Parameters of the PDESolver
	vector< vector<double> > fTable;	///< fTable of the PDESolver
	string className;					///< class name of the PDESolver (useful for naming the files)
public:
	/**
	* Printer's constructor
	*
	* @param pdeSolver: scheme for which we would like to print something
	* @param fileName: fileName to use
	*/
	Printer(PDESolver* pdeSolver);

	/**
	* Setter for PDESolver (also changes the parameters using the one from the new pdeSolver
	*
	* @param pdeSolver: PDESolver* to print
	*/
	void setPdeSolver(PDESolver* pdeSolver);

	/**
	* Function that prints the value in console
	*
	* @param t: time step for which we want to see the values
	*/
	void printInConsole(int t);

	/**
	* Function that creates a datFile for a given time step (found in the datFiles repo)
	*
	* @param t: time step for which we want to get a datFile
	*/
	void createDatFileForT(int t);

	/**
	* Function to delete the .txt file with the commands (inside the repo of the code)
	*/
	void deleteGnuplotCommands();

	/**
	* Function that add to the command.txt (or create it) the commands to plot the scheme at the time step t using gnuplot
	*
	* @param t time step for which we wish to plot a graph
	*/
	void gnuplotForT(int t);

	/**
	* Function that add to the command.txt (or create it) the commands to plot the L2-norm of the difference between two schemes
	*
	* @param PDESolver* that we want to do the L2-norm with
	*/
	void gnuplotErrorsCompareTo(PDESolver* pdeSolver2);

	/**
	* Function that add to the command.txt (or create it) the commands to plot 2 schemes on the same graph in order to compare them
	*
	* @param t time step for which we wish to plot the graph
	* @param PDESolver* that we want to plot with our scheme
	*/
	void gnuplotForTCompareTo(int t, PDESolver* pdeSolver2);

	/**
	* Print the norm (L2) of the errors in a datFile for given time steps
	*
	* @param ts: time steps for which we will have a look at the errors
	* @param analyticalSolution: to compare with our scheme
	*/
	void datFileErrorsComparedTo(vector<int> ts, PDESolver* pdeSolver2);
};

#endif