#include "Maths.h"

mat4 Maths::setmat4(mat4 mat, float i)
{
	mat.setMat(glm::mat4(i)); // Identity matrix
	return mat;
}

mat4 Maths::setmat4(mat4 mat, float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
{
	mat.setMat(glm::mat4(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p));
	return mat;
}

vec4 Maths::setvec4(vec4 vec, float a, float b, float c, float d)
{
	vec.setVec(glm::vec4(a, b, c, d));

	return vec;
}

vec3 Maths::setvec3(vec3 vec, float a, float b, float c)
{
	vec.setVec(glm::vec3(a, b, c));
	return vec;
}

vec4 Maths::mat4Xvec4(mat4 mat, vec4 vec)
{
	vec4 tmp;
	tmp.setVec(mat.getMat() * vec.getVec());
	return tmp;
}

mat4 Maths::translate(mat4 mat, vec3 vec)
{
	mat4 tmp;
	tmp.setMat(glm::translate(mat.getMat(), vec.getVec()));
	return tmp;
}

mat4 Maths::rotate(mat4 mat, float angle, vec3 vec)
{
	mat4 tmp;
	tmp.setMat(glm::rotate(mat.getMat(), angle, vec.getVec()));
	return tmp;
}

mat4 Maths::scale(mat4 mat, vec3 scalev)
{
	mat4 tmp;
	tmp.setMat(glm::scale(mat.getMat(), scalev.getVec()));
	return tmp;
}

mat4 Maths::perspective(float fovy, float width, float height, float near, float far)
{
	mat4 tmp;
	tmp.setMat(glm::perspective(fovy, width / height, near, far));
	return tmp;
}

vec4 Maths::normalize(vec4 vec)
{
	vec.setVec(glm::normalize(vec.getVec()));
	return vec;
}

vec3 Maths::normalize(vec3 vec)
{
	vec.setVec(glm::normalize(vec.getVec()));
	return vec;
}

float Maths::radians(float a)
{
	return glm::radians(a);
}

mat4 Maths::inverse(mat4 m)
{
	m.setMat(glm::inverse(m.getMat()));
	return m;
}

mat4 Maths::perspective(float a, float b, float c, float d)
{
	mat4 m;
	m.setMat(glm::perspective(a, b, c, d));
	return m;
}

mat4 Maths::transform(mat4 mat1, mat4 mat2)
{
	mat4 tmp;
	tmp.setMat(mat1.getMat() * mat2.getMat());
	return tmp;
}

mat4 Maths::transform(mat4 projectionm, mat4 translatem, mat4 rotm)
{
	mat4 tmp;
	tmp.setMat(projectionm.getMat() * translatem.getMat() * rotm.getMat());
	return tmp;
}

mat4 Maths::transform(mat4 translatem, mat4 rotatem, mat4 scalem, mat4 mat)
{
	mat4 tmp;
	tmp.setMat(translatem.getMat() * rotatem.getMat() * scalem.getMat() * mat.getMat());
	return tmp;
}