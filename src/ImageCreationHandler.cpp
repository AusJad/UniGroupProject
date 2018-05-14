#include "ImageCreationHandler.h"


ImageCreationHandler::ImageCreationHandler()
{
	currimage = NULL;
}

ImageCreationHandler::~ImageCreationHandler()
{
	if (currimage != NULL) {
		currimage->clear();
		delete currimage;
		currimage = NULL;
	}
}

bool ImageCreationHandler::CreateImage(std::string path, std::string type) {
	ImageLoaderFactory temp;

	if (currimage != NULL) currimage->clear();

	currimage = temp.getNewLoader(type);

	if (currimage == NULL) return false;

	bool success = currimage->loadFile(path);

	if (!success) {
		currimage->clear();
		delete currimage;
		currimage = NULL;
		return false;
	}

	return true;
}

bool ImageCreationHandler::bindImage(const int & id, RenderModuleStubb* renderer) {
	if (currimage == NULL) return false;

	renderer->storeTexture(id, currimage->getBits(), currimage->getWidth(), currimage->getHeight(), currimage->getData());

	currimage->clear();
	delete currimage;
	currimage = NULL;
	return true;
}

void ImageCreationHandler::unbindImage(const int & id, RenderModuleStubb* renderer) {
	renderer->deleteTexture(id);
}

bool ImageCreationHandler::CreateMultiTexture(std::vector<vec3> heightmap, std::vector<std::string> textures, std::string name, const int & id) {
	if (textures.size() % 2 != 0 || textures.empty()) return false;

	unsigned char** data;
	data = new unsigned char*[(textures.size() / 2)];

	bool good = true;

	unsigned dataind = 0;

	for (unsigned i = 0; i < textures.size() && good; i += 2) {
		good = CreateImage(textures.at(i), textures.at(i + 1));
		if (good) {
			data[dataind] = new unsigned char[currimage->getDataSize()];

			for (unsigned j = 0; j < currimage->getDataSize(); j++) {
				data[dataind][j] = currimage->getData()[j];
			}

			dataind++;
			currimage->clear();
			delete currimage;
			currimage = NULL;
		}
	}

	if (!good) {
		for (unsigned i = 0; i < dataind; i++) {
			delete[] data[i];
		}

		delete[] data;

		return false;
	}

	unsigned char* imagedata = new unsigned char[heightmap.size() * 3];

	float height;

	float weight;

	float range = 255 / (float)(textures.size() / 2);

	unsigned char rgb[3];

	int ntexind = 0;

	int dimensions = (int)sqrt(heightmap.size());

	unsigned xind;
	unsigned zind;

	for (unsigned i = 0; i < heightmap.size(); i++) {
		height = heightmap.at(i).y();
		rgb[0] = 0;
		rgb[1] = 0;
		rgb[2] = 0;
		xind = (int)heightmap.at(i).x();
		zind = (int)heightmap.at(i).z();

		for (unsigned j = 0; j < textures.size() / 2; j++) {
			weight = (range - abs(height - ((j + 1)*range))) / range;

			if (weight > 0) {
				rgb[0] += (unsigned char) (data[j][((xind + (zind * dimensions)) * 3)] * weight);
				rgb[1] += (unsigned char) (data[j][((xind + (zind * dimensions)) * 3) + 1] * weight);
				rgb[2] += (unsigned char) (data[j][((xind + (zind * dimensions)) * 3) + 2] * weight);
			}
		}
		imagedata[((xind + (zind * dimensions)) * 3)] = rgb[0];
		imagedata[((xind + (zind * dimensions)) * 3) + 1] = rgb[1];
		imagedata[((xind + (zind * dimensions)) * 3) + 2] = rgb[2];
	}

	Singleton<RenderModuleStubb>::getInstance()->storeTexture(id, 24, dimensions, dimensions, imagedata);

	for (unsigned i = 0; i < textures.size() / 2; i++) {
		delete[] data[i];
	}

	delete[] data;

	delete[] imagedata;

	return true;
}

unsigned char* ImageCreationHandler::getActiveImageData() {
	if (currimage == NULL) return NULL;

	return currimage->getData();
}

bool ImageCreationHandler::bindSubImage(const int & id, unsigned subwidth, unsigned subheight, unsigned x, unsigned y) {
	if (currimage == NULL) return NULL;

	RNDR->genSubTex(id, currimage->getBits(), currimage->getWidth(), currimage->getHeight(), x, y, subwidth, subheight, currimage->getData());

	return true;
}