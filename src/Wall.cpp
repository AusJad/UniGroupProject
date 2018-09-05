#include "Wall.h"

bool Wall::drawBounds = false;
void Wall::toggleDrawBounds() {
	Wall::drawBounds = !Wall::drawBounds;
}

void Wall::DisableBB() {
	Wall::drawBounds = false;
}

bool Wall::boundsVis() {
	return Wall::drawBounds;
}


Wall::Wall(){
	width = 10;
	height = 10;
	depth = 10;
	angley = 0;
	anglex = 0;
	anglez = 0;
	id.setType("WALL");
	texrepx = 1;
	texrepy = 1;
	hasCol = true;
}

std::string Wall::toString() {
	std::string out;

	out += "WALL_START\n";
	out += "POS," + std::to_string(trans.x()) + "," + std::to_string(trans.y()) +"," + std::to_string(trans.z()) + "\n";
	out += "DIMENSIONS," + std::to_string(width) + "," + std::to_string(height) + "," + std::to_string(depth) + "\n";
	out += "ANGLE," + std::to_string(anglex) + "," + std::to_string(angley) + "," + std::to_string(anglez) + "\n";
	if (!tex.empty()) out += "TEX," + tex + "\n";
	if (hasCol) out += "COL,1\n";
	else out += "COL,0\n";
	out += "TEXCOORD," + std::to_string(texrepx) + "," + std::to_string(texrepy) + "\n";
	out += "WALL_END\n";

	return out;
}

void Wall::render() {
	if (!tex.empty()) TXMAN->useTexture(tex, RNDR);

	GeoStream << BEGIN_STREAM << trans_3(trans) << rot_4(anglex, 1, 0, 0) << rot_4(angley, 0, 1, 0) << rot_4(anglez, 0, 0, 1);

	RNDR->DrawRectangularPrism(drawpos, width, height, depth, texrepx, texrepy);

	GeoStream << END_STREAM;

	if (!tex.empty()) TXMAN->disableTexture(RNDR);

	if (drawBounds) {
		GeoStream << START_ATTRIB << color_3(1.0f, 0.5f, 0.0f);
		aabb.render(vec3());
		GeoStream << END_ATTRIB;
	}
}

Wall::Wall(const Wall & tocpy) : GameObject(*this) {
	width = tocpy.width;
	height = tocpy.height;
	depth = tocpy.depth;
	trans = tocpy.trans;
	tex = tocpy.tex;
	angley = tocpy.angley;
	anglex = tocpy.anglex;
	anglez = tocpy.anglez;
	texrepx = tocpy.texrepx;
	texrepy = tocpy.texrepy;
	hasCol = tocpy.hasCol;
}