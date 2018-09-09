
local function loadResources(AMAN)
	--Load fonts
	if AMAN:addResource("./Resources/Fonts/MonoFont.csv", "FNT", "CONSOLEFONT") then print("loaded res: ConsoleFont")
	else print("failed to load ConsoleFont") end
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

	--Initalise Level 1
	SM:addScene();
	SM:setCurrScene(level1);

	SM:addObject(Identifiers("PLYR", "Player"), level1, vec3(0, 0, 0), ResourceList("camera", "Camera"));
	
	--SM:setSceneHeightMap(level1, SM:GetGameObject("Terrain"));

	--AE:setListenerSource(SM:GetGameObjectID("Camera"), vec3(0, 0, 0));

	SM:setCurrScene(level1);

end