//
//  main.cpp
//  
//
//  Created by Baptiste Claudon on 09.05.20.
//

#include <stdio.h>
#include <time.h>
#include <string>
#include <cmath>
#include "Engine.hpp"
#include "shooting.hpp"
#include "matching.hpp"
#include "variationalMC.hpp"
#include "ConfigFile.h"
#include "potentials.hpp"

using namespace std;

int main(int argc, char* argv[])	{
	srand (time(NULL));
	string inputPath("configuration.in");
	if (argc > 1)   {
		inputPath = argv[1];
	}
	/*
	bool keep_simulating = configFile.get<bool>("continue");
	if (keep_simulating)	{
		CopyFile("output.out", "copy.txt", false);
	}
	 */
	ConfigFile configFile(inputPath);
	for (int i(2); i<argc; ++i)  {
		configFile.process(argv[i]);
	}
	string simulation(configFile.get<string>("simulation"));
	Engine* engine;
	if (simulation == "shooting")	{
		engine = new Engine_shooting(configFile);
	} else if (simulation == "matching")	{
		engine = new Engine_matching(configFile);
	} else if (simulation == "variational")	{
		engine = new Engine_variationalMC(configFile);
	} else	{
		engine = new Engine_shooting(configFile);
		delete engine;
		cout << "No simulation" << endl;
	}
	engine->run();
	delete engine;
	cout << "End of simulation" << endl;
	return 0;
}



