//
//  shooting.hpp
//  
//
//  Created by Baptiste Claudon on 09.05.20.
//

#ifndef shooting_hpp
#define shooting_hpp

#include <stdio.h>
#include "Engine.hpp"
#include "ConfigFile.h"
#include <vector>

class Engine_shooting : public Engine	{
protected:
	unsigned nsteps_max;
	double dE;
	double E0;
	double tolerance;
	size_t ninters;
	std::vector<double> x;
	double dx;
	double divergence_criterion;
	double V0;
	double V_infinite_wells(const double& x);
	std::vector<double> psi;
	std::ofstream *outputFile_energy;
	
public:
	void printOut();
	void printEnergy(double E);
	void run();
	void look_for_even();
	void look_for_odd();
	void normalize_psi();
	Engine_shooting(ConfigFile configFile);
};

#endif /* shooting_hpp */
