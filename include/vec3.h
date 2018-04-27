#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "vec4.h"

/**
*@class vec3
* @brief Facade of vec3 GLM functionality.
*
* @author Matthew MacLennan
* @version 1.3
* @date 10 / 04 / 2018
*/
class vec3
{
public:
	vec3();
	vec3(float x, float y, float z);
	vec3(const vec4 & v4);
	vec3(const vec3 & v);
	vec3(const glm::vec3 & v);

	/**
	* @brief Get function for glm::vec3 type variable.
	*
	* @param vector(glm::vec3) - GLM type vector.
	*
	* @return glm::vec3 - GLM type vector.
	*/
	glm::vec3 getVec() const;

	/**
	* @brief Set function for glm::vec3 type variable.
	*
	* @param vector(glm::vec3) - GLM type vector.
	* @param vec(glm::vec3) - New GLM type vector.
	*
	* @return NONE.
	*/
	void setVec(glm::vec3 vec);

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
	* @brief Overload function for [] operator to return the value at the location in the vector specified.
	*
	* @param x(int) - Location in vector being requested.
	*
	* @return float& - Data in requested location.
	*/
	float& operator[] (int x);

	/** 
	* @brief Overload function for - operator to turn vector negative.
	*
	* @param tmp(vec3) - Temporary vector.
	*
	* @return vec3 - Negative vector.
	*/
	vec3 operator- ();
	
	/**
	* @brief Function to subtract input vector from current vector.
	*
	* @param vec(vec3) - Vector being subtracted.
	* 
	* @return NONE.
	*/
	void subtract(vec3 vec);

	/**
	* @brief Function to add input vector to current vector.
	*
	* @param vec(vec3) - Vector being added.
	*
	* @return NONE.
	*/
	void add(vec3 vec);

	/**
	* @brief Normalize returning void.
	*
	* @return NONE.
	*/
	const vec3 &  normailse();

	/**
	* @brief Use dot mulitplcation
	*
	* @param v(vec3) - The 2nd vector.
	*
	* @return float - The outcome.
	*/
	float dot(const vec3 & v);

	/**
	* @brief Get the angle.
	*
	* @param v(vec3) - The 2nd vector.
	*
	* @return float - The outcome.
	*/
	float angle(const vec3 & v);

	/**
	* @brief Get the cross product.
	*
	* @param v(vec3) - The 2nd vector.
	*
	* @return float - The outcome.
	*/
	vec3 cross(const vec3 & v);

	/**
	* @brief Overload function for += operator with a vec3.
	*
	* @param v(vec3) - The vector being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator += (const vec3 & v);

	/**
	* @brief Overload function for *= operator with a vec3.
	*
	* @param v(vec3) - The vector being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator *= (const vec3 & v);

	/**
	* @brief Overload function for /= operator with a vec3.
	*
	* @param v(vec3) - The vector being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator /= (const vec3 & v);

	/**
	* @brief Overload function for -= operator with a vec3.
	*
	* @param v(vec3) - The vector being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator -= (const vec3 & v);

	/**
	* @brief Overload function for + operator with a vec3.
	*
	* @param v(vec3) - The vector being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator + (const vec3 & v);

	/**
	* @brief Overload function for - operator with a vec3.
	*
	* @param v(vec3) - The vector being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator - (const vec3 & v);

	/**
	* @brief Overload function for * operator with a vec3.
	*
	* @param v(vec3) - The vector being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator * (const vec3 & v);

	/**
	* @brief Overload function for / operator with a vec3.
	*
	* @param v(vec3) - The vector being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator / (const vec3 & v);

	/**
	* @brief Overload function for += operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator += (const float f);

	/**
	* @brief Overload function for *= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator *= (const float f);

	/**
	* @brief Overload function for /= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator /= (const float f);

	/**
	* @brief Overload function for -= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator -= (const float f);

	/**
	* @brief Overload function for + operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator + (const float f);

	/**
	* @brief Overload function for - operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator - (const float f);

	/**
	* @brief Overload function for * operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator * (const float f);

	/**
	* @brief Overload function for / operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return vec3 - The outcome.
	*/
	vec3 operator / (const float f);

	/**
	* @brief Function to determine if the two vectors are within a certain threshold of eachother.
	*
	* @param v(vec3) - The 2nd vector.
	* @param threshold(float) - The accecptable variance.
	*
	* @return bool - If they are within the threshold of eachother.
	*/
	bool almostEqual(const vec3 & v, float threshold);

	/**
	* @brief Overload function for = operator.
	*
	* @param v(vec3) - New vector.
	*
	* @return NONE.
	*/
	void operator = (const vec3 & v);

	float getLength();

private:
	glm::vec3 vector; /// GLM type vec3.
};