#include "FontLoader.h"

bool FontLoader::loadFont(std::string filename, Font & toset, std::string name) {
	std::ifstream infile(filename.c_str());
	if (!infile) return false;

	std::string tmp;

	std::string linehead;

	unsigned tmpu;
	char tmpc;

	while (infile.peek() != EOF) {
		getline(infile, tmp);

		if (tmp.find(",") != std::string::npos) {
				
			linehead = tmp.substr(0, tmp.find(","));
			if (linehead.find(" ") != std::string::npos) linehead = linehead.substr(0, linehead.find(" "));

			if (linehead == IMAGE_WIDTH) {
				tmpu = (unsigned) atoi(tmp.substr(tmp.find(",") + 1).c_str());
				toset.setImgWidth(tmpu);
			}
			else
			if (linehead == IMAGE_HEIGHT) {
				tmpu = (unsigned) atoi(tmp.substr(tmp.find(",") + 1).c_str());
				toset.setImgHeight(tmpu);
			}
			else
			if (linehead == CHAR_WIDTH) {
				tmpu = (unsigned) atoi(tmp.substr(tmp.find(",") + 1).c_str());
				toset.setCharWidth(tmpu);
			}
			else
			if (linehead == CHAR_HEIGHT) {
				tmpu = (unsigned)atoi(tmp.substr(tmp.find(",") + 1).c_str());
				toset.setCharHeight(tmpu);
			}
			else
			if (linehead == START_CHAR) {
				tmpu = (unsigned)atoi(tmp.substr(tmp.find(",") + 1).c_str());
				toset.setStartChar(tmpu);
			}
			else 
			if (linehead == CHAR_BASE_WIDTH) {
				tmpc = (char) atoi(tmp.substr(tmp.find(" ") + 1, tmp.find(",")).c_str());
				tmpu = (unsigned) atoi(tmp.substr(tmp.find(",") + 1).c_str());
				toset.addCharOffsetMapping(tmpc, tmpu);
			}
			else
			if (linehead == TEXTURE) {
				toset.setTexture(tmp.substr(tmp.find(",") + 1));
			}
		}
	}

	if (toset.getTex().empty()) return false;

	return genImgMapping(toset, name);
}

bool FontLoader::genImgMapping(Font & toset, std::string name) {
	if (!TXMAN->loadTempTex(toset.getTex(), "BMP")) return false;

	unsigned xoffset;
	unsigned yoffset;

	unsigned maxx = toset.getImgWidth() / toset.getCharWidth();
	unsigned maxy = toset.getImgHeight() / toset.getCharHeight();

	unsigned curchar = (toset.getImgWidth() / toset.getCharWidth()) * (toset.getImgHeight() / toset.getCharHeight());

	for (unsigned i = 0; i < maxx; i++) {
		xoffset = i * toset.getCharWidth();
		for (unsigned j = 0; j < maxy; j++) {
			curchar = toset.getStartChar() + (i) + ((maxy-j - 1)*maxy);

			yoffset = j * toset.getCharHeight();

			TXMAN->createSubTexFromTemp(name + (char) curchar, toset.getCharWidth(), toset.getCharHeight(), xoffset, yoffset);

			toset.bindCharImg((char) curchar, name + (char) curchar);
		}
	}

	return true;
}
