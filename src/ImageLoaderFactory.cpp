#include "ImageLoaderFactory.h"


ImageLoader* ImageLoaderFactory::getNewLoader(std::string type){
	if (type == "TGA"){
		return new TGALoader;
	}
	else
	if (type == "BMP"){
		return new BMPLoader;
	}

	return NULL;
}