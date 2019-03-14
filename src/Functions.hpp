#include <Windows.h>

bool fileExist(std::string path) {
	DWORD attrib = GetFileAttributes(path.c_str());
	
	return (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY));
}