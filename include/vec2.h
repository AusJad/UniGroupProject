#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/type_ptr.hpp"

/**
*@class vec2
* @brief Facade of vec2 GLM functionality.
*
* @author Matthew MacLennan
* @version 1.3
* @date 10 / 04 / 2018
*/
class vec2
{
public:
	vec2();
	vec2(float a, float b);
	vec2(const vec2 & v);
	vec2(const glm::vec2 & v);

	/**
	* @brief Get function for glm::vec2 type variable.
	*
	* @param vector(glm::vec2) - GLM type vector.
	*
	* @return glm::vec2 - GLM type vector.
	*/
	glm::vec2 getVec() const;

	/**
	* @brief Set function for glm::vec2 type variable.
	*
	* @param vector(glm::vec2) - GLM type vector.
	* @param vec(glm::vec2) - New GLM type vector.
	*
	* @return NONE.
	*/
	void setVec(glm::vec2 vec);

	/**
	* @brief Overload function for = operator to set current vector to new vector.
	*
	* @param v(vec2) - New vector.
	*
	* @return NONE.
	*/
	void operator = (const vec2 & v);

	/**
	* @brief Overload function for [] operator to return the value at the location in the vector specified.
	*
	* @param x(int) - Location in vector being requested.
	* 
	* @return float& - Data in requested location.
	*/
	float& operator[] (int x);

	/**
	* @brief Return first value (x).
	*
	* @return float - x value.
	*/
	float x();

	/**
	* @brief Return second value (y).
	*
	* @return float - y value.
	*/
	float y();

	/**
	* @brief Set x value.
	*
	* @param nx(float) - New x value.
	*
	* @return float - New value.
	*/
	float sx(float nx);

	/**
	* @brief Set y value.
	*
	* @param ny(float) - New y value.
	*
	* @return float - New value.
	*/
	float sy(float ny);

	/**
	* @brief Add second vector to first.
	*
	* @param vec(vec2) - Second vector being added.
	*
	* @return NONE.
	*/
	void add(vec2 vec);

	/**
	* @brief Nomalize returning vec2.
	*
	* @return vec2 - The normalized vector
	*/
	vec2 normalise();

	/**
	* @brief Normalize returning void.
	*
	* @return NONE.
	*/
	void normailse();

	/**
	* @brief Use dot mulitplcation
	*
	* @param v(vec2) - The 2nd vector.
	*
	* @return float - The outcome.
	*/
	float dot(const vec2 & v);

	/**
	* @brief Get the angle.
	*
	* @param v(vec2) - The 2nd vector.
	*
	* @return float - The outcome.
	*/
	float angle(const vec2 & v);

	/**
	* @brief Overload function for += operator with a vec2.
	*
	* @param v(vec2) - The vector being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator += (const vec2 & v);

	/**
	* @brief Overload function for *= operator with a vec2.
	*
	* @param v(vec2) - The vector being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator *= (const vec2 & v);

	/**
	* @brief Overload function for /= operator with a vec2.
	*
	* @param v(vec2) - The vector being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator /= (const vec2 & v);

	/**
	* @brief Overload function for -= operator with a vec2.
	*
	* @param v(vec2) - The vector being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator -= (const vec2 & v);

	/**
	* @brief Overload function for + operator with a vec2.
	*
	* @param v(vec2) - The vector being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator + (const vec2 & v);

	/**
	* @brief Overload function for - operator with a vec2.
	*
	* @param v(vec2) - The vector being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator - (const vec2 & v);

	/**
	* @brief Overload function for * operator with a vec2.
	*
	* @param v(vec2) - The vector being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator * (const vec2 & v);

	/**
	* @brief Overload function for / operator with a vec2.
	*
	* @param v(vec2) - The vector being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator / (const vec2 & v);

	/**
	* @brief Overload function for += operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator += (const float f);

	/**
	* @brief Overload function for *= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator *= (const float f);

	/**
	* @brief Overload function for /= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator /= (const float f);

	/**
	* @brief Overload function for -= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator -= (const float f);

	/**
	* @brief Overload function for + operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator + (const float f);

	/**
	* @brief Overload function for - operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator - (const float f);

	/**
	* @brief Overload function for * operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator * (const float f);

	/**
	* @brief Overload function for / operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec2 - The outcome.
	*/
	vec2 operator / (const float f);

private:
	glm::vec2 vector; /// GLM type vec2.
};