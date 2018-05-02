#include "fileNameReader.h"
// Function to check that the filename has the correct extension.
bool fileNameReader::fileTypeCheck(const string& s, const string& fileType)
{
	return (s.size() >= fileType.size()) && equal(fileType.rbegin(), fileType.rend(), s.rbegin());
}

// Function to open the MetData folder and read all the .csv files in the folder and save the filenames.
vector<string> fileNameReader::getFileNames(const char* dirPath, const string& fileType)
{
	DIR* directptr; // Pointer to directory.
	struct dirent *epdf; // Temp storage to save raw data from directory.
	vector<string> fileNames; // End vector with all filenames.
	string tmp; // Temp string to transfer data to fileNames.

	// Open directory
	directptr = opendir(dirPath);

	if (directptr != NULL) // Check if directory has contents
	{
		cout << "Directory Opened..." << endl;

		while ((epdf = readdir(directptr))) // Read in all file names
		{
			if (fileTypeCheck(epdf->d_name, fileType)) // Check files are right type
			{
				tmp = dirPath; // Add directory address to string
				tmp.append(string(epdf->d_name)); // Add file name to end of string
				fileNames.push_back(tmp); // Add file path to vector
			}
		}
	}

	// Output to annouce what files were found
	cout << endl << "The following files were found..." << endl;

	for (int i = 0; i < fileNames.size(); i++)
	{
		cout << "File " << i + 1 << ": " << fileNames[i] << endl;
	}

	return fileNames;
}