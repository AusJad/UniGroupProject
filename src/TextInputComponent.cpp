#include "TextInputComponent.h"



TextInputComponent::TextInputComponent(int width, int height, vec2 pos) : WndComponent(width, height, pos)
{
	inputactive = false;
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

	//todo(morgan): Should not be called every frame! Remove this when able
	if(!value.empty()) calcVis();

	//entered text
	if (!value.empty()) {
		if(inputactive) FNT_ENG->RenderStringO(editvis + "_", FNT_SIZE_MEDIUM_O, pos.x() + INPUT_BORDER, pos.y() + INPUT_BORDER);
		else FNT_ENG->RenderStringO(staticvis, FNT_SIZE_MEDIUM_O, pos.x() + INPUT_BORDER, pos.y() + INPUT_BORDER);
	}
	else
	if (inputactive) FNT_ENG->RenderStringO("_", FNT_SIZE_MEDIUM_O, pos.x() + INPUT_BORDER, pos.y() + INPUT_BORDER);
}

bool TextInputComponent::testClick(int x, int y) {
	if (x > pos.x() && x < pos.x() + width && y > pos.y() && y < pos.y() + height) {
		CONT->switchContextTextInput(&value, callback, &inputactive);
		inputactive = true;
		return true;
	}

	return false;
}

void TextInputComponent::calcVis() {
	
	if (inputactive) {
		editvis = value;
		int size = (int)FNT_ENG->precomputeStringWidth(value, FNT_SIZE_MEDIUM_O);

		if (size > width - INPUT_BORDER * 2) {
			while (size > width - INPUT_BORDER * 2 && !editvis.empty()) {
				editvis = editvis.substr(1);
				size = (int)FNT_ENG->precomputeStringWidth(editvis, FNT_SIZE_MEDIUM_O);
			}
		}
	}
	else {
		staticvis = value;
		int size = (int)FNT_ENG->precomputeStringWidth(value, FNT_SIZE_MEDIUM_O);

		if (size > width - INPUT_BORDER * 2) {
			while (size > width - INPUT_BORDER * 2 && !staticvis.empty()) {
				staticvis.pop_back();
				size = (int)FNT_ENG->precomputeStringWidth(staticvis, FNT_SIZE_MEDIUM_O);
			}
		}
	}
}
