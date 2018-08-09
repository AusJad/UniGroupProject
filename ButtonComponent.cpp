#include "ButtonComponent.h"



ButtonComponent::ButtonComponent(int width, int height, vec2 pos) : WndComponent(width, height, pos)
{
	buttontex = "buttontex";
}


void ButtonComponent::render() {
	if (!buttontex.empty()) TXMAN->useTexture(buttontex, RNDR);
	RNDR->DrawQuadOrtho(vec2(pos), vec2(pos.x() + width, pos.y() + height));
}

bool ButtonComponent::testClick(int x, int y) {
	if (x > pos.x() && x < pos.x() + width && y > pos.y() && y < pos.y() + height) {
		if(callback != NULL) callback(BUTTON_CLICK);
		std::cout << "clicked" << std::endl;
		return true;
	}
	std::cout << "not clicked" << std::endl;
	return false;
}