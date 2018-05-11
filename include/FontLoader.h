#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Font.h"

#define IMAGE_WIDTH "IW"
#define IMAGE_HEIGHT "IH"
#define CHAR_WIDTH "CW"
#define CHAR_HEIGHT "CH"
#define START_CHAR "SC"
#define CHAR_BASE_WIDTH "CBW"
#define TEXTURE "T"

/**
* @class FontLoader
* @brief Provides an interface for adding font.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
class FontLoader
{
public:
	/**
	* @brief A method to load the font.
	*
	* @param filename - The file path of the font data.
	* @param toset - The Font object to be set.
	* @param name - The name of the font.
	*
	* @return bool - If the font was set.
	*/
	static bool loadFont(std::string filename, Font & toset, std::string name);

private:
	/**
	* @brief A method to generate the image mapping for the font.
	*
	* @param toset - The font object to be mapped.
	* @param name - The name of the font.
	*
	* @return bool - If the image was mapped.
	*/
	static bool genImgMapping(Font & toset, std::string name);
};

