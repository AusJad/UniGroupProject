#include "mat4.h"
#include "vec3.h"

mat4::mat4()
{

}

mat4::mat4(const mat4 & m)
{
	matrix = m.getMat();
}

mat4::mat4(const glm::mat4 & m)
{
	matrix = m;
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
	return vec4(matrix * v.getVec());
}

void mat4::operator = (const mat4 & m)
{
	matrix = m.getMat();
}

float & mat4::operator[] (int index)
{
	int i;

	if (index <= 3)
	{
		i = 0;
	}
	else if (index <= 7)
	{
		i = 1;
	}
	else if (i <= 11)
	{
		i = 2;
	}
	else
	{
		i = 3;
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
	return mat4(matrix + m.getMat());
}

mat4 mat4::operator - (const mat4 & m)
{
	return mat4(matrix - m.getMat());
}

mat4 mat4::operator * (const mat4 & m)
{
	return mat4(matrix * m.getMat());
}

mat4 mat4::operator / (const mat4 & m)
{
	return mat4(matrix / m.getMat());
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
	return mat4(matrix + f);
}

mat4 mat4::operator - (const float f)
{
	return mat4(matrix - f);
}

mat4 mat4::operator * (const float f)
{
	return mat4(matrix * f);
}

mat4 mat4::operator / (const float f)
{
	return mat4(matrix / f);
}
