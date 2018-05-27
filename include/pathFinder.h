#pragma once
#include <SimpleStack.h>
#include <vector>
#include <vec2.h>
#include <GameObject.h>
class pathFinder
{
public:
	pathFinder();
	SimpleStack<vec2> findpath(std::vector<GameObject*> & objects, GameObject* & pathfor, vec2 target);
};

