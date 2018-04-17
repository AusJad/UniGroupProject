#pragma once
#include <string>
#include <string>
#include <fstream>

/**
* @class ImageLoader
* @brief Class for loading in images and getting all data about them
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class ImageLoader
{
public:
	/**
	* @brief Virtual method to load the file.
	*
	* @param filename - The name of the file to be loaded.
	*
	* @return bool - If the file was loaded.
	*/
	virtual bool loadFile(std::string filename) = 0;

	/**
	* @brief Virtual method to get the data.
	*
	* @return unsigned char* - The data.
	*/
	virtual unsigned char* getData() const = 0;

	/**
	* @brief Virtual method to get the number of bits
	*
	* @return unsigned - The number of bits in the image.
	*/
	virtual unsigned getBits() const = 0;

	/**
	* @brief Virtual method to get the width.
	*
	* @return unsigned - The width of the image.
	*/
	virtual unsigned getWidth() const = 0;

	/**
	* @brief Virtual method to get the height.
	*
	* @return unsigned - The height of the image.
	*/
	virtual unsigned getHeight() const = 0;

	/**
	* @brief Virtual method to clear the image object.
	*/
	virtual void clear() = 0;

	/**
	* @brief Virtual method to get the data size
	*
	* @return unsigned - The size of the image.
	*/
	virtual unsigned getDataSize() = 0;
};

