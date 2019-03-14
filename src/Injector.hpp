#pragma once

#include <string>

class Injector {
	std::string exeName;
	std::string dllName;
	
	bool delay;
	
	int delayTime;
	int injectionType;
	
	bool StandardInjector();
	
public:
	Injector();
	~Injector();
	
	void setData(std::string, std::string, bool, int, int);
	
	bool Inject();
};