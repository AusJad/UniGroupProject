#pragma once

#include "WindowFactory.h"
#include "fileNameReader.h"
#include "ItemScrollComponent.h"
#include "SceneManager.h"
#include "EngineStateWriter.h"
#include "Alert.h"
#include "ModelManger.h"

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	bool isActive();

	bool init(onClick playGameCallBack);

	void render();

	void update(float time);

	bool testClick(int x, int y);

	void show();

	void hide();

private:
	enum MenuState {
		inactive = 0,
		menu = 1,
		selectlvl = 2
	};

	float modelrotz;
	float modelrot;
	Model * menubackmodel;

	static onClick playcallback;

	static MenuState state;

	static Window * options;

	static ButtonComponent * play;
	static ButtonComponent * lvlselect;
	static ButtonComponent * quit;

	static Window * levelselector;

	static ItemScrollComponent * lvllist;
	static LabelComponent * selectedlevel;

	static std::string selectedlevelraw;

	static void windowResizeCallback(int nwidth, int nheight);

	bool initLevelBar();

	static void levelSelectCallback(int code);
	static void quitGameCallback(int code);
	static void returnToMain(int code);
	static void lvlSelectCallback(int code);

	static void loadLevelPlayCallback(int code);
	static void loadLevelEditCallback(int code);
	static void deleteLevelCallback(int code);
	static void createNewLevelCallback(int code);

	static void checkItemListSize();
	
	Window * getActiveWindow();
};

