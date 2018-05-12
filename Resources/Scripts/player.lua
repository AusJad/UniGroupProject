require "./Resources/Scripts/helperfunctions";

local culmtime = 0;
local health = 100;
local ammo = 45;

local scantrans = 0;
local scantransup = true;

local function renderScan()
	if(scantransup) then
		scantrans = scantrans + 0.05 * time;
		if(scantrans > 0.05) then scantransup = false; end
	else
		scantrans = scantrans - 0.05 * time;
		if(scantrans < -0.05) then scantransup = true; end
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
diagnostics[1] = "Tactical Note #233MisOE21:$Elevated Position Acquired$Victory Assured";
diagnostics[2] = "Battle Music Playback Code #xf329sMKd:$La_Dee_Da.wav";
local diagind = 0;
local maxdiag = 3;
local curtext = "";
local wait = false;
local waittime = 0;

local function renderDiagnostics()
	
	if (wait == false) then
		if(string.len(curtext) < string.len(diagnostics[diagind])) then
			curtext = string.sub(diagnostics[diagind], 0, string.len(curtext) + 1);
		else
			diagind = diagind + 1;
			if(diagind == 3) then maxdiag = maxdiag - 1; end
			if(diagind >= maxdiag) then diagind = 0; end
			waittime = 4.5;
			wait = true;
		end
	else
		waittime = waittime - time;
		if(waittime <= 0) then wait = false; curtext = ""; end
	end

	MenuTools.renderText(vec2(-1.4, 0.7), -2, 0.05, curtext);
end

local function renderAmmo()
	MenuTools.drawTSquare(vec2(-1.3, -.2), vec2(-1.1, -.4), -1.95, "AMMO", true);
	MenuTools.renderText(vec2(-1.11, -0.4), -2, 0.15, tostring(ammo));
	MenuTools.drawTSquare(vec2(-1.3, -.45), vec2(-1.1, -.65), -1.95, "ROBOT", true);
	MenuTools.renderText(vec2(-1.11, -0.65), -2, 0.15, tostring(health));
end

function playerHUDRenderer(this, msgbus)
	if(time ~= nil) then culmtime = culmtime + time; end

	playAnimationLoop(msgbus, this:getIdentifiers(), "attack");
	
	this:drawModel(vec3(8,2,-10), 90);

	renderScan();

	renderReticule();

	renderDiagnostics();

	renderAmmo();
end

function playerMsgRcvr(this, msgbus)
	while msgbus:hasMessage(this:getIdentifiers()) do
		tocheck = msgbus:getMessage(this:getIdentifiers());
		
		--if(checkDamage(msg, this)) then
		--	if(this:getHealth() < 0) then this:setState(STATE_DEAD) end
		if(checkDamage(msg) > -1) then
			print("here");
			health = health - checkDamage(msg);
		elseif (tocheck:getInstruction() == "FIRE") then 
			if(ammo > 0) then
				fireProjectile(this:getPos(), this:getFront(), "bullet", msgbus);
				playSoundAtPlayer(msgbus,"gunshot");
				ammo = ammo - 1;
			end
		elseif this:playerDefaultMessageHandler(tocheck) == false then 
			this:defaultMessageHandler(tocheck) 
		end
	end
end