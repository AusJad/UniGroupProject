#include "Engine.h"
	
bool Engine::Initalise(std::string initscript){
	if (!initaliseScriptingInterface()) return false;
	if (!initaliseRenderer()) return false;
	if (!initaliseAudioEngine()) return false;

	if(!Singleton<LUAScriptManager>::getInstance()->doScriptFromFile(initscript)) return false;

	Singleton<LUAScriptManager>::getInstance()->callFunction<SceneManager, LUAScriptManager, AssetManager, AudioEngine>("initGame", SM, *Singleton<LUAScriptManager>::getInstance(), *Singleton<AssetManager>::getInstance(), *Singleton<AudioEngine>::getInstance());

	return true;
}

void Engine::Run() {
	while (Singleton<RenderModuleStubb>::getInstance()->shouldContinue()) {
		Singleton<RenderModuleStubb>::getInstance()->startRenderCycle();

		SM.update(Singleton<RenderModuleStubb>::getInstance()->getTimeSinceUpdate());

		SM.render();

		Singleton<AudioEngine>::getInstance()->update();
		
		Singleton<RenderModuleStubb>::getInstance()->endRenderCycle();
	}
}

bool Engine::initaliseScriptingInterface() {
	LUAScriptManager* LSM = Singleton<LUAScriptManager>::getInstance();
	if (!LSM->initLuaState()) return false;
	CtoLUABinder().bindClasses(LSM->getState());

	return true;
}

bool Engine::initaliseRenderer() {
	RenderModuleStubb* RNDR = Singleton<RenderModuleStubb>::getInstance();

	//BAD!!!! temporary while mat does rendering
	RNDR->init(0, NULL);
	
	return true;
}


bool Engine::initaliseAudioEngine() {
	AudioEngine* AE = Singleton<AudioEngine>::getInstance();

	AE->initalise(Singleton<RenderModuleStubb>::getInstance()->getWinWindow());
	
	return true;
}