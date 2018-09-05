#include "MainMenu.h"

Window * MainMenu::options = NULL;
ButtonComponent * MainMenu::play = NULL;
ButtonComponent * MainMenu::lvlselect = NULL;
ButtonComponent * MainMenu::quit = NULL;

Window * MainMenu::levelselector = NULL;
ItemScrollComponent * MainMenu::lvllist = NULL;

MainMenu::MenuState MainMenu::state = inactive;

LabelComponent * MainMenu::selectedlevel = NULL;

std::string MainMenu::selectedlevelraw;

onClick MainMenu::playcallback = NULL;

bool MainMenu::canedit = true;

MainMenu::MainMenu(){
	modelrot = 90;
	modelrotz = 45;
	menubackmodel = NULL;
}

MainMenu::~MainMenu(){
	if (options != NULL) delete options;
	if (menubackmodel != NULL) delete menubackmodel;
	if (levelselector != NULL) delete levelselector;
}

bool MainMenu::isActive() {
	return state != inactive;
}

bool MainMenu::init(onClick playGameCallBack) {
	playcallback = playGameCallBack;

	if (!titlescrn.init()) return false;

	options = WindowFactory::getWindow(WINDOW_MEDIUM_WIDE, "NO_HEADER", vec2(0, 0));
	if (options == NULL) return false;
	options->setBGTex("menubg.tga");

	ButtonComponent * m = NULL;
	m = new ButtonComponent();
	if (m == NULL) return false;
	m->setTex("mmlogotx.tga");
	m->setWidth(490);
	m->setHeight(245);
	options->addComponent(m);

	play = new ButtonComponent();
	if (play == NULL) return false;
	play->setTitle("Continue Game");
	play->setCallback(playGameCallBack);
	options->addComponent(play, 100, 10);

	lvlselect = new ButtonComponent();
	if (lvlselect == NULL) return false;
	lvlselect->setTitle("Select Level");
	lvlselect->setCallback(levelSelectCallback);
	options->addComponent(lvlselect, 100, 10);

	quit = new ButtonComponent();
	if (quit == NULL) return false;
	quit->setTitle("Quit");
	quit->setCallback(quitGameCallback);
	options->addComponent(quit, 100, 10);

	options->FitToContent();

	levelselector = WindowFactory::getWindow(WINDOW_MEDIUM_WIDE, "NO_HEADER", vec2(0, 0));
	if (levelselector == NULL) return false;
	levelselector->setBGTex("menubg.tga");

	if(!initLevelBar()) return false;

	levelselector->FitToContent();

	RNDR->addResizeCallBack(windowResizeCallback);
	windowResizeCallback(0, 0);

	menubackmodel = MMAN->useModel("corvet.obj", "");
	if (menubackmodel == NULL) return false;
	menubackmodel->setScale(vec3(2, 2, 2));

	return true;
}

void MainMenu::levelSelectCallback(int code) {
	state = selectlvl;
}

void MainMenu::render() {
	static Window * active;
	
	if (titlescrn.canRenderMenu()) {
		RNDR->RenderFacingCamera();
		RNDR->enableWireframe();
		GeoStream << BEGIN_STREAM << rot_4(modelrot, 0, 1, 0) << rot_4(modelrotz, 0, 0, 1);
		menubackmodel->render(vec3());
		GeoStream << END_STREAM;
		RNDR->disableWireFrame();
		RNDR->StopRenderFacingCamera();

		active = getActiveWindow();

		if (active != NULL) active->render();
	}

	if (!titlescrn.done()) {
		titlescrn.render();
	}
}

void MainMenu::update(float time) {
	static Window * active;

	if (!titlescrn.done()) {
		titlescrn.update(time);
	}
	else{
		active = getActiveWindow();

		if (active != NULL) active->update(time);
	}
	modelrot += 1.5f * time;
	if (modelrot >= 360) modelrot = 0.0f;

	modelrotz += 0.5f * time;
	if (modelrotz >= 360) modelrotz = 0.0f;
}

bool MainMenu::testClick(int x, int y) {
	static Window * active;

	if (titlescrn.canRenderMenu()) {
		active = getActiveWindow();

		if (active != NULL) return active->testClick(x, y);
	}
	return false;
}

Window * MainMenu::getActiveWindow() {
	switch (state) {
		case menu:
			return options;
			break;
		case selectlvl:
			return levelselector;
			break;
	}

	return NULL;
}

void MainMenu::show() {
	state = menu;
}

void MainMenu::hide() {
	state = inactive;
}

