#pragma once

#include "TGALoader.h"
#include "BMPLoader.h"

/**
* @class ImageLoaderFactory
* @brief Class for creaing new image loader objects.
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class ImageLoaderFactory
{
	public:
		/**
		* @brief Get a new loader.
		*
		* @param type - The type of image.
		* 
		* @return ImageLoader* - The new image loader object.
		*/
		ImageLoader* getNewLoader(std::string type);
};

