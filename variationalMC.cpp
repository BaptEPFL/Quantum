//
//  variationalMC.cpp
//  
//
//  Created by Baptiste Claudon on 18.05.20.
//

#include "variationalMC.hpp"
#include "ConfigFile.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <random>
using namespace std;

void Engine_variationalMC::run()	{
	unsigned int nsteps(0);
	double residu(1.e9);
	double residu_tmp(residu);
	double energy(Energy(psi));
	double old_energy(energy);
	vector<double> psi_tmp;
	unsigned int improvement_count(0);
	while ((nsteps < nmax) and (residu > tolerance))	{
		psi_tmp = psi;
		for (size_t i(0); i < 100; ++i)	MC_variation(psi_tmp);
		energy = Energy(psi_tmp);
		if (energy < old_energy)	{
			psi = psi_tmp;
			old_energy = energy;
			normalise();
			++improvement_count;
		}
		//residu_tmp = max(residu_tmp,abs(energy - old_energy));
		if (nsteps % 100 == 0)	{
			residu = residu_tmp;
			residu_tmp = tolerance+1.0;
			normalise();
		}
		if (nsteps % 10000 == 0)	{
			cout << "Improvement between : " << nsteps-100 << " and " << nsteps << " : " << improvement_count << endl;
			improvement_count = 0;
		}
		++nsteps;
	}
	normalise();
	printOut();
}

Engine_variationalMC::Engine_variationalMC(ConfigFile configFile)
: Engine(configFile)	{
	outputFile = new ofstream(configFile.get<string>("output","output.out").c_str());
	tolerance = configFile.get<double>("tolerance");
	nmax = configFile.get<unsigned int>("nsteps_max");
	nattempts = configFile.get<unsigned int>("nattempts");
	npoints = configFile.get<size_t>("ninters") + 1;
	dx = 2.0/(npoints-1);
	for (size_t i(0); i < npoints; ++i)	{
		x.push_back(-1. + dx*i);
	}
	psi = vector<double>(npoints,0.1);
	size_t sigma(0.25*npoints);
	bool keep_simulating = configFile.get<bool>("continue");
	if (keep_simulating)	{
		ifstream infile("outputcopy.txt");
		double x_val;
		double psi_val;
		size_t i(0);
		while (infile >> x_val >> psi_val)	{
			cout << x_val << " ";
			cout << psi_val << endl;
			psi[i] = psi_val;
			++i;
		}
		cout << "---------------------" << endl;
	} else	{
		for (size_t i(sigma); i < npoints/2+sigma; ++i)	{
			psi[i] = 1.;
		}
	}
	normalise();
	diagH = vector<double>(npoints,0.);
	lowerH = vector<double>(npoints-1,0.);
	for (size_t i(0); i < npoints; ++i)	{
		diagH[i] = 1./dx/dx+V(x[i]);
	}
	for (size_t i(0); i < npoints-1; ++i)	{
		lowerH[i] = -1./2.0/dx/dx;
	}
	upperH = lowerH;
	dphi = configFile.get<double>("dphi");
}

void Engine_variationalMC::printOut()	{
	for (size_t i(0); i < npoints; ++i)	{
		*outputFile << x[i] << " " << psi[i] << endl;
	}
}

double Engine_variationalMC::norm2()	{
	double sum(0.);
	for (size_t i(0); i<psi.size()-2; ++i)	{
		sum += 1./6.0*(psi[i]*psi[i]+4*psi[i+1]*psi[i+1]+psi[i+2]*psi[i+2]);
	}
	return sum*dx;
}

double Engine_variationalMC::norm()	{
	return sqrt(norm2());
}

double Engine_variationalMC::Energy(const vector<double>& psi)	{
	size_t n(psi.size());
	vector<double> psi_tmp(n);
	double energy(0.);
	psi_tmp[0] = diagH[0]*psi[0]+upperH[0]*psi[1];
	for (size_t i(1); i<n-1; ++i)	{
		psi_tmp[i] = lowerH[i-1]*psi[i-1]+diagH[i]*psi[i]+upperH[i]*psi[i+1];
	}
	psi_tmp[n-1] = lowerH[n-2]*psi[n-2]+diagH[n-1]*psi[n-1];
	for (size_t i(0); i<n-1; ++i)	{
		energy += 0.5*(psi[i]*psi_tmp[i]+psi[i+1]*psi_tmp[i+1]);
	}
	return dx*energy/norm2();
}

size_t Engine_variationalMC::get_random(const size_t& npoints)	{
	static default_random_engine generator;
	normal_distribution<double> distribution(0.5,0.5);
	size_t random(npoints+1);
	while ((random < 0) or (npoints-1 < random))	{
		random = (size_t)(distribution(generator)*npoints);
	}
	/*
	if (random == 0)	{
		return npoints/2;
	} else if (random == npoints - 1){
		return npoints/2;
	} else	{
		return rand()%npoints;
	}
	 */
	return random;
}

double Engine_variationalMC::get_random(const double& dphi)	{
	return (pow(-1,rand()%2))*(double)rand()/(double)RAND_MAX*dphi;
	//return pow(-1,rand()%2)*dphi;
}

void Engine_variationalMC::MC_variation(std::vector<double>& psi_tmp)	{
	double psi_max(abs(psi_tmp[npoints/2]));
	size_t random_point;
	for (unsigned int i(0); i < nattempts; ++i)	{
		random_point = get_random(npoints);
		if (double(rand()/RAND_MAX) < abs(psi[random_point]/psi_max))	{
			break;
		}
		/*
		if (abs(psi[random_point]) > psi_max)	{
			psi_max = psi[random_point];
		}*/
	}
	double random_dphi(get_random(dphi));
	psi_tmp[random_point] += random_dphi;
}

void Engine_variationalMC::normalise()	{
	double normalisation_constant(norm());
	for (size_t i(0); i < psi.size(); ++i)	{
		psi[i] *= 1./normalisation_constant;
	}
}

double Engine_variationalMC::V(const double& x)	{
	return 100.*x*x/2.;
}
