#include "Wall.h"



Wall::Wall(){
	width = 10;
	height = 10;
	depth = 10;
	angley = 0;
	anglex = 0;
	anglez = 0;
	id.setType("WALL");
}

std::string Wall::toString() {
	std::string out;

	out += "WALL_START\n";
	out += "POS," + std::to_string(trans.x()) + "," + std::to_string(trans.y()) +"," + std::to_string(trans.z()) + "\n";
	out += "DIMENSIONS," + std::to_string(width) + "," + std::to_string(height) + "," + std::to_string(depth) + "\n";
	out += "ANGLE," + std::to_string(anglex) + "," + std::to_string(angley) + "," + std::to_string(anglez) + "\n";
	if (!tex.empty()) out += "TEX," + tex + "\n";
	out += "WALL_END\n";

	return out;
}

void Wall::render() {
	if (!tex.empty()) TXMAN->useTexture(tex, RNDR);

	GeoStream << BEGIN_STREAM << trans_3(trans) << rot_4(anglex, 1, 0, 0) << rot_4(angley, 0, 1, 0) << rot_4(anglez, 0, 0, 1);

	RNDR->DrawRectangularPrism(drawpos, width, height, depth);

	GeoStream << END_STREAM;

	if (!tex.empty()) TXMAN->disableTexture(RNDR);
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
}