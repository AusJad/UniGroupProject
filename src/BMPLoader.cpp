#include "BMPLoader.h"

BMPLoader::BMPLoader(){
	data = NULL;
	width = 0;
	height = 0;
	bits = 0;
}

BMPLoader::~BMPLoader(){
	if (data != NULL){
		delete[] data;
		data = NULL;
	}
}

bool BMPLoader::loadFile(std::string filename){
	std::ifstream filedata(filename.c_str(), std::ios::binary);
	if (!filedata) return false;

	unsigned char header[54];

	filedata.read((char*) header, 54);
	if (header[0] != 0x42 || header[1] != 0x4D){
		return false;
	}

	size = header[34];
	size += header[35] * 256;
	size += header[36] * 65536;
	size += header[37] * 16777216;

	width = header[18];
	width += header[19] * 256;
	width += header[20] * 65536;
	width += header[21] * 16777216;

	height = header[22];
	height += header[23] * 256;
	height += header[24] * 65536;
	height += header[25] * 16777216;

	bits = header[28];

	if (bits != 24)
		return false;

	unsigned compression = header[30];
	compression += header[31] * 256;

	if (compression != 0)
		return false;

	unsigned offset = header[10];
	offset += header[11] * 256;
	offset += header[12] * 65536;
	offset += header[13] * 16777216;

	size = width*height*bits;

	data = new unsigned char[width*height*bits];

	if (data == NULL) return false;

	try{
		filedata.read((char*) data, size);

		filedata.close();

		unsigned char tmp;

		for (unsigned i = 0; i < size; i += 3){
			tmp = data[i];
			data[i] = data[i + 2];
			data[i + 2] = tmp;
		}
	}
	catch (...){
		delete[] data;
		data = NULL;
		return false;
	}

	return true;
}

unsigned char* BMPLoader::getData() const{
	return data;
}

unsigned BMPLoader::getBits() const{
	return bits;
}

unsigned BMPLoader::getWidth() const{
	return width;
}

unsigned BMPLoader::getHeight() const{
	return height;
}

unsigned BMPLoader::getDataSize() {
	return size;
}

void BMPLoader::clear(){
	if (data != 0){
		delete[] data;
		data = NULL;
	}
}