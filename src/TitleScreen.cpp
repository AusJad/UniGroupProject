#include "TitleScreen.h"

Window * TitleScreen::logo = NULL;

TitleScreen::TitleScreen()
{
	fadeprcnt = 1.0f;
	fadeinc = -0.5f;
	progress = fadein;
}


TitleScreen::~TitleScreen()
{
	delete logo;
}

bool TitleScreen::init() {
	logo = WindowFactory::getWindow(WINDOW_MEDIUM_SQUARE, "NO_HEADER", vec2(0, 0));
	if (logo == NULL) return false;

	logo->setPadding(0);

	ButtonComponent * b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setTex(G1_LOGO);
	logo->addComponent(b, 100, 100);
	
	logo->show();

	logo->centerInDisplay();

	RNDR->addResizeCallBack(onresize);

	return true;
}

void TitleScreen::update(float time) {
	fadeprcnt += fadeinc * time;

	progressNextStage();
}

void TitleScreen::render() {
	if (progress != showmainmenu) logo->render();

	if (fadeprcnt >= 0) {
		RNDR->RenderModeOrtho();
		GeoStream << ENABLE_TRANSPARENCY << START_ATTRIB << color_4(0, 0, 0, fadeprcnt);
		RNDR->DrawQuadOrtho(vec2(), vec2((float) RNDR->getWinWidth(), (float) RNDR->getWinHeight()));
		RNDR->DrawQuad(point(-100, -100), point(100, 100), -1);
		GeoStream << END_ATTRIB << DISABLE_TRANSPARENCY;
		RNDR->RenderModePerspective();
	}
}

bool TitleScreen::canRenderMenu() {
	return progress == showmainmenu;
}

void TitleScreen::progressNextStage() {
	switch (progress) {
		case 	fadein:
			if (fadeprcnt <= -1.0f) {
				progress = hidelogo;
				fadeinc = 0.7f;
			}
		case	hidelogo:
			if (fadeprcnt >= 1.0f) {
				progress = showmainmenu;
				fadeinc = -0.7f;
			}
	}
}

bool TitleScreen::done() {
	if (progress == showmainmenu && fadeprcnt <= -1) return true;

	return false;
}

void TitleScreen::onresize(int nwidth, int nheight) {
	logo->centerInDisplay();
}