//
//  variationalMC.hpp
//  
//
//  Created by Baptiste Claudon on 18.05.20.
//

#ifndef variationalMC_hpp
#define variationalMC_hpp

#include <stdio.h>
#include "Engine.hpp"
#include "ConfigFile.h"
#include <vector>

class Engine_variationalMC : public Engine	{
protected:
	double tolerance;
	std::vector<double> psi;
	double norm2();
	double norm();
	double V(const double& x);
	std::vector<double> diagH, lowerH, upperH;
	double Energy(const std::vector<double>& psi);
	double dx;
	size_t npoints;
	double dphi;
	size_t get_random(const size_t& npoints);
	double get_random(const double& npoints);
	void MC_variation(std::vector<double>& psi_tmp);
	unsigned int nmax;
	void normalise();
	std::vector<double> x;
	unsigned int nattempts;
	
public:
	void run();
	void printOut();
	Engine_variationalMC(ConfigFile configFile);
};

#endif /* variationalMC_hpp */
