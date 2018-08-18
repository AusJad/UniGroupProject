#include "ItemScrollComponent.h"



ItemScrollComponent::ItemScrollComponent(){
	width = 0;
	height = 0;
	visiblestart = 0;
	visibleend = 0;
	scrollbarheight = 0;

}


ItemScrollComponent::ItemScrollComponent(int width, int height, vec2 pos) {
	this->width = width;
	this->height = height;
	scrollbarheight = height;
	this->pos = pos;
	visiblestart = 0;
	visibleend = 0;
	recalcDimensions();
}

void ItemScrollComponent::update(float time) {
	if (scrolldat.moving == true) {
		if (scrolldat.offset.y() != 0) {
			scrollbarpos.sy(scrollbarpos.y() + scrolldat.offset.y());
			if (scrollbarpos.y() > pos.y() + height - padding - scrollbarheight)
				scrollbarpos.sy(pos.y() + height - padding - scrollbarheight);
			if (scrollbarpos.y() < pos.y() + padding)
				scrollbarpos.sy(pos.y() + padding);
			getVisibleComponents();
		}
		scrolldat.offset = vec2();
	}
}

void ItemScrollComponent::render() {
	//draw backdrop
	GeoStream << START_ATTRIB << UI_DARK_COLOR;
	RNDR->DrawQuadOrtho(pos, vec2(pos.x() + width, pos.y() + height));
	GeoStream << END_ATTRIB;

	//draw scrollbar
	GeoStream << START_ATTRIB << UI_LIGHT_COLOR;
	RNDR->DrawQuadOrtho(scrollbarpos, vec2(scrollbarpos.x() + scrollbarwidth, scrollbarpos.y() + scrollbarheight));
	GeoStream << END_ATTRIB;

	for (unsigned i = visiblestart; i <= visibleend && i< options.size(); i++) {
		options.at(i).render();
	}
}

bool ItemScrollComponent::testClick(int x, int y) {
	if (x > scrollbarpos.x() && x < scrollbarpos.x() + scrollbarwidth && y > scrollbarpos.y() && y < scrollbarpos.y() + scrollbarheight) {
		scrolldat.moving = true;
		scrolldat.inital = vec2(x, y);
		scrolldat.offset = vec2();
		CONT->switchContextMenuMove(&scrolldat);
		return true;
	}

	for (unsigned i = visiblestart; i <= visibleend && i < options.size(); i++) {
		if (options.at(i).testClick(x, y)) {
			if (callbacks.at(i) != NULL) callbacks.at(i)(i);
			return true;
		}
	}

	return false;
}

void ItemScrollComponent::removeOption(std::string toremove) {
	bool found = false;

	for (unsigned i = 0; i < options.size() && !found; i++) {
		if (options.at(i).getTitle() == toremove) {
			options.erase(options.begin() + i);
			callbacks.erase(callbacks.begin() + i);
			found = true;
		}
	}

	if(found) recalcDimensions();
}

std::string ItemScrollComponent::getOptionvalue(int index) {
	if (index >= options.size()) return "";
	else return options.at(index).getTitle();
}

void ItemScrollComponent::getVisibleComponents() {
	visiblestart = calcFirstVis();
	visibleend = calcLastVis();
	//add guard to prevent unecessary processing
	setButtonPositions();
}

void ItemScrollComponent::setButtonPositions() {
	float curpos = pos.y() + padding;

	for (unsigned i = visiblestart; i <= visibleend && i< options.size(); i++) {
		options.at(i).setPos(vec2(pos.x() + padding, curpos));
		curpos += options.at(i).getHeight();
	}
}

int ItemScrollComponent::calcFirstVis() {
	float ystart = scrollbarpos.y() - (pos.y() + padding);
	//if (ystart == 0) return 0;

	float ystartprcnt = ystart / scrollbarheight;

	float scrlbrprcnt = scrollbarheight / (height - padding * 2);

	ystartprcnt *= scrlbrprcnt;

	float startheight = pos.y() + padding + getCulmHeight() * ystartprcnt;

	float culmheight = pos.y() + padding;

	int strt = 0;

	bool strtfnd = false;

	for (unsigned i = 0; i < options.size() && !strtfnd; i++) {
		culmheight += options.at(i).getHeight();
		if (culmheight >= startheight) {
			strt = i;
			strtfnd = true;
		}
	}

	return strt;
}

void ItemScrollComponent::setWidth(int toset) {
	width = toset;
	recalcDimensions();
}

void ItemScrollComponent::setHeight(int toset) {
	height = toset;
	recalcDimensions();
}

void ItemScrollComponent::setPos(vec2 toset) {
	pos = toset;
}

float ItemScrollComponent::getCulmHeight() {
	float culmheight = padding * 2;

	for (unsigned i = 0; i < options.size(); i++) {
		culmheight += options.at(i).getHeight();
	}

	return culmheight;
}

void ItemScrollComponent::addOption(std::string title, onClick callback) {
	ButtonComponent toadd(width - padding * 2 - scrollbarwidth, componentheight, vec2(pos.x() + padding, pos.y() + padding));
	toadd.setTitle(title);

	callbacks.push_back(callback);

	options.push_back(toadd);
	recalcDimensions();
}

void ItemScrollComponent::optionsAdded() {
	float culmheight = getCulmHeight();

	if (culmheight < height - padding * 2) {
		height = culmheight + padding * 2;
	}
}

void ItemScrollComponent::recalcDimensions() {
	//optionsAdded();

	scrollbarpos = vec2(pos.x() + width - scrollbarwidth, pos.y() + padding);
	scrollbarheight = calcScrollbarHeight();
	
	for (unsigned i = 0; i < options.size(); i++) {
		options.at(i).setWidth(width - padding * 2 - scrollbarwidth);
	}

	visiblestart = 0;
	visibleend = calcLastVis();
	setButtonPositions();
}

void ItemScrollComponent::move(float x, float y) {
	pos = vec2(pos.x() + x, pos.y() + y);
	recalcDimensions();
}

float ItemScrollComponent::calcScrollbarHeight() {
	float culmheight = getCulmHeight();

	if (culmheight == 0) return height - padding * 2;

	if (culmheight <= height - padding * 2) return height - padding * 2;

	float prcntheight = (height - padding * 2) / culmheight;

	return prcntheight * (height - padding * 2);
}

int ItemScrollComponent::calcLastVis() {
	if (options.size() == 0) return 0;

	int curviable = 0;

	float offset = padding;

	for (unsigned i = visiblestart; i < options.size() && offset < height; i++) {
		offset += options.at(i).getHeight();
		if (offset < height + padding) curviable = i;
	}

	return curviable;
}