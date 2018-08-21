#pragma once

#include <sys/stat.h>
#include <string>

#ifdef __linux__
#define REMOVE_FILE_CMD "rm"
#elif _WIN32
#define REMOVE_FILE_CMD "del"
#endif

inline bool file_exists(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
