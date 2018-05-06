require "./Resources/Scripts/helperfunctions";

local health;

local scantrans = 0;
local scantransup = false;

local function renderScan()
	if(scantransup) then
		scantrans = scantrans + 0.1 * time;
		if(scantrans > 0.1) then scantransup = false; end
	else
		scantrans = scantrans - 0.1 * time;
		if(scantrans < 0.1) then scantransup = true; end
	end
	MenuTools.drawTSquare(vec2(-1.5, 1 + scantrans), vec2(1.5, -1 + scantrans), -2, "SCAN", true);
end

local retrot = 0;

local function renderReticule()
	retrot = retrot + 10 * time;

	if(retrot > 360) then retrot = 0; end

	MenuTools.drawRotTSquare(vec2(-.1, .1), vec2(.1, -.1), -1.95, "TARGET", true, vec4(retrot, 0, 0, 40));
	MenuTools.drawRotTSquare(vec2(-.1, .1), vec2(.1, -.1), -1.9, "TARGETINNER", true, vec4(360 - retrot*10, 0, 0, 40));
end

local diagnostics = {};
diagnostics[0] = "Status Check #98SImxb434:$All Systems At Maximum Capacity";

local function renderDiagnostics()
	MenuTools.renderText(vec2(-1.4, 0.7), -2, 0.05, diagnostics[0]);
end

local function renderAmmo()
	MenuTools.drawTSquare(vec2(-1.3, -.2), vec2(-1.1, -.4), -1.95, "AMMO", true);
	MenuTools.renderText(vec2(-1.11, -0.4), -2, 0.15, "45");
	MenuTools.drawTSquare(vec2(-1.3, -.45), vec2(-1.1, -.65), -1.95, "ROBOT", true);
	MenuTools.renderText(vec2(-1.11, -0.65), -2, 0.15, "100");
end

local function 	renderObjective()
	MenuTools.renderText(vec2(0, 0.65), -2, 0.1, "Objective: Defeat Enemies");
end

function playerHUDRenderer(this, msgbus)
	playAnimationLoop(msgbus, this:getIdentifiers(), "crattak");
	
	
	this:drawModel(vec3(2,-5,-2), 90);

	renderScan();

	renderReticule();

	renderDiagnostics();

	renderAmmo();

	renderObjective();
end