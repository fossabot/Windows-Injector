#include "Injector.hpp"
#include "Functions.hpp"

#include <iostream>

int main(int argc, char** argv) {
	Injector injector;

	std::string exeName = "";
	std::string dllName = "";
	bool delay = false;
	bool res = false;
	int delayTime = 0;
	int injectionType = 0;

	printf("Injector\n\n");

	if (argc == 1) {
		printf("Process name with extension: ");
		std::getline(std::cin, exeName);

		printf("Dll name with extension: ");
		std::getline(std::cin, dllName);
		
		printf("Injection type: ");
		std::cin >> injectionType;

		printf("Delay time: ");
		std::cin >> delayTime;

		if (delayTime > 0) delay = true;
	}
	else if (argc == 3) {
		exeName = argv[1];
		dllName = argv[2];
		injectionType = 0;
	}
	else if (argc == 4) {
		exeName = argv[1];
		dllName = argv[2];
		delay = true;
		delayTime = std::stoi(argv[3]);
		injectionType = 0;
	}
	else if (argc == 5) {
		exeName = argv[1];
		dllName = argv[2];

		delay = true;
		delayTime = std::stoi(argv[3]);

		injectionType = std::stoi(argv[4]);
	}
	else {
		printf("Usage: Injector.exe <processName.exe> <dllName.dll> [<delayTIme>(in ms) <injectionType>]\n");
		return 0;
	}

	size_t exeFind = exeName.find(".exe");
	size_t dllFind = dllName.find(".dll");

	if (exeFind == -1 || exeFind == 0) {
		printf("\nYou need to specify exe name with the extension (*.exe)!\n");
		std::cin.get();
		return -1;
	}
	else if (dllFind == -1 || dllFind == 0) {
		printf("\nYou need to specify dll name with the extension (*.dll)!\n");
		std::cin.get();
		return -2;
	}

	if (!fileExist(dllName)) {
		printf("\nSpecified .dll file does not exist!\n");
		std::cin.get();
		return -3;
	}

	injector.setData(exeName, dllName, delay, delayTime, injectionType);
	res = injector.Inject();

	return res;
}