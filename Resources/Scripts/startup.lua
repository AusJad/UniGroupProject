require "./Resources/Scripts/controls";

local function loadResources(AMAN)
	--Load height maps
	AMAN:addResource("./Resources/Models/RAW2.tdef", "RAWTRN", "Terrain");

	--Load fonts
	if AMAN:addResource("./Resources/Fonts/ConsoleFont.csv", "FNT", "CONSOLEFONT") then print("loaded res: ConsoleFont")
	else print("failed to load ConsoleFont") end
	if AMAN:addResource("./Resources/Textures/console.bmp", "BMP", "Console") then print("loaded res: Console")
	else print("failed to load Console") end
	if AMAN:addResource("./Resources/Textures/Menu/Window/bggrey.tga", "TGA", "windowbg") then print("loaded res: windowbg")
	else print("failed to load windowbg") end
	if AMAN:addResource("./Resources/Textures/Menu/Window/header.tga", "TGA", "wndheader") then print("loaded res: wndheader")
	else print("failed to load wndheader") end
	if AMAN:addResource("./Resources/Textures/Menu/Window/button.tga", "TGA", "close_button") then print("loaded res: close_button")
	else print("failed to load close_button") end
	if AMAN:addResource("./Resources/Textures/Menu/Window/button_left.tga", "TGA", "button_left") then print("loaded res: button_left")
	else print("failed to load button_left") end
	if AMAN:addResource("./Resources/Textures/Menu/Window/button_right.tga", "TGA", "button_right") then print("loaded res: button_right")
	else print("failed to load button_right") end
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

	SM:attachControls(level1, ResourceList("keyCallback", "keys", "mouseCallback", "mouse", "mouseButtonCallback", "playerAttack"));
	SM:attachTerrain(Identifiers("TO", "Terrain"), level1, vec3(0,0,0), ResourceList("model", "Terrain"));

	SM:addObject(Identifiers("CAM","Camera"), level1, vec3(0, 0, 0), ResourceList("player", "Player"));

	SM:addObject(Identifiers("PLYR", "Player"), level1, vec3(0, 0, 0), ResourceList("camera", "Camera"));
	
	SM:setSceneHeightMap(level1, SM:GetGameObject("Terrain"));

	AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));

	SM:setCurrScene(level1);

end