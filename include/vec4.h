#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/type_ptr.hpp"

/**
* @class vec4
* @brief Facade of vec4 GLM functionality.
*
* @author Matthew MacLennan
* @version 1.3
* @date 10 / 04 / 2018
*/
class vec4
{
public:
	vec4();
	vec4(float a, float b, float c, float d);
	vec4(const vec4 & v);

	/**
	* @brief Get function for glm::vec4 type variable.
	*
	* @param vector(glm::vec4) - GLM type vector.
	*
	* @return glm::vec4 - GLM type vector.
	*/
	glm::vec4 getVec() const;

	/**
	* @brief Set function for glm::vec4 type variable.
	*
	* @param vector(glm::vec4) - GLM type vector.
	* @param vec(glm::vec4) - New GLM type vector.
	*
	* @return NONE.
	*/
	void setVec(glm::vec4 vec);

	/**
	* @brief Overload function for [] operator to return the value at the location in the vector specified.
	*
	* @param x(int) - Location in vector being requested.
	*
	* @return float& - Data in requested location.
	*/
	float& operator[] (int x);

	/**
	* @brief Overload function for * operator with another vec4.
	*
	* @param vec2(vec4) - The second vector.
	* @param tmpglm(glm::vec4) - Temporary glm type vector.
	* @param tmp(vec4) - Temporary vector.
	*
	* @return vec4 - Calcuation.
	*/
	vec4 operator* (vec4 vec2);

	/**
	* @brief Function to add input vector to current vector.
	*
	* @param vec(vec4) - Vector being added.
	*
	* @return NONE.
	*/
	void add(vec4 vec);

	/**
	* @brief Get the x value.
	*
	* @return float - The x value.
	*/
	float x() const;

	/**
	* @brief Get the y value.
	*
	* @return float - The y value.
	*/
	float y() const;

	/**
	* @brief Get the z value.
	*
	* @return float - The z value.
	*/
	float z() const;

	/**
	* @brief Get the w value.
	*
	* @return float - The w value.
	*/
	float w() const;

	/**
	* @brief Set the x value.
	*
	* @param sx(float) - The new x value.
	*
	* @return float - The x value.
	*/
	float sx(float nx);

	/**
	* @brief Set the y value.
	*
	* @param sx(float) - The new y value.
	*
	* @return float - The y value.
	*/
	float sy(float ny);

	/**
	* @brief Set the z value.
	*
	* @param sz(float) - The new x value.
	*
	* @return float - The z value.
	*/
	float sz(float nz);

	/**
	* @brief Set the w value.
	*
	* @param sw(float) - The new x value.
	*
	* @return float - The w value.
	*/
	float sw(float nw);

	/**
	* @brief Nomalize returning vec4.
	*
	* @return vec4 - The normalized vector
	*/
	vec4 normalise();

	/**
	* @brief Normalize returning void.
	*
	* @return NONE.
	*/
	void normailse();

	/**
	* @brief Use dot mulitplcation
	*
	* @param v(vec4) - The 2nd vector.
	*
	* @return float - The outcome.
	*/
	float dot(const vec4 & v);

	/**
	* @brief Get the angle.
	*
	* @param v(vec4) - The 2nd vector.
	*
	* @return float - The outcome.
	*/
	float angle(const vec4 & v);

	/**
	* @brief Overload function for += operator with a vec4.
	*
	* @param v(vec4) - The vector being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator += (const vec4 & v);

	/**
	* @brief Overload function for *= operator with a vec4.
	*
	* @param v(vec4) - The vector being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator *= (const vec4 & v);

	/**
	* @brief Overload function for /= operator with a vec4.
	*
	* @param v(vec4) - The vector being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator /= (const vec4 & v);

	/**
	* @brief Overload function for -= operator with a vec4.
	*
	* @param v(vec4) - The vector being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator -= (const vec4 & v);

	/**
	* @brief Overload function for + operator with a vec4.
	*
	* @param v(vec4) - The vector being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator + (const vec4 & v);

	/**
	* @brief Overload function for - operator with a vec4.
	*
	* @param v(vec4) - The vector being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator - (const vec4 & v);

	/**
	* @brief Overload function for * operator with a vec4.
	*
	* @param v(vec4) - The vector being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator * (const vec4 & v);

	/**
	* @brief Overload function for / operator with a vec4.
	*
	* @param v(vec4) - The vector being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator / (const vec4 & v);

	/**
	* @brief Overload function for += operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator += (const float f);

	/**
	* @brief Overload function for *= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator *= (const float f);

	/**
	* @brief Overload function for /= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator /= (const float f);

	/**
	* @brief Overload function for -= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator -= (const float f);

	/**
	* @brief Overload function for + operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator + (const float f);

	/**
	* @brief Overload function for - operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator - (const float f);

	/**
	* @brief Overload function for * operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator * (const float f);

	/**
	* @brief Overload function for / operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec4 - The outcome.
	*/
	vec4 operator / (const float f);


private:
	glm::vec4 vector; /// GLM type vec4.
};