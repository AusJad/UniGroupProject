#include "..\include\pathFinderGrid.h"

pathFinderGrid::pathFinderGrid()
{
	scaleisSet = false;
}

void pathFinderGrid::greyOut(vec2 pos) {
	float tmpx = pos.x() * nodeMutliX;
	float tmpy = pos.y() * nodeMultiZ;
	int tmpxi = (int)tmpx;
	int tmpyi = (int)tmpy;
	//std::cout << "Greying out x: " << tmpxi << " z: " << tmpyi << std::endl;
	grid[tmpxi][tmpyi] = 2;
};

bool pathFinderGrid::isGrey(vec2 pos) {
	float tmpx = (float)pos.x() * nodeMutliX;
	float tmpy = (float)pos.y() * nodeMultiZ;
	int tmpxi = (int)tmpx;
	int tmpyi = (int)tmpy;
	
	if (grid[tmpxi][tmpyi] == 2) {
		//std::cout << "Retured isGrey true for x: " << tmpxi << " z: " << tmpyi << std::endl;
		return true;
	}
	else
	{
		//std::cout << "Retured isGrey false for x: " << tmpxi << " z: " << tmpyi << std::endl;
		return false;
	}
}

bool pathFinderGrid::setGridScale(int xmin, int xmax, int ymin, int ymax) {
	//expensive, but only needs to be done once
	nodeMutliX = 1 / (float)((xmax - xmin) / 100.0f);
	nodeMultiZ = 1 / (float)((ymax - ymin) / 100.0f);
	scaleisSet = true;
	std::cout << "xmax: " << xmax << " xmin " << xmin << "\n"<< std::endl;
	std::cout << "Grid Multipliers are: " << nodeMutliX << " and " << nodeMultiZ << std::endl;
	return true;
}

