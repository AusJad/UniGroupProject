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

class FontLoader
{
public:
	static bool loadFont(std::string filename, Font & toset, std::string name);

private:
	static bool genImgMapping(Font & toset, std::string name);
};

