#include "TexturedSquare.h"

TexturedSquare::TexturedSquare()
{
}


TexturedSquare * TexturedSquare::create() const {
	TexturedSquare * tmp = new TexturedSquare();
	tmp->br = this->br;
	tmp->tl = this->tl;
	tmp->texture = this->texture;
	tmp->verts = this->verts;
	tmp->id = this->id;

	return tmp;
}

bool TexturedSquare::loadModel(std::string filename) {
	std::ifstream infile(filename.c_str());
	if (!infile) return false;
	
	std::string tmp;
	char linehead;

	while (infile.peek() != EOF) {
		getline(infile, tmp);
		linehead = tmp.at(0);
		tmp = tmp.substr(tmp.find(" ") + 1);
		
		switch (linehead) {
			case 't':
				texture = RandomString(25);
				if (Singleton<TextureManager>::getInstance()->loadNewTexture(tmp, "BMP", texture, Singleton<RenderModuleStubb>::getInstance()) == false)
					texture = "";
				break;
			case 'l':
				tl.sx((float)atof(tmp.substr(0, tmp.find(" ")).c_str()));
				tmp = tmp.substr(tmp.find(" ") + 1);
				tl.sy((float)atof(tmp.c_str()));
				break;
			case 'b':
				br.sx((float)atof(tmp.substr(0, tmp.find(" ")).c_str()));
				tmp = tmp.substr(tmp.find(" ") + 1);
				br.sy((float)atof(tmp.c_str()));
				break;
		}
	}

	return true;
}

void TexturedSquare::update(float time) {

}

void TexturedSquare::render(const vec3 & transmat) {
	if (texture.empty() == false) Singleton<TextureManager>::getInstance()->useTexture(texture, Singleton<RenderModuleStubb>::getInstance());
	Singleton<RenderModuleStubb>::getInstance()->DrawQuad(point(br.x(), tl.y()), point(tl.x(), br.y()), -3);
	Singleton<TextureManager>::getInstance()->disableTexture(Singleton<RenderModuleStubb>::getInstance());
}

void TexturedSquare::centerOnPoint(vec3 & point) {

}

std::vector<vec3>& TexturedSquare::getVerticies() {
	verts.clear();
	verts.push_back(vec3(tl.x(), tl.y(), -1));
	verts.push_back(vec3(br.x(), br.y(), -1));
	return verts;
}

void TexturedSquare::setScale(vec3 & toset) {
	tl *= vec2(toset.x(), toset.y());
	br *= vec2(toset.x(), toset.y());
}

std::string TexturedSquare::RandomString(unsigned len) {
	std::string tmp;

	for (unsigned i = 0; i < len; ++i) {
		tmp.push_back((char)97 + (rand() % static_cast<int>(122 - 97 + 1)));
	}

	return tmp;
}