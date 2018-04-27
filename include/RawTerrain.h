#pragma once

#include "terrain.h"
#include <fstream>
#include <iostream>
#include <cmath>

/**
* @class RAWTerrain
* @brief Class loading terrain data in
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class RAWTerrain : public terrain
{
	public:
		RAWTerrain();
		~RAWTerrain();

		/**
		* @brief Virtual method to load the model.
		*
		* @param filename - The file name.
		*/
		virtual bool loadModel(std::string filename);

		/**
		* @brief Virtual method to update the terrain.
		*/
		virtual void update(float time);

		/**
		* @brief Virtual method to render the terrain.
		*/
		virtual void render(const vec3 & transmat);

		/**
		* @brief Method to create a terrain.
		*
		* @return RAWTerrain* - The terrain data.
		*/
		RAWTerrain * create() const;

	private:
		/// The multi-texture data.
		std::string multitexture;
		/// The detail map data.
		std::string detailmap;
		
		/**
		* @brief Load the data in from file.
		*
		* @param filename - The filename.
		*
		* @return bool - If the data was loaded.
		*/
		bool loadData(std::string filename);

		/**
		* @brief Parse the options.
		*
		* @param file - The filename.
		*
		* @return string - The parse options.
		*/
		std::string parseOptions(std::string file);

		/**
		* @brief Generate a random string.
		*
		* @param len - The string length.
		*
		* @return string - A random string.
		*/
		std::string RandomString(unsigned len);

		/// A vector containing the image data.
		std::vector<std::string> images;

		RAWTerrain(const RAWTerrain& tocpy);
};

