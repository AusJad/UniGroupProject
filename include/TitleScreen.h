#pragma once

#include "WindowFactory.h"

enum renderstage {
	fadein = 0,
	hidelogo = 1,
	showmainmenu = 2
};

/**
* @class TitleScreen
*
* @author Morgan Smolder
*/
class TitleScreen
{
public:
	TitleScreen();
	~TitleScreen();

	bool init();
	void update(float time);
	void render();
	bool done();
	bool canRenderMenu();

private:
	static Window * logo;
	float fadeprcnt;
	float fadeinc;

	renderstage progress;

	static void onresize(int nwidth, int nheight);
	void progressNextStage();
};

