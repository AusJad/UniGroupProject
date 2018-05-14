require "./Resources/Scripts/scriptedsegment";

level1 = 2;

local segments = {};
local maxsegment = 3;

local poda = {"E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "E10"};
local podasize = 10;

local podb = {"E11", "E12", "E13", "E14", "E15", "E16", "E17", "E18", "E19", "E20"};
local podbsize = 10;

local podc = {"E21", "E22", "E23", "E24", "E25", "E26", "E27", "E28", "E29", "E30"};
local podcsize = 10;

function loadLvl1Res(AMAN)
	AMAN:addModel("./Resources/Models/skybox.obj", "IM", "SKYBOX", vec3(1000,750,1000));
	AMAN:addResource("./Resources/Models/RAW1.tdef", "RAWTRN", "TERRAIN");

	AMAN:addSound("./Resources/Audio/Voices/lvl1_1.wav", "WAV", "lvl1_1", false);
	AMAN:addSound("./Resources/Audio/Voices/lvl1_2.wav", "WAV", "lvl1_2", false);
	AMAN:addSound("./Resources/Audio/Voices/lvl1_3.wav", "WAV", "lvl1_3", false);
	AMAN:addSound("./Resources/Audio/Voices/lvl1_4.wav", "WAV", "lvl1_4", false);
	AMAN:addResource("./Resources/Audio/battlemusic.wav", "WAV", "S1MUSIC");
end

function initLvl1(SM, AE)
	SM:setSceneResources(ResourceList("updatefunc", "level1Update", "renderfunc", "level1Render"), level1);

	SM:attachControls(level1, ResourceList("keyCallback", "keys", "mouseCallback", "mouse", "mouseButtonCallback", "playerAttack"));
	SM:attachTerrain(Identifiers("TO", "Terrain"), level1, vec3(0,0,0), ResourceList("model", "TERRAIN"));
	
	--add rocks
	for i =  20,1,-1 
	do 
		SM:addObject(Identifiers("SE"), level1, vec3(math.random (-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "ROCK")); 
	end

	--initalise pod a
	for i = 1,podasize,1
	do
		SM:addObject(Identifiers("NPC", poda[i]), level1, vec3(math.random(-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "PLAYERW", "updatefunc", "start", "msgrcvr", "msgrcvr"));
	end

	--initalise pod b
	for i = 1,podbsize,1
	do
		SM:addObject(Identifiers("NPC", podb[i]), level1, vec3(math.random(-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "PLAYERW", "updatefunc", "start", "msgrcvr", "msgrcvr"));
	end

	--initalise pod c
	for i = 1,podcsize,1
	do
		SM:addObject(Identifiers("NPC", podc[i]), level1, vec3(math.random(-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "PLAYERW", "updatefunc", "start", "msgrcvr", "msgrcvr"));
	end

	SM:addObject(Identifiers("CAM","Camera"), level1, vec3(0, 0, -4000), ResourceList("player", "Player"));
	SM:addObject(Identifiers("PROP", "SKYBOX"), level1, vec3(0,-5000,0), ResourceList("model", "SKYBOX"));
	SM:addObject(Identifiers("PROP", "SHIP"), level1, vec3(-1000,2500,2000), ResourceList("model", "SHIP"));
	SM:addObject(Identifiers("PROP", "SHIP2"), level1, vec3(1000,4000,-2000), ResourceList("model", "SHIP"));

	SM:addObject(Identifiers("PLYR", "Player"), level1, vec3(0, 0, -4000), ResourceList("camera", "Camera", "msgrcvr", "playerMsgRcvr", "renderfunc", "playerHUDRenderer", "model", "PWEAPON"));
	
	SM:setSceneHeightMap(level1, SM:GetGameObject("Terrain"));

	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));
end

local function init(this, msgbus)
	segments[0] = S_Seg:create("Objective: Communicate with Allies");
	
	segments[0]:Add_Event(A_Conv:create("BGIMG1", "Prime-Tron, They're in The Valley!", "lvl1_1"));
	segments[0]:Add_Event(A_Conv:create("BGIMG2", "Don't worry, I can't Lose.$I have the High Ground.", "lvl1_2"));
	segments[0]:Add_Event(A_Conv:create("BGIMG2", "Just Give Me a moment to activate my$battle music.", "lvl1_3"));
	segments[0]:Add_Event(A_Conv:create(nil, nil, "S1MUSIC", true));
	--segments[0]:Add_Event(A_Conv:create("BGIMG2", "Oh Yeah!", "lvl1_4"));

	segments[1] = S_Seg:create("Objective: Defeat Enemies in the$valley.");

	segments[1]:Add_Event(A_Battle:create(poda, podasize));
	segments[1]:Add_Event(A_Conv:create("BGIMG2", "Oh Yeah!", "lvl1_4"));
	
	segments[2] = S_Seg:create("Objective: Defeat the Other Enemies");

	segments[2]:Add_Event(A_Battle:create(podb, podbsize));
	segments[2]:Add_Event(A_Conv:create("BGIMG2", "Oh Yeah!", "lvl1_4"));

	segments[3] = S_Seg:create("Objective: Defeat the Last Enemies");

	segments[3]:Add_Event(A_Battle:create(podc, podcsize));
	segments[3]:Add_Event(A_Conv:create("BGIMG2", "Oh Yeah!", "lvl1_4"));

	this:setState(0);
end

function level1Update(this, msgbus)
	if(this:getState() == -2) then return; end
	if(this:getState() == -1) then init(this, msgbus); end

	segments[this:getState()]:Do(msgbus);
	if(segments[this:getState()]:Check_Done()) then 
		this:setState(this:getState() + 1); 
		if(this:getState() > maxsegment) then this:setState(-2); end
	end
end

function level1Render(this, msgbus)
	if(this:getState() == -2) then return; end
	segments[this:getState()]:Render();
end