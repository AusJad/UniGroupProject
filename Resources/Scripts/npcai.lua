require "./Resources/Scripts/helperfunctions";
require "./Resources/Scripts/level1";

--NPC variables

local plyr_targ = vec3();

local culmtime = 0;

local STATE_CHASE = 1;
local STATE_WAIT = 0;
local STATE_DEAD = 2;
local STATE_INACTIVE = 3;
local STATE_FLEE = 4;

function msgrcvr(this, msgbus)
	msg = Message("POS");
	msg:setFrom(this:getIdentifiers());
	msgbus:postMessage(msg, Identifiers("", "Camera"));

	msg = Message("TRGT");
	msg:setFrom(this:getIdentifiers());
	msgbus:postMessage(msg, Identifiers("", "Camera"));
	 
	while msgbus:hasMessage(this:getIdentifiers()) do
		msg = msgbus:getMessage(this:getIdentifiers());

		if(checkDamage(msg) > -1) then
			this:setHealth(this:getHealth() - checkDamage(msg));
		elseif (animFinished(msg) ~= nil) then
			if(animFinished(msg)) then 
				this:setCanAttack(true); 
			end
		elseif msg:getInstruction() == "PR" then
			this:setTarget(msg:getData():getvData());
		elseif msg:getInstruction() == "TRGTR" then
			plyr_targ = msg:getData():getvData();
		elseif msg:getInstruction() == "TACTICAL_WITHDRAWL_WINK_WINK" then
			if(this:getState() ~= STATE_DEAD and this:getState() ~= STATE_INACTIVE) then
				this:setState(STATE_FLEE);
			end
		elseif this:defaultMessageHandler(msg) == false then
			this:NPCDefaultMessageHandler(msg);
		end
	end
end

local function getPod(id)
	for i = 1,podasize,1
	do
		if(poda[i] == id:getName()) then return 1; end
	end

	for i = 1,podbsize,1
	do
		if(podb[i] == id:getName()) then return 2; end
	end

	return 3;
end

local function stateFlee(this, msgbus)
	heading = AIMvmnt.Flee(this:getPos(), this:getTarget(), this:getSpeed());
	heading = AIMvmnt.capSpeed(heading, this:getSpeed());
	this:setVelocity(heading);

	playAnimationLoop(msgbus, this:getIdentifiers(), "run");

	if(math.random(0, 10000) <= 10) then
		pod = getPod(this:getIdentifiers());

		if(pod == 1) then
			msgbus:postMessage(Message("TACTICAL_WITHDRAWL_WINK_WINK"), Identifiers("", poda[math.random(1,10)]));
		elseif (pod == 2) then
			msgbus:postMessage(Message("TACTICAL_WITHDRAWL_WINK_WINK"), Identifiers("", podb[math.random(1,10)]));
		else
			msgbus:postMessage(Message("TACTICAL_WITHDRAWL_WINK_WINK"), Identifiers("", podc[math.random(1,10)]));
		end
	end

	if(math.random(0, 5000) <= 10) then
		this:setHealth(1500);
		this:setState(STATE_CHASE);
	end
end

local function stateSeek(this, msgbus)
	heading = AIMvmnt.Chase(this:getPos(), this:getTarget(), this:getVelocity(), plyr_targ, this:getHeading(), this:getSpeed(), 3);
	heading = AIMvmnt.capSpeed(heading, this:getSpeed());
	this:setVelocity(heading);

	playerdistance = AIMvmnt.getDistance(this:getPos(), this:getTarget());

	playAnimationLoop(msgbus, this:getIdentifiers(), "run");

	if playerdistance < 400 then
		this:setState(STATE_WAIT);
		this:setCanAttack(true);
	end
end

local function stateWait(this, msgbus)
	this:setVelocity(vec3());

	if(math.random(0, 1500) == 1) then playSoundatSource(msgbus, this:getIdentifiers(), "TAUNT1"); 
	elseif(math.random(0, 1500) == 1) then playSoundatSource(msgbus, this:getIdentifiers(), "TAUNT2"); end

	if this:getCanAttack() == true then 
		playAnimationOnce(msgbus, this:getIdentifiers(), "attack");

		velocity = AIMvmnt.Seek(this:getPos(), this:getTarget(), this:getSpeed());
		fireProjectile(this:getPos(), Math.normalize(velocity), "bullet", msgbus);

		playSoundatSource(msgbus, this:getIdentifiers(), "gunshot");
		
		this:setCanAttack(false);
	else
		if(math.random(0, 100) <= 10) then checkAnimFinished(this:getIdentifiers(), msgbus); end
		
		playerdistance = AIMvmnt.getDistance(this:getPos(), this:getTarget());

		if playerdistance > 450 then
			this:setState(1);
		end
	end
end

local function stateDIE(this, msgbus)
	this:setVelocity(vec3());

	playAnimationOnce(msgbus, this:getIdentifiers(), "death");

	this:setUpdateable(false);

	this:setState(STATE_INACTIVE);
end

local function initEntity(this, msgbus)
	this:setSpeed(300);
	this:setHealth(1000);
	this:setState(0);
	this:setTarget(vec3());
end

function isnan(x) return x ~= x end

--Entry Point
function start(this, msgbus)
	if this:getState() == -1 then
		initEntity(this, msgbus);
	elseif this:getState() == 1 then
		stateSeek(this, msgbus);
	elseif this:getState() == STATE_WAIT then
		stateWait(this, msgbus);
	elseif this:getState() == STATE_DEAD then
		stateDIE(this, msgbus);
	elseif this:getState() == STATE_FLEE then
		stateFlee(this, msgbus);
	end
		
	if(this:getPos():y() < 310 and this:getPos():y() ~= 0) then
		this:setHealth(0);
	end

	if(this:getHealth() <= 0) then this:setState(STATE_DEAD) end

	if(this:getHealth() <= 500) then
		if(math.random(0, 5000) <= 10) then
			this:setState(STATE_FLEE);
			if(math.random(0, 10) == 1) then playSoundatSource(msgbus, this:getIdentifiers(), "NOOO"); end
		end
	end

	if isnan(AIMvmnt.faceTarget(this:getPos(), this:getTarget())) == false then
		if(this:getState() ~= STATE_FLEE) then
			this:setLAngle(math.abs(AIMvmnt.faceTarget(this:getPos(), this:getTarget())));
		else
			this:setLAngle(AIMvmnt.faceTarget(this:getPos(), AIMvmnt.Flee(this:getPos(), this:getTarget(), this:getSpeed())));
		end
	end
end