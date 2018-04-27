#pragma once

#include <map>
#include "TextureManager.h"

class Font
{
public:
	Font();
	~Font();
	void setImgWidth(unsigned imgwidth);
	void setImgHeight(unsigned imgheight);
	void setCharWidth(unsigned charwidth);
	void setCharHeight(unsigned charheight);
	void setStartChar(unsigned startchar);
	void addCharOffsetMapping(char character, int offset);
	void setTexture(std::string texture);
	unsigned getImgWidth();
	unsigned getImgHeight();
	unsigned getCharWidth();
	unsigned getCharHeight();
	unsigned getStartChar();
	const std::string & getTex();
	int getCharOffset(char key);
	void bindCharImg(char key, std::string id);
	bool useChar(char touse);
	bool hasChar(char totest);

private:
	unsigned imgwidth;
	unsigned imgheight;
	unsigned charwidth;
	unsigned charheight;
	unsigned startchar;
	std::map<char, int> fontoffsets;
	std::map<char, std::string> fontmappings;
	std::string texture;
};

