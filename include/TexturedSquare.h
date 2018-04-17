#pragma once

#include "Model.h"
//#include "vec2.h"
#include "Singleton.h"
#include "TextureManager.h"
#include "Maths.h"


/**
* @class TexturedSquare
* @brief Class for texturing a square
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class TexturedSquare : public Model
{
public:
	TexturedSquare();

	/**
	* @brief Create a textured square.
	*
	* @return TexturedSquare* - The textured square data.
	*/
	TexturedSquare * create() const;

	/**
	* @brief Load the model from file.
	*
	* @param filename - The file name.
	*
	* @return bool - If the file was loaded.
	*/
	bool loadModel(std::string filename);

	/**
	* @brief The update file.
	*/
	void update();

	/**
	* @brief The render function.
	*
	* @param transmat - The translation matrix.
	*/
	void render(const vec3 & transmat);

	/**
	* @brief Set the center on point vector.
	*
	* @param point - The point vector.
	*/
	void centerOnPoint(vec3 & point);

	/**
	* @brief Get the verticies.
	*
	* @return vector<vec3> - The vector of verticies.
	*/
	std::vector<vec3>& getVerticies();

	/**
	* @brief Set the scale vector.
	*
	* @param toset - The scale vector.
	*/
	void setScale(vec3 & toset);
private:
	/// Top texture position.
	vec2 tl;
	/// Bottom texture position.
	vec2 br;
	/// Vector of verticies.
	std::vector<vec3> verts;
	/// Texture data.
	std::string texture;
	/**
	* @brief Create a random string of specified length.
	*
	* @param len - The length of the string.
	*
	* @param string - The random string.
	*/
	std::string RandomString(unsigned len);
};

