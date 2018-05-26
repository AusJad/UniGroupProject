#include "CtoLUABinder.h"


void CtoLUABinder::bindClasses(lua_State* lstate) {
	luabind::module(lstate)[
		luabind::class_<SceneManager>("SceneManager")
			.def(luabind::constructor<>())
			.def("addObject", &SceneManager::addObject)
			.def("addScene", &SceneManager::addScene)
			.def("setCurrScene", &SceneManager::setCurrScene)
			.def("GetGameObjectID", &SceneManager::GetGameObjectID)
			.def("GetGameObject", &SceneManager::GetGameObject)
			.def("setSceneHeightMap", &SceneManager::setSceneHeightMap)
			.def("attachControls", &SceneManager::attachControls)
			.def("attachTerrain", &SceneManager::attachTerrain)
			.def("attachConsoleBehaviour", &SceneManager::attachConsoleBehaviour)
			.def("attachConsoleTex", &SceneManager::attachConsoleTex)
			.def("setSceneResources", &SceneManager::setSceneResources)
	];
	luabind::module(lstate)[
		luabind::class_<Scene>("Scene")
			.def(luabind::constructor<>())
			.def("GetGameObject", &Scene::GetGameObject)
			.def("getState", &Scene::getState)
			.def("setState", &Scene::setState)
			.def("getLoaded", &Scene::getLoaded)
	];
	luabind::module(lstate)[
		luabind::class_<vec3>("vec3")
			.def(luabind::constructor<>())
			.def(luabind::constructor<float, float, float>())
			.def("x", &vec3::sx)
			.def("y", &vec3::sy)
			.def("z", &vec3::sz)
			.def("x", &vec3::x)
			.def("y", &vec3::y)
			.def("z", &vec3::z)
			.def(luabind::self + vec3())
			.def(luabind::self - vec3())
			.def(luabind::self / vec3())
			.def(luabind::self * vec3())
	];
	luabind::module(lstate)[
		luabind::class_<vec2>("vec2")
			.def(luabind::constructor<>())
			.def(luabind::constructor<float, float>())
			.def("x", &vec2::sx)
			.def("y", &vec2::sy)
			.def("x", &vec2::x)
			.def("y", &vec2::y)
			.def(luabind::self + vec2())
			.def(luabind::self - vec2())
			.def(luabind::self / vec2())
	];
	luabind::module(lstate)[
		luabind::class_<vec4>("vec4")
			.def(luabind::constructor<>())
			.def(luabind::constructor<float, float, float, float>())
			.def("x", &vec4::sx)
			.def("y", &vec4::sy)
			.def("z", &vec4::sz)
			.def("w", &vec4::sw)
			.def("x", &vec4::x)
			.def("y", &vec4::y)
			.def("z", &vec4::z)
			.def("w", &vec4::w)
			.def(luabind::self + vec4())
			.def(luabind::self - vec4())
			.def(luabind::self / vec4())
	];
	luabind::module(lstate)[
		luabind::class_<LUAScriptManager >("LUAScriptManager")
			.def(luabind::constructor<>())
			.def("loadScript", &LUAScriptManager::loadScript)
			.def("doScriptFromFile", &LUAScriptManager::doScriptFromFile)
	];
	luabind::module(lstate)[
		luabind::class_<NPC>("NPC")
			.def(luabind::constructor<>())
			.def(luabind::constructor<Identifiers &, vec3, ResourceList>())
			.def("setPos", &NPC::setPos)
			.def("getPos", &NPC::getPos)
			.def("setState", &NPC::setState)
			.def("getState", &NPC::getState)
			.def("getID", &NPC::getID)
			.def("getIdentifiers", &NPC::getIdentifiers)
			.def("getHealth", &NPC::getHealth)
			.def("setHealth", &NPC::setHealth)
			.def("getVelocity", &NPC::getVelocity)
			.def("setVelocity", &NPC::setVelocity)
			.def("getTarget", &NPC::getTarget)
			.def("setTarget", &NPC::setTarget)
			.def("getSpeed", &NPC::getSpeed)
			.def("setSpeed", &NPC::setSpeed)
			.def("defaultMessageHandler", &NPC::defaultMessageHandler)
			.def("NPCDefaultMessageHandler", &NPC::NPCDefaultMessageHandler)
			.def("getHeading", &NPC::getHeading)
			.def("setHeading", &NPC::setHeading)
			.def("setLAngle", &NPC::setLAngle)
			.def("setUpdateable", &NPC::setUpdatable)
			.def("getCanAttack", &NPC::getCanAttack)
			.def("setCanAttack", &NPC::setCanAttack)
	];
	luabind::module(lstate)[
		luabind::class_<StaticEntity>("StaticEntity")
			.def(luabind::constructor<>())
			.def(luabind::constructor<Identifiers &, vec3, ResourceList>())
			.def("setPos", &StaticEntity::setPos)
			.def("getPos", &StaticEntity::getPos)
			.def("setState", &StaticEntity::setState)
			.def("getState", &StaticEntity::getState)
			.def("getID", &StaticEntity::getID)
			.def("getIdentifiers", &StaticEntity::getIdentifiers)
	];
	luabind::module(lstate)[
		luabind::class_<MenuObject>("MenuObject")
			.def(luabind::constructor<>())
			.def(luabind::constructor<Identifiers &, vec3, ResourceList>())
			.def("setPos", &MenuObject::setPos)
			.def("getPos", &MenuObject::getPos)
			.def("setState", &MenuObject::setState)
			.def("getState", &MenuObject::getState)
			.def("getID", &MenuObject::getID)
			.def("getIdentifiers", &MenuObject::getIdentifiers)
	];
	luabind::module(lstate)[
		luabind::class_<TerrainObject>("TerrainObject")
			.def(luabind::constructor<>())
			.def(luabind::constructor<Identifiers &, vec3, ResourceList>())
			.def("setPos", &TerrainObject::setPos)
			.def("getPos", &TerrainObject::getPos)
			.def("setState", &TerrainObject::setState)
			.def("getState", &TerrainObject::getState)
			.def("getID", &TerrainObject::getID)
			.def("getIdentifiers", &TerrainObject::getIdentifiers)
	];
	luabind::module(lstate)[
		luabind::class_<Player>("Player")
			.def(luabind::constructor<>())
			.def(luabind::constructor<Identifiers &, vec3, ResourceList>())
			.def("setPos", &Player::setPos)
			.def("getPos", &Player::getPos)
			.def("setState", &Player::setState)
			.def("getState", &Player::getState)
			.def("getID", &Player::getID)
			.def("getIdentifiers", &Player::getIdentifiers)
			.def("drawModel", &Player::drawModel)
			.def("defaultMessageHandler", &Player::defaultMessageHandler)
			.def("playerDefaultMessageHandler", &Player::playerDefaultMessageHandler)
			.def("getFront", &Player::getFront)
			.def("getHealth", &Player::getHealth)
			.def("getAmmo", &Player::getAmmo)
			.def("setHealth", &Player::setHealth)
			.def("setAmmo", &Player::setAmmo)

	];
	luabind::module(lstate)[
		luabind::class_<Scenery>("Scenery")
			.def(luabind::constructor<>())
			.def(luabind::constructor<Identifiers &, vec3, ResourceList>())
			.def("setPos", &Scenery::setPos)
			.def("getPos", &Scenery::getPos)
			.def("setState", &Scenery::setState)
			.def("getState", &Scenery::getState)
			.def("getID", &Scenery::getID)
			.def("getIdentifiers", &Scenery::getIdentifiers)
	];
	luabind::module(lstate)[
		luabind::class_<Identifiers>("Identifiers")
			.def(luabind::constructor<>())
			.def(luabind::constructor<std::string>())
			.def(luabind::constructor<std::string, std::string>())
			.def(luabind::constructor<std::string, std::string, std::string>())
			.def("setId", &Identifiers::setId)
			.def("setName", &Identifiers::setName)
			.def("setType", &Identifiers::setType)
			.def("setObjectname", &Identifiers::setObjectname)
			.def("getId", &Identifiers::getId)
			.def("getName", &Identifiers::getName)
			.def("getType", &Identifiers::getType)
			.def("getObjectname", &Identifiers::getObjectname)
	];
	luabind::module(lstate)[
		luabind::class_<MessagingBus>("MessagingBus")
			.def("getMessage", &MessagingBus::getMessage)
			.def("hasMessage", &MessagingBus::hasMessage)
			.def("postMessage", &MessagingBus::postMessage)
			.def("postIMessage", &MessagingBus::postIMessage)
	];
	luabind::module(lstate)[
		luabind::class_<Message>("Message")
			.def(luabind::constructor<std::string>())
			.def("getInstruction", &Message::getInstruction)
			.def("setInstruction", &Message::setInstruction)
			.def("setFrom", &Message::setFrom)
			.def("getFrom", &Message::getFrom)
			.def("setfData", &Message::setfData)
			.def("setiData", &Message::setIData)
			.def("setsData", &Message::setsData)
			.def("addmvData", &Message::addmvData)
			.def("getData", &Message::getData)
			.def("getiData", &Message::getiData)
			.def("getsData", &Message::getsData)
			.def("getvData", &Message::getvData)
			.def("setvData", &Message::setvData)
	];
	luabind::module(lstate)[
		luabind::class_<Data>("data")
			.def("getvData", &Data::getvData)
	];
	luabind::module(lstate)[
		luabind::class_<ResourceList>("ResourceList")
			.def(luabind::constructor<>())
			.def(luabind::constructor<std::string, std::string>())
			.def(luabind::constructor<std::string, std::string, std::string, std::string>())
			.def(luabind::constructor<std::string, std::string, std::string, std::string, std::string, std::string>())
			.def(luabind::constructor<std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string>())
			.def("hasResource", &ResourceList::hasResource)
			.def("getResource", &ResourceList::getResource)
			.def("addResource", &ResourceList::addResource)
	];
	luabind::module(lstate)[
		luabind::class_<AssetManager>("AssetManager")
			.def(luabind::constructor<>())
			.def("addResource", &AssetManager::addResource)
			.def("useResource", &AssetManager::useResource)
			.def("addModel", &AssetManager::addModel)
			.def("addSound", &AssetManager::addSound)
	];
	luabind::module(lstate)[
		luabind::class_<AudioEngine>("AudioEngine")
			.def("loadSound", &AudioEngine::loadSound)
			.def("playSoundatSource", &AudioEngine::playSoundatSource)
			.def("setListenerSource", &AudioEngine::setListenerSource)
			.def("loadSound", &AudioEngine::loadSound)
	];
	luabind::module(lstate)[
		luabind::class_<SimpleString>("SimpleString")
			.def(luabind::constructor<>())
			.def(luabind::constructor<std::string>())
			.def("equals", &SimpleString::equals)
			.def("toDouble", &SimpleString::toDouble)
			.def("getData", &SimpleString::getData)
			.def("setData", &SimpleString::setData)
	];
	luabind::module(lstate, "AIMvmnt")[
		luabind::def("Seek", &AIMovementBehaviours::Seek),
		luabind::def("Flee", &AIMovementBehaviours::Flee), 
		luabind::def("Arrive", &AIMovementBehaviours::Arrive),
		luabind::def("Chase", &AIMovementBehaviours::Chase),
		luabind::def("capSpeed", &AIMovementBehaviours::capSpeed), 
		luabind::def("getDistance", &AIMovementBehaviours::getDistance),
		luabind::def("faceTarget", &AIMovementBehaviours::faceTarget)
	];
	luabind::module(lstate, "MenuTools")[
		luabind::def("drawTSquare", &MenuTools::drawTSquare),
		luabind::def("drawSquare", &MenuTools::drawSquare),
		luabind::def("drawButton", &MenuTools::drawButton),
		luabind::def("renderText", &MenuTools::renderText),
		luabind::def("fadeIn", &MenuTools::fadeIn),
		luabind::def("fadeOut", &MenuTools::fadeOut),
		luabind::def("drawModel", &MenuTools::drawModel),
		luabind::def("drawRotTSquare", &MenuTools::drawRotTSquare),
		luabind::def("renderTextF", &MenuTools::renderTextF)
	];
	luabind::module(lstate, "Math")[
		luabind::def("normalize", &Maths::normalize)
	];

	// mm
	luabind::module(lstate, "File")[
		luabind::def("readFileNames", &fileNameReader::getFileNames),
		luabind::def("hasFiles", &fileNameReader::hasFiles),
		luabind::def("getFile", &fileNameReader::getFile)
	];
}