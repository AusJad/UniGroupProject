#pragma once

#include <map>
#include "TextureManager.h"

/**
* @class Font
* @brief Provides an interface for creating fonts.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
class Font
{
public:
	Font();
	~Font();

	/**
	* @brief Set method for image width.
	*
	* @param imgwidth - The new image width.
	*/
	void setImgWidth(unsigned imgwidth);

	/**
	* @brief Set method for image height.
	*
	* @param imgheight - The new image height.
	*/
	void setImgHeight(unsigned imgheight);

	/**
	* @brief Set method for character width.
	*
	* @param charwidth - The new character width.
	*/
	void setCharWidth(unsigned charwidth);

	/**
	* @brief Set method for the character height.
	*
	* @param charheight - The new character height.
	*/
	void setCharHeight(unsigned charheight);

	/**
	* @brief Set method for the start character.
	*
	* @param startchar - The new start character.
	*/
	void setStartChar(unsigned startchar);

	/**
	* @brief A method to add character offset mapping data.
	*
	* @param charcter - The character the offset data is for.
	* @param offset - The offset.
	*/
	void addCharOffsetMapping(char character, int offset);

	/**
	* @brief Set the texture of the font.
	*
	* @param texture - The path to the texture data.
	*/
	void setTexture(std::string texture);

	/**
	* @brief Get the image width.
	*
	* @return unsigned The image width.
	*/
	unsigned getImgWidth();

	/**
	* @brief Get the image height.
	*
	* @return unsigned The image height.
	*/
	unsigned getImgHeight();

	/**
	* @brief Get the character width.
	*
	* @return unsigned The character width.
	*/
	unsigned getCharWidth();

	/**
	* @brief Get the character height.
	*
	* @return unsigned The character height.
	*/
	unsigned getCharHeight();

	/**
	* @brief Get the start character.
	*
	* @return unsigned The start character.
	*/
	unsigned getStartChar();

	/**
	* @brief Get the texture path.
	*
	* @return string - The texture path.
	*/
	const std::string & getTex();

	/**
	* @brief Get the character offsett data.
	* 
	* @param key - The character the offset data is about.
	*
	* @return int - The offset.
	*/
	int getCharOffset(char key);

	/**
	* @brief A method to bind the character to the image.
	*
	* @param key - The character.
	* @param id - The image id.
	*/
	void bindCharImg(char key, std::string id);

	/**
	* @brief A method to use the character.
	*
	* @param touse - The character.
	*
	* @return bool - If the character was used.
	*/
	bool useChar(char touse);

	/**
	* @brief A method to test if a font has a character.
	*
	* @param totest - The character.
	*
	* @return bool - If the font has the character.
	*/
	bool hasChar(char totest);

private:
	/// The width of the image.
	unsigned imgwidth;
	/// The height of the image.
	unsigned imgheight;
	/// The character width.
	unsigned charwidth;
	/// The character height.
	unsigned charheight;
	/// The first character.
	unsigned startchar;
	/// The offsets for all the charaters.
	std::map<char, int> fontoffsets;
	/// The mapping data for all the chracters.
	std::map<char, std::string> fontmappings;
	/// The path to the texture.
	std::string texture;
};

