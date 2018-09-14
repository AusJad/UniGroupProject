#ifndef _H_MATH_VECTORS_
#define _H_MATH_VECTORS_
#include <ostream>

// From Game Physics Cookbook by Gabor Szauer

//#define RAD2DEG(x) ((x) * 57.295754f)
//#define DEG2RAD(x) ((x) * 0.0174533f)

#ifndef RAD2DEG
float RAD2DEG(float radians);
#endif 
#ifndef DEG2RAD
float DEG2RAD(float degrees);
#endif
float CorrectDegrees(float degrees);

/**
* @struct physvec2
*
* @author Game Physics Cookbook
*/
typedef struct physvec2 {
	union {
		struct {
			float x;
			float y;
		};
		float asArray[2];
	};

	inline float& operator[](int i) {
		return asArray[i];
	}

	inline physvec2() : x(0.0f), y(0.0f) { }
	inline physvec2(float _x, float _y) : x(_x), y(_y) { }
} physvec2;

/**
* @struct physvec3
*
* @author Game Physics Cookbook
*/
typedef struct physvec3 {
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float asArray[3];
	};

	inline float& operator[](int i) {
		return asArray[i];
	}

	inline physvec3() : x(0.0f), y(0.0f), z(0.0f) { }
	inline physvec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }

} physvec3;

physvec2 operator+(const physvec2& l, const physvec2& r);
physvec3 operator+(const physvec3& l, const physvec3& r);

physvec2 operator-(const physvec2& l, const physvec2& r);
physvec3 operator-(const physvec3& l, const physvec3& r);

physvec2 operator*(const physvec2& l, const physvec2& r);
physvec3 operator*(const physvec3& l, const physvec3& r);

physvec2 operator*(const physvec2& l, float r);
physvec3 operator*(const physvec3& l, float r);

physvec2 operator/(const physvec2& l, const physvec2& r);
physvec3 operator/(const physvec3& l, const physvec3& r);

physvec2 operator/(const physvec2& l, float r);
physvec3 operator/(const physvec3& l, float r);

std::ostream& operator<<(std::ostream& os, const physvec2& m);
std::ostream& operator<<(std::ostream& os, const physvec3& m);

bool operator==(const physvec2& l, const physvec2& r);
bool operator==(const physvec3& l, const physvec3& r);

bool operator!=(const physvec2& l, const physvec2& r);
bool operator!=(const physvec3& l, const physvec3& r);

physvec2& operator+=(physvec2& l, const physvec2& r);
physvec2& operator-=(physvec2& l, const physvec2& r);
physvec2& operator*=(physvec2& l, const physvec2& r);
physvec2& operator*=(physvec2& l, const float r);
physvec2& operator/=(physvec2& l, const physvec2& r);
physvec2& operator/=(physvec2& l, const float r);

physvec3& operator+=(physvec3& l, const physvec3& r);
physvec3& operator-=(physvec3& l, const physvec3& r);
physvec3& operator*=(physvec3& l, const physvec3& r);
physvec3& operator*=(physvec3& l, const float r);
physvec3& operator/=(physvec3& l, const physvec3& r);
physvec3& operator/=(physvec3& l, const float r);

float Dot(const physvec2& l, const physvec2& r);
float Dot(const physvec3& l, const physvec3& r);

float Magnitude(const physvec2& v);
float Magnitude(const physvec3& v);

float MagnitudeSq(const physvec2& v);
float MagnitudeSq(const physvec3& v);

float Distance(const physvec2& p1, const physvec2& p2);
float Distance(const physvec3& p1, const physvec3& p2);

float DistanceSq(const physvec2& p1, const physvec2& p2);
float DistanceSq(const physvec3& p1, const physvec3& p2);

physvec2 RotateVector(const physvec2& vector, float degrees);

void Normalize(physvec2& v);
void Normalize(physvec3& v);

physvec2 Normalized(const physvec2& v);
physvec3 Normalized(const physvec3& v);

physvec3 Cross(const physvec3& l, const physvec3& r);

float Angle(const physvec2& l, const physvec2& r);
float Angle(const physvec3& l, const physvec3& r);

physvec2 Project(const physvec2& length, const physvec2& direction);
physvec3 Project(const physvec3& length, const physvec3& direction);

physvec2 Perpendicular(const physvec2& length, const physvec2& direction);
physvec3 Perpendicular(const physvec3& length, const physvec3& direction);

physvec2 Reflection(const physvec2& sourceVector, const physvec2& normal);
physvec3 Reflection(const physvec3& sourceVector, const physvec3& normal);

#endif