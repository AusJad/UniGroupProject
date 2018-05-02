#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "fileNameReader.h"
#include <vector>
#include "Maths.h"
#include "Identifiers.h"

using namespace std;

typedef struct
{
	// bad design but this was quick and easy to implement will change later
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
	save(string fn);
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

	vector<goData> getData() const;

private:
	/// The entire path of the save file.
	string savePath;
	/// The name of the save file.
	string filename;
	/// The directory that the save file is held in.
	const char* directory = "./saveData/";
	/// The type of file for the save file.
	string fileType = ".txt";
	
	vector<goData> d;

	/**
	* @brief Opens file and loads variables into the member variables of the class
	*
	* @param fp - The file path
	*/
	void openFile(string fp);
};

