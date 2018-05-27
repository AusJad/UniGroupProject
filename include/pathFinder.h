#pragma once
#include <SimpleStack.h>
#include <vector>
#include <vec2.h>
#include <GameObject.h>
#include <unordered_map>

#define SEEN 0
#define OPEN 1
#define CLOSED 2

struct indexpair {
	indexpair(int nz, int nx) : x(nx), z(nz) {};
	int x;
	int z;
};

struct AsNode {
	AsNode() : f(0), g(0), h(0), x(0), z(0), parent(-1, -1), status(SEEN) {};
	AsNode(int nx, int nz) : f(0), g(0), h(0), x(nx), z(nz), parent(-1, -1), status(SEEN) {};
	int f;
	int g;
	int h;
	int x;
	int z;
	indexpair parent;
	int status;
};

class pathFinder
{
public:
	pathFinder();
	SimpleStack<vec3> findpath(std::vector<GameObject*> & objects, vec3 pos, vec3 target);

private:
	static int calcH(AsNode & start, AsNode & target);
};

