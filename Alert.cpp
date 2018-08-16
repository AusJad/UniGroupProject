#include "Alert.h"

Alert::Alert()
{
	alert = NULL;
	alert = NULL;
	yes = NULL;
	no = NULL;
	prompt = NULL;
}


Alert::~Alert(){
	delete alert;
}

void Alert::hide() {
	alert->hide();
}

void Alert::update(float time) {
	alert->update(time);
}

void Alert::render() {
	alert->render();
}

bool Alert::isVis() {
	return alert->isVis();
}

void Alert::setPrompt(std::string toset) {
	prompt->setLabel(toset);
}

void Alert::show() {
	alert->show();
}

void Alert::done() {
	alert->hide();
	prompt->setLabel("No Label Set");
	yes->setCallback(NULL);
	yes->setCallback(NULL);
}

void Alert::doAlert(std::string label, onClick yes, onClick no) {
	prompt->setLabel(label);
	
	float centery = (float) RNDR->getWinHeight();
	centery /= 2;
	centery -= alert->getHeight() / 2;

	float centerx = (float)RNDR->getWinWidth();
	centerx /= 2;
	centerx -= alert->getWidth() / 2;

	alert->placeAt(centerx, centery);

	if(no == NULL) this->no->setCallback(defaultNo);
	else this->no->setCallback(no);
		
	this->yes->setCallback(yes);
	show();
}

void Alert::setNoCallback(onClick toset) {
	no->setCallback(toset);
}

void Alert::setYesCallback(onClick toset) {
	yes->setCallback(toset);
}

bool Alert::testClick(int x, int y) {
	if (alert->isVis()) return alert->testClick(x, y);
	else return false;
}

bool Alert::init() {
	alert = WindowFactory::getWindow(WINDOW_SMALL_WIDE, "GENERIC", vec2(768, 592), "Alert!");
	if (alert == NULL) return false;

	prompt = new LabelComponent();
	if (prompt == NULL) return false;
	prompt->setLabel("No Label Set");
	alert->addComponent(prompt, 100, 50);

	yes = new ButtonComponent();
	if (yes == NULL)return false;
	yes->setTitle("Yes");
	alert->addComponent(yes, 50, 50);

	no = new ButtonComponent();
	if (no == NULL) return false;
	no->setTitle("No");
	alert->addComponent(no, 50, 50);

	alert->hide();

	return true;
}

void Alert::defaultNo(int code) {
	ALERT->done();
}