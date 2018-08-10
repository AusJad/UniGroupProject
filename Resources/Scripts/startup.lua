require "./Resources/Scripts/controls";

local function loadResources(AMAN)
	--Load height maps
	AMAN:addResource("./Resources/Models/RAW2.tdef", "RAWTRN", "Terrain");

	--Load fonts
	AMAN:addResource("./Resources/Fonts/ConsoleFont.csv", "FNT", "CONSOLEFONT");
	AMAN:addResource("./Resources/Textures/console.bmp", "BMP", "Console");
	AMAN:addResource("./Resources/Textures/Menu/Window/bggrey.tga", "TGA", "bggrey");
	AMAN:addResource("./Resources/Textures/Menu/Window/header.tga", "TGA", "header");
	AMAN:addResource("./Resources/Textures/Menu/Window/button.tga", "TGA", "buttontex");
	AMAN:addResource("./Resources/Textures/Menu/Window/button_left.tga", "TGA", "button_left");
	AMAN:addResource("./Resources/Textures/Menu/Window/button_right.tga", "TGA", "button_right");
end

function loadLoadRes(AMAN)
	AMAN:addResource("./Resources/Textures/startup.tga", "TGA", "LOADICON"); 
end


function renderLoad(AMAN)
	MenuTools.drawTSquare(vec2(.3, -.1), vec2(.7, -0.5), -1, "LOADICON", false);
end


level1 = 0;

function initGame(SM, LSM, AMAN, AE)

	--Load resources
	loadResources(AMAN);

	--Seed random for deterministic object placement
	math.randomseed(5);

	--Set Console Resources
	SM:attachConsoleTex("Console");

	--Initalise Level 1
	SM:addScene();
	SM:setCurrScene(level1);

	SM:attachControls(level1, ResourceList("keyCallback", "keys", "mouseCallback", "mouse2", "mouseButtonCallback", "playerAttack"));
	SM:attachTerrain(Identifiers("TO", "Terrain"), level1, vec3(0,0,0), ResourceList("model", "Terrain"));

	SM:addObject(Identifiers("CAM","Camera"), level1, vec3(0, 0, 0), ResourceList("player", "Player"));

	SM:addObject(Identifiers("PLYR", "Player"), level1, vec3(0, 0, 0), ResourceList("camera", "Camera"));
	
	SM:setSceneHeightMap(level1, SM:GetGameObject("Terrain"));

	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));

	SM:setCurrScene(level1);

end