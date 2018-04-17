#pragma once
#include <vector>
#include <vec3.h>
#include <fstream>
#include <string>
#include <cstdlib>
//#include "mat4.h"
#include "Maths.h"

/**
* @class Model
* @brief Class for creating models
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class Model
{
	public:

		/**
		* @brief Virtual method to create a model
		*
		* @return Model * - The model data.
		*/
		virtual Model * create() const = 0;

		/**
		* @brief Virtual method to load a model.
		*
		* @param filename - The filename.
		*
		* @return bool - If the model loaded.
		*/
		virtual bool loadModel(std::string filename) = 0;

		/**
		* @brief Virtual method to update the model.
		*/
		virtual void update() = 0;

		/**
		* @brief Virtual method to render the model.
		*
		* @param transmat - The translation matrix.
		*/
		virtual void render(const vec3 & transmat) = 0;

		/**
		* @brief Virtual method to get the center on the point.
		*
		* @param point - The position to get the center of.
		*/
		virtual void centerOnPoint(vec3 & point) = 0;

		/**
		* @brief Virtual method to get the verticies.
		*
		* @return vector<vec3> - The verticies.
		*/
		virtual std::vector<vec3>& getVerticies() = 0;

		/**
		* @brief Virtual method to get the scale.
		*
		* @param toset - The vector to be set.
		*/
		virtual void setScale(vec3 & toset) = 0;

		/**
		* @brief Get the min x value.
		*
		* @return float - The min x value.
		*/
		float getMinX() { return minx; };

		/**
		* @brief Get the min z value.
		*
		* @return float - The min z value.
		*/
		 float getMinZ() { return minz; };

		 /**
		 * @brief Get the min y value.
		 *
		 * @return float - The min y value.
		 */
		 float getMinY() { return miny; };

		 /**
		 * @brief Get the max x value.
		 *
		 * @return float - The max x value.
		 */
		 float getMaxX() { return maxx; };

		 /**
		 * @brief Get the max z value.
		 *
		 * @return float - The maz z value.
		 */
		 float getMaxZ() { return maxz; };

		 /**
		 * @brief Get the max y value.
		 *
		 * @return float - The max y value.
		 */
		 float getMaxY() { return maxy; };
		 
		 /**
		 * @brief Set the id of the model.
		 * 
		 * @param nid - The new id.
		 */
		void setId(unsigned nid) { id = nid; };

		/**
		* @brief Get the id of the model.
		* 
		* @return unsigned - The id.
		*/
		unsigned getId() { return id; };
	protected:
		/// The min and max x and z values.
		float minx, maxx, minz, maxz, miny, maxy;
		/// The models id.
		unsigned id;
};

