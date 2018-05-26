require "./Resources/Scripts/controls";
require "./Resources/Scripts/npcai";
require "./Resources/Scripts/console";
require "./Resources/Scripts/mainmenu";
require "./Resources/Scripts/deathmenu";
require "./Resources/Scripts/player";
require "./Resources/Scripts/level1";
require "./Resources/Scripts/helperfunctions";

cutsceneid = "";

local cs1 = 0;
mainmenu = 1;
level2 = 3;
deathscreen = 4;
local endscreen = 5;

local function loadResources(AMAN)
	--Load height maps
	AMAN:addResource("./Resources/Models/RAW2.tdef", "RAWTRN", "Terrain2");
	
	--Load audio
	AMAN:addResource("./Resources/Audio/bgmusic1.wav", "WAV", "BGMUSIC1");
	AMAN:addResource("./Resources/Audio/rb.wav", "WAV", "robotnoise");
	AMAN:addSound("./Resources/Audio/gunshot.wav", "WAV", "gunshot", false);


	--Load fonts
	AMAN:addResource("./Resources/Fonts/DODGE.csv", "FNT", "DODGE");
	AMAN:addResource("./Resources/Fonts/COURIER_NEW.csv", "FNT", "COURIERNEW");
	AMAN:addResource("./Resources/Fonts/ConsoleFontBlue.csv", "FNT", "CONSOLEFONTBLUE");
	AMAN:addResource("./Resources/Fonts/ConsoleFont.csv", "FNT", "CONSOLEFONT");
	

	if(AMAN:addResource("./Resources/Textures/console.bmp", "BMP", "Console") == false) then print("Failed to load con tex"); end

	--Load models
	AMAN:addResource("./Resources/Models/lvl1popup.tsqr", "TX", "POPUP");
	AMAN:addResource("./Resources/Models/lvl2popup.tsqr", "TX", "popup2");
	AMAN:addResource("./Resources/Models/endscreen.tsqr", "TX", "endscrn");

	--Cutscene test
	if(AMAN:addResource("./Resources/CutScenes/test.cs", "CUT_S", "CUTSCENE1")) then print("Loaded resource 'test.cs'!"); 
	else print("Failed to load resource 'test.cs'!"); end 


	AMAN:addModel("./Resources/Models/Rock.obj", "IM", "ROCK", vec3(15,15,15));
	AMAN:addModel("./Resources/Models/bullet.obj", "IM", "bullet", vec3(1,1,1));
	AMAN:addModel("./Resources/Models/robotgreen.obj", "IM", "ROBOT", vec3(0.5,0.5,0.5));
	AMAN:addModel("./Resources/Models/robotgreen.obj", "IM", "Robot2", vec3(0.3,0.3,0.3));
	AMAN:addModel("./Resources/Models/corvet.obj", "IM", "SHIP", vec3(0.5,0.5,0.5));
	if AMAN:addModel("./Resources/Models/guard.md2", "MD2", "PLAYERW", vec3(0.6,0.6,0.6)) == false then
	print("Bad") end
	if AMAN:addModel("./Resources/Models/playerweapon.md2", "MD2", "PWEAPON", vec3(0.6,0.6,0.6)) == false then
	print("Bad") end
	if AMAN:addModel("./Resources/Models/tris.md2", "MD2", "DOOMGUY", vec3(0.6,0.6,0.6)) == false then
	print("Bad") end

	loadMenuRes(AMAN);
	loadDeathMenuRes(AMAN);
	loadLvl1Res(AMAN);
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

	SM:addObject(Identifiers("MO", "CUTSCENE"), cs1, vec3(0, 0, 0), ResourceList("model", "CUTSCENE1"));
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
	initLvl1(SM, AE);

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


	--Initalise death screen scene
	SM:addScene();

	SM:setCurrScene(deathscreen);

	SM:attachControls(deathscreen, ResourceList("keyCallback", "deathMenuControls"));

	SM:addObject(Identifiers("CAM","Camera"), deathscreen, vec3(0, 0, 0), ResourceList());
	SM:addObject(Identifiers("MO","DEATHMENU"), deathscreen, vec3(0, 0, 0), ResourceList("renderfunc", "deathMenuRender", "updatefunc", "deathMenuUpdate"));

	--Initalise end screen scene
	SM:addScene();

	SM:setCurrScene(endscreen);
	
	SM:attachControls(endscreen, ResourceList("mouseButtonCallback", "exitGameControls"));
	
	SM:addObject(Identifiers("CAM","Camera"), endscreen, vec3(0, 0, 0), ResourceList());
	SM:addObject(Identifiers("MO","Guide"), endscreen, vec3(0, 0, 0), ResourceList("model", "endscrn"));

	--Set Starting Scene
	SM:setCurrScene(cs1);
end