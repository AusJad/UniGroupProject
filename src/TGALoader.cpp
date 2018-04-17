#include "TGALoader.h"

TGALoader::TGALoader(){
	data = NULL;
	width = 0;
	height = 0;
	bits = 0;
}

TGALoader::~TGALoader(){
	if (data != NULL){
		delete[] data;
		data = NULL;
	}
}

bool TGALoader::loadFile(std::string filename){
	std::ifstream filedata(filename.c_str(), std::ios::binary);
	if (!filedata) return false;

	unsigned char header[18];

	filedata.read((char*)header, 18);

	bits = header[16];

	if (bits != 32 && bits != 24){
		return false;
	}

	width = header[12];
	width += header[13] * 256;

	height = header[14];
	height += header[15] * 256;

	size = width * height * ((bits == 24) ? 3 : 4);

	data = new unsigned char[size];

	unsigned char tmp;
	unsigned char pixel[4];

	if (header[2] == 2){
		try{
			filedata.read((char*) data, size);
		}
		catch (...){
			delete[] data;
			data = NULL;
			return false;
		}

		for (unsigned i = 0; i < size; i += 3){
			tmp = data[i];
			data[i] = data[i + 2];
			data[i + 2] = tmp;
		}
	}
	else{
		try{
			for (unsigned i = 0; i < size;){
				filedata.read((char *)&tmp, 1);

				if (tmp > 128){
					tmp -= 127;

					if (bits == 24) filedata.read((char*)pixel, 3);
					else filedata.read((char*)pixel, 4);

					while (tmp > 0){
						data[i++] = pixel[2];
						data[i++] = pixel[1];
						data[i++] = pixel[0];

						if (bits == 32) data[i++] = pixel[3];

						tmp -= 1;
					}
				}
				else{
					tmp += 1;

					while (tmp > 0){
						if (bits == 24) filedata.read((char*)pixel, 3);
						else filedata.read((char*)pixel, 4);

						data[i++] = pixel[2];
						data[i++] = pixel[1];
						data[i++] = pixel[0];

						if (bits == 32) data[i++] = pixel[3];

						tmp -= 1;
					}
				}
			}
		}
		catch (...){
			delete[] data;
			data = NULL;
			return false;
		}
	}

	return true;
}

unsigned char* TGALoader::getData() const{
	return data;
}

unsigned TGALoader::getBits() const{
	return bits;
}

unsigned TGALoader::getWidth() const{
	return width;
}

unsigned TGALoader::getDataSize() {
	return size;
}

unsigned TGALoader::getHeight() const{
	return height;
}

void TGALoader::clear(){
	if (data != NULL){
		delete[] data;
	}
}