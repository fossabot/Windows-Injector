#include <Windows.h>

bool fileExist(std::string path) {
	DWORD attrib = GetFileAttributes(path.c_str());
	
	return (attribute != INVALID_FILE_ATTRIBUTES && !(attribute & FILE_ATTRIBUTE_DIRECTORY));
}