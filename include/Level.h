#pragma once
#include "Singleton.h"
#include "vec3.h"
#include "vec2.h"

#define LVL Singleton<Level>::getInstance()

class Level
{
public:
	Level();
	std::string toString();
	vec3 getStartPos();
	vec2 getStartOrientation();
	std::string getName();
	void setStartPos(vec3 & toset);
	void setStartOreientation(vec2 toset);
	void setName(std::string toset);
	void reset();

private:
	vec3 startPos;
	vec2 orentatation;
	std::string name;
};

