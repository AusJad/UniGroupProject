#pragma once
#include "ImageCreationHandler.h"
#include <map>

/**
* @class TextureManager
* @brief Class for handling textures
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class TextureManager
{
public:
	TextureManager();

	/**
	* @brief Load the new texture
	*
	* @param path - The file path.
	* @param type - The texture type.
	* @param name - The texture name.
	* @param renderer - The rendering object.
	*
	* return bool - If the texture loaded.
	*/
	bool loadNewTexture(std::string path, std::string type, std::string name, RenderModuleStubb* renderer);

	/**
	* @brief Store the texutre data.
	*
	* @param name - The name of the texture.
	* @param data - The texture data.
	* @param bits - The number of bits in the file.
	* @param width - The width of the file.
	* @param height - The height of the file.
	* 
	* @return bool - If the data was stored.
	*/
	bool storeTextureFromData(std::string name, unsigned char* data, unsigned bits, unsigned width, unsigned height);

	/**
	* @brief Use the texture data.
	*
	* @param name - The texture name
	* @param renderer - The rendering object.
	*
	* @return bool - If the data was used.
	*/
	bool useTexture(std::string name, RenderModuleStubb* renderer);

	/**
	* @brief Use the texture data.
	*
	* @param name - The texture name.
	* @param name2 - The second texture name.
	* @param renderer - The rendering object.
	*
	* @return bool - If the data was used.
	*/
	bool useTexture(std::string name, std::string name2, RenderModuleStubb* renderer);

	/**
	* @brief Delete the texture data.
	*
	* @param name - The texture name.
	* @param renderer - The rendering object.
	*
	* @return bool - If the texture was deleted.
	*/
	bool deleteTexture(std::string name, RenderModuleStubb* renderer);

	/**
	* @brief Disable a texture.
	*
	* @param renderer - The rendering object.
	*
	* @return bool - If the texture was disabled.
	*/
	void disableTexture(RenderModuleStubb* renderer);

	/**
	* @brief Generate a multi-texture.
	*
	* @param heightmap - The heightmap data.
	* @param textures - The texture data for the heightmap.
	* @param name - The heightmap name.
	*
	* @return bool - If the texture was generated.
	*/
	bool genMultiTexture(std::vector<vec3> heightmap, std::vector<std::string> textures, std::string name);

	/**
	* @brief Disable the multi-texture.
	*
	* @param renderer - The rendering object.
	*/
	void DisableMultiTex(RenderModuleStubb* renderer);

private:
	/// Map of the images.
	std::map<std::string, int> images;
	/// The image creation handler.
	ImageCreationHandler ImgCH;
	/// The next texture id.
	unsigned nextid;
};

