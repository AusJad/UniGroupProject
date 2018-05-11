require "./Resources/Scripts/controls";
require "./Resources/Scripts/npcai";
require "./Resources/Scripts/console";
require "./Resources/Scripts/mainmenu";
require "./Resources/Scripts/player";
require "./Resources/Scripts/level1";
require "./Resources/Scripts/helperfunctions";

cutsceneid = "";

local cs1 = 0;
local mainmenu = 1;
local level1 = 2;
local level2 = 3;
local endscreen = 4;

local function loadResources(AMAN)
	--Load height maps
	AMAN:addResource("./Resources/Models/RAW1.tdef", "RAWTRN", "Terrain");
	AMAN:addResource("./Resources/Models/RAW2.tdef", "RAWTRN", "Terrain2");
	
	--Load audio
	AMAN:addResource("./Resources/Audio/battlemusic.wav", "WAV", "S1MUSIC");
	AMAN:addResource("./Resources/Audio/bgmusic1.wav", "WAV", "BGMUSIC1");
	AMAN:addResource("./Resources/Audio/rb.wav", "WAV", "robotnoise");
	AMAN:addSound("./Resources/Audio/gunshot.wav", "WAV", "gunshot", false);
	AMAN:addSound("./Resources/Audio/introclip.wav", "WAV", "HIGHGROUND", false);

	--Load fonts
	if(AMAN:addResource("./Resources/Fonts/DODGE.csv", "FNT", "DODGE")) then print("Successfully Loaded Resource DODGE.");
	else print("Failed to Load Resource DODGE."); end
	if(AMAN:addResource("./Resources/Fonts/COURIER_NEW.csv", "FNT", "COURIERNEW")) then print("Successfully Loaded Resource COURIER_NEW.");
	else print("Failed to Load Resource COURIER_NEW."); end
	if(AMAN:addResource("./Resources/Fonts/ConsoleFont.csv", "FNT", "CONSOLEFONT")) then print("Successfully Loaded Resource CONSOLEFONT.");
	else print("Failed to Load Resource CONSOLEFONT."); end

	if(AMAN:addResource("./Resources/Textures/console.bmp", "BMP", "Console") == false) then print("Failed to load con tex"); end

	--Load models
	AMAN:addResource("./Resources/Models/lvl1popup.tsqr", "TX", "popup");
	AMAN:addResource("./Resources/Models/lvl2popup.tsqr", "TX", "popup2");
	AMAN:addResource("./Resources/Models/endscreen.tsqr", "TX", "endscrn");

	--Cutscene test
	if(AMAN:addResource("./Resources/CutScenes/test.cs", "CUT_S", "cutscene1")) then print("Loaded resource 'test.cs'!"); 
	else print("Failed to load resource 'test.cs'!"); end 

	AMAN:addModel("./Resources/Models/skybox.obj", "IM", "SKYBOX", vec3(1000,750,1000));
	AMAN:addModel("./Resources/Models/Rock.obj", "IM", "ROCK", vec3(15,15,15));
	AMAN:addModel("./Resources/Models/bullet.obj", "IM", "bullet", vec3(1,1,1));
	AMAN:addModel("./Resources/Models/robotgreen.obj", "IM", "ROBOT", vec3(0.5,0.5,0.5));
	AMAN:addModel("./Resources/Models/robotgreen.obj", "IM", "Robot2", vec3(0.3,0.3,0.3));
	AMAN:addModel("./Resources/Models/corvet.obj", "IM", "SHIP", vec3(0.5,0.5,0.5));
	if AMAN:addModel("./Resources/Models/guard.md2", "MD2", "PLAYERW", vec3(0.6,0.6,0.6)) == false then
	print("Bad") end
	if AMAN:addModel("./Resources/Models/tris.md2", "MD2", "DOOMGUY", vec3(0.6,0.6,0.6)) == false then
	print("Bad") end

	loadMenuRes(AMAN);
end

function initGame(SM, LSM, AMAN, AE)

	--Load resources
	loadResources(AMAN);

	--Seed random for deterministic object placement
	math.randomseed(5);

	--Set Console Resources
	SM:attachConsoleBehaviour("consoleEntryPoint");
	SM:attachConsoleTex("Console");

	--Start cutscene
	SM:addScene();

	SM:setCurrScene(cs1);

	SM:attachControls(cs1, ResourceList("keyCallback", "skipCutScene"));

	SM:addObject(Identifiers("MO", "CUTSCENE"), cs1, vec3(0, 0, 0), ResourceList("model", "cutscene1"));
	SM:addObject(Identifiers("CAM","Camera"), cs1, vec3(0, 0, 0), ResourceList());
	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));
	
	cutsceneid = tostring(SM:GetGameObjectID("CUTSCENE"));

	--Main menu
	SM:addScene();

	SM:setCurrScene(mainmenu);

	SM:attachControls(mainmenu, ResourceList("keyCallback", "MenuControls"));

	SM:addObject(Identifiers("MO", "MAINMENU"), mainmenu, vec3(0, 0, 0), ResourceList("renderfunc", "mainMenuRender", "updatefunc", "mainMenuUpdate"));
	SM:addObject(Identifiers("CAM","Camera"), mainmenu, vec3(0, 0, 0), ResourceList());
	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));

	--Initalise Level 1
	SM:addScene();
	SM:setCurrScene(level1);
	SM:setSceneResources(ResourceList("updatefunc", "level1Update", "renderfunc", "level1Render"), level1);

	SM:attachControls(level1, ResourceList("keyCallback", "keys", "mouseCallback", "mouse"));
	SM:attachTerrain(Identifiers("TO", "Terrain"), level1, vec3(0,0,0), ResourceList("model", "Terrain"));
	
	--Adding game objects
	for i = 11,1,-1 
	do 
		id = tostring(math.random())
		SM:addObject(Identifiers("SE"), level1, vec3(math.random (-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "ROCK")); 
		SM:addObject(Identifiers("NPC", id), level1, vec3(math.random(-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "PLAYERW", "updatefunc", "start", "msgrcvr", "msgrcvr"));
	end
	SM:addObject(Identifiers("CAM","Camera"), level1, vec3(0, 0, -4000), ResourceList());
	SM:addObject(Identifiers("PROP", "SKYBOX"), level1, vec3(0,-5000,0), ResourceList("model", "SKYBOX"));
	--SM:addObject(Identifiers("MO","Guide"), level1, vec3(0, 0, 0), ResourceList("model", "popup"));
	--SM:addObject(Identifiers("NPC", "R1"), level1, vec3(-80,0,0), ResourceList("model", "ROBOT", "updatefunc", "start", "msgrcvr", "msgrcvr"));
	--SM:addObject(Identifiers("NPC", "R2"), level1, vec3(480,0,-1000), ResourceList("model", "ROBOT"));
	SM:addObject(Identifiers("PROP", "SHIP"), level1, vec3(-1000,1500,2000), ResourceList("model", "SHIP"));
	SM:addObject(Identifiers("PROP", "SHIP2"), level1, vec3(1000,2000,-2000), ResourceList("model", "SHIP"));

	SM:addObject(Identifiers("PLYR", "Player"), level1, vec3(0, 0, -4000), ResourceList("camera", "Camera", "projmodel", "bullet", "projsnd", "gunshot", "renderfunc", "playerHUDRenderer"));
	
	--Set height map
	SM:setSceneHeightMap(level1, SM:GetGameObject("Terrain"));

	--Setup sound
	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));
	AE:playSoundatSource("S1MUSIC", SM:GetGameObjectID("Camera"), vec3(0, 0, 0));
	AE:playSoundatSource("HIGHGROUND", SM:GetGameObjectID("Camera"), vec3(0, 0, 0));

	--Initalise Level 2
	SM:addScene();
	SM:setCurrScene(level2);

	SM:attachControls(level2, ResourceList("keyCallback", "keys", "mouseCallback", "mouse"));
	SM:attachTerrain(Identifiers("TO", "Terrain2"), level2, vec3(0,0,0), ResourceList("model", "Terrain2"));

	--Set height map
	SM:setSceneHeightMap(level2, SM:GetGameObject("Terrain2"));

	--Adding game objects
	for i = 15,1,-1 
	do 
		SM:addObject(Identifiers("SE"), level2, vec3(math.random (-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "ROCK")); 
		SM:addObject(Identifiers("NPC"), level2, vec3(math.random(-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "PLAYERW"));
	end

	SM:addObject(Identifiers("CAM","Camera"), level2, vec3(0, 0, 0), ResourceList());
	SM:addObject(Identifiers("PLYR", "Player"), level2, vec3(0, 0, 0), ResourceList("camera", "Camera", "projmodel", "bullet", "projsnd", "gunshot"));

	--SM:addObject(Identifiers("MO","Guide"), level2, vec3(0, 0, 0), ResourceList("model", "popup2"));
	
	--Setup Sound
	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));
	AE:playSoundatSource("BGMUSIC1", SM:GetGameObjectID("Camera"), vec3(0, 0, 0));

	--Initalise end screen scene
	SM:addScene();

	SM:setCurrScene(endscreen);
	
	SM:attachControls(endscreen, ResourceList("mouseButtonCallback", "exitGameControls"));
	
	SM:addObject(Identifiers("CAM","Camera"), endscreen, vec3(0, 0, 0), ResourceList());
	SM:addObject(Identifiers("MO","Guide"), endscreen, vec3(0, 0, 0), ResourceList("model", "endscrn"));

	--Set Starting Scene
	SM:setCurrScene(cs1);
end