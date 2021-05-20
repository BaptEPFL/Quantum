//
//  matching.hpp
//  
//
//  Created by Baptiste Claudon on 09.05.20.
//

#ifndef matching_hpp
#define matching_hpp

#include <stdio.h>
#include "Engine.hpp"
#include "ConfigFile.h"
#include <vector>

class Engine_matching : public Engine	{
protected:
	std::ofstream *outputFile_energy;
	void printOut();
	void solve_left();
	void solve_right();
	void solve();
	double dx;
	std::vector<double> x;
	double dE;
	double tolerance;
	unsigned int nsteps_max;
	size_t ninters;
	std::vector<double> psi_left;
	std::vector<double> psi_right;
	double E;
//	size_t find_intersections();
	double intersection_criterion;
	void rescale_wave_functions();
	double derivative_diff();
	void normalize_psi();
	std::vector<double> psi;
	size_t xm;
	
public:
	Engine_matching(ConfigFile configFile);
	void run();
	double V(const double& x);
	void printEnergy();
};

#endif /* matching_hpp */
