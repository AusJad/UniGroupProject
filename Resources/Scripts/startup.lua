require "./Resources/Scripts/controls";
require "./Resources/Scripts/npcai";
require "./Resources/Scripts/console";
require "./Resources/Scripts/mainmenu";
require "./Resources/Scripts/deathmenu";
require "./Resources/Scripts/player";
require "./Resources/Scripts/level1";
require "./Resources/Scripts/helperfunctions";
require "./Resources/Scripts/harmlessnpc";


cutsceneid = "";
cutscene2id = "";
cutscene3id = ""

local cs1 = 0;
mainmenu = 1;
level2 = 3;
deathscreen = 4;
victorycutscene = 5;
level1cutscene = 6

local function loadResources(AMAN)
	--Load height maps
	AMAN:addResource("./Resources/Models/RAW2.tdef", "RAWTRN", "Terrain2");
	
	--Load audio
	AMAN:addResource("./Resources/Audio/bgmusic1.wav", "WAV", "BGMUSIC1");
	AMAN:addResource("./Resources/Audio/rb.wav", "WAV", "robotnoise");
	AMAN:addSound("./Resources/Audio/gunshot.wav", "WAV", "gunshot", false);
	AMAN:addSound("./Resources/Audio/no.wav", "WAV", "NOOO", false);
	AMAN:addSound("./Resources/Audio/taunt1.wav", "WAV", "TAUNT1", false);
	AMAN:addSound("./Resources/Audio/taunt2.wav", "WAV", "TAUNT2", false);

	--Load fonts
	AMAN:addResource("./Resources/Fonts/DODGE.csv", "FNT", "DODGE");
	AMAN:addResource("./Resources/Fonts/COURIER_NEW.csv", "FNT", "COURIERNEW");
	AMAN:addResource("./Resources/Fonts/ConsoleFontBlue.csv", "FNT", "CONSOLEFONTBLUE");
	AMAN:addResource("./Resources/Fonts/ConsoleFont.csv", "FNT", "CONSOLEFONT");
	

	if(AMAN:addResource("./Resources/Textures/console.bmp", "BMP", "Console") == false) then print("Failed to load con tex"); end

	--Load models
	AMAN:addResource("./Resources/Models/lvl1popup.tsqr", "TX", "POPUP");

	--Cutscene test
	AMAN:addResource("./Resources/CutScenes/test.cs", "CUT_S", "CUTSCENE1");
	AMAN:addResource("./Resources/CutScenes/csvictory.cs", "CUT_S", "CUTSCENEVICTORY"); 
	AMAN:addResource("./Resources/CutScenes/cslevel1.cs", "CUT_S", "CUTSCENELEVEL1"); 

	AMAN:addModel("./Resources/Models/skybox2.obj", "IM", "SKYBOX2", vec3(1000,1000,1000));

	AMAN:addModel("./Resources/Models/Rock.obj", "IM", "ROCK", vec3(15,15,15));
	AMAN:addModel("./Resources/Models/lava.obj", "IM", "LAVA", vec3(15,3,15));
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

	AMAN:addSound("./Resources/Audio/deathm.wav", "WAV", "DEATHMUSIC", true);

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

	SM:setSceneResources(ResourceList("updatefunc", "level2Update"), level2);

	SM:attachControls(level2, ResourceList("keyCallback", "keys", "mouseCallback", "mouse"));
	SM:attachTerrain(Identifiers("TO", "Terrain2"), level2, vec3(0,0,0), ResourceList("model", "Terrain2"));

	SM:addObject(Identifiers("PROP", "SKYBOX"), level2, vec3(0,-8750,0), ResourceList("model", "SKYBOX2"));

	--Set height map
	SM:setSceneHeightMap(level2, SM:GetGameObject("Terrain2"));

	--Adding game objects
	for i = 15,1,-1 
	do 
		SM:addObject(Identifiers("SE"), level2, vec3(math.random (-128*35, 128*35), 0, math.random(-128*35, 128*35)), ResourceList("model", "ROCK")); 
	end

	SM:addObject(Identifiers("CAM","Camera"), level2, vec3(0, 0, 0), ResourceList());
	SM:addObject(Identifiers("PLYR", "Player"), level2, vec3(0, 0, 0), ResourceList("camera", "Camera", "projmodel", "bullet", "projsnd", "gunshot"));
	
	SM:addObject(Identifiers("NPC", "GUY"), level2, vec3(math.random(-128*35, 128*35), 0, math.random(-128*35, 128*35)), ResourceList("model", "DOOMGUY", "updatefunc", "hupdate", "msgrcvr", "hmsgrcvr"));

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
	
	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));

	--Initalise victory cut scene
	SM:addScene();

	SM:setCurrScene(victorycutscene);

	SM:attachControls(victorycutscene, ResourceList("keyCallback", "skipCutScene2"));

	SM:addObject(Identifiers("CAM","Camera"), victorycutscene, vec3(0, 0, 0), ResourceList());
	SM:addObject(Identifiers("MO","VICTORYCUTSCENE"), victorycutscene, vec3(0, 0, 0), ResourceList("model", "CUTSCENEVICTORY"));

	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));

	cutscene2id = tostring(SM:GetGameObjectID("VICTORYCUTSCENE"));

	--Initalise level 1 cut scene
	SM:addScene();

	SM:setCurrScene(level1cutscene);

	SM:attachControls(level1cutscene, ResourceList("keyCallback", "skipCutScene3"));

	SM:addObject(Identifiers("CAM","Camera"), level1cutscene, vec3(0, 0, 0), ResourceList());
	SM:addObject(Identifiers("MO","LEVEL1CUT"), level1cutscene, vec3(0, 0, 0), ResourceList("model", "CUTSCENELEVEL1"));
	
	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));

	cutscene3id = tostring(SM:GetGameObjectID("LEVEL1CUT"));

	--Set Starting Scene
	SM:setCurrScene(cs1);
end