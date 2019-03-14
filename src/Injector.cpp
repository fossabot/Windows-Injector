#include "Injector.hpp"

Injector::Injector() {
	exeName = "";
	dllName = "";
	delay = false;
	delayTime = 0;
	injectionType = 0;
}
Injector::~Injector() {}

void Injector::setData(std::string exeName, std::string dllName, bool delay, int delayTime, int injectionType) {
	this->exeName = exeName;
	this->dllName = dllName;
	this->delay = delay;
	this->delayTime = delayTime;
	this->injectionType = injectionType;
}

bool Injector::Inject() {
	if (injectionType == 0) return StandardInjector();
	else return false;
}

bool Injector::StandardInjector() {
	
}