#pragma once

#include "ImageLoaderFactory.h"
#include "RenderModuleStubb.h"

/**
* @class ImageCreationHandler
* @brief Class for handling image creation for textures or any other images
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class ImageCreationHandler
{
public:
	ImageCreationHandler();
	~ImageCreationHandler();

	/**
	* @brief Create a imgage object.
	*
	* @param path - The path to the image.
	* @param type - The type of image.
	*
	* @return bool - If the image was created.
	*/
	bool CreateImage(std::string path, std::string type);

	/**
	* @brief Bind the image to a object in the renderer.
	*
	* @param id - The image id.
	* @param renderer - The rendering object.
	*
	* @return bool - If the image was bound.
	*/
	bool bindImage(const int & id, RenderModuleStubb* renderer);

	/**
	* @brief Unbind the image from the object in the renderer.
	*
	* @param id - The image id.
	* @param renderer - The rendering object.
	*/
	void unbindImage(const int & id, RenderModuleStubb* renderer);

	/**
	* @brief Create a multi-texture object.
	*
	* @param heightmap - The heightmap position data.
	* @param texture - The texture data.
	* @param name - The name of the texture.
	* @param id - The id of the texture.
	*
	* @return bool - If the multi-texture was created.
	*/
	bool CreateMultiTexture(std::vector<vec3> heightmap, std::vector<std::string> textures, std::string name, const int & id);

	unsigned char* getActiveImageData();

	bool bindSubImage(const int & id, unsigned subwidth, unsigned subheight, unsigned x, unsigned y);
private:
	/// Current image loader object.
	ImageLoader* currimage;
};

