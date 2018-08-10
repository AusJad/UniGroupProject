#include "LabelComponent.h"

void LabelComponent::render() {
	if (!texture.empty()) {
		TXMAN->useTexture(texture, RNDR);
		RNDR->DrawQuadOrtho(pos, vec2(pos.x() + width, pos.y() + height));
		TXMAN->disableTexture(RNDR);
	}

	if (!vislabel.empty()) {
		FNT_ENG->RenderStringO(vislabel, FNT_SIZE_MEDIUM_O,
			pos.x() + padding, pos.y() + padding);
	}
}

bool LabelComponent::testClick(int x, int y) {
	if (x > pos.x() && x < pos.x() + width && y > pos.y() && y < pos.y() + height) {
		if (callback != NULL) callback(LABEL_CLICK);
		return true;
	}
	return false;
}

void LabelComponent::setWidth(int toset) {
	width = toset;
	recalcDimensions();
}

void LabelComponent::setHeight(int toset){
	height = toset;
	recalcDimensions();
}

void LabelComponent::setPos(vec2 toset) {
	pos = toset;
	recalcDimensions();
}

void LabelComponent::recalcDimensions() {
	vislabel = label;
	int size = (int)FNT_ENG->precomputeStringWidth(label, FNT_SIZE_MEDIUM_O);

	if (size > width - padding * 2) {
		while (size > width - padding * 2  && !vislabel.empty()) {
			vislabel.pop_back();
			size = (int)FNT_ENG->precomputeStringWidth(vislabel, FNT_SIZE_MEDIUM_O);
		}
	}
}

void LabelComponent::setLabel(std::string toset) {
	label = toset;
	recalcDimensions();
}