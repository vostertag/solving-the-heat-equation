#include"PDESolver.h"
#include"Parameters.h"
#include"DuFortFrankel.h"
#include"Richardson.h"
#include"Laasonen.h"
#include"FTCS.h"
#include"AnalyticalSolution.h"
#include"CrankNicholson.h"
#include"Printer.h"
#include<vector>
#include<iostream>

int main() {
	// values given in the subject
	Parameters parameters;
	parameters.D = 0.1;
	parameters.L = 1;
	parameters.tIn = 100;
	parameters.tSur = 300;
	parameters.deltaX = 0.05;
	parameters.deltaT = 0.01;
	parameters.numberOfTimePoints = (int)(0.5/parameters.deltaT);
	parameters.numberOfSpacePoints = (int)(parameters.L / parameters.deltaX);

	// creating all the schemes
	AnalyticalSolution analytical = AnalyticalSolution(parameters);
	CrankNicholson crank = CrankNicholson(parameters);
	FTCS ftcs = FTCS(parameters);
	DuFortFrankel dufort = DuFortFrankel(parameters);
	Laasonen laasonen = Laasonen(parameters);
	Richardson richardson = Richardson(parameters);
	vector< PDESolver* > methods{ &analytical, &crank, &laasonen, &dufort, &richardson};
	vector< int > timesteps{10,20,30,40,50};
	Printer printer = Printer(&analytical);

	// going over each scheme and creating its .dat files and gnuplot commands
	for (int i = 0; i<methods.size(); i++){
		methods[i]->solve();
		printer.setPdeSolver(methods[i]);
		for (int j = 0; j < timesteps.size(); j++) {
			printer.createDatFileForT(timesteps[j]);
			if (i > 0) {
				printer.gnuplotForTCompareTo(timesteps[j], &analytical);
			}
		}
		if (i > 0) {
			printer.datFileErrorsComparedTo(timesteps, &analytical);
			printer.gnuplotErrorsCompareTo(&analytical);
		}
	}
}
