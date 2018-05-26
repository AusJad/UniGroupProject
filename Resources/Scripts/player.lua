require "./Resources/Scripts/helperfunctions";
require "./Resources/Scripts/consolehelperfunctions";

local culmtime = 0;
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

local function renderAmmo(this)
	MenuTools.drawTSquare(vec2(-1.3, -.2), vec2(-1.1, -.4), -1.95, "AMMO", true);
	MenuTools.renderText(vec2(-1.11, -0.4), -2, 0.15, tostring(this:getAmmo()));
	MenuTools.drawTSquare(vec2(-1.3, -.45), vec2(-1.1, -.65), -1.95, "ROBOT", true);
	MenuTools.renderText(vec2(-1.11, -0.65), -2, 0.15, tostring(this:getHealth()));
end

local sway = 0;
local swayup = true;

local function calcSway()
	if(swayup) then
		if(sway < 0.1) then
			sway = sway + 0.2 * time;
		else
			swayup = false;
		end
	else
		if(sway > -0.1) then
			sway = sway - 0.2 * time;
		else
			swayup = true;
		end
	end
end

function playerHUDRenderer(this, msgbus)
	if(time ~= nil) then culmtime = culmtime + time; end

	if(time ~= nil) then calcSway(); end

	--playAnimationOnce(msgbus, this:getIdentifiers(), "idle");
	
	this:drawModel(vec3(8,2 + sway,-10), 90);

	renderScan();

	renderReticule();

	renderDiagnostics();

	renderAmmo(this);
end

local function init(this)
	this:setAmmo(200);
	this:setHealth(15000);
end

local bulletcooldown = .75;

function playerMsgRcvr(this, msgbus)
	if(this:getAmmo() == -20) then init(this); end

	if(time ~= nil and bulletcooldown > 0) then
		bulletcooldown = bulletcooldown - time;
	end

	if(this:getPos():y() < 310 and this:getPos():y() > 280) then
		this:setHealth(0);
	end

	if this:getHealth() <= 0 then
		print(this:getHealth());
		msgbus:postMessage(Message("RESET_S"), Identifiers("", "level1"));
		this:setHealth(15000);
		this:setAmmo(200);

		msgbus:postMessage(Message("SMF"), Identifiers("", "Camera"));
		msgbus:postMessage(Message("SML"), Identifiers("", "Camera"));
		msgbus:postMessage(Message("SMR"), Identifiers("", "Camera"));
		msgbus:postMessage(Message("SMB"), Identifiers("", "Camera"));
		msgbus:postMessage(Message("SLD"), Identifiers("", "Camera"));
		msgbus:postMessage(Message("SLU"), Identifiers("", "Camera"));

		tmpm = Message("CS");
		tmpm:setiData(deathscreen);
		msgbus:postMessage(tmpm, Identifiers("", "SM"));

		pushChanges(msgbus);
	end

	while msgbus:hasMessage(this:getIdentifiers()) do
		tocheck = msgbus:getMessage(this:getIdentifiers());
		
		if(checkDamage(tocheck) > -1) then
			this:setHealth(this:getHealth() - checkDamage(tocheck));
		elseif (tocheck:getInstruction() == "FIRE") then 
			if(this:getAmmo() > 0 and bulletcooldown <= 0) then
				fireProjectile(this:getPos(), this:getFront(), "bullet", msgbus);
				playSoundAtPlayer(msgbus,"gunshot");
				playAnimationOnce(msgbus, this:getIdentifiers(), "attack");
				this:setAmmo(this:getAmmo() - 1);
				bulletcooldown = .75;
			end
		elseif this:playerDefaultMessageHandler(tocheck) == false then 
			this:defaultMessageHandler(tocheck) 
		end
	end
end