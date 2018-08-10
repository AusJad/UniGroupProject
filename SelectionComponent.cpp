#include "SelectionComponent.h"



SelectionComponent::SelectionComponent(int width, int height, vec2 pos) : WndComponent(width, height, pos),
left(height / 2, height / 2, pos),
right(height / 2, height / 2, vec2(pos.x() + width - height / 2, pos.y())),
enter(width, height / 2, vec2(pos.x(), pos.y() + height / 2))
{
	left.setTex("button_left");
	right.setTex("button_right");
	enter.setTitle("Enter");
	pos = vec2(pos.x() + height / 2, pos.y());
	width -= height / 2;
	options.push_back("Option 1"); options.push_back("Option 2"); options.push_back("Option 3");
	curoption = 0;
}

void SelectionComponent::render() {
	left.render();
	right.render();
	enter.render();

	//render text background
	/*	
	GeoStream << START_ATTRIB << color_3(.44, .44, .44);
	RNDR->DrawQuadOrtho(pos, vec2(pos.x() + width, pos.y() + height/2));
	GeoStream << END_ATTRIB;
	*/
	//render cur selection text
	if(options.size() != 0) FNT_ENG->RenderStringO(options.at(curoption), FNT_SIZE_MEDIUM_O, pos.x() + height/2 + 10, pos.y() + 3);
	else FNT_ENG->RenderStringO("No Options Available!", FNT_SIZE_MEDIUM_O, pos.x() + height + 10, pos.y() + 3);
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
}

void SelectionComponent::decOpt() {
	curoption--;
	if (curoption < 0) curoption = options.size() - 1;
}