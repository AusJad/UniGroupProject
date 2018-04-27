#include "Font.h"

Font::Font()
{

}

Font::~Font()
{
}

void Font::setImgWidth(unsigned imgwidth) {
	this->imgwidth = imgwidth;
}

void Font::setImgHeight(unsigned imgheight) {
	this->imgheight = imgheight;
}

void Font::setCharWidth(unsigned charwidth) {
	this->charwidth = charwidth;
}

void Font::setCharHeight(unsigned charheight) {
	this->charheight = charheight;
}

void Font::setStartChar(unsigned startchar) {
	this->startchar = startchar;
}

void Font::setTexture(std::string texture) {
	this->texture = texture;
}

void Font::addCharOffsetMapping(char character, int offset) {
	fontoffsets[character] = offset;
}

unsigned Font::getImgWidth() {
	return imgwidth;
}

unsigned Font::getImgHeight() {
	return imgheight;
}

unsigned Font::getCharWidth() {
	return charwidth;
}

unsigned Font::getCharHeight() {
	return charheight;
}

unsigned Font::getStartChar() {
	return startchar;
}

int Font::getCharOffset(char key) {
	if (fontoffsets.count(key) == 0) return -1;

	return fontoffsets.at(key);
}

const std::string & Font::getTex() {
	return texture;
}

bool Font::useChar(char touse) {
	if (fontmappings.count(touse) == 0) return false;

	TXMAN->useTexture(fontmappings.at(touse), RNDR);

	return true;
}

void Font::bindCharImg(char key, std::string id) {
	fontmappings[key] = id;
}

bool Font::hasChar(char totest){
	return fontmappings.count(totest) == 1;
}