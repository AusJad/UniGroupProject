#pragma once

#include "WindowFactory.h"

#define ALERT Singleton<Alert>::getInstance()

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

private:
	Window * alert;
	ButtonComponent * yes;
	ButtonComponent * no;
	LabelComponent * prompt;

	static void defaultNo(int code);
};

