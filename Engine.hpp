//
//  Engine.hpp
//  
//
//  Created by Baptiste Claudon on 09.05.20.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <stdio.h>
#include <iostream>
#include "ConfigFile.h"

class Engine	{
protected:
	std::ofstream *outputFile;
	virtual void printOut() = 0;
	
public:
	Engine(ConfigFile configFile);
	virtual void run() = 0;
		   
	virtual ~Engine();
};

#endif /* Engine_hpp */
