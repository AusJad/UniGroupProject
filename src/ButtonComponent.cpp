#include "ButtonComponent.h"



ButtonComponent::ButtonComponent(int width, int height, vec2 pos) : WndComponent(width, height, pos)
{
}


void ButtonComponent::render() {
	if (!buttontex.empty()) TXMAN->useTexture(buttontex, RNDR);
	else GeoStream << START_ATTRIB << UI_MID_DARK_COLOR;
	RNDR->DrawQuadOrtho(pos, vec2(pos.x() + width, pos.y() + height));
	if (!buttontex.empty()) TXMAN->disableTexture(RNDR);
	else GeoStream << END_ATTRIB;

	if (buttontex.empty()) {
		GeoStream << START_ATTRIB << UI_LIGHT_COLOR;
		RNDR->DrawQuadOrtho(pos, vec2(pos.x() + width, pos.y() + INPUT_BORDER));
		RNDR->DrawQuadOrtho(pos, vec2(pos.x() + INPUT_BORDER, pos.y() + height));
		RNDR->DrawQuadOrtho(vec2(pos.x() + width - INPUT_BORDER, pos.y()), vec2(pos.x() + width, pos.y() + height));
		RNDR->DrawQuadOrtho(vec2(pos.x(), pos.y() + height - INPUT_BORDER), vec2(pos.x() + width, pos.y() + height));
		GeoStream << END_ATTRIB;
	}

	if (!vistext.empty()) {
		FNT_ENG->RenderStringO(vistext, FNT_SIZE_MEDIUM_O, textpos.x(), textpos.y() + 3);
	}
}

bool ButtonComponent::testClick(int x, int y) {
	if (x > pos.x() && x < pos.x() + width && y > pos.y() && y < pos.y() + height) {
		if(callback != NULL) callback(BUTTON_CLICK);
		return true;
	}
	return false;
}

void ButtonComponent::move(float x, float y) {
	pos = vec2(pos.x() + x, pos.y() + y);
	recalcDimensions();
}

void ButtonComponent::setWidth(int toset) {
	width = toset;
	if (!text.empty()) recalcDimensions();
}

void ButtonComponent::setHeight(int toset) {
	height = toset;
	if (!text.empty()) recalcDimensions();
}

void ButtonComponent::setPos(vec2 toset) {
	pos = toset;
	if(!text.empty()) recalcDimensions();
}

void ButtonComponent::recalcDimensions() {
	vistext = text;
	int size = (int)FNT_ENG->precomputeStringWidth(text, FNT_SIZE_MEDIUM_O);

	if (size > width) {
		while (size > width && !vistext.empty()) {
			vistext.pop_back();
			size = (int)FNT_ENG->precomputeStringWidth(vistext, FNT_SIZE_MEDIUM_O);
		}
	}

	textpos.sx(pos.x() + (width - size) / 2);
	textpos.sy(pos.y() + (height - FNT_SIZE_MEDIUM_O) / 2);
}

void ButtonComponent::setTitle(std::string toset) {
	text = toset;
	
	recalcDimensions();
}

void ButtonComponent::setTex(std::string ntex) {
	buttontex = ntex;
}