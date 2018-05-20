#include "fileNameReader.h"

std::stack<std::string> fileNameReader::files;

// Function to check that the filename has the correct extension.
bool fileNameReader::fileTypeCheck(const std::string& s, const std::string& fileType)
{
	return (s.size() >= fileType.size()) && equal(fileType.rbegin(), fileType.rend(), s.rbegin());
}

// Function to open the MetData folder and read all the .csv files in the folder and save the filenames.
bool fileNameReader::getFileNames(const char* dirPath, const std::string& fileType)
{
	while(!files.empty()) files.pop();
	DIR* directptr; // Pointer to directory.
	struct dirent *epdf; // Temp storage to save raw data from directory.
	std::string tmp; // Temp string to transfer data to fileNames.

	// Open directory
	directptr = opendir(dirPath);

	if (directptr != NULL) // Check if directory has contents
	{
		while ((epdf = readdir(directptr))) // Read in all file names
		{
			if (fileTypeCheck(epdf->d_name, fileType)) // Check files are right type
			{
				tmp =  std::string(epdf->d_name); // Add file name to end of string
				files.push(tmp); // Add file path to vector
			}
		}

		return true;
	}

	return false;
}


bool fileNameReader::hasFiles() {
	return files.empty() == false;
}

std::string fileNameReader::getFile() {
	std::string tmp = files.top();
	files.pop();

	return tmp;
}