#include "Alert.h"

Alert::Alert()
{
	alert = NULL;
	alert = NULL;
	yes = NULL;
	no = NULL;
	prompt = NULL;
	notification = NULL;
	ok = NULL;
	notificationtxt = NULL;
}


Alert::~Alert(){
	delete alert;
	delete notification;
}

void Alert::hide() {
	if(alert->isVis()) alert->hide();
	if (notification->isVis()) notification->hide();
}

void Alert::update(float time) {
	if(alert->isVis()) alert->update(time);
	if (notification->isVis()) notification->update(time);
}

void Alert::render() {
	if (alert->isVis()) alert->render();
	if (notification->isVis()) notification->render();
}

bool Alert::isVis() {
	return alert->isVis() || notification->isVis();
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
	alert->show();
}

void Alert::setNoCallback(onClick toset) {
	no->setCallback(toset);
}

void Alert::setYesCallback(onClick toset) {
	yes->setCallback(toset);
}

bool Alert::testClick(int x, int y) {
	if (alert->isVis()) return alert->testClick(x, y);
	else if (notification->isVis()) return notification->testClick(x, y);
	else return false;
}

bool Alert::init() {
	//init alert
	alert = WindowFactory::getWindow(WINDOW_SMALL_WIDE, "GENERIC", vec2(0, 0), "Alert!");
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

	alert->FitToContent();
	alert->hide();

	//init notification
	notification = WindowFactory::getWindow(WINDOW_SMALL_WIDE, "GENERIC", vec2(0, 0), "Notification");
	if (notification == NULL) return false;

	notificationtxt = new LabelComponent();
	if (notificationtxt == NULL) return false;
	notificationtxt->setLabel("No Label Set");
	notification->addComponent(notificationtxt, 100, 50);

	ok = new ButtonComponent();
	if (ok == NULL) return false;
	ok->setTitle("Ok");
	notification->addComponent(ok, 100, 50);

	notification->FitToContent();
	notification->hide();

	return true;
}


void Alert::doNotify(std::string label, onClick callback) {
	notificationtxt->setLabel(label);

	float centery = (float)RNDR->getWinHeight();
	centery /= 2;
	centery -= notification->getHeight() / 2;

	float centerx = (float)RNDR->getWinWidth();
	centerx /= 2;
	centerx -= notification->getWidth() / 2;

	notification->placeAt(centerx, centery);

	if (callback == NULL) this->ok->setCallback(defaultOk);
	else this->ok->setCallback(callback);

	notification->show();
}

void Alert::notifyDone() {
	notification->hide();
	notificationtxt->setLabel("No Label Set");
	ok->setCallback(NULL);
}

void Alert::defaultNo(int code) {
	ALERT->done();
}

void Alert::defaultOk(int code) {
	ALERT->notifyDone();
}