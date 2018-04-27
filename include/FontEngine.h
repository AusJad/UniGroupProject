#pragma once

#include "Singleton.h"
#include "FontLoader.h"

#define FNT_ENG Singleton<FontEngine>::getInstance()
#define FNT_SIZE_SMALL 0.05f
#define FNT_SIZE_MEDIUM 0.1f
#define FNT_SIZE_LRGE 0.25f

class FontEngine
{
public:
	FontEngine();
	~FontEngine();
	bool RenderChar(char toRender);
	bool hasFont(std::string font);
	bool setActiveFont(std::string font);
	bool loadFont(std::string path, std::string name);
	bool RenderString(std::string torender, float fontsize, unsigned numrow, unsigned maxwidth, float startx, float starty, float depth);
	bool fontHasChar(char totest);

private:
	std::map<std::string, Font> fonts;
	std::string activefont;
};

