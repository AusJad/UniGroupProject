require "./Resources/Scripts/scriptedsegment";
require "./Resources/Scripts/consolehelperfunctions";

level1 = 2;

local segments = {};
local maxsegment = 3;

poda = {"E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "E10"};
podapos = {};
podasize = 10;

podb = {"E11", "E12", "E13", "E14", "E15", "E16", "E17", "E18", "E19", "E20"};
podbpos = {};
podbsize = 10;

podc = {"E21", "E22", "E23", "E24", "E25", "E26", "E27", "E28", "E29", "E30"};
podcpos = {};
podcsize = 10;

function loadLvl1Res(AMAN)
	AMAN:addModel("./Resources/Models/skybox.obj", "IM", "SKYBOX", vec3(1000,750,1000));
	AMAN:addResource("./Resources/Models/RAW1.tdef", "RAWTRN", "TERRAIN");

	AMAN:addSound("./Resources/Audio/Voices/lvl1_1.wav", "WAV", "lvl1_1", false);
	AMAN:addSound("./Resources/Audio/Voices/lvl1_2.wav", "WAV", "lvl1_2", false);
	AMAN:addSound("./Resources/Audio/Voices/lvl1_3.wav", "WAV", "lvl1_3", false);
	AMAN:addSound("./Resources/Audio/Voices/lvl1_4.wav", "WAV", "lvl1_4", false);
	AMAN:addResource("./Resources/Audio/battlemusic.wav", "WAV", "S1MUSIC");
end


local function setEvents(loaded)
	segments[0] = S_Seg:create("Objective: Communicate with Allies");
	
	segments[0]:Add_Event(A_Conv:create(nil, nil, nil, true));
	segments[0]:Add_Event(A_Conv:create(nil, nil, nil, true));
	segments[0]:Add_Event(A_Conv:create("BGIMG1", "Prime-Tron, They're in The Valley!", "lvl1_1"));
	segments[0]:Add_Event(A_Conv:create("BGIMG2", "Don't worry, I can't Lose.$I have the High Ground.", "lvl1_2"));
	segments[0]:Add_Event(A_Conv:create("BGIMG2", "Just Give Me a moment to activate my$battle music.", "lvl1_3"));
	segments[0]:Add_Event(A_Conv:create(nil, nil, "S1MUSIC", true));
	--segments[0]:Add_Event(A_Conv:create("BGIMG2", "Oh Yeah!", "lvl1_4"));

	segments[1] = S_Seg:create("Objective: Defeat Enemies in the$valley.");

	segments[1]:Add_Event(A_Conv:create("BGIMG2", "Oh Yeah!", "lvl1_4"));
	segments[1]:Add_Event(A_Battle:create(poda, podasize, loaded));
	segments[1]:Add_Event(A_Conv:create("BGIMG2", "Oh Yeah!", "lvl1_4"));
	
	segments[2] = S_Seg:create("Objective: Defeat the Other Enemies");

	segments[2]:Add_Event(A_Battle:create(podb, podbsize, loaded));
	segments[2]:Add_Event(A_Conv:create("BGIMG2", "Oh Yeah!", "lvl1_4"));

	segments[3] = S_Seg:create("Objective: Defeat the Last Enemies");

	segments[3]:Add_Event(A_Battle:create(podc, podcsize, loaded));
	segments[3]:Add_Event(A_Conv:create("BGIMG2", "Oh Yeah!", "lvl1_4"));
end

function initLvl1(SM, AE)
	
	SM:setSceneResources(ResourceList("updatefunc", "level1Update", "renderfunc", "level1Render"), level1);

	SM:attachControls(level1, ResourceList("keyCallback", "keys", "mouseCallback", "mouse", "mouseButtonCallback", "playerAttack"));
	SM:attachTerrain(Identifiers("TO", "Terrain"), level1, vec3(0,0,0), ResourceList("model", "TERRAIN"));
	
	SM:addObject(Identifiers("PROP"), level1, vec3(4000,300,0), ResourceList("model", "LAVA"));

	--add rocks
	for i =  20,1,-1 
	do  
		SM:addObject(Identifiers("SE"), level1, vec3(math.random (-128*40, 128*40), 0, math.random(-128*40, 128*40)), ResourceList("model", "ROCK")); 
	end

	--initalise pod a
	for i = 1,podasize,1
	do
		podapos[i] =vec3(math.random(-128*35, 128*35), 0, math.random(-128*35, 128*35));
		SM:addObject(Identifiers("NPC", poda[i]), level1, podapos[i], ResourceList("model", "PLAYERW", "updatefunc", "start", "msgrcvr", "msgrcvr"));
	end

	--initalise pod b
	for i = 1,podbsize,1
	do
		podbpos[i] =vec3(math.random(-128*35, 128*35), 0, math.random(-128*35, 128*35));
		SM:addObject(Identifiers("NPC", podb[i]), level1, podbpos[i], ResourceList("model", "PLAYERW", "updatefunc", "start", "msgrcvr", "msgrcvr"));
	end

	--initalise pod c
	for i = 1,podcsize,1
	do
		podcpos[i] =vec3(math.random(-128*35, 128*35), 0, math.random(-128*35, 128*35));
		SM:addObject(Identifiers("NPC", podc[i]), level1, podcpos[i], ResourceList("model", "PLAYERW", "updatefunc", "start", "msgrcvr", "msgrcvr"));
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
	setEvents(false);

	this:setState(0);
end

local function reset(this, msgbus)
	
	local msg = Message("S_STATE");
	msg:setiData(-1);

	local posmsg = Message("SS_POS");

	for i = 1,podasize,1
	do
		posmsg:setvData(podapos[i]);
		msgbus:postMessage(posmsg, Identifiers("", poda[i]));
		msgbus:postMessage(msg, Identifiers("", poda[i]));
		msgbus:postMessage(Message("S_ND"), Identifiers("", poda[i]));
		msgbus:postMessage(Message("S_H"), Identifiers("", poda[i]));
	end

	for i = 1,podbsize,1
	do
		posmsg:setvData(podbpos[i]);
		msgbus:postMessage(posmsg, Identifiers("", podb[i]));
		msgbus:postMessage(msg, Identifiers("", podb[i]));
		msgbus:postMessage(Message("S_ND"), Identifiers("", podb[i]));
		msgbus:postMessage(Message("S_H"), Identifiers("", podb[i]));
	end

	for i = 1,podcsize,1
	do
		posmsg:setvData(podcpos[i]);
		msgbus:postMessage(posmsg, Identifiers("", podc[i]));
		msgbus:postMessage(msg, Identifiers("", podc[i]));
		msgbus:postMessage(Message("S_ND"), Identifiers("", podc[i]));
		msgbus:postMessage(Message("S_H"), Identifiers("", podc[i]));
	end

	msgbus:postMessage(Message("STP_ALL_S"), Identifiers("", "AE"));
	msgbus:postMessage(Message("RESET_CAM"), Identifiers("", "Camera"));
	msgbus:postMessage(Message("RESET_PLYR"), Identifiers("", "Player"));

	pushChanges(msgbus);

	segments = {};

	this:setState(-1);
end

function level1Update(this, msgbus)
	if(this:getLoaded()) then 
		msgbus:postMessage(Message("STP_ALL_S"), Identifiers("", "AE")); 
		setEvents(true); 
		msgbus:postMessage(Message("SMF"), Identifiers("", "Camera"));
		msgbus:postMessage(Message("SML"), Identifiers("", "Camera"));
		msgbus:postMessage(Message("SMR"), Identifiers("", "Camera"));
		msgbus:postMessage(Message("SMB"), Identifiers("", "Camera"));
		msgbus:postMessage(Message("SLD"), Identifiers("", "Camera"));
		msgbus:postMessage(Message("SLU"), Identifiers("", "Camera"));
		if(this:getState() ~= 0) then
			tmp = A_Conv:create(nil, nil, "S1MUSIC", true);
			tmp:Do(msgbus);
		end
	end

	if(this:getState() == -3) then reset(this, msgbus); end
	if(this:getState() == -2) then return; end
	if(this:getState() == -1) then init(this, msgbus); end

	if(msgbus:hasMessage(Identifiers("", "level1"))) then
		msg = msgbus:getMessage(Identifiers("", "level1"));

		if(msg:getInstruction() == "RESET_S") then
			this:setState(-3);
			return;
		end
	end

	segments[this:getState()]:Do(msgbus);
	if(segments[this:getState()]:Check_Done()) then 
		this:setState(this:getState() + 1); 
		if(this:getState() > maxsegment) then 
			reset(this, msgbus); 
			tmpm = Message("CS");
			tmpm:setiData(victorycutscene);
			msgbus:postMessage(tmpm, Identifiers("", "SM"));
		end
	end
end

function level1Render(this, msgbus)
	if(this:getState() == -2) then return; end
	if(this:getState() >= 0 and this:getState() <= maxsegment) then segments[this:getState()]:Render(); end
end