
local function loadScripts(LSM)
	--Load Scripts
	LSM:doScriptFromFile("./Resources/Scripts/controls.lua");
end

local function loadResources(AMAN)
	--Load height maps
	AMAN:addResource("./Resources/Models/RAW1.tdef", "RAWTRN", "Terrain");
	AMAN:addResource("./Resources/Models/RAW2.tdef", "RAWTRN", "Terrain2");
	
	--Load audio
	AMAN:addResource("./Resources/Audio/mgmusic.wav", "WAV", "bgmusic");
	AMAN:addResource("./Resources/Audio/bgmusic1.wav", "WAV", "bgmusic1");
	AMAN:addResource("./Resources/Audio/rb.wav", "WAV", "robotnoise");
	AMAN:addSound("./Resources/Audio/gunshot.wav", "WAV", "gunshot", false);

	--Load models
	AMAN:addResource("./Resources/Models/lvl1popup.tsqr", "TX", "popup");
	AMAN:addResource("./Resources/Models/lvl2popup.tsqr", "TX", "popup2");
	AMAN:addResource("./Resources/Models/endscreen.tsqr", "TX", "endscrn");
	AMAN:addModel("./Resources/Models/Rock.obj", "IM", "rock", vec3(15,15,15));
	AMAN:addModel("./Resources/Models/bullet.obj", "IM", "bullet", vec3(1,1,1));
	AMAN:addModel("./Resources/Models/robotgreen.obj", "IM", "Robot", vec3(0.5,0.5,0.5));
	AMAN:addModel("./Resources/Models/robotorange.obj", "IM", "Robot2", vec3(0.3,0.3,0.3));
	AMAN:addModel("./Resources/Models/corvet.obj", "IM", "ship", vec3(0.9,0.9,0.9));
end

function initGame(SM, LSM, AMAN, AE)

	--Load resources
	loadScripts(LSM);
	loadResources(AMAN);
	
	--Seed random for deterministic object placement
	math.randomseed(5);
	
	--Initalise Level 1
	SM:addScene();
	SM:setCurrScene(0);
	

	SM:attachControls(0, ResourceList("keyCallback", "keys", "mouseCallback", "mouse"));
	SM:attachTerrain(Identifiers("TO", "Terrain"), 0, vec3(0,0,0), ResourceList("model", "Terrain"));
	
	--Adding game objects
	for i = 11,1,-1 
	do 
		SM:addObject(Identifiers("SE"), 0, vec3(math.random (-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "rock")); 
		SM:addObject(Identifiers("NPC"), 0, vec3(math.random(-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "Robot"));
	end
	SM:addObject(Identifiers("CAM","Camera"), 0, vec3(0, 0, 0), ResourceList());
	SM:addObject(Identifiers("PLYR", "Player"), 0, vec3(0, 0, 0), ResourceList("camera", "Camera", "projmodel", "bullet", "projsnd", "gunshot"));
	SM:addObject(Identifiers("MO","Guide"), 0, vec3(0, 0, 0), ResourceList("model", "popup"));
	SM:addObject(Identifiers("NPC", "R1`"), 0, vec3(-80,0,0), ResourceList("model", "Robot"));
	SM:addObject(Identifiers("NPC", "R2"), 0, vec3(480,0,-1000), ResourceList("model", "Robot"));
	SM:addObject(Identifiers("PROP", "ship"), 0, vec3(-1000,1500,2000), ResourceList("model", "ship"));
	SM:addObject(Identifiers("PROP", "ship2"), 0, vec3(1000,2000,-2000), ResourceList("model", "ship"));
	
	--Set height map
	SM:setSceneHeightMap(0, SM:GetGameObject("Terrain"));

	--Setup sound
	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));
	AE:playSoundatSource("bgmusic", SM:GetGameObjectID("Camera"), vec3(0, 0, 0));
	AE:playSoundatSource("robotnoise", SM:GetGameObjectID("R1"), vec3(-80,0,0));
	AE:playSoundatSource("robotnoise", SM:GetGameObjectID("R2"), vec3(480,0,-1000));
	
	--Initalise Level 2
	SM:addScene();
	SM:setCurrScene(1);

	SM:attachControls(1, ResourceList("keyCallback", "keys", "mouseCallback", "mouse"));
	SM:attachTerrain(Identifiers("TO", "Terrain2"), 1, vec3(0,0,0), ResourceList("model", "Terrain2"));

	--Set height map
	SM:setSceneHeightMap(1, SM:GetGameObject("Terrain2"));
	
	--Adding game objects
	for i = 15,1,-1 
	do 
		SM:addObject(Identifiers("SE"), 1, vec3(math.random (-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "rock")); 
		SM:addObject(Identifiers("NPC"), 1, vec3(math.random(-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "Robot2"));
	end
	SM:addObject(Identifiers("CAM","Camera"), 1, vec3(0, 0, 0), ResourceList());	
	SM:addObject(Identifiers("PLYR", "Player"), 1, vec3(0, 0, 0), ResourceList("camera", "Camera", "projmodel", "bullet", "projsnd", "gunshot"));
	SM:addObject(Identifiers("MO","Guide"), 1, vec3(0, 0, 0), ResourceList("model", "popup2"));
	
	--Setup Sound
	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));
	AE:playSoundatSource("bgmusic1", SM:GetGameObjectID("Camera"), vec3(0, 0, 0));

	--Initalise end screen scene
	SM:addScene();

	SM:setCurrScene(2);
	
	SM:attachControls(2, ResourceList("mouseButtonCallback", "exitGameControls"));
	
	SM:addObject(Identifiers("CAM","Camera"), 2, vec3(0, 0, 0), ResourceList());
	SM:addObject(Identifiers("MO","Guide"), 2, vec3(0, 0, 0), ResourceList("model", "endscrn"));

	--Set Starting Scene
	SM:setCurrScene(0);
end