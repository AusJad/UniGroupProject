#include "Level.h"



Level::Level()
{
	name = "No Name Defined";
}


void Level::reset() {
	name = "No Name Defined";
	startPos = vec3();
	orentatation = vec2();
}

std::string Level::toString() {
	std::string ret;

	ret += "LEVEL_HEAD\n";
	ret += "NAME," + name + "\n";
	ret += "START_POS," + std::to_string(startPos.x()) + "," + std::to_string(startPos.y()) + "," + std::to_string(startPos.z()) + "\n";
	ret += "START_OR," + std::to_string(orentatation.x()) + "," + std::to_string(orentatation.y()) + "\n";
	ret += "LEVEL_TAIL\n";
	
	return ret;
}

vec3 Level::getStartPos() {
	return startPos;
}

vec2 Level::getStartOrientation() {
	return orentatation;
}

std::string Level::getName() {
	return name;
}

void Level::setStartPos(vec3 & toset) {
	startPos = toset;
}

void Level::setStartOreientation(vec2 toset) {
	orentatation = toset;
}

void Level::setName(std::string toset) {
	name = toset;
}