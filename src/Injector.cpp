#include "Injector.hpp"

#include <Windows.h>
#include <TlHelp32.h>

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
	DWORD(WINAPI* llAddr)(LPVOID) = nullptr;
	HMODULE kernel32 = nullptr;
	HANDLE proc = nullptr;
	PROCESSENTRY32 entry;

	char* pAddr = nullptr;
	void* alloc = nullptr;
	char path[260] = { 0 };

	entry.dwSize = sizeof(PROCESSENTRY32);

	proc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!proc) {
		printf("Failed to create process handle!\n");

		CloseHandle(proc);
		return false;
	}

	do {
		if (!strcmp(entry.szExeFile, exeName.c_str())) {
			CloseHandle(proc);

			proc = OpenProcess(PROCESS_ALL_ACCESS, false, entry.th32ProcessID);
			if (!proc) {
				printf("Failed to open process handle!\n");

				CloseHandle(proc);
				return false;
			}

			break;
		}
	} while (Process32Next(proc, &entry));

	GetFullPathName(dllName.c_str(), sizeof(path), path, nullptr);
	pAddr = &path[strlen(path) + 1];

	kernel32 = GetModuleHandle("kernel32.dll");
	if (!kernel32) {
		printf("Failed to get kernel32 handle!\n");

		CloseHandle(proc);
		return false;
	}

	llAddr = (DWORD(WINAPI*)(LPVOID))GetProcAddress(kernel32, "LoadLibraryA");
	alloc = VirtualAllocEx(proc, nullptr, strlen(path), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	
	WriteProcessMemory(proc, alloc, path, pAddr - &path[1], nullptr);
	CreateRemoteThread(proc, nullptr, 0, llAddr, alloc, 0, nullptr);

	CloseHandle(proc);
	return true;
}