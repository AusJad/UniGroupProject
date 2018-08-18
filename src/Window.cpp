#include "Window.h"

Window::Window(vec2 & stpos, float width, float height, std::string title)
{
	//bgtex = WND_HEADER_BG;

	tlscreen = stpos;
	brscreen = vec2(tlscreen.x() + width, tlscreen.y() + height);
	hasHeader = true;
	visible = true;
	
	padding = 10;

	if (hasHeader) initHeader(title);
	
}

void Window::disableHeader() {
	hasHeader = false;
}

void Window::centerInDisplay() {
	float centery = (float)RNDR->getWinHeight();
	centery /= 2;
	centery -= this->getHeight() / 2;

	float centerx = (float)RNDR->getWinWidth();
	centerx /= 2;
	centerx -= this->getWidth() / 2;

	this->placeAt(centerx, centery);
}

float Window::getHeight() {
	return brscreen.y() - tlscreen.y();
}

float Window::getWidth() {
	return brscreen.x() - tlscreen.x();
}

void Window::initHeader(std::string title) {
	closebutton = ButtonComponent(HEAD_BAR_SIZE, HEAD_BAR_SIZE, vec2(brscreen.x() - HEAD_BAR_SIZE, tlscreen.y()));
	closebutton.setTex(BUTTON_CLOSE);
	
	header.setPos(tlscreen);
	header.setHeight(HEAD_BAR_SIZE);
	header.setWidth((int) (brscreen.x() - tlscreen.x() - HEAD_BAR_SIZE));
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

void Window::update(float time) {
	if (mvdata.moving) {
		move(mvdata.offset.x(), mvdata.offset.y());
	}

	for (unsigned i = 0; i < components.size(); i++) {
		components.at(i)->update(time);
	}
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

	if (bgtex.empty()) {
		GeoStream << START_ATTRIB << UI_LIGHT_COLOR;
		RNDR->DrawQuadOrtho(tlscreen, vec2(brscreen.x(), tlscreen.y() + INPUT_BORDER));
		RNDR->DrawQuadOrtho(tlscreen, vec2(tlscreen.x() + INPUT_BORDER, brscreen.y()));
		RNDR->DrawQuadOrtho(vec2(brscreen.x() - INPUT_BORDER, tlscreen.y()), vec2(brscreen.x(), brscreen.y()));
		RNDR->DrawQuadOrtho(vec2(tlscreen.x(), brscreen.y() - INPUT_BORDER), vec2(brscreen.x(), brscreen.y()));
		GeoStream << END_ATTRIB;
	}

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

void Window::placeAt(float x, float y) {
	float diffx = x - tlscreen.x();
	float diffy = y - tlscreen.y();

	move(diffx, diffy);
}

void Window::move(float x, float y) {
	tlscreen = vec2(tlscreen.x() + x, tlscreen.y() + y);
	brscreen = vec2(brscreen.x() + x, brscreen.y() + y);
	mvdata.offset = vec2();

	if (hasHeader) {
		header.move(x, y);
		closebutton.move(x, y);
	}

	for (unsigned i = 0; i < components.size(); i++) {
		components.at(i)->move(x, y);
	}
}

bool Window::testClick(int x, int y) {
	if (x > tlscreen.x() && x < brscreen.x() && y < brscreen.y() && y > tlscreen.y()) {
		if (hasHeader) {
			if (header.testClick(x, y)) {
				mvdata.moving = true;
				mvdata.inital = vec2((float) x, (float) y);
				mvdata.offset = vec2();
				CONT->switchContextMenuMove(&mvdata);

				return true;
			}

			if (closebutton.testClick(x, y)) {
				visible = false;
				return true;
			}
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
	int nwidth = (int) ((brscreen.x() - tlscreen.x()) * (widthprcnt / 100.0f));
	nwidth -= 2 * padding;

	int nheight;
	if(hasHeader) nheight = (int) ((brscreen.y() - tlscreen.y() - HEAD_BAR_SIZE) * (heightprcnt / 100.0f));
	else nheight = (int) ((brscreen.y() - tlscreen.y()) * (heightprcnt / 100.0f));

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
	
	int lasty = (int) components.at(components.size() - 1)->getPos().y();
	int lastx = (int) components.at(components.size() - 1)->getPos().x();
	
	int lastw = 0;

	for (unsigned i = 0; i < components.size(); i++) {
		if (components.at(i)->getPos().y() == lasty)
			lastw += components.at(i)->getWidth();
	}

	int lasth = components.at(components.size() - 1)->getHeight();
	
	if (lastw + toplace->getWidth() > brscreen.x() - tlscreen.x()) {
		tmp.sy((float) lasth + lasty + padding);
	}
	else {
		tmp.sx((float) lastx + components.at(components.size() - 1)->getWidth());
		tmp.sy((float) lasty);
	}

	return tmp;
}

void Window::FitToContent() {
	if (components.empty()) return;

	float min = components.at(components.size() - 1)->getPos().y() + components.at(components.size() - 1)->getHeight() + padding;

	brscreen.sy(min);
}