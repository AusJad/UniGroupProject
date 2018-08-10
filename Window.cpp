#include "Window.h"



Window::Window(vec2 & stpos, float width, float height, std::string title)
{
	bgtex = "bggrey";
	hdtex = "header";
	this->title = title;
	tlscreen = stpos;
	brscreen = vec2(tlscreen.x() + width, tlscreen.y() + height);
	visible = true;
	closebutton = ButtonComponent(32, 32, vec2(brscreen.x() - 32, tlscreen.y()));
	closebutton.setTex("buttontex");

	padding = 10;
	
}

void Window::setCloseButtonCallBack(onClick callback) {
	closebutton.setCallback(callback);
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

	closebutton.render();

	for (unsigned i = 0; i < components.size(); i++) {
		components.at(i)->render();
	}

	RNDR->RenderModePerspective();
}

void Window::move(int x, int y) {

}

bool Window::testClick(int x, int y) {
	if (x > tlscreen.x() && x < brscreen.x() && y < brscreen.y() && y > tlscreen.y()) {
		if (closebutton.testClick(x, y)) {
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

void Window::addComponent(WndComponent * toadd, int widthprcnt, int heightprcnt) {
	int nwidth = (brscreen.x() - tlscreen.x()) * (widthprcnt / 100.0f);
	nwidth -= 2 * padding;
	int nheight = (brscreen.y() - tlscreen.y()) * (heightprcnt / 100.0f);
	nheight -= 2 * padding;
	
	toadd->setWidth(nwidth);
	toadd->setHeight(nheight);
	toadd->setPos(calcComponentPlacement(toadd));

	components.push_back(toadd);
}

void Window::addComponent(WndComponent * toadd) {
	toadd->setPos(calcComponentPlacement(toadd));
	components.push_back(toadd);
}

vec2 Window::calcComponentPlacement(WndComponent * toplace) {
	vec2 tmp(tlscreen.x() + padding, tlscreen.y() + 32 + padding);
	
	if (components.size() == 0) return tmp;
	
	int lasty = components.at(components.size() - 1)->getPos().y();
	int lastx = components.at(components.size() - 1)->getPos().x();
	
	int lastw = 0;

	for (unsigned i = 0; i < components.size(); i++) {
		if (components.at(i)->getPos().y() == lasty)
			lastw += components.at(i)->getWidth();
	}

	int lasth = components.at(components.size() - 1)->getHeight();
	
	if (lastw + toplace->getWidth() > brscreen.x() - tlscreen.x()) {
		tmp.sy(lasth + lasty);
	}
	else {
		tmp.sx(lastx + components.at(components.size() - 1)->getWidth());
		tmp.sy(lasty);
	}
}