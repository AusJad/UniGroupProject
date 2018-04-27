#include "vec3.h"

vec3::vec3()
{

}

vec3::vec3(float x, float y, float z)
{
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
}

vec3::vec3(const vec4 & v4)
{
	vector = v4.getVec();
}

vec3::vec3(const vec3 & v)
{
	vector = v.getVec();
}

glm::vec3 vec3::getVec() const
{
	return vector;
}
void vec3::setVec(glm::vec3 vec)
{
	vector = vec;
}

float vec3::x() const
{
	return vector[0];
}

float vec3::y() const
{
	return vector[1];
}

float vec3::z() const
{
	return vector[2];
}

float vec3::sx(float nx)
{
	vector[0] = nx;
	return vector[0];
}

float vec3::sy(float ny)
{
	vector[1] = ny;
	return vector[1];
}

float vec3::sz(float nz)
{
	vector[2] = nz;
	return vector[2];
}

void vec3::add(vec3 vec)
{
	vector[0] = vector[0] + vec.getVec()[0];
	vector[1] = vector[1] + vec.getVec()[1];
	vector[2] = vector[2] + vec.getVec()[2];
}

void vec3::subtract(vec3 vec)
{
	vector[0] = vector[0] - vec.getVec()[0];
	vector[1] = vector[1] - vec.getVec()[1];
	vector[2] = vector[2] - vec.getVec()[2];
}

const vec3 & vec3::normailse()
{
	this->vector = glm::normalize(this->vector);
	return *this;
}

float vec3::dot(const vec3 & v)
{
	return glm::dot(vector, v.getVec());
}

float vec3::angle(const vec3 & v)
{
	return glm::angle(vector, v.getVec());
}

vec3 vec3::cross(const vec3 & v)
{
	glm::vec3 tmpglm = glm::cross(vector, v.getVec());
	vec3 tmp;
	tmp.setVec(tmpglm);
	return tmp;
}

bool vec3::almostEqual(const vec3 & v, float threshold)
{
	return(abs(v.getVec()[0] - vector[0]) < threshold && abs(v.getVec()[1] - vector[1]) < threshold && abs(v.getVec()[2] - vector[2]) < threshold);
}

void vec3::operator = (const vec3 & v)
{
	vector = v.getVec();
}

vec3 vec3::operator *= (const vec3 & v)
{
	vector *= v.getVec();
	return *this;
}

vec3 vec3::operator /= (const vec3 & v)
{
	vector /= v.getVec();
	return *this;
}

vec3 vec3::operator -= (const vec3 & v)
{
	vector -= v.getVec();
	return *this;
}

vec3 vec3::operator += (const vec3 & v)
{
	vector += v.getVec();
	return *this;
}

vec3 vec3::operator + (const vec3 & v)
{
	vec3 tmp;
	tmp.setVec(vector + v.getVec());
	return tmp;
}

vec3 vec3::operator - (const vec3 & v)
{
	vec3 tmp;
	tmp.setVec(vector - v.getVec());
	return tmp;
}

vec3 vec3::operator * (const vec3 & v)
{
	vec3 tmp;
	tmp.setVec(vector * v.getVec());
	return tmp;
}

vec3 vec3::operator / (const vec3 & v)
{
	vec3 tmp;
	tmp.setVec(vector / v.getVec());
	return tmp;
}

vec3 vec3::operator += (const float f)
{
	vector += f;
	return *this;
}

vec3 vec3::operator *= (const float f)
{
	vector *= f;
	return *this;
}

vec3 vec3::operator /= (const float f)
{
	vector /= f;
	return *this;
}

vec3 vec3::operator -= (const float f)
{
	vector -= f;
	return *this;
}

vec3 vec3::operator + (const float f)
{
	vec3 tmp;
	tmp.setVec(vector + f);
	return tmp;
}

vec3 vec3::operator - (const float f)
{
	vec3 tmp;
	tmp.setVec(vector - f);
	return tmp;
}

vec3 vec3::operator * (const float f)
{
	vec3 tmp;
	tmp.setVec(vector * f);
	return tmp;
}

vec3 vec3::operator / (const float f)
{
	vec3 tmp;
	tmp.setVec(vector / f);
	return tmp;
}

vec3 vec3::operator- ()
{
	vec3 tmp;
	tmp.setVec(-vector);
	return tmp;
}

float& vec3::operator[] (int x)
{
	return vector[x];
}

float vec3::getLength() {
	return vector.length();
}