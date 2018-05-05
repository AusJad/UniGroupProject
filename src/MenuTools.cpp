#include "MenuTools.h"

void MenuTools::drawButton(vec2 & tl, vec2 & br, float z, vec4 & color, std::string text, std::string font) {
	GeoStream << ENABLE_TRANSPARENCY << START_ATTRIB << color_4(color.x(), color.y(), color.z(), color.w());

	RNDR->DrawQuad(point(tl.x(), tl.y()), point(br.x(), br.y()), z);

	GeoStream << END_ATTRIB << DISABLE_TRANSPARENCY << ENABLE_ALPHA;

	FNT_ENG->setActiveFont(font);

	float offset = (br.x() - tl.x()) - (FNT_SIZE_SMALL * font.size());
	offset = abs(offset / 8);

	FNT_ENG->RenderString(text, FNT_SIZE_SMALL, 0, 0, tl.x() + offset, br.y(), z);

	GeoStream << DISABLE_ALPHA;
}

void MenuTools::drawSquare(vec2 & tl, vec2 & br, float z, vec4 & color) {
	GeoStream << ENABLE_TRANSPARENCY << START_ATTRIB << color_4(color.x(), color.y(), color.z(), color.w());

	RNDR->DrawQuad(point(tl.x(), tl.y()), point(br.x(), br.y()), z);

	GeoStream << END_ATTRIB << DISABLE_TRANSPARENCY;
}

void MenuTools::drawTSquare(vec2 & tl, vec2 & br, float z, std::string texture, bool trans) {
	if(trans) GeoStream << ENABLE_ALPHA;
	
	TXMAN->useTexture(texture, RNDR);

	RNDR->DrawQuad(point(tl.x(), tl.y()), point(br.x(), br.y()), z);

	TXMAN->disableTexture(RNDR);
	
	if(trans) GeoStream << DISABLE_ALPHA;
}

void MenuTools::renderText(vec2 start, float z, float size, std::string torender) {
	GeoStream << ENABLE_ALPHA;

	std::string tmpstr;
	float culmheight = start.y();
	if (torender.find('$') == std::string::npos) {
		FNT_ENG->RenderString(torender, size, 30, 30, start.x(), start.y(), z);
	}
	else {
		tmpstr = torender;
		while (tmpstr.find('$') != std::string::npos) {
			FNT_ENG->RenderString(tmpstr.substr(0, tmpstr.find('$')), size, 30, 30, start.x(), culmheight, z);
			tmpstr = tmpstr.substr(tmpstr.find('$') + 1);
			culmheight -= size;
		}
		FNT_ENG->RenderString(tmpstr, size, 30, 30, start.x(), culmheight, z);
	}

	GeoStream << DISABLE_ALPHA;
}

float MenuTools::fadeIn(vec2 & tl, vec2 & br, float z, float curfade, float time) {
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GeoStream << ENABLE_TRANSPARENCY << START_ATTRIB << color_4(0, 0, 0, curfade);

	RNDR->DrawQuad(point(tl.x(), tl.y()), point(br.x(), br.y()), z);

	GeoStream << END_ATTRIB << DISABLE_TRANSPARENCY;

	curfade -= time;

	return curfade;
}

float MenuTools::fadeOut(vec2 & tl, vec2 & br, float z, float curfade, float time) {
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GeoStream << ENABLE_TRANSPARENCY << START_ATTRIB << color_4(0, 0, 0, curfade);

	RNDR->DrawQuad(point(tl.x(), tl.y()), point(br.x(), br.y()), z);

	GeoStream << END_ATTRIB << DISABLE_TRANSPARENCY;

	curfade += time;

	return curfade;
}

void MenuTools::drawModel(vec3 loc, std::string model) {

}