void MainMenu::windowResizeCallback(int nwidth, int nheight) {
	options->centerInDisplay();
	levelselector->centerInDisplay();
}

bool MainMenu::initLevelBar() {
	ButtonComponent * b = NULL;
	LabelComponent * l = NULL;

	if (!fileNameReader::getFileNames("./Resources/Levels/", ".lvl")) {
		std::cerr << "Note to Programmer: Vital Directory './Resources/Levels/' Does Not Exist." << std::endl;
		return false;
	}
	else {
		l = new LabelComponent();
		if (l == NULL) return false;

		l->setLabel("Select Level:");
		levelselector->addComponent(l, 100, 5);

		lvllist = new ItemScrollComponent();
		if (lvllist == NULL) return false;

		while (fileNameReader::hasFiles()) {
			lvllist->addOption(fileNameReader::getFile(), lvlSelectCallback);
		}

		checkItemListSize();

		levelselector->addComponent(lvllist, 100, 40);

		selectedlevel = new LabelComponent();
		if (selectedlevel == NULL) return false;
		selectedlevel->setLabel("Selected Level: No Level Selected.");

		levelselector->addComponent(selectedlevel, 100, 5);

		b = new ButtonComponent(); 
		if (b == NULL) return false;
		b->setTitle("Play Level");
		b->setCallback(loadLevelPlayCallback);

		levelselector->addComponent(b, 100, 10);

		b = NULL;
		b = new ButtonComponent();
		if (b == NULL) return false;
		b->setTitle("Edit Level");
		b->setCallback(loadLevelEditCallback);

		levelselector->addComponent(b, 100, 10);

		b = NULL;
		b = new ButtonComponent();
		if (b == NULL) return false;
		b->setTitle("Delete Level");
		b->setCallback(deleteLevelCallback);

		levelselector->addComponent(b, 100, 10);

		b = NULL;
		b = new ButtonComponent();
		if (b == NULL) return false;
		b->setTitle("Create New Level"); 
		b->setCallback(createNewLevelCallback);

		levelselector->addComponent(b, 100, 10);
	}

	b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setTitle("Go Back");
	b->setCallback(returnToMain);

	levelselector->addComponent(b, 100, 10);

	return true;
}

void MainMenu::checkItemListSize() {
	if (lvllist->getNumOptions() == 0) {
		lvllist->addOption("No Levels to Show!", NULL);
	}
}

void MainMenu::quitGameCallback(int code) {
	RNDR->killProgram();
}

void MainMenu::returnToMain(int code) {
	state = menu;
}

void MainMenu::lvlSelectCallback(int code) {
	std::string val = lvllist->getOptionvalue(code);

	selectedlevel->setLabel("Selected Level: " + val);

	selectedlevelraw = val;
}

void MainMenu::deleteLevelCallback(int code) {
	if (selectedlevelraw == "") {
		ALERT->doNotify("Select a Level First!", NULL);
		return;
	}

	if (remove(("./Resources/Levels/" + selectedlevelraw).c_str()) != 0) {
		ALERT->doNotify("Unkown Error! Could Not Delete File.", NULL);
	}
	else {
		ALERT->doNotify("File Deleted Successfully.", NULL);
		lvllist->removeOption(selectedlevelraw);
		selectedlevelraw = "";
		selectedlevel->setLabel("Selected Level: No Level Selected.");
		checkItemListSize();
	}
}

void  MainMenu::loadLevelPlayCallback(int code) {
	if (selectedlevelraw == "") {
		ALERT->doNotify("Select a Level First!", NULL);
		return;
	}

	Wall::DisableBB();

	canedit = false;

	SM->getGOH().clear();

	CAM->getActiveCam()->reset();

	if (!EngineStateWriter::readState("./Resources/Levels/" + selectedlevelraw)) {
		ALERT->doNotify("Failed to Load Level: Invalid Data", NULL);
	}
	else {
		if (playcallback != NULL) playcallback(0);
	}
}

void  MainMenu::loadLevelEditCallback(int code) {
	if (selectedlevelraw == "") {
		ALERT->doNotify("Select a Level First!", NULL);
		return;
	}

	canedit = true;

	SM->getGOH().clear();

	CAM->getActiveCam()->reset();

	if (!EngineStateWriter::readState("./Resources/Levels/" + selectedlevelraw)) {
		ALERT->doNotify("Failed to Load Level: Invalid Data", NULL);
	}
	else {
		if (playcallback != NULL) playcallback(0);
	}

}

void  MainMenu::createNewLevelCallback(int code) {
	canedit = true;
	SM->getGOH().clear();
	if (playcallback != NULL) playcallback(0);
}