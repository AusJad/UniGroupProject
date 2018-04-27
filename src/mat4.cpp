#include "mat4.h"
#include "vec3.h"

mat4::mat4()
{

}

mat4::mat4(float x_0, float y_0, float z_0, float w_0,
	float x_1, float y_1, float z_1, float w_1,
	float x_2, float y_2, float z_2, float w_2,
	float x_3, float y_3, float z_3, float w_3) {
	
	matrix = glm::mat4(x_0, y_0, z_0, w_0,
						x_1, y_1, z_1, w_1,
						x_2, y_2, z_2, w_2,
						x_3, y_3, z_3, w_3);
}

mat4::mat4(const mat4 & m)
{
	matrix = m.getMat();
}

glm::mat4 mat4::getMat() const
{
	return matrix;
}

void mat4::setMat(glm::mat4 mat)
{
	matrix = mat;
}

vec4 mat4::operator* (const vec4 & v)
{
	glm::vec4 tmpglm;
	tmpglm = matrix * v.getVec();

	vec4 tmp;
	tmp.setVec(tmpglm);

	return tmp;
}

void mat4::operator = (const mat4 & m)
{
	matrix = m.getMat();
}

float & mat4::operator[] (int index)
{
	int i = 1;

	if (index <= 3)
	{
		i = 1;
	}
	else if (index <= 7)
	{
		i = 2;
	}
	else if (i <= 11)
	{
		i = 3;
	}
	else
	{
		i = 4;
	}

	return matrix[i][index / i];
}

float mat4::operator[] (int index) const
{
	int i = 1;

	if (index <= 3)
	{
		i = 1;
	}
	else if (index <= 7)
	{
		i = 2;
	}
	else if (i <= 11)
	{
		i = 3;
	}
	else
	{
		i = 4;
	}

	return matrix[i][index / i];
}

mat4 mat4::operator += (const mat4 & m)
{
	matrix += m.getMat();
	return *this;
}

mat4 mat4::operator *= (const mat4 & m)
{
	matrix *= m.getMat();
	return *this;
}

mat4 mat4::operator /= (const mat4 & m)
{
	matrix /= m.getMat();
	return *this;
}

mat4 mat4::operator -= (const mat4 & m)
{
	matrix -= m.getMat();
	return *this;
}

mat4 mat4::operator + (const mat4 & m)
{
	mat4 tmp;
	tmp.setMat(matrix + m.getMat());
	return tmp;
}

mat4 mat4::operator - (const mat4 & m)
{
	mat4 tmp;
	tmp.setMat(matrix - m.getMat());
	return tmp;
}

mat4 mat4::operator * (const mat4 & m)
{
	mat4 tmp;
	tmp.setMat(matrix * m.getMat());
	return tmp;
}

mat4 mat4::operator / (const mat4 & m)
{
	mat4 tmp;
	tmp.setMat(matrix / m.getMat());
	return tmp;
}

mat4 mat4::operator += (const float f)
{
	matrix += f;
	return *this;
}

mat4 mat4::operator *= (const float f)
{
	matrix *= f;
	return *this;
}

mat4 mat4::operator /= (const float f)
{
	matrix /= f;
	return *this;
}

mat4 mat4::operator -= (const float f)
{
	matrix -= f;
	return *this;
}

mat4 mat4::operator + (const float f)
{
	mat4 tmp;
	tmp.setMat(matrix + f);
	return tmp;
}

mat4 mat4::operator - (const float f)
{
	mat4 tmp;
	tmp.setMat(matrix - f);
	return tmp;
}

mat4 mat4::operator * (const float f)
{
	mat4 tmp;
	tmp.setMat(matrix * f);
	return tmp;
}

mat4 mat4::operator / (const float f)
{
	mat4 tmp;
	tmp.setMat(matrix / f);
	return tmp;
}
