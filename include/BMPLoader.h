#pragma once

#include "ImageLoader.h"

/**
* @class BMPLoader
* @brief Class for loading and saving BMP data.
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class BMPLoader : public ImageLoader
{
public:
	BMPLoader();
	~BMPLoader();

	/**
	* @brief Load in a BMP file.
	*
	* @param filename - The filename.
	*
	* @return bool - If file was loaded.
	*/
	bool loadFile(std::string filename);

	/**
	* @brief Get the data from the BMP file.
	*
	* @return unsigned char* - Pointer to the data.
	*/
	unsigned char* getData() const;

	/**
	* @brief Get the number of bits in the bmp file.
	*
	* @return unsigned - The number of bits in the file.
	*/
	unsigned getBits() const;

	/**
	* @brief Get the width of the file.
	*
	* @return unsigned - The width.
	*/
	unsigned getWidth() const;

	/**
	* @brief Get the height of the file.
	*
	* @return unsigned - The height.
	*/
	unsigned getHeight() const;

	/**
	* @brief Clear the data.
	*/
	void clear(); 

	/**
	* @brief Get the data size of the file.
	*
	* @return unsigned - The data size of the file.
	*/
	unsigned getDataSize();
private:
	/// The data of the BMP.
	unsigned char * data; 
	/// The width of the BMP.
	unsigned width;
	/// The height of the BMP.
	unsigned height;
	/// The amount of bits in the BMP.
	unsigned bits;
	/// The size of the BMP.
	unsigned size;
};
