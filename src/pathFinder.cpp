#include "pathFinder.h"
#include "SceneManager.h"

pathFinder::pathFinder()
{
}

int pathFinder::calcH(AsNode & start, AsNode & target) {
	int distancez = 0;
	int distancex = 0;

	if (start.x > target.x) {
		for (int i = target.x; i <= start.x; i++) {
			distancex++;
		}
	}
	else {
		for (int i = start.x; i <= target.x; i++) {
			distancex++;
		}
	}

	if (start.z > target.z) {
		for (int i = target.z; i <= start.z; i++) {
			distancez++;
		}
	}
	else {
		for (int i = start.z; i <= target.z; i++) {
			distancez++;
		}
	}
	//square the distances for the heuristic
	return ((distancex * distancex) + (distancez * distancez));
}

SimpleStack pathFinder::findpath(std::vector<GameObject*> & objects, vec3 pos, vec3 target){
	
	// SEEN 0
	// OPEN 1
	// CLOSED 2

	//G is the distance between the current node and the start node.
	//H is the estimated distance from the current node to the end node.
	//F is the total cost of the node

	for (int i = 0; i < objects.size(); i++) {
		SM->gridGreyOut(vec2(objects.at(i)->getPos().x(), objects.at(i)->getPos().z()));
	}


	AsNode cSquare;
	AsNode dSquare;
	std::stack<AsNode> path;

	//multi shrinks to a point 1% of grid value
	//inv mutil expands a 1% point back to its true co-ordinate

	float multiX = SM->getGridMultiX();
	float multiZ = SM->getGridMultiZ();
	float invMultiX = 1 / multiX;
	float invMultiZ = 1 / multiZ;

	dSquare.x = (int)(target.x() * multiX);
	dSquare.z = (int)(target.z() * multiZ);
	//std::cout << "dSquare.x: " << dSquare.x << " dSquare.z: " << dSquare.z << std::endl;
	
	//if (SM->gridIsGrey(vec2(((dSquare.x) * invMultiX), (dSquare.z) * invMultiZ))) {
		//std::cout << "Destination is greyed out!!" << std::endl;
	//}


	cSquare.parent = { -1,-1 };
	cSquare.g = 0;
	cSquare.h = calcH(cSquare, dSquare);
	cSquare.f = cSquare.g + cSquare.h;
	cSquare.x = (int)(pos.x() * multiX);
	cSquare.z = (int)(pos.z() * multiZ);

	std::unordered_map<int, std::unordered_map<int, AsNode> > seennodes;
	std::vector<indexpair> openlist;
	std::stack<AsNode> adjacentsquares;
	
	openlist.push_back({ cSquare.z, cSquare.x });
	seennodes[cSquare.z][cSquare.x] = cSquare;

	bool pathfound = false;

	unsigned currind;

	do {
		cSquare = seennodes.at(openlist.at(0).z).at(openlist.at(0).x);
		currind = 0;

		for (unsigned i = 1; i < openlist.size(); i++) {
			if (seennodes.at(openlist.at(i).z).at(openlist.at(i).x).f < cSquare.f)
			{
				currind = i;
				cSquare = seennodes.at(openlist.at(i).z).at(openlist.at(i).x);
			}
		}

		seennodes[cSquare.z][cSquare.x].status = CLOSED;

		openlist.erase(openlist.begin() + currind);

		AsNode temp;
		//std::cout << "Reaching Here" << std::endl;
		bool isGrey = SM->gridIsGrey(vec2(((cSquare.x + 1) * invMultiX), (cSquare.z) * invMultiZ));
		//std::cout << "isGrey returned " << SM->gridIsGrey(vec2(((cSquare.x + 1) * invMultiX), (cSquare.z) * invMultiZ)) << " in the 8th test for x: " << (cSquare.x + 1) << " z: " << (cSquare.z) << std::endl;
		if (!isGrey && (-100 < cSquare.x + 1 < 100) && (-100 < cSquare.z < 100) || ((cSquare.x + 1 == dSquare.x) && (cSquare.z == dSquare.z))) {
			temp.x = cSquare.x + 1;
			temp.z = cSquare.z;
			temp.g = cSquare.g + 1;
			temp.h = calcH(temp, dSquare);
			temp.f = temp.g + temp.h;
			temp.parent = { cSquare.z, cSquare.x };
			adjacentsquares.push(temp);
			//std::cout << "1st temp.x" << temp.x << " 1st temp.z: " << temp.z << std::endl;
		}

		isGrey = SM->gridIsGrey(vec2(((cSquare.x - 1) * invMultiX), ((cSquare.z) * invMultiZ)));
		//std::cout << "isGrey returned " << SM->gridIsGrey(vec2(((cSquare.x - 1) * invMultiX), ((cSquare.z) * invMultiZ))) << " in the 8th test for x: " << (cSquare.x - 1) << " z: " << (cSquare.z) << std::endl;
		if (!isGrey && (-100 < cSquare.x - 1 < 100) && (-100 < cSquare.z < 100) || ((cSquare.x - 1 == dSquare.x) && (cSquare.z == dSquare.z))) {
			temp.x = cSquare.x - 1;
			temp.z = cSquare.z;
			temp.g = cSquare.g + 1;
			temp.h = calcH(temp, dSquare);
			temp.f = temp.g + temp.h;
			temp.parent = { cSquare.z, cSquare.x };
			adjacentsquares.push(temp);
			//std::cout << "2nd temp.x" << temp.x << " 2nd temp.z: " << temp.z << std::endl;
		}

		isGrey = SM->gridIsGrey(vec2(((cSquare.x) * invMultiX), ((cSquare.z + 1) * invMultiZ)));
		//std::cout << "isGrey returned " << SM->gridIsGrey(vec2(((cSquare.x) * invMultiX), ((cSquare.z + 1) * invMultiZ))) << " in the 8th test for x: " << (cSquare.x) << " z: " << (cSquare.z + 1) << std::endl;
		if (!isGrey && (-100 < cSquare.x < 100) && (-100 < cSquare.z + 1 < 100) || ((cSquare.x == dSquare.x) && (cSquare.z + 1 == dSquare.z))) {
			temp.x = cSquare.x;
			temp.z = cSquare.z + 1;
			temp.g = cSquare.g + 1;
			temp.h = calcH(temp, dSquare);
			temp.f = temp.g + temp.h;
			temp.parent = { cSquare.z, cSquare.x };
			adjacentsquares.push(temp);
			//std::cout << "3rd temp.x" << temp.x << " 3rd temp.z: " << temp.z << std::endl;
		}

		isGrey = SM->gridIsGrey(vec2((cSquare.x * invMultiX), ((cSquare.z - 1)*invMultiZ)));
		//std::cout << "isGrey returned " << SM->gridIsGrey(vec2((cSquare.x * invMultiX), ((cSquare.z - 1)*invMultiZ))) << " in the 8th test for x: " << (cSquare.x) << " z: " << (cSquare.z - 1) << std::endl;
		if (!isGrey && (-100 < cSquare.x < 100) && (-100 < cSquare.z - 1 < 100) || ((cSquare.x == dSquare.x) && (cSquare.z - 1 == dSquare.z))) {
			temp.x = cSquare.x;
			temp.z = cSquare.z - 1;
			temp.g = cSquare.g + 1;
			temp.h = calcH(temp, dSquare);
			temp.f = temp.g + temp.h;
			temp.parent = { cSquare.z, cSquare.x };
			adjacentsquares.push(temp);
			//std::cout << "4th temp.x" << temp.x << " 4th temp.z: " << temp.z << std::endl;

		}

		isGrey = SM->gridIsGrey(vec2(((cSquare.x + 1)*invMultiX), ((cSquare.z - 1)*invMultiZ)));
		//std::cout << "isGrey returned " << SM->gridIsGrey(vec2(((cSquare.x + 1)*invMultiX), ((cSquare.z - 1)*invMultiZ))) << " in the 8th test for x: " << (cSquare.x + 1) << " z: " << (cSquare.z - 1) << std::endl;
		if (!isGrey && (-100 < cSquare.x + 1 < 100) && (-100 < cSquare.z - 1 < 100) || ((cSquare.x + 1 == dSquare.x) && (cSquare.z - 1 == dSquare.z))) {
			temp.x = cSquare.x + 1;
			temp.z = cSquare.z - 1;
			temp.g = cSquare.g + 1;
			temp.h = calcH(temp, dSquare);
			temp.f = temp.g + temp.h;
			temp.parent = { cSquare.z, cSquare.x };
			adjacentsquares.push(temp);
			//std::cout << "5th temp.x" << temp.x << " 5th temp.z: " << temp.z << std::endl;
		}

		isGrey = SM->gridIsGrey(vec2(((cSquare.x - 1)*invMultiX), ((cSquare.z - 1)*invMultiZ)));
		//std::cout << "isGrey returned " << SM->gridIsGrey(vec2(((cSquare.x - 1)*invMultiX), ((cSquare.z - 1)*invMultiZ))) << " in the 8th test for x: " << (cSquare.x - 1) << " z: " << (cSquare.z - 1) << std::endl;
		if (!isGrey && (-100 < cSquare.x - 1 < 100) && (-100 < cSquare.z - 1 < 100) || ((cSquare.x - 1 == dSquare.x) && (cSquare.z - 1 == dSquare.z))) {
			temp.x = cSquare.x - 1;
			temp.z = cSquare.z - 1;
			temp.g = cSquare.g + 1;
			temp.h = calcH(temp, dSquare);
			temp.f = temp.g + temp.h;
			temp.parent = { cSquare.z, cSquare.x };
			adjacentsquares.push(temp);
			//std::cout << "6th temp.x" << temp.x << " 6th temp.z: " << temp.z << std::endl;

		}

		isGrey = SM->gridIsGrey(vec2(((cSquare.x + 1)*invMultiX), ((cSquare.z + 1)*invMultiZ)));
		//std::cout << "isGrey returned " << SM->gridIsGrey(vec2(((cSquare.x + 1)*invMultiX), ((cSquare.z + 1)*invMultiZ))) << " in the 8th test for x: " << (cSquare.x + 1) << " z: " << (cSquare.z + 1) << std::endl;
		if (!isGrey && (-100 < cSquare.x + 1 < 100) && (-100 < cSquare.z + 1 < 100) || ((cSquare.x + 1 == dSquare.x) && (cSquare.z + 1 == dSquare.z))) {
			temp.x = cSquare.x + 1;
			temp.z = cSquare.z + 1;
			temp.g = cSquare.g + 1;
			temp.h = calcH(temp, dSquare);
			temp.f = temp.g + temp.h;
			temp.parent = { cSquare.z, cSquare.x };
			adjacentsquares.push(temp);
			//std::cout << "7th temp.x" << temp.x << " 7th temp.z: " << temp.z << std::endl;
		}

		isGrey = SM->gridIsGrey(vec2(((cSquare.x - 1)*invMultiX), ((cSquare.z + 1)*invMultiZ)));
		//isGrey = SM->gridIsGrey(tmpvec2);
		//std::cout << "isGrey returned " << SM->gridIsGrey(vec2(((cSquare.x - 1)*invMultiX), ((cSquare.z + 1)*invMultiZ))) << " in the 8th test for x: " << (cSquare.x - 1) << " z: " << (cSquare.z + 1) << std::endl;
		if (!isGrey && (-100 < cSquare.x - 1 < 100) && (-100 < cSquare.z + 1 < 100) || ((cSquare.x - 1 == dSquare.x) && (cSquare.z + 1 == dSquare.z))){
				temp.x = cSquare.x - 1;
				temp.z = cSquare.z + 1;
				temp.g = cSquare.g + 1;
				temp.h = calcH(temp, dSquare);
				temp.f = temp.g + temp.h;
				temp.parent = { cSquare.z, cSquare.x };
				adjacentsquares.push(temp);
				//std::cout << "8th temp.x" << temp.x << " 8th temp.z: " << temp.z << std::endl;
		}

		while (!adjacentsquares.empty()) {
			if (seennodes.find(adjacentsquares.top().z) != seennodes.end()) {
				if (seennodes.at(adjacentsquares.top().z).find(adjacentsquares.top().x) != seennodes.at(adjacentsquares.top().z).end()) {
					if (seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).status == OPEN && seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).g > adjacentsquares.top().g) {
						seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).parent = adjacentsquares.top().parent;
						seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).g = cSquare.g + 1;
						seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).h = calcH(seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x), dSquare);
						seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).f = seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).g + seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).h;
						openlist.push_back({ adjacentsquares.top().z, adjacentsquares.top().x });
					}
				}
			}

			if (seennodes.find(adjacentsquares.top().z) == seennodes.end()) {
				seennodes[adjacentsquares.top().z][adjacentsquares.top().x] = adjacentsquares.top();
				seennodes[adjacentsquares.top().z][adjacentsquares.top().x].status = OPEN;
				openlist.push_back({ adjacentsquares.top().z, adjacentsquares.top().x });
			}
			else
				if (seennodes.at(adjacentsquares.top().z).find(adjacentsquares.top().x) == seennodes.at(adjacentsquares.top().z).end()) {
					seennodes[adjacentsquares.top().z][adjacentsquares.top().x] = adjacentsquares.top();
					seennodes[adjacentsquares.top().z][adjacentsquares.top().x].status = OPEN;
					openlist.push_back({ adjacentsquares.top().z, adjacentsquares.top().x });
				}

			adjacentsquares.pop();
		}

		if (seennodes.find(dSquare.z) != seennodes.end()) {
			if (seennodes.at(dSquare.z).find(dSquare.x) != seennodes.at(dSquare.z).end()) {
				pathfound = true;
				//std::cout << "Path found" << std::endl;
			}
		}

	} while (!pathfound && !openlist.empty());

	if (!pathfound) { std::cout << "path not found " << std::endl; };
	if (openlist.empty()) { std::cout << "openlist empty " << std::endl; };
	if (!openlist.empty()) {
		
		indexpair parent = seennodes.at(dSquare.z).at(dSquare.x).parent;

		while (parent.z != -1)
		{
			path.push(seennodes.at(parent.z).at(parent.x));
			parent = path.top().parent;
			path.top().x = path.top().x * invMultiX;
			path.top().z = path.top().z * invMultiZ;
		}

		if (!path.empty()) path.pop();
	}

	SimpleStack vec3pathtmp;
	SimpleStack vec3path;

	while(!path.empty()) {
		//std::cout << "path not empty" << std::endl;
		//std::cout << path.top().x << " " << path.top().z << std::endl;
		vec3pathtmp.push(vec3(path.top().x, 0, path.top().z));
		path.pop();
		vec3path.push(vec3pathtmp.top());
		vec3pathtmp.pop();
	}

	
	return vec3path;

};
