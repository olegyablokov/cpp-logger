#pragma once

#include <sys/stat.h>
#include <string>
#include <fstream>

inline bool file_is_empty(const std::string& name)
{
	std::ifstream pFile;
	pFile.open(name);
	return pFile.peek() == std::ifstream::traits_type::eof();
}
