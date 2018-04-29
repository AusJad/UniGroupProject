#include "FontEngine.h"



FontEngine::FontEngine()
{
	id.setName("FE");
}


FontEngine::~FontEngine()
{
}

void FontEngine::update() {
	Message tmp;

	while (MSGBS->hasMessage(id)) {
		tmp = MSGBS->getMessage(id);
		if (tmp.getInstruction() == CHNGE_FNT) {
			setActiveFont(tmp.getData().sdata);
		}

	}
}

bool FontEngine::RenderChar(char toRender) {

	RNDR->RenderFacingCamera();

	if (!fonts.at(activefont).useChar(toRender)) return false;

	RNDR->DrawQuad(point(-0.5, 0.5), point(0.5,-0.5), -2);

	RNDR->bindTexture(NULL);

	RNDR->StopRenderFacingCamera();

	return true;
}

bool FontEngine::RenderString(std::string torender, float fontsize, unsigned numrow, unsigned maxwidth, float startx, float starty, float depth) {

	unsigned culmwidth;

	char curchar;

	RNDR->RenderFacingCamera();

	bool errorflagnotset = true;

	for (unsigned i = 0; i < torender.size(); i++) {

		curchar = toupper(torender.at(i));

		if (!fonts.at(activefont).useChar(curchar)) errorflagnotset = false;
		
		RNDR->DrawQuad(point(startx, starty + fontsize), point(startx + fontsize, starty), depth);

		RNDR->bindTexture(NULL);

		startx += ((float)fonts.at(activefont).getCharOffset(curchar) / (float)fonts.at(activefont).getCharWidth()) * fontsize;
	
	}

	RNDR->StopRenderFacingCamera();

	return errorflagnotset;
}

bool FontEngine::hasFont(std::string font) {
	return fonts.count(font) == 1;
}

bool FontEngine::setActiveFont(std::string font) {
	if (fonts.count(font) == 0) return false;

	activefont = font;

	return true;
}

bool FontEngine::loadFont(std::string path, std::string name) {
	Font tmp;

	if(fonts.count(name) == 1) return false;

	if (!FontLoader::loadFont(path, tmp, name)) return false;

	fonts[name] = tmp;

	activefont = name;

	return true;
}

bool FontEngine::fontHasChar(char totest){
	return fonts.at(activefont).hasChar(totest);
}