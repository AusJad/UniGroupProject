#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "fileNameReader.h"
#include <vector>
#include "Maths.h"
#include "Identifiers.h"

/**
* @class save
* @brief A class to store relevant SceneManager, Scene and GameObject data in a external file and to load that data back in.
*
* @author Matthew MacLennan
* @version 1.0
* @date 2/05/2018
*/
class save
{
public:
	save();
	save(std::string fn);
	~save();

	/**
	* @brief A method to output a string to a file.
	*
	* @parma data - The data to be saved.
	*/
	void saveGame(std::vector<std::string> data);

	/**
	* @brief Check if the file requested can be found and if so load it in.
	*
	* @return bool - If the file was loaded in.
	*/
	bool loadFile();

	/**
	* @brief Get method for the data.
	*
	* @return vector<goData> - Vector of GameObject data points.
	*/
	std::vector<std::string> & getData();

private:
	/// The entire path of the save file.
	std::string savePath;
	/// The name of the save file.
	std::string filename;
	/// The directory that the save file is held in.
	const char* directory = "./saveData/";
	/// The type of file for the save file.
	std::string fileType = ".save";
	//^ make ourselves look a little cooler with a format the OS won't recognise

	/// All objects and their data.
	std::vector<std::string> d;
	/// Temp string for moving scene number between two saveGame() functions for efficiency reasons.
};

