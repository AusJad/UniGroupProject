#include "Window.h"



Window::Window(vec2 & stpos, float width, float height, std::string title)
{
	//bgtex = WINDOW_BG;

	tlscreen = stpos;
	brscreen = vec2(tlscreen.x() + width, tlscreen.y() + height);
	hasHeader = true;
	visible = true;

	padding = 10;

	if (hasHeader) initHeader(title);
	
}

void Window::initHeader(std::string title) {
	closebutton = ButtonComponent(HEAD_BAR_SIZE, HEAD_BAR_SIZE, vec2(brscreen.x() - HEAD_BAR_SIZE, tlscreen.y()));
	closebutton.setTex(BUTTON_CLOSE);
	
	header.setPos(tlscreen);
	header.setHeight(HEAD_BAR_SIZE);
	header.setWidth(brscreen.x() - tlscreen.x() - HEAD_BAR_SIZE);
	header.setPadding(6);
	header.setTex(WND_HEADER_BG);

	header.setLabel(title);
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

	//render background - either ui base color or texture
	if (!bgtex.empty()) TXMAN->useTexture(bgtex, RNDR);
	else GeoStream << START_ATTRIB << UI_BASE_COLOR;

	RNDR->DrawQuadOrtho(tlscreen, brscreen);
	
	if (!bgtex.empty()) TXMAN->disableTexture(RNDR);
	else GeoStream << END_ATTRIB;
	
	//render header bar
	if (hasHeader) {
		header.render();
		closebutton.render();
	}

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
	vec2 tmp;
	
	if(hasHeader) tmp = vec2(tlscreen.x() + padding, tlscreen.y() + HEAD_BAR_SIZE + padding);
	else tmp = vec2(tlscreen.x() + padding, tlscreen.y() + padding);
	
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