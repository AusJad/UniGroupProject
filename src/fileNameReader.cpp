#include "fileNameReader.h"
// Function to check that the filename has the correct extension.
bool fileNameReader::fileTypeCheck(const std::string& s, const std::string& fileType)
{
	return (s.size() >= fileType.size()) && equal(fileType.rbegin(), fileType.rend(), s.rbegin());
}

// Function to open the MetData folder and read all the .csv files in the folder and save the filenames.
std::vector<std::string> fileNameReader::getFileNames(const char* dirPath, const std::string& fileType)
{
	DIR* directptr; // Pointer to directory.
	struct dirent *epdf; // Temp storage to save raw data from directory.
	std::vector<std::string> fileNames; // End vector with all filenames.
	std::string tmp; // Temp string to transfer data to fileNames.

	// Open directory
	directptr = opendir(dirPath);

	if (directptr != NULL) // Check if directory has contents
	{
		std::cout << "Directory Opened..." << std::endl;

		while ((epdf = readdir(directptr))) // Read in all file names
		{
			if (fileTypeCheck(epdf->d_name, fileType)) // Check files are right type
			{
				tmp = dirPath; // Add directory address to string
				tmp.append(std::string(epdf->d_name)); // Add file name to end of string
				fileNames.push_back(tmp); // Add file path to vector
			}
		}
	}

	// Output to annouce what files were found
	std::cout << std::endl << "The following files were found..." << std::endl;

	for (int i = 0; i < fileNames.size(); i++)
	{
		std::cout << "File " << i + 1 << ": " << fileNames[i] << std::endl;
	}

	return fileNames;
}