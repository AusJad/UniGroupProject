#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "mat4.h"
#include "vec4.h"
#include "vec3.h"
#include "vec2.h"

/**
* @class Maths
* @brief Overall facade class for GLM maths providing vector and matrix functionality.
*
* @author Matthew MacLennan
* @version 1.3
* @date 10 / 04 / 2018
*/
class Maths
{
public:
	/**
	* @brief Set matrix to its identity.
	*
	* @param mat(mat4) - Matrix being set.
	* @param i(float) - The identity.
	*
	* @return mat4 - Set matrix.
	*/
	static mat4 setmat4(mat4 mat, float i);

	/**
	* @brief Set each individual value in matrix.
	*
	* @param a(float) - A value to be added to matrix.
	* @param b(float) - A value to be added to matrix.
	* @param c(float) - A value to be added to matrix.
	* @param d(float) - A value to be added to matrix.
	* @param e(float) - A value to be added to matrix.
	* @param f(float) - A value to be added to matrix.
	* @param g(float) - A value to be added to matrix.
	* @param h(float) - A value to be added to matrix.
	* @param i(float) - A value to be added to matrix.
	* @param j(float) - A value to be added to matrix.
	* @param k(float) - A value to be added to matrix.
	* @param l(float) - A value to be added to matrix.
	* @param m(float) - A value to be added to matrix.
	* @param n(float) - A value to be added to matrix.
	* @param o(float) - A value to be added to matrix.
	* @param p(float) - A value to be added to matrix.
	*
	* @return mat4 - Set matrix.
	*/
	static mat4 setmat4(mat4 mat, float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);

	/**
	* @brief Set all values in vec4
	*
	* @param vec(vec4) - The vector being set.
	* @param a(float) - The value being added to the vector.
	* @param b(float) - The value being added to the vector.
	* @param c(float) - The value being added to the vector.
	* @param d(float) - The value being added to the vector.
	*
	* @return vec4 - Set vector.
	*/
	static vec4 setvec4(vec4 vec, float a, float b, float c, float d);

	/**
	* @brief Set all values in vec3
	*
	* @param vec(vec3) - The vector being set.
	* @param a(float) - The value being added to the vector.
	* @param b(float) - The value being added to the vector.
	* @param c(float) - The value being added to the vector.
	*
	* @return vec3 - Set vector.
	*/
	static vec3 setvec3(vec3 vec, float a, float b, float c);

	/**
	* @brief Mulitplying a mat4 and a vec4.
	*
	* @param mat(mat4) - Matrix being multiplied.
	* @param vec(vec3) - Vector being mulitplied.
	*
	* @return vec4 - Outcome vector of calculation.
	*/
	static vec4 mat4Xvec4(mat4 mat, vec4 vec);

	/**
	* @brief Translate a mat4 with a vec3.
	*
	* @param mat(mat4) - Matrix being translated.
	* @param vec(vec3) - Translating vector.
	*
	* @return mat4 - Translated matrix.
	*/
	static mat4 translate(mat4 mat, vec3 vec);

	/**
	* @brief Rotate a mat4 with a vec3.
	*
	* @param mat(mat4) - Matrix being rotated.
	* @param vec(vec3) - Rotating vector.
	*
	* @return mat4 - Rotated matrix.
	*/
	static mat4 rotate(mat4 mat, float angle, vec3 rotv);

	/**
	* @brief Scale a mat4 with a vec3.
	*
	* @param mat(mat4) - Matrix being scaled.
	* @param scalev(vec3) - scaling vector.
	*
	* @return mat4 - Scaled matrix.
	*/
	static mat4 scale(mat4 mat, vec3 scalev);

	/**
	* @brief Take inputs of fovy, width, height, near and far and return a perspective mat4.
	*
	* @param fovy(float)
	* @param width(float)
	* @param height(float)
	* @param near(float)
	* @param far(float)
	*
	* @return mat4.
	*/
	static mat4 perspective(float fovy, float width, float height, float near, float far);

	/**
	* @brief Nomalize a vec4.
	*
	* @param vec(vec4) - Vector being normalized.
	*
	* @return vec4 - Normalized vector.
	*/
	static vec4 normalizev4(vec4 vec);

	/**
	* @brief Nomalize a vec3.
	*
	* @param vec(vec3) - Vector being normalized.
	*
	* @return vec3 - Normalized vector.
	*/
	static vec3 normalize(vec3 vec);

	/**
	* @brief Turn degrees into radians.
	*
	* @param a(float) - Angle being converted.
	*
	* @return float - Radians.
	*/
	static float radians(float a);

	/**
	* @brief Return inverse matrix of input.
	*
	* @param m(mat4) - Matrix being inversed.
	*
	* @return mat4 - Inversed matrix.
	*/
	static mat4 inverse(mat4 m);

	/**
	* @brief Returns perspective matrix from 4 inputs.
	*
	* @param a(float).
	* @param b(float).
	* @param c(float).
	* @param d(float).
	*
	* @return mat4 - Perspective matrix.
	*/
	static mat4 perspective(float a, float b, float c, float d);

	/**
	* @brief Transform(multiply) 2 matricies.
	*
	* @param mat1(mat4) - First matrix.
	* @param mat2(mat4) - Second matrix.
	*
	* @return mat4 - Outcome.
	*/
	static mat4 transform(mat4 mat1, mat4 mat2);

	/**
	* @brief Transform(multiply) 3 matricies.
	*
	* @param projectionm(mat4) - First matrix.
	* @param translatem(mat4) - Second matrix.
	* @param rotm(mat4) - Third matrix.
	*
	* @return mat4 - Outcome.
	*/
	static mat4 transform(mat4 projectionm, mat4 translatem, mat4 rotm);

	/**
	* @brief Transform(multiply) 4 matricies.
	*
	* @param projectionm(mat4) - First matrix.
	* @param rotm(mat4) - Second matrix.
	* @param scalem(mat4) - Third matrix.
	* @param mat(mat4) - Fourth matrix.
	*
	* @return mat4 - Outcome.
	*/
	static mat4 transform(mat4 translatem, mat4 rotm, mat4 scalem, mat4 mat);
};