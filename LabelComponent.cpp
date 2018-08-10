#include "LabelComponent.h"

void LabelComponent::render() {
	if (!label.empty()) {
		FNT_ENG->RenderStringO(label, FNT_SIZE_MEDIUM_O, 
			pos.x(), pos.y());
	}
}

bool LabelComponent::testClick(int x, int y) {
	if (x > pos.x() && x < pos.x() + width && y > pos.y() && y < pos.y() + height) {
		if (callback != NULL) callback(LABEL_CLICK);
		return true;
	}
	return false;
}

void LabelComponent::setLabel(std::string toset) {
	label = toset;

	int size = (int)FNT_ENG->precomputeStringWidth(label, FNT_SIZE_MEDIUM_O);

	if (size > width) {
		while (size > width && !label.empty()) {
			label.pop_back();
			size = (int)FNT_ENG->precomputeStringWidth(label, FNT_SIZE_MEDIUM_O);
		}
	}

}