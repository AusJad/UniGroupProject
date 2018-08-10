#include "SelectionComponent.h"



SelectionComponent::SelectionComponent() : WndComponent(),
left(), right(), enter(), selection()
{
	left.setTex("button_left");
	right.setTex("button_right");
	enter.setTitle("Enter");
	options.push_back("Option 1"); options.push_back("Option 2"); options.push_back("Option 3");
	curoption = 0;
	selection.setLabel(options.at(curoption));
	selection.setPadding(6);
}

SelectionComponent::SelectionComponent(int width, int height, vec2 pos) : WndComponent(width, height, pos), 
left(), right(), enter(), selection()
{
	left.setTex("button_left");
	right.setTex("button_right");
	enter.setTitle("Enter");
	options.push_back("Option 1"); options.push_back("Option 2"); options.push_back("Option 3");
	curoption = 0;
	selection.setLabel(options.at(curoption));
	selection.setPadding(6);

	recalcDimensions();
}

void SelectionComponent::setWidth(int toset) {
	width = toset;
	recalcDimensions();
}

void SelectionComponent::setHeight(int toset) {
	height = toset;
	recalcDimensions();
}

void SelectionComponent::setPos(vec2 toset) {
	pos = toset;
	recalcDimensions();
}

void SelectionComponent::move(float x, float y) {
	pos = vec2(pos.x() + x, pos.y() + y);
	recalcDimensions();
}

void SelectionComponent::recalcDimensions() {
	left.setWidth(height / 2);
	left.setHeight(height / 2);
	left.setPos(pos);

	right.setWidth(height / 2);
	right.setHeight(height / 2);
	right.setPos(vec2(pos.x() + width - height / 2, pos.y()));

	enter.setWidth(width);
	enter.setHeight(height / 2);
	enter.setPos(vec2(pos.x(), pos.y() + height / 2));

	selection.setPos(vec2(pos.x() + height / 2, pos.y()));
	selection.setWidth(width - height);
	selection.setHeight(height / 2);
}

void SelectionComponent::render() {
	GeoStream << START_ATTRIB << UI_DARK_COLOR;
	RNDR->DrawQuadOrtho(pos, vec2(pos.x() + width, pos.y() + height / 2));
	GeoStream << END_ATTRIB;

	left.render();
	right.render();
	enter.render();
	selection.render();
}

bool SelectionComponent::testClick(int x, int y) {
	if (x > pos.x() && x < pos.x() + width && y > pos.y() && y < pos.y() + height*2) {
		if (left.testClick(x, y)) {
			decOpt();
			return true;
		}
		else
		if (right.testClick(x, y)) {
			incOpt();
		}
		else
		if(enter.testClick(x,y)){
			if (callback != NULL) callback(curoption);
		}
		
	}

	return false;
}

void SelectionComponent::incOpt() {
	curoption++;
	if (curoption >= options.size()) curoption = 0;
	selection.setLabel(options.at(curoption));
}

void SelectionComponent::decOpt() {
	curoption--;
	if (curoption < 0) curoption = options.size() - 1;
	selection.setLabel(options.at(curoption));
}