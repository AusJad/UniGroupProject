#include "Compare.h"
#include "vectors.h"
#include <cmath>
#include <cfloat>

float CorrectDegrees(float degrees) {
	while (degrees > 360.0f) {
		degrees -= 360.0f;
	}
	while (degrees < -360.0f) {
		degrees += 360.0f;
	}
	return degrees;
}

#ifndef RAD2DEG
float RAD2DEG(float radians) {
	float degrees = radians * 57.295754f;
	degrees = CorrectDegrees(degrees);
	return degrees;
}
#endif
#ifndef DEG2RAD
float DEG2RAD(float degrees) {
	degrees = CorrectDegrees(degrees);
	float radians = degrees * 0.0174533f;
	return radians;
}
#endif

bool operator==(const physvec2& l, const physvec2& r) {
	return CMP(l.x, r.x) && CMP(l.y, r.y);
}

bool operator==(const physvec3& l, const physvec3& r) {
	return CMP(l.x, r.x) && CMP(l.y, r.y) && CMP(l.z, r.z);
}

bool operator!=(const physvec2& l, const physvec2& r) {
	return !(l == r);
}

bool operator!=(const physvec3& l, const physvec3& r) {
	return !(l == r);
}

physvec2 operator+(const physvec2& l, const physvec2& r) {
	return{ l.x + r.x, l.y + r.y };
}

physvec3 operator+(const physvec3& l, const physvec3& r) {
	return{ l.x + r.x, l.y + r.y, l.z + r.z };
}

physvec2 operator-(const physvec2& l, const physvec2& r) {
	return{ l.x - r.x, l.y - r.y };
}

physvec3 operator-(const physvec3& l, const physvec3& r) {
	return{ l.x - r.x, l.y - r.y, l.z - r.z };
}

physvec2 operator*(const physvec2& l, const physvec2& r) {
	return{ l.x * r.x, l.y * r.y };
}

physvec3 operator*(const physvec3& l, const physvec3& r) {
	return{ l.x * r.x, l.y * r.y, l.z * r.z };
}

physvec2 operator*(const physvec2& l, float r) {
	return{ l.x * r, l.y * r };
}

physvec3 operator*(const physvec3& l, float r) {
	return{ l.x * r, l.y * r, l.z * r };
}

physvec2 operator/(const physvec2& l, const physvec2& r) {
	return{ l.x / r.x, l.y / r.y };
}

physvec3 operator/(const physvec3& l, const physvec3& r) {
	return{ l.x / r.x, l.y / r.y, l.z / r.z };
}

physvec2 operator/(const physvec2& l, float r) {
	return{ l.x / r, l.y / r };
}

physvec3 operator/(const physvec3& l, float r) {
	return{ l.x / r, l.y / r, l.z / r };
}

std::ostream& operator<<(std::ostream& os, const physvec2& m) {
	os << "(" << m.x << ", " << m.y << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const physvec3& m) {
	os << "(" << m.x << ", " << m.y << ", " << m.z << ")";
	return os;
}

float Dot(const physvec2& l, const physvec2& r) {
	return l.x * r.x + l.y * r.y;
}

float Dot(const physvec3& l, const physvec3& r) {
	return l.x * r.x + l.y * r.y + l.z * r.z;
}

physvec2& operator+=(physvec2& l, const physvec2& r) {
	l.x += r.x;
	l.y += r.y;
	return l;
}

physvec2& operator-=(physvec2& l, const physvec2& r) {
	l.x -= r.y;
	l.y -= r.y;
	return l;
}

physvec2& operator*=(physvec2& l, const physvec2& r) {
	l.x *= r.x;
	l.y *= r.y;
	return l;
}

physvec2& operator*=(physvec2& l, const float r) {
	l.x *= r;
	l.y *= r;
	return l;
}

physvec2& operator/=(physvec2& l, const physvec2& r) {
	l.x /= r.x;
	l.y /= r.y;
	return l;
}

physvec2& operator/=(physvec2& l, const float r) {
	l.x /= r;
	l.y /= r;
	return l;
}

physvec3& operator+=(physvec3& l, const physvec3& r) {
	l.x += r.x;
	l.y += r.y;
	l.z += r.z;
	return l;
}

physvec3& operator-=(physvec3& l, const physvec3& r) {
	l.x -= r.x;
	l.y -= r.y;
	l.z -= r.z;
	return l;
}

physvec3& operator*=(physvec3& l, const physvec3& r) {
	l.x *= r.x;
	l.y *= r.y;
	l.z *= r.z;
	return l;
}

physvec3& operator*=(physvec3& l, const float r) {
	l.x *= r;
	l.y *= r;
	l.z *= r;
	return l;
}

physvec3& operator/=(physvec3& l, const physvec3& r) {
	l.x /= r.x;
	l.y /= r.y;
	l.z /= r.z;
	return l;
}

physvec3& operator/=(physvec3& l, const float r) {
	l.x /= r;
	l.y /= r;
	l.z /= r;
	return l;
}

float Magnitude(const physvec2& v) {
	return sqrtf(Dot(v, v));
}

float Magnitude(const physvec3& v) {
	return sqrtf(Dot(v, v));
}

float MagnitudeSq(const physvec2& v) {
	return Dot(v, v);
}

float MagnitudeSq(const physvec3& v) {
	return Dot(v, v);
}

float Distance(const physvec2& p1, const physvec2& p2) {
	return Magnitude(p1 - p2);
}

float Distance(const physvec3& p1, const physvec3& p2) {
	return Magnitude(p1 - p2);
}

float DistanceSq(const physvec2& p1, const physvec2& p2) {
	return MagnitudeSq(p1 - p2);
}

float DistanceSq(const physvec3& p1, const physvec3& p2) {
	return MagnitudeSq(p1 - p2);
}

physvec2 RotateVector(const physvec2& vector, float degrees) {
	degrees = DEG2RAD(degrees);
	float s = sinf(degrees);
	float c = cosf(degrees);

	return physvec2(
		vector.x * c - vector.y * s,
		vector.x * s + vector.y * c
	);
}

void Normalize(physvec2& v) {
	v = v * (1.0f / Magnitude(v));
}

void Normalize(physvec3& v) {
	v = v * (1.0f / Magnitude(v));
}

physvec2 Normalized(const physvec2& v) {
	return v * (1.0f / Magnitude(v));
}
physvec3 Normalized(const physvec3& v) {
	return v * (1.0f / Magnitude(v));
}

physvec3 Cross(const physvec3& l, const physvec3& r) {
	physvec3 result;
	result.x = l.y * r.z - l.z * r.y;
	result.y = l.z * r.x - l.x * r.z;
	result.z = l.x * r.y - l.y * r.x;
	return result;
}

float Angle(const physvec2& l, const physvec2& r) {
	return acosf(Dot(l, r) / sqrtf(MagnitudeSq(l) * MagnitudeSq(r)));
}

float Angle(const physvec3& l, const physvec3& r) {
	return acosf(Dot(l, r) / sqrtf(MagnitudeSq(l) * MagnitudeSq(r)));
}

physvec2 Project(const physvec2& length, const physvec2& direction) {
	float dot = Dot(length, direction);
	float magSq = MagnitudeSq(direction);
	return direction * (dot / magSq);
}

physvec3 Project(const physvec3& length, const physvec3& direction) {
	float dot = Dot(length, direction);
	float magSq = MagnitudeSq(direction);
	return direction * (dot / magSq);
}

physvec2 Perpendicular(const physvec2& length, const physvec2& direction) {
	return length - Project(length, direction);
}

physvec3 Perpendicular(const physvec3& length, const physvec3& direction) {
	return length - Project(length, direction);
}

physvec2 Reflection(const physvec2& sourceVector, const physvec2& normal) {
	return sourceVector - normal * (Dot(sourceVector, normal) *  2.0f);
}

physvec3 Reflection(const physvec3& sourceVector, const physvec3& normal) {
	return sourceVector - normal * (Dot(sourceVector, normal) *  2.0f);
}
