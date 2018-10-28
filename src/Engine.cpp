#include "Engine.h"

bool Engine::Initalise(std::string initscript){
	if (!initaliseScriptingInterface()) return false;
	
	if (!initaliseRenderer()) return false;
	if (!initaliseAudioEngine()) return false;
	if (!LSM->doScriptFromFile(initscript)) return false;

	if (LSM->callFunction<AssetManager>("loadLoadRes", *Singleton<AssetManager>::getInstance())) {
		renderLoad();
	}

	LSM->callFunction<SceneManager, LUAScriptManager, AssetManager, AudioEngine>("initGame", *SM, *LSM, *Singleton<AssetManager>::getInstance(), *Singleton<AudioEngine>::getInstance());
	
	CONT->registerCallbacks(SwitchInterfaceContext);
	CONT->registerGUICallback(SwitchPlayContext);
	CONT->registerGUIMMCallback(SwitchMainMenuContext);
	CONT->switchContextPlay();

	TXMAN->loadBatch(UI_TEX_GROUP, "./Resources/Textures/UI/", "TGA");
	TXMAN->loadBatch(WALL_TEX_GROUP, "./Resources/Textures/WallTex/", "TGA");
	MMAN->loadBatch(MODEL_MAIN_GROUP, "./Resources/Models/", "IM", "obj");
	MMAN->loadBatch(MODEL_AGENT_GROUP, "./Resources/Models/", "MD2", "md2");
	MMAN->loadBatch(TERRAIN_GROUP, "./Resources/Models/", "RAWTRN", "tdef");
	AE->loadBatch(MAIN_SOUND_BANK, "./Resources/Audio/", "WAV", "wav");

	if (!GI->initalise()) return false;
	GI->setState(mainmenu);
	AE->playSound(MAIN_MENU_MUSIC);

	return true;
}

void Engine::renderLoad() {
	RNDR->startRenderCycle();
	RNDR->RenderFacingCamera();
	LSM->callFunction<AudioEngine>("renderLoad", *AE);
	RNDR->StopRenderFacingCamera();
	RNDR->endRenderCycle();
}

void Engine::Run() {
	float time;

	while (RNDR->shouldContinue()) {
		RNDR->startRenderCycle();

		time = RNDR->getTimeSinceUpdate();

		if (GI->getState() != mainmenu) {
			SM->update(time);
		}
		GI->update(time);
		AE->update(vec3(), vec3(), vec3());
		FNT_ENG->update();
		CONT->update();

		if (GI->getState() != mainmenu)	SM->render();
		GI->render();

		RNDR->endRenderCycle();
	}
}

bool Engine::initaliseScriptingInterface() {
	if (!LSM->initLuaState()) return false;
	CtoLUABinder().bindClasses(LSM->getState());

	return true;
}

bool Engine::initaliseRenderer() {
	RNDR->init(0, NULL);
	
	return true;
}


bool Engine::initaliseAudioEngine() {
	AE->initalise(Singleton<RenderModuleStubb>::getInstance()->getWinWindow());
	
	return true;
}

void Engine::SwitchInterfaceContext() {
	if (GI->canEdit()) {
		CONT->switchContextGUIInteract();
		GI->setState(editorst);
	}
}

void Engine::SwitchPlayContext() {
	CONT->switchContextPlay();
	GI->setState(inactive);
}

void Engine::SwitchMainMenuContext() {
	CONT->switchContextGUIInteract();
	GI->setState(mainmenu);
}