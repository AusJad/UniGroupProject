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
	grid[tmpxi][tmpyi] = 2;
};

bool pathFinderGrid::isGrey(vec2 pos) {
	float tmpx = (float)pos.x() * nodeMutliX;
	float tmpy = (float)pos.y() * nodeMultiZ;
	int tmpxi = (int)tmpx;
	int tmpyi = (int)tmpy;
	
	if (grid[tmpxi][tmpyi] == 2) {
		return true;
	}
	else
	{
		return false;
	}
}

bool pathFinderGrid::setGridScale(int xmin, int xmax, int ymin, int ymax) {
	nodeMutliX = 1 / (float)((xmax - xmin) / 100.0f);
	nodeMultiZ = 1 / (float)((ymax - ymin) / 100.0f);
	scaleisSet = true;
	return true;
}

