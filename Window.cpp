#include "Window.h"



Window::Window(vec2 & stpos, float width, float height, std::string title){
	bgtex = "bggrey";
	hdtex = "header";
	this->title = title;
	tlscreen = stpos;
	brscreen = vec2(tlscreen.x() + width, tlscreen.y() + height);
	visible = true;
	closebutton = new ButtonComponent(32, 32, vec2(brscreen.x() - 32, tlscreen.y()));
	components.push_back(new SelectionComponent(480, 64, vec2(tlscreen.x() + 10, tlscreen.y() + 64)));
	components.push_back(new TextInputComponent(480, 64, vec2(tlscreen.x() + 10, tlscreen.y() + 140)));
}

void Window::setCloseButtonCallBack(onClick callback) {
	closebutton->setCallback(callback);
}

void Window::tglVis(){
	visible = !visible;
}
bool Window::isVis() {
	return visible;
}

void Window::render() {
	if (!visible) return;

	RNDR->RenderModeOrtho();
	
	//render header bar
	if (!hdtex.empty()) TXMAN->useTexture("header", RNDR);
	RNDR->DrawQuadOrtho(tlscreen, vec2(brscreen.x(), tlscreen.y() + 32));
	TXMAN->disableTexture(RNDR);

	//render title text
	FNT_ENG->RenderStringO(title, FNT_SIZE_MEDIUM_O, tlscreen.x() + 10, tlscreen.y() + 3);
	
	//render background
	if (!bgtex.empty()) TXMAN->useTexture(bgtex, RNDR);
	RNDR->DrawQuadOrtho(vec2(tlscreen.x(), tlscreen.y() + 32), brscreen);
	TXMAN->disableTexture(RNDR);

	closebutton->render();

	for (unsigned i = 0; i < components.size(); i++) {
		components.at(i)->render();
	}

	RNDR->RenderModePerspective();
}

void Window::move(int x, int y) {

}

bool Window::testClick(int x, int y) {
	if (x > tlscreen.x() && x < brscreen.x() && y < brscreen.y() && y > tlscreen.y()) {
		if (closebutton->testClick(x, y)) {
			visible = false;
			return true;
		}

		for (unsigned i = 0; i < components.size(); i++) {
			if (components.at(i)->testClick(x, y)) return true;
		}
	}

	return false;
}

void Window::calculateSize() {

}