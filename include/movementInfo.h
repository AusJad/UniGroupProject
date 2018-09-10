#pragma once

#include "vec2.h"
/**
* @struct movementInfo
*
* @author Morgan Smolder
*/
struct movementInfo {
	vec2 inital;
	vec2 offset;
	bool moving;
	movementInfo() { moving = false; }
};