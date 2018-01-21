#include"Printer.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

// CONSTRUCTOR
Printer::Printer(PDESolver* pdeSolver): pdeSolver(pdeSolver), parameters(pdeSolver->getParameters()), fTable(pdeSolver->getFTable()), className(pdeSolver->getClassName()) {
	deleteGnuplotCommands();
}

// Auxiliary method to throw exceptions if the scheme is not solved
void exceptions(vector< vector<double> > fTable, Parameters parameters) {
	try {
		if (fTable[0][0] != parameters.tSur) {
			throw invalid_argument("The scheme must be solved in order to be printed");
		}
	}
	catch (invalid_argument &error) {
		cout << "ERROR:" << endl;
		cout << error.what() << endl;
		abort();
	}
}

/**
* Auxiliary function: Convert a float into a string
*
* Useful to get delta t and delta x in the file name. Ex: 0.005 -> 0_005
*
* @param double float, float to be converted
* @return String with float converted in a string
*/
string convertFloatToString(double flt) {
	string str = to_string(flt);
	str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	str.replace(str.find("."), 1, "_");
	return str;
}

// Set Printer's member using the new PDESolver
void Printer::setPdeSolver(PDESolver* pdeSolver) {
	this->pdeSolver = pdeSolver;
	this->parameters = pdeSolver->getParameters();
	this->fTable = pdeSolver->getFTable();
	this->className = pdeSolver->getClassName();
}

// Print values in console for a give time step t
void Printer::printInConsole(int t) {
	exceptions(fTable, parameters);
	cout << "f(" << t << ") = ";
	for (int i = 0; i < fTable[0].size() ; i++) {
		cout << fTable[t][i] << "\t" ;
	}
	cout << endl;
}

// Create a datFile with the values of a give time step t
void Printer::createDatFileForT(int t) {
	exceptions(fTable, parameters);
	string deltaT = convertFloatToString(parameters.deltaT);
	string file = className + "_t" + to_string((int)t) + "_deltaT" + deltaT + ".dat";
	ofstream datFile;
	datFile.open("datFiles/" + file);
	// Create the file and fill it up with the values
	for (int i = 0; i < fTable[0].size(); i++) {
		datFile << parameters.deltaX*i << " " << fTable[t][i] << endl;
	}
	datFile.close();
}

// Create a datFile with the norm L2 to check the errors from the scheme
void Printer::datFileErrorsComparedTo(vector<int> ts, PDESolver* pdeSolver2){
	exceptions(fTable, parameters);
	exceptions(pdeSolver2->getFTable(), parameters);
	string deltaT = convertFloatToString(parameters.deltaT);
	string file = className + "_compare_to_" + pdeSolver2->getClassName	() + "_for_deltaT_" + deltaT + ".dat";
	ofstream datFile;
	datFile.open("datFiles/" + file);								// Create the .dat file
	vector< double > L2Norms = pdeSolver->L2NormWith(pdeSolver2);
	for (int t = 0; t < ts.size(); t++) {
		datFile << ts[t]*parameters.deltaT << " " << L2Norms[ts[t]] << endl;
	}
	datFile.close();
}

void Printer::gnuplotForT(int t) {
	string deltaT = convertFloatToString(parameters.deltaT);
	ofstream commands;
	commands.open("commands.txt", ios::out | ios::app);
	commands << "set terminal png" << endl;
	commands << "set output '" << className << "_t" << t << "_deltaT" << deltaT << ".png'" << endl;
	commands << "set grid" << endl;
	commands << "set xlabel \"Distance (feets)\"" << endl;
	commands << "set ylabel \"Temperature (fahrenheits)\"" << endl;
	commands << "plot \"" << className << "_t" << t << "_deltaT" << deltaT << ".dat\" w lp pt 4 lc rgb \"red\" lw 1 title '" << className << "'" << endl;
	commands.close();
}

void Printer::gnuplotForTCompareTo(int t, PDESolver* pdeSolver2) {
	string name = pdeSolver2->getClassName();
	string deltaT = convertFloatToString(parameters.deltaT);
	ofstream commands;
	commands.open("commands.txt", ios::out | ios::app);
	commands << "set terminal png" << endl;
	commands << "set output '" << className << "_compareTo_" << name << "_t_" << t << "_deltaT" << deltaT << ".png'" << endl;
	commands << "set grid" << endl;
	commands << "set xlabel \"Distance (feets)\"" << endl;
	commands << "set ylabel \"Temperature (fahrenheits)\"" << endl;
	commands << "plot \"" + name + "_t" << t << "_deltaT" << deltaT << ".dat\"" << " w l lw 2 lc 'green' title 'Analytic solution',\\" << endl;
	commands << "\"" << className << "_t" << t << "_deltaT" << deltaT << ".dat\" w p pt 4 lc rgb \"red\" lw 1 title '" << className << "'" << endl;
	commands.close();
}

void Printer::gnuplotErrorsCompareTo(PDESolver* pdeSolver2) {
	string name = pdeSolver2->getClassName();
	string deltaT = convertFloatToString(parameters.deltaT);
	ofstream commands;
	commands.open("commands.txt", ios::out | ios::app);
	commands << "set terminal png" << endl;
	commands << "set output '" << className + "_errors_for_deltaT_" + deltaT + ".png" << endl;
	commands << "set grid" << endl;
	commands << "set xlabel \"t (no unit)\"" << endl;
	commands << "set ylabel \"L2 norm\"" << endl;
	commands << "plot \"" << className + "_compare_to_" + name + "_for_deltaT_" + deltaT + ".dat\"" << " w l lw 2 lc 'green' title 'L2 norm for " << className << "'" << endl;	// Graph of the errors
	commands.close();
}

// Delete the previous gnuplotcommands file
void Printer::deleteGnuplotCommands() {
	ofstream commands;
	commands.open("commands.txt");
	commands.close();
}