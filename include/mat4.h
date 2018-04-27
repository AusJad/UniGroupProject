#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "vec4.h"

/**
*@class Mat4
* @brief Facade of mat4 GLM functionality.
*
* @author Matthew MacLennan
* @version 1.3
* @date 10 / 04 / 2018
*/
class mat4
{
public:
	mat4();

	mat4(float x_0, float y_0, float z_0, float w_0,
		float x_1, float y_1, float z_1, float w_1,
		float x_2, float y_2, float z_2, float w_2,
		float x_3, float y_3, float z_3, float w_3);

	mat4(const mat4 & m);

	/**
	* @brief Get function for glm::mat4 type variable.
	*
	* @param matrix(glm::mat4) - GLM type matrix.
	*
	* @return glm::mat4 - GLM type matrix.
	*/
	glm::mat4 getMat() const;

	/**
	* @brief Set function for glm::mat4 type variable.
	*
	* @param matrix(glm::mat4) - GLM type matrix.
	* @param mat(glm::mat4) - New GLM type matrix.
	*
	* @return NONE.
	*/
	void setMat(glm::mat4 mat);

	/**
	* @brief Overload function for * operator with a vec4.
	*
	* @param v(vec4) - Vector being multiplied to current vector.
	* @param tmpglm(glm::vec4) - Temporary GLM vector used to store calculation to be returned.
	*
	* @return vec4 - Calculation.
	*/
	vec4 operator* (const vec4 & v);

	/**
	* @brief Overload function for = operator.
	*
	* @param m(const mat4) - The new matrix.
	*
	* @return NONE.
	*/
	void operator = (const mat4 & m);

	/**
	* @brief Overload function for [] operator.
	*
	* @param index(int) - The index for the matrix.
	*
	* @return float - The data at the index.
	*/
	float & operator[] (int index);

	/**
	* @brief Overload function for += operator with a mat4.
	*
	* @param m(mat4) - The matrix being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator += (const mat4 & m);

	/**
	* @brief Overload function for *= operator with a mat4.
	*
	* @param m(mat4) - The matrix being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator *= (const mat4 & m);

	/**
	* @brief Overload function for /= operator with a mat4.
	*
	* @param m(mat4) - The matrix being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator /= (const mat4 & m);

	/**
	* @brief Overload function for -= operator with a mat4.
	*
	* @param m(mat4) - The matrix being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator -= (const mat4 & m);

	/**
	* @brief Overload function for + operator with a mat4.
	*
	* @param m(mat4) - The matrix being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator + (const mat4 & m);

	/**
	* @brief Overload function for - operator with a mat4.
	*
	* @param m(mat4) - The matrix being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator - (const mat4 & m);

	/**
	* @brief Overload function for * operator with a mat4.
	*
	* @param m(mat4) - The matrix being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator * (const mat4 & m);

	/**
	* @brief Overload function for / operator with a mat4.
	*
	* @param m(mat4) - The matrix being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator / (const mat4 & m);

	/**
	* @brief Overload function for += operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator += (const float f);

	/**
	* @brief Overload function for *= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator *= (const float f);

	/**
	* @brief Overload function for /= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator /= (const float f);

	/**
	* @brief Overload function for -= operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator -= (const float f);

	/**
	* @brief Overload function for + operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator + (const float f);

	/**
	* @brief Overload function for - operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator - (const float f);

	/**
	* @brief Overload function for * operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator * (const float f);

	/**
	* @brief Overload function for / operator with a float.
	*
	* @param f(float) - The f being operated on.
	*
	* @return mat4 - The outcome.
	*/
	mat4 operator / (const float f);

	float operator[] (int index) const;

private:
	glm::mat4 matrix; /// GLM type mat4.
};