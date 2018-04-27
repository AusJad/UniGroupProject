#pragma once
#include <string>
#include <vector>
#include "Model.h"
#include "RenderModuleStubb.h"
#include "Singleton.h"
#include "TextureManager.h"
//#include "vec2.h"
#include "Maths.h"

/**
* @class terrain
* @brief Class for loading and creating the terrain
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class terrain : public Model
{
	public:
		terrain();
		 ~terrain();

		/**
		* @brief Virtual method to load the model.
		*
		* @param filename - The file name.
		*
		* @return bool - If the model is loaded.
		*/
		virtual bool loadModel(std::string filename) = 0;

		/**
		* @brief Virtual update function.
		*/
		virtual void update(float time) = 0;

		/**
		* @brief Virtual render function.
		*
		* @param transmat - Translation matrix.
		*/
		virtual void render(const vec3 & transmat) = 0;

		/**
		* @brief Virtual creation function.
		*
		* @return terrain*  - The terrain data.
		*/
		virtual terrain * create() const = 0;

		/**
		* @brief Get the center on point.
		*
		* @param point - The vector point.
		*/
		void centerOnPoint(vec3 & point);

		/**
		* @brief Get the verticies.
		*
		* @return vector<vec3> - The verticies.
		*/
		std::vector<vec3>& getVerticies();

		/**
		* @brief Get the scale vector.
		*
		* @param toset - The new scale vector.
		*/
		void setScale(vec3 & toset);

		/**
		*@brief Generates a light map.
		*/
		void genLightmap();

	protected:
		/// The terrian data.
		float * data;
		/// The plane vectors.
		std::vector<vec3> plane;
		/// The plane indexies.
		std::vector<unsigned> planInd;
		/// The texture coords.
		std::vector<vec2> texcoords;
		/// The vector for the lights.
		std::vector<float> lights;
		/// The scale vector.
		vec3 scale;
		/// The dimensions of the world.
		unsigned dimensions;

		/**
		* @brief Calculate the max and min values.
		*/
		void calcMaxMin();

		/**
		* @brief Generate the plane data.
		*
		* @param size - The size of the plane.
		*/
		void genPlane(unsigned size);
		
		/**
		* @brief Generate the plane indicies.
		*
		* @param size - the size of the plane.
		*/
		void genPlaneIndicies(unsigned size);

		/**
		* @brief Generate the texture coods.
		*/
		void genTexCoords();

		/**
		* @brief Apply the scaling vector.
		*
		* @param scale - The new scaling vector.
		*/
		void applyScaling(vec3 & scale);
};

