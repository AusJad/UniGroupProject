#pragma once
#include <vector>
#include <vec3.h>
#include <fstream>
#include <string>
#include <cstdlib>
//#include "mat4.h"
#include "Maths.h"
#include "Identifiers.h"

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
		virtual void update(float time) = 0;

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
		virtual float getMinX() { return minx; };

		/**
		* @brief Get the min z value.
		*
		* @return float - The min z value.
		*/
		virtual float getMinZ() { return minz; };

		 /**
		 * @brief Get the min y value.
		 *
		 * @return float - The min y value.
		 */
		virtual float getMinY() { return miny; };

		 /**
		 * @brief Get the max x value.
		 *
		 * @return float - The max x value.
		 */
		virtual float getMaxX() { return maxx; };

		 /**
		 * @brief Get the max z value.
		 *
		 * @return float - The maz z value.
		 */
		virtual float getMaxZ() { return maxz; };

		 /**
		 * @brief Get the max y value.
		 *
		 * @return float - The max y value.
		 */
		virtual float getMaxY() { return maxy; };
		 
		/**
		* @brief Get the min translated adjusted x value
		*
		* @return float - The min x value + the last translation x value.
		*/
		virtual float getMinTX() { return minx + lasttrans.x(); };

		/**
		* @brief Get the min translated adjusted z value
		*
		* @return float - The min z value + the last translation z value.
		*/
		virtual float getMinTZ() { return minz + lasttrans.z(); };

		/**
		* @brief Get the min translated adjusted y value
		*
		* @return float - The min y value + the last translation y value.
		*/
		virtual float getMinTY() { return miny + lasttrans.y(); };

		/**
		* @brief Get the max translated adjusted x value
		*
		* @return float - The max x value + the last translation x value.
		*/
		virtual float getMaxTX() { return maxx + lasttrans.x(); };

		/**
		* @brief Get the max translated adjusted z value
		*
		* @return float - The max z value + the last translation z value.
		*/
		virtual float getMaxTZ() { return maxz + lasttrans.z(); };

		/**
		* @brief Get the max translated adjusted y value
		*
		* @return float - The max y value + the last translation y value.
		*/
		virtual float getMaxTY() { return maxy + lasttrans.y(); };

		 /**
		 * @brief Set the id of the model.
		 * 
		 * @param nid - The new id.
		 */
		void setId(unsigned nid) {	id.setId(nid); };

		/**
		* @brief Get the id of the model.
		* 
		* @return unsigned - The id.
		*/
		unsigned getId() { return id.getId(); };

		std::string getName() { return id.getName(); }

		/**
		* @brief Set the name.
		*
		* @param name - The new name;
		*/
		void setName(std::string name) { id.setName(name); };

	protected:
		/// The min and max x and z values.
		float minx, maxx, minz, maxz, miny, maxy;
		/// The models id.
		Identifiers id;
		/// The last translation position.
		vec3 lasttrans;
};

