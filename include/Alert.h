#pragma once

#include "WindowFactory.h"

#define ALERT Singleton<Alert>::getInstance()

/**
* @class Alert
*
* @author Morgan Smolder
*/
class Alert
{
public:
	Alert();
	~Alert();

	void render();

	bool isVis();
	void setPrompt(std::string toset);
	void show();
	void hide();

	void update(float time);
	void setNoCallback(onClick toset);
	void setYesCallback(onClick toset);
	bool testClick(int x, int y);
	bool init();
	void done();

	void doAlert(std::string label, onClick yes, onClick no);

	void doNotify(std::string label, onClick callback);
	void notifyDone();

private:
	Window * alert;
	Window * notification;

	ButtonComponent * ok;
	ButtonComponent * yes;
	ButtonComponent * no;

	LabelComponent * prompt;
	LabelComponent * notificationtxt;

	static void defaultNo(int code);

	static void defaultOk(int code);
};

