require "./Resources/Scripts/helperfunctions";
require "./Resources/Scripts/consolehelperfunctions";

local dmenuselcted = 0;

--Planes
local back = -2.5; local bminx = -1.85; local bxwidth = 3.7; local bminy = -1.1; local byheight = 2.2;

local middle = -2; local mminx = -1.4; local mxwidth = 2.8; local mminy = -.8; local mheight = 1.6;
local front = -1.75;


function loadDeathMenuRes(AMAN)
	AMAN:addResource("./Resources/Textures/DeathMenu/skull.tga", "TGA", "SKULL");
end

local function init(this, msgbus)
	playSoundAtPlayer(msgbus, "DEATHMUSIC");
	print("here");
	this:setState(0);
end

function deathMenuUpdate(this, msgbus)
	if(this:getState() == -1) then init(this, msgbus); end
end

function deathMenuRender(this, msgbus)
	MenuTools.drawTSquare(vec2(-.5, .76), vec2(.5, -.25), middle, "SKULL", true);

	if dmenuselcted == 0 then
		MenuTools.renderTextF(vec2(-.6, -.4), middle, .1, "Try Again", "CONSOLEFONTBLUE");
		MenuTools.renderTextF(vec2(-10,-10), 0, 0.005, "", "CONSOLEFONT");
	else
		MenuTools.renderText(vec2(-.6, -.4), middle, .1, "Try Again");
	end
	
	if dmenuselcted == 1 then
		MenuTools.renderTextF(vec2(.3, -.4), middle, .1, "Give Up", "CONSOLEFONTBLUE");
		MenuTools.renderTextF(vec2(-10,-10), 0, 0.005, "", "CONSOLEFONT");
	else
		MenuTools.renderText(vec2(.3, -.4), middle, .1, "Give Up");
	end
end

local function doSelected(MB)
	if(dmenuselcted == 0) then
		tmpm = Message("CS");
		tmpm:setiData(level1);
		reset = true;
		MB:postMessage(tmpm, Identifiers("", "SM"));
	else
		tmpm = Message("CS");
		tmpm:setiData(mainmenu);
		MB:postMessage(tmpm, Identifiers("", "SM"));
	end
end

function deathMenuControls(key, action, MB)
	if key:equals("A") and action:equals("press") or key:equals("left") and action:equals("press") then
		if(dmenuselcted > 0) then dmenuselcted = dmenuselcted - 1; end
	elseif key:equals("D") and action:equals("press") or key:equals("right") and action:equals("press") then
		if(dmenuselcted < 1) then dmenuselcted = dmenuselcted + 1; end
	elseif key:equals("enter") and action:equals("press") then
		doSelected(MB);
	end
end