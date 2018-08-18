#include "WndComponent.h"


WndComponent::WndComponent() {
	width = 0;
	height = 0;
	callback = NULL;
}

WndComponent::WndComponent(int width, int height, vec2 pos) {
	this->width = width;
	this->height = height;
	this->pos = pos;
	callback = NULL;
}

void WndComponent::setCallback(onClick toset) {
	callback = toset;
}

void WndComponent::setWidth(int toset) {
	width = toset;
}

void WndComponent::setHeight(int toset) {
	height = toset;
}

void WndComponent::setPos(vec2 toset) {
	pos = toset;
}

void WndComponent::move(float x, float y) {
	pos = vec2(pos.x() + x, pos.y() + y);
}