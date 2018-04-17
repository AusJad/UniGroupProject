#pragma once

#include "AssetManager.h"
#include "AudioEngine.h"
#include "LUAScriptManager.h"
#include "ModelManger.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"
#include "MessagingBus.h"
#include "Controls.h"
#include "RenderModuleStubb.h"

typedef Singleton<AssetManager> assetmngr;
typedef Singleton<AudioEngine> audioeng;
typedef Singleton<LUAScriptManager> luasmngr;
typedef Singleton<ModelManger> mdlmngr;
typedef Singleton<TextureManager> texmngr;
typedef Singleton<GameObjectFactory> gameobjfact;
typedef Singleton<MessagingBus> msgbus;
typedef Singleton<Controls> controls;
typedef Singleton<RenderModuleStubb> rndermod;

#define AMAN assetmngr::getInstance()
#define AE audioeng::getInstance()
#define LSM luasmngr::getInstance()
#define MDLMAN mdlmngr::getInstance()
#define TXMAN texmngr::getInstance()
#define GOF gameobjfact::getInstance()
#define MSGBS msgbus::getInstance()
#define CONT controls::getInstance()
#define RNDR rndermod::getInstance()