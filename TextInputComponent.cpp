#include "TextInputComponent.h"



TextInputComponent::TextInputComponent(int width, int height, vec2 pos) : WndComponent(width, height, pos)
{

}


void TextInputComponent::render() {
	GeoStream << START_ATTRIB << color_3(.44,.44,.44);

	//border
	RNDR->DrawQuadOrtho(pos, vec2(pos.x() + width, pos.y() + 3));
	RNDR->DrawQuadOrtho(pos, vec2(pos.x() + 3, pos.y() + height));
	RNDR->DrawQuadOrtho(vec2(pos.x() + width -3, pos.y()), vec2(pos.x() + width, pos.y() + height));
	RNDR->DrawQuadOrtho(vec2(pos.x(), pos.y() + height - 3), vec2(pos.x() + width, pos.y() + height));

	//backdrop
	GeoStream << color_3(.30, .30, .30);
	RNDR->DrawQuadOrtho(vec2(pos.x() + 3, pos.y() + 3), vec2(pos.x() + width - 3, pos.y() + height - 3));
	GeoStream << END_ATTRIB;
}

bool TextInputComponent::testClick(int x, int y) {
	if (x > pos.x() && x < pos.x() + width && y > pos.y() && y < pos.y() + height) {
		if (callback != NULL) callback(id);
		std::cout << "hit text box" << std::endl;
		return true;
	}

	return false;
}