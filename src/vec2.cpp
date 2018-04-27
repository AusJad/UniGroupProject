#include "vec2.h"

vec2::vec2()
{

}

vec2::vec2(float a, float b)
{
	vector[0] = a;
	vector[1] = b;
}

vec2::vec2(const vec2 & v)
{
	vector = v.getVec();
}

vec2::vec2(const glm::vec2 & v)
{
	vector = v;
}

glm::vec2 vec2::getVec() const
{
	return vector;
}

void vec2::setVec(glm::vec2 vec)
{
	vector = vec;
}

float vec2::x()
{
	return vector[0];
}

float vec2::y()
{
	return vector[1];
}

float vec2::sx(float nx)
{
	vector[0] = nx;
	return vector[0];
}

float vec2::sy(float ny)
{
	vector[1] = ny;
	return vector[1];
}

void vec2::add(vec2 vec)
{
	vector[0] = vector[0] + vec.getVec()[0];
	vector[1] = vector[1] + vec.getVec()[1];
}

vec2 vec2::normalise()
{
	return vec2(normalize(vector));
}

void vec2::normailse()
{
	glm::normalize(vector);
}

float vec2::dot(const vec2 & v)
{
	return glm::dot(vector, v.getVec());
}

float vec2::angle(const vec2 & v)
{
	return glm::angle(vector, v.getVec());
}

void vec2::operator = (const vec2 & v)
{
	vector = v.getVec();
}

float& vec2::operator[] (int x)
{
	return vector[x];
}

vec2 vec2::operator += (const vec2 & v)
{
	vector += v.getVec();
	return *this;
}

vec2 vec2::operator *= (const vec2 & v)
{
	vector *= v.getVec();
	return *this;
}

vec2 vec2::operator /= (const vec2 & v)
{
	vector /= v.getVec();
	return *this;
}

vec2 vec2::operator -= (const vec2 & v)
{
	vector -= v.getVec();
	return *this;
}

vec2 vec2::operator + (const vec2 & v)
{
	return vec2(vector + v.getVec());
}

vec2 vec2::operator - (const vec2 & v)
{
	return vec2(vector - v.getVec());
}

vec2 vec2::operator * (const vec2 & v)
{
	return vec2(vector * v.getVec());
}

vec2 vec2::operator / (const vec2 & v)
{
	return vec2(vector / v.getVec());
}

vec2 vec2::operator += (const float f)
{
	vector += f;
	return *this;
}

vec2 vec2::operator *= (const float f)
{
	vector *= f;
	return *this;
}

vec2 vec2::operator /= (const float f)
{
	vector /= f;
	return *this;
}

vec2 vec2::operator -= (const float f)
{
	vector -= f;
	return *this;
}

vec2 vec2::operator + (const float f)
{
	return vec2(vector + f);
}

vec2 vec2::operator - (const float f)
{
	return vec2(vector - f);
}

vec2 vec2::operator * (const float f)
{
	return vec2(vector * f);
}

vec2 vec2::operator / (const float f)
{
	return vec2(vector / f);
}