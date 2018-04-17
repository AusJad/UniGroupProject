#pragma once

#include "ImageLoader.h"

/**
* @class TGALoader
* @brief Class for loading TGAs
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class TGALoader : public ImageLoader
{
public:
	TGALoader();
	~TGALoader();
	
	/**
	* @brief Load the file.
	*
	* @param filename - The file name.
	*
	* @return bool - If the file loaded.
	*/
	bool loadFile(std::string filename);

	/**
	* @brief Get the data.
	*
	* @return unsigned char* - The image data.
	*/
	unsigned char* getData() const;

	/**
	* @brief Get the number of bits.
	*
	* @return unsigned - The number of bits.
	*/
	unsigned getBits() const;

	/**
	* @brief Get the width.
	*
	* @return unsigned - The width.
	*/
	unsigned getWidth() const;

	/**
	* @brief Get the height.
	*
	* @return unsigned - The height.
	*/
	unsigned getHeight() const ;

	/**
	* @brief Clear the data.
	*/
	void clear();

	/**
	* @brief Get the data size.
	*
	* @return unsigned - The data size.
	*/
	unsigned getDataSize();

private:
	/// The TGA data.
	unsigned char * data;
	/// The file width.
	unsigned width;
	/// The file height.
	unsigned height;
	/// The number of bits in the file.
	unsigned bits;
	/// The file size.
	unsigned size;
};

