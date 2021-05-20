//
//  matching.cpp
//  
//
//  Created by Baptiste Claudon on 09.05.20.
//

#include "matching.hpp"
using namespace std;
#include <cmath>
#include <vector>

void Engine_matching::printOut()	{
	for (size_t i(0); i < ninters; ++i)	{
		*outputFile << x[i] << " " << psi[i] << endl;
	}
}

void Engine_matching::printEnergy()	{
	*outputFile_energy << E << endl;
}

Engine_matching::Engine_matching(ConfigFile configFile)
:	Engine(configFile)	{
	outputFile = new ofstream(configFile.get<string>("output","output.out").c_str());
	outputFile_energy = new ofstream(configFile.get<string>("output_energy","output_energy.out").c_str());
	dE = configFile.get<double>("dE");
	E = configFile.get<double>("E0");
	tolerance = configFile.get<double>("tolerance");
	nsteps_max = configFile.get<unsigned int>("nsteps_max");
	ninters = configFile.get<size_t>("ninters");
	intersection_criterion = configFile.get<double>("intersection_criterion");
	tolerance = configFile.get<double>("tolerance");
	dx = 2.0/ninters;
	for (size_t i(0); i < ninters+1; ++i)	{
		x.push_back(-1. + dx*i);
	}
	psi_left = vector<double>(ninters+1,0.0);
	psi_right = vector<double>(ninters+1,0.0);
	psi = vector<double>(ninters+1,0.);
	xm = size_t((configFile.get<double>("x_match")+1.0)/2.*ninters);
}

void Engine_matching::run()	{
	int last_diverge(-1);
	int diverge(0);
	vector<double> psi_temp_left;
	vector<double> psi_temp_right;
	double delta;
	double last_delta;
	double residual(10000.0);
	unsigned int nsteps(0);
	do	{
		//psi_temp_left = psi_left;
		//psi_temp_right = psi_right;
		solve();
		delta = derivative_diff();
		if (delta > 0)	{
			diverge = 1;
		} else {
			diverge = -1;
		}
		if (diverge*last_diverge < 0)	{
			dE *= -0.5;
		} else if (abs(delta) > abs(last_delta))	{
			E = E - dE;
			dE *= -1.;
		}
		E += dE;
		last_diverge = diverge;
		last_delta = delta;
		residual = abs(dE);
		++nsteps;
		printEnergy();
	} while ((residual > tolerance) and (nsteps < nsteps_max));
	for (size_t i(0); i < xm; ++i)	{
		psi[i] = psi_left[i];
	}
	for (size_t i(xm); i < psi.size(); ++i)	{
		psi[i] = psi_right[i];
	}
	normalize_psi();
	printOut();
}

void Engine_matching::solve_left()	{
	psi_left[0] = 0.;
	psi_left[1] = 0.01;
	for (size_t i(2); i<ninters+1; ++i)	{
		psi_left[i] = 2*psi_left[i-1] - psi_left[i-2] - 2*dx*dx*(E-V(x[i-1]))*psi_left[i-1];
	}
}

void Engine_matching::solve_right()	{
	psi_right[ninters] = 0.;
	psi_right[ninters-1] = 0.01;
	//for (size_t i(ninters-2); i>=0; --i)	{
	size_t i = ninters-2;
	do	{
		psi_right[i] = 2*psi_right[i+1] - psi_right[i+2] - 2*dx*dx*(E-V(x[i+1]))*psi_right[i+1];
		i = i-1;
	} while (i > 0);
	psi_right[0] = 2*psi_right[1] - psi_right[2] - 2*dx*dx*(E-V(x[1]))*psi_right[1];
}

double Engine_matching::V(const double& x)	{
	/*double K(100.);
	return K*x*x/2.0;*/ // Harmonic oscillator
	if (x>-1)	{
		double epsilon(10.);
		double sigma(0.2);
		double safety_delta(0.);
		return 4*epsilon*pow(sigma,6)*(pow(sigma,6)/pow(x+2+safety_delta,12) - pow(1/(x+2+safety_delta),6));
	} else return 1e10;
}

/*
size_t Engine_matching::find_intersections()	{
	rescale_wave_functions();
	for (size_t i(0); i<ninters; ++i)	{
		if (abs(psi_left[i]-psi_right[i]) < intersection_criterion)	{
			cout << "Intersection : " << x[i] << endl;
			return i;
		}
	}
	cout << "Wave functions do not intersect..." << endl;
	return 0.;
} */

double Engine_matching::derivative_diff()	{
	rescale_wave_functions();
	double dpsiL = (psi_left[xm+1] - psi_left[xm-1])/2./dx;
	double dpsiR = (psi_right[xm+1] - psi_right[xm-1])/2./dx;
	return dpsiR-dpsiL;
}

void Engine_matching::normalize_psi()	{
	double prob(0.0);
	for (size_t i(0); i<psi.size()-1; ++i)	{
		prob += 0.5*dx*(psi[i]*psi[i]+psi[i+1]*psi[i+1]);
	}
	for (size_t i(0); i<psi.size(); ++i)	{
		psi[i] = psi[i]/sqrt(prob);
	}
}

void Engine_matching::solve()	{
	solve_left();
	solve_right();
}

void Engine_matching::rescale_wave_functions()	{
	double C(psi_right[xm]/psi_left[xm]);
	for (size_t i(0); i < psi_left.size(); ++i)	{
		psi_left[i] *= C;
	}
}
