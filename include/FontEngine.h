#pragma once

#include "Singleton.h"
#include "FontLoader.h"
#include "Identifiers.h"
#include "MessagingBus.h"

#define FNT_ENG Singleton<FontEngine>::getInstance()
#define FNT_SIZE_SMALL 0.05f
#define FNT_SIZE_MEDIUM 0.1f
#define FNT_SIZE_LRGE 0.25f

#define FNT_SIZE_SMALL_O 19
#define FNT_SIZE_MEDIUM_O 26
#define FNT_SIZE_LRGE_O 32


/**
* @class FontEngine
* @brief Provides an interface for creating fonts.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
class FontEngine
{
public:
	FontEngine();
	~FontEngine();
	
	/**
	* @brief A method to render a character.
	*
	* @param toRender - The character to render in the font.
	*
	* @return bool - If the character was rendered.
	*/
	bool RenderChar(char toRender);

	/**
	* @brief A method to find out if a font object exists.
	*
	* @param font - The name of the font to find.
	* 
	* @return bool - If the font exists.
	*/
	bool hasFont(std::string font);

	/**
	* @brief A method to set the active font.
	*
	* @param font - The name of the font to be set to active.
	*
	* @return bool - If the font was set to active.
	*/
	bool setActiveFont(std::string font);

	/**
	* @brief A method to load in a font.
	*
	* @param path - The path of the font data.
	* @param name - The name of the font.
	*
	* @return bool - If the font was loaded in.
	*/
	bool loadFont(std::string path, std::string name);

	/**
	* @brief Render a string in the font.
	*
	* @param torender - The string.
	* @param fontsize - The size of the font.
	* @param numrow - The row number the string should appear on in the console.
	* @param maxwidth - The max width of the console.
	* @param startx - The starting x position of the text.
	* @param starty - The starting y position of the text.
	* @param depth - The depth of the text.
	*
	* @return bool - If the string was rendered.
	*/
	bool RenderString(std::string torender, float fontsize, unsigned numrow, unsigned maxwidth, float startx, float starty, float depth);

	void RenderStringO(std::string torender, float fontsize, float startx, float starty);

	/**
	* @brief Find if the font has a specific character defined.
	*
	* @param totest - The char being looked for.
	* 
	* @return bool - The output of the test.
	*/
	bool fontHasChar(char totest);

	/**
	* @brief Update method for the text.
	*/
	void update();

	float precomputeStringWidth(std::string torender, float fontsize);

private:
	/// A map of fonts.
	std::map<std::string, Font> fonts;
	/// The active font name.
	std::string activefont;
	/// Identifier for the engine.
	Identifiers id;
};

