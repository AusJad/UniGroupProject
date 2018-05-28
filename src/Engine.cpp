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

	return true;
}

void Engine::renderLoad() {
	RNDR->startRenderCycle();
	RNDR->RenderFacingCamera();
	LSM->callFunction<AssetManager>("renderLoad", *Singleton<AssetManager>::getInstance());
	RNDR->StopRenderFacingCamera();
	RNDR->endRenderCycle();
}

void Engine::Run() {
	while (RNDR->shouldContinue()) {
		RNDR->startRenderCycle();

		SM->update(RNDR->getTimeSinceUpdate());

		SM->render();

		Singleton<AudioEngine>::getInstance()->update();
		
		FNT_ENG->update();

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