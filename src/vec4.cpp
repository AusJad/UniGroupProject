#include "vec4.h"

vec4::vec4()
{

}

vec4::vec4(float a, float b, float c, float d)
{
	vector[0] = a;
	vector[1] = b;
	vector[2] = c;
	vector[3] = d;
}

vec4::vec4(const vec4 & v)
{
	vector = v.getVec();
}

vec4::vec4(const glm::vec4 & v)
{
	vector = v;
}

glm::vec4 vec4::getVec() const
{
	return vector;
}

void vec4::setVec(glm::vec4 vec)
{
	vector = vec;
}

void vec4::add(vec4 vec)
{
	vector[0] = vector[0] + vec.getVec()[0];
	vector[1] = vector[1] + vec.getVec()[1];
	vector[2] = vector[2] + vec.getVec()[2];
	vector[3] = vector[3] + vec.getVec()[3];
}

float vec4::x() const
{
	return vector[0];
}

float vec4::y() const
{
	return vector[1];
}

float vec4::z() const
{
	return vector[2];
}

float vec4::w() const
{
	return vector[3];
}

float vec4::sx(float nx)
{
	vector[0] = nx;
	return vector[0];
}

float vec4::sy(float ny)
{
	vector[1] = ny;
	return vector[1];
}

float vec4::sz(float nz)
{
	vector[2] = nz;
	return vector[2];
}

float vec4::sw(float nw)
{
	vector[3] = nw;
	return vector[4];
}

vec4 vec4::normalise()
{
	return vec4(glm::normalize(vector));
}

void vec4::normailse()
{
	glm::normalize(vector);
}

float vec4::dot(const vec4 & v)
{
	return glm::dot(vector, v.getVec());
}

float vec4::angle(const vec4 & v)
{
	return glm::angle(vector, v.getVec());
}

float& vec4::operator[] (int x)
{
	return vector[x];
}

vec4 vec4::operator* (vec4 vec2)
{
	return vec4(vector * vec2.getVec());
}

vec4 vec4::operator += (const vec4 & v)
{
	vector += v.getVec();
	return *this;
}

vec4 vec4::operator *= (const vec4 & v)
{
	vector *= v.getVec();
	return *this;
}

vec4 vec4::operator /= (const vec4 & v)
{
	vector /= v.getVec();
	return *this;
}

vec4 vec4::operator -= (const vec4 & v)
{
	vector -= v.getVec();
	return *this;
}

vec4 vec4::operator + (const vec4 & v)
{
	return vec4(vector + v.getVec());
}

vec4 vec4::operator - (const vec4 & v)
{
	return vec4(vector - v.getVec());
}

vec4 vec4::operator * (const vec4 & v)
{
	return vec4(vector * v.getVec());
}

vec4 vec4::operator / (const vec4 & v)
{
	return vec4(vector / v.getVec());
}

vec4 vec4::operator += (const float f)
{
	vector += f;
	return *this;
}

vec4 vec4::operator *= (const float f)
{
	vector *= f;
	return *this;
}

vec4 vec4::operator /= (const float f)
{
	vector /= f;
	return *this;
}

vec4 vec4::operator -= (const float f)
{
	vector -= f;
	return *this;
}

vec4 vec4::operator + (const float f)
{
	return vec4(vector + f);
}

vec4 vec4::operator - (const float f)
{
	return vec4(vector - f);
}

vec4 vec4::operator * (const float f)
{
	return vec4(vector * f);
}

vec4 vec4::operator / (const float f)
{
	return vec4(vector / f);
}