#pragma once
#include <string>
#include <stack>

// Headers for directory searching
#include "dirent/dirent.h"
#include <algorithm>
#include <sys/types.h>

/**
* @class fileNameReader
*
* @brief A class to read a directory and return a vector of strings containing all files within given parameters.
*
* @author Matthew MacLennan.
* @data 19/04/2018
* @version 1.0
*/
class fileNameReader
{
public:
	/**
	* @brief Get the file names in a vector of strings.
	*
	* @return Vector<string> - A vector of strings of file names.
	*/
	static bool getFileNames(const char* dirPath, const std::string& fileType);

	static bool hasFiles();

	static std::string getFile();
private:
	/**
	* @brief Check the files in the directory for the correct type.
	*
	* @param s(string) - The name of the file.
	* @param fileType(string) - The type of file allowed.
	*
	* @return bool - If the file is the correct type.
	*/
	static bool fileTypeCheck(const std::string& s, const std::string& fileType);
	
	static std::stack<std::string> files;
};

