#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "fileNameReader.h"
#include <vector>
#include "Maths.h"
#include "Identifiers.h"

// This struct was created as a quick and easy fix for better access to the stored game object data.
typedef struct
{
	unsigned sceneno;
	int state;
	vec3 position, targetPos, targetLook;
	Identifiers id;
}goData;

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
	* @brief The save game call function for scene number.
	* 
	* @param sceneno - The scene number being saved.
	*/
	void saveGame(int sceneno);

	/**
	* @brief The save game call function for game object.
	*
	* @param state - The game objects state.
	* @param pos - The position of the game object.
	* @param target - The target position of the game object.
	* @param targetlook - The target look at position of the game object.
	* @param id - The identifier of the object.
	*/
	void saveGame(int state, vec3 pos, vec3 target, vec3 targetlook, Identifiers id);

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
	std::vector<goData> getData() const;

private:
	/// The entire path of the save file.
	std::string savePath;
	/// The name of the save file.
	std::string filename;
	/// The directory that the save file is held in.
	const char* directory = "./saveData/";
	/// The type of file for the save file.
	std::string fileType = ".txt";
	/// All objects and their data.
	std::vector<goData> d;
	/// Temp string for moving scene number between two saveGame() functions for efficiency reasons.
	std::string tmpsceneno;
	/**
	* @brief Opens file and loads variables into the member variables of the class
	*
	* @param fp - The file path
	*/
	void openFile();
};

