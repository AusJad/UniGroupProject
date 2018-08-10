#include "TextInputComponent.h"



TextInputComponent::TextInputComponent(int width, int height, vec2 pos) : WndComponent(width, height, pos)
{

}


void TextInputComponent::render() {
	GeoStream << START_ATTRIB << UI_LIGHT_COLOR;

	//border
	RNDR->DrawQuadOrtho(pos, vec2(pos.x() + width, pos.y() + INPUT_BORDER));
	RNDR->DrawQuadOrtho(pos, vec2(pos.x() + INPUT_BORDER, pos.y() + height));
	RNDR->DrawQuadOrtho(vec2(pos.x() + width - INPUT_BORDER, pos.y()), vec2(pos.x() + width, pos.y() + height));
	RNDR->DrawQuadOrtho(vec2(pos.x(), pos.y() + height - INPUT_BORDER), vec2(pos.x() + width, pos.y() + height));

	//backdrop
	GeoStream << UI_DARK_COLOR;
	RNDR->DrawQuadOrtho(vec2(pos.x() + INPUT_BORDER, pos.y() + INPUT_BORDER), vec2(pos.x() + width - INPUT_BORDER, pos.y() + height - INPUT_BORDER));
	GeoStream << END_ATTRIB;

	//entered text
	if (!value.empty()) {
		FNT_ENG->RenderStringO(value, FNT_SIZE_MEDIUM_O, pos.x() + INPUT_BORDER, pos.y() + INPUT_BORDER);
	}
}

bool TextInputComponent::testClick(int x, int y) {
	if (x > pos.x() && x < pos.x() + width && y > pos.y() && y < pos.y() + height) {
		CONT->switchContextTextInput(&value, callback);
		return true;
	}

	return false;
}
