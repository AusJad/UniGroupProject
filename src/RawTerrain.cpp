#include "RAWTerrain.h"


RAWTerrain::RAWTerrain() :terrain()
{

}


RAWTerrain::~RAWTerrain()
{

}

void RAWTerrain::update(float time) {

}

RAWTerrain::RAWTerrain(const RAWTerrain & tocpy) {
	dimensions = tocpy.dimensions;
	
	if (tocpy.data != NULL) {
		data = new float[tocpy.dimensions * tocpy.dimensions];

		for (unsigned i = 0; i < dimensions*dimensions; i++) {
			data[i] = tocpy.data[i];
		}
	}
	else {
		data = NULL;
	}

	plane = tocpy.plane;
	planInd = tocpy.planInd;
	texcoords = tocpy.texcoords;
	scale = tocpy.scale;
	multitexture = tocpy.multitexture;
	detailmap = tocpy.detailmap;
	lights = tocpy.lights;
	id = tocpy.id;
}

RAWTerrain * RAWTerrain::create() const {
	return new RAWTerrain(*this);
}

void RAWTerrain::render(const vec3 & transmat) {
	vec3 trans(0, 0, 0);
	if (!multitexture.empty()) {
		Singleton<TextureManager>::getInstance()->useTexture(multitexture, detailmap, Singleton<RenderModuleStubb>::getInstance());
		Singleton<RenderModuleStubb>::getInstance()->renderMultiTexturedArrayTriStrip(planInd, plane, texcoords, lights, trans);
		Singleton<TextureManager>::getInstance()->DisableMultiTex(Singleton<RenderModuleStubb>::getInstance());
	}
	else {
		Singleton<RenderModuleStubb>::getInstance()->renderArrayTriStrip(planInd, plane, trans);
	}
}

bool RAWTerrain::loadData(std::string filename){
	std::ifstream infile(filename.c_str(), std::ios::binary);
	if (!infile) return false;

	infile.seekg(0, std::ios::end);

	unsigned size = (unsigned) infile.tellg();
	infile.seekg(0, std::ios::beg);

	dimensions = (unsigned) sqrt(size);

	unsigned char* data2 = new unsigned char[size];

	if (!data2) return false;

	if (infile.read((char*)data2, size)) {

		data = new float[size];

		for(unsigned i = 0; i < size; i++) {
			data[i] = data2[i];
		}

		delete[] data2;
		data2 = NULL;

		return true;
	}
	else{
		delete[] data2;
		data2 = NULL;
		return false;
	}
}

std::string RAWTerrain::parseOptions(std::string file) {
	std::string hm;
	
	std::ifstream infile(file.c_str());
	if (!infile) return hm;

	std::string tmp;
	char linehead;

	float x, y, z;

	while (infile.peek() != EOF) {
		getline(infile, tmp);

		linehead = tmp.at(0);
		tmp = tmp.substr(tmp.find(" ") + 1);
		std::string path;
		std::string name;
		bool good;
		std::string mettype;

		switch (linehead) {
		case 's':
			x = (float) atof(tmp.substr(0, tmp.find(" ")).c_str());
			tmp = tmp.substr(tmp.find(" ") + 1);
			y = (float) atof(tmp.substr(0, tmp.find(" ")).c_str());
			tmp = tmp.substr(tmp.find(" ") + 1);
			z = (float) atof(tmp.c_str());
			scale = vec3(x, y, z);
			break;
		case 'f':
			hm = tmp;
			break;
		case 't':
			path = tmp.substr(0, tmp.find(" "));
			tmp = tmp.substr(tmp.find(" ") + 1);
			mettype = tmp;
			name = RandomString(25);
			good = Singleton<TextureManager>::getInstance()->loadNewTexture(path, mettype, name, Singleton<RenderModuleStubb>::getInstance());
			if (good) detailmap = name;
			break;
		case 'm':
			multitexture = RandomString(25);
			while (tmp.find(' ') != std::string::npos) {
				images.push_back(tmp.substr(0, tmp.find(" ")));
				tmp = tmp.substr(tmp.find(" ") + 1);
			}
			images.push_back(tmp);
			break;
		}
	}

	return hm;
}

bool RAWTerrain::loadModel(std::string filename){

	std::string file = parseOptions(filename);
	
	if (file.empty()) return false;

	bool good = loadData(file);
	
	if (good) {
		genPlane(dimensions);
		genLightmap();
		genPlaneIndicies(dimensions);
		genTexCoords();
		if (!multitexture.empty()) {
			if ((Singleton<TextureManager>::getInstance()->genMultiTexture(plane, images, multitexture)) == false) {
				multitexture = "";
			}
		}
		applyScaling(scale);
		delete[] data;
		data = NULL;
	}

	return good;
}

std::string RAWTerrain::RandomString(unsigned len) {
	std::string tmp;

	for (unsigned i = 0; i < len; ++i) {
		tmp.push_back((char) 97 + (rand() % static_cast<int>(122 - 97 + 1)));
	}

	return tmp;
}