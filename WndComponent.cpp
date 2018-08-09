#include "WndComponent.h"

WndComponent::WndComponent(int width, int height, vec2 pos) {
	this->width = width;
	this->height = height;
	this->pos = pos;
	callback = NULL;
}

void WndComponent::setCallback(onClick toset) {
	callback = toset;
}