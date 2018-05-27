#include "pathFinder.h"
#include "SceneManager.h"

pathFinder::pathFinder()
{
}

SimpleStack<vec2> pathFinder::findpath(std::vector<GameObject*> & objects, GameObject* & pathfor, vec2 target){
	//Need to get access to grid in scene object withing Scenemanager's scene vector, for current scene

	//SceneManager *tmp = Singleton<SceneManager>::getInstance();
	//tmp->
	SimpleStack<vec2> path;
	return path;
}
