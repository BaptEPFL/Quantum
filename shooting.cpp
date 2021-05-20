//
//  shooting.cpp
//  
//
//  Created by Baptiste Claudon on 09.05.20.
//

#include "shooting.hpp"
#include "ConfigFile.h"
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include "potentials.hpp"

using namespace std;

void Engine_shooting::printOut()	{
	for (size_t i(0); i < ninters; ++i)	{
		*outputFile << x[i] << " " << psi[i] << endl;
	}
}

void Engine_shooting::printEnergy(double E)	{
	*outputFile_energy << E << endl;
}

void Engine_shooting::run()	{
	int last_diverge(0);
	int diverge(0);
	double residual(100.0);
	unsigned int nsteps(0);
	double E=E0;
	size_t temp(0);
	do	{
		look_for_even();
		for (size_t i(1); i<ninters; ++i)	{
			psi[i+1] = 2.*psi[i] - psi[i-1] - 2*(E-V_infinite_wells(x[i]))*dx*dx*psi[i];
			if (psi[i+1] > divergence_criterion)	{
				temp = i+1;
				break;
			}
			if (i==ninters-1) temp = ninters;
		}
		if (psi[temp] > 0)	{
			diverge = 1;
		} else {
			diverge = -1;
		}
		if (diverge*last_diverge < 0)	{
			dE *= -0.5;
		}
		E += dE;
		last_diverge = diverge;
		residual = abs(dE);
		++nsteps;
	} while ((residual > tolerance) and (nsteps < nsteps_max));
	normalize_psi();
	printOut();
	printEnergy(E);
}

void Engine_shooting::look_for_even()	{
	psi[0] = 1.;
	psi[1] = 1.;
}

void Engine_shooting::look_for_odd()	{
	psi[0] = 0.;
	psi[1] = 0.001;
}

Engine_shooting::Engine_shooting(ConfigFile configFile)
: Engine(configFile)	{
	outputFile = new ofstream(configFile.get<string>("output","output.out").c_str());
	outputFile_energy = new ofstream(configFile.get<string>("output_energy","output_energy.out").c_str());
	divergence_criterion = configFile.get<double>("divergence_criterion");
	V0 = configFile.get<double>("V0");
	dE = configFile.get<double>("dE");
	E0 = configFile.get<double>("E0");
	tolerance = configFile.get<double>("tolerance");
	nsteps_max = configFile.get<unsigned int>("nsteps_max");
	ninters = configFile.get<size_t>("ninters");
	dx = 1.0/ninters;
	double eps(0.); // Useful in case we want to calculate the wave functions outside the interval
	for (size_t i(0); i < ninters+1; ++i)	{
		x.push_back((dx+eps)*i);
	}
	psi = vector<double>(ninters+2,0.0);
}

double Engine_shooting::V_infinite_wells(const double& x)	{
	if (abs(x) <= 1)	{
		return 0.;
	} else 	{
		return V0;
	}
}

void Engine_shooting::normalize_psi()	{
	double prob(0.0);
	for (size_t i(0); i<psi.size()-1; ++i)	{
		prob += 0.5*dx*(psi[i]*psi[i]+psi[i+1]*psi[i+1]);
	}
	for (size_t i(0); i<psi.size(); ++i)	{
		psi[i] = sqrt(2)*psi[i]/2./sqrt(prob);
	}
}
