//
//  Engine.cpp
//  
//
//  Created by Baptiste Claudon on 09.05.20.
//

#include "Engine.hpp"
#include <iostream>
#include <iomanip>
#include "ConfigFile.h"

using namespace std;

Engine::Engine(ConfigFile configFile)	{}

Engine::~Engine()   {
	outputFile->close();
	delete outputFile;
}
