#pragma once

#define GLFW_INCLUDE_GLU 
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32
#include "gl/glew.h"
#include "glfw/glfw3.h"
#include "GLFW/glfw3native.h"
#include "vec3.h"

struct vertex_3{
	float x,y,z;
	vertex_3() : x(0), y(0), z(0) {};
	vertex_3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {};
};

struct texCoord_2{
	float x, y;
	texCoord_2() : x(0), y(0) {};
	texCoord_2(float nx, float ny) : x(nx), y(ny) {};
};

struct normal_3 {
	float x, y, z;
	normal_3() : x(0), y(0), z(0) {};
	normal_3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {};
};

struct trans_3 {
	float x, y, z;
	trans_3() : x(0), y(0), z(0) {};
	trans_3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {};
	trans_3(const vec3 & tocpy) : x(tocpy.x()), y(tocpy.y()), z(tocpy.z()) {};
};

struct rot_4 {
	float x, y, z, w;
	rot_4() : x(0), y(0), z(0), w(0) {};
	rot_4(float nx, float ny, float nz, float nw) : x(nx), y(ny), z(nz), w(nw) {};
};

struct color_3{
	float r, g, b;
	color_3() : r(0), g(0), b(0) {};
	color_3(float nx, float ny, float nz) : r(nx), g(ny), b(nz) {};
};

struct color_4 {
	float r, g, b, a;
	color_4() : r(0), g(0), b(0) {};
	color_4(float nx, float ny, float nz, float na) : r(nx), g(ny), b(nz), a(na) {};
};

#define BEGIN_STREAM 1
#define END_STREAM 2
#define END_PRIMITIVES 3
#define START_PRIMITIVE_TRI 4
#define START_ATTRIB 5
#define END_ATTRIB 6
#define ENFORCE_POLYGON_MODE_SOLID 7
#define RESTORE_POLYGON_MODE 8
#define POLY_MODE_CHANGED 9
#define POLY_MODE_CONST 10
#define ENABLE_ALPHA 11
#define DISABLE_ALPHA 12
#define ENABLE_TRANSPARENCY 13
#define DISABLE_TRANSPARENCY 14
#define ENABLE_LIGHTING 15
#define DISABLE_LIGHTING 16

class GeometeryStream
{
public:
	const GeometeryStream & operator << (const vertex_3 & rhs) const;
	const GeometeryStream & operator << (const texCoord_2 & rhs) const;
	const GeometeryStream & operator << (const normal_3 & rhs) const;
	const GeometeryStream & operator << (const trans_3 & rhs) const;
	const GeometeryStream & operator << (const rot_4 & rhs) const;
	const GeometeryStream & operator << (const color_3 & rhs) const;
	const GeometeryStream & operator << (const color_4 & rhs) const;
	GeometeryStream & operator << (int rhs);
private:
	int polymodeflag = POLY_MODE_CONST;
};

