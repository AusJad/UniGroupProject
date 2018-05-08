require "./Resources/Scripts/helperfunctions";

--NPC variables
local pos_table = {};

local plyr_targ = vec3();

local culmtime = 0;

local STATE_CHASE = 1;
local STATE_WAIT = 0;
local STATE_DEAD = 2;
local STATE_INACTIVE = 3;

function msgrcvr(this, msgbus)
	msg = Message("POS");
	msg:setFrom(this:getIdentifiers());
	msgbus:postMessage(msg, Identifiers("", "Camera"));

	msg = Message("TRGT");
	msg:setFrom(this:getIdentifiers());
	msgbus:postMessage(msg, Identifiers("", "Camera"));
	 
	while msgbus:hasMessage(this:getIdentifiers()) do
		msg = msgbus:getMessage(this:getIdentifiers());

		if(checkDamage(msg, this)) then
			if(this:getHealth() < 0) then this:setState(STATE_DEAD) end
		elseif msg:getInstruction() == "PR" then
			this:setTarget(msg:getData():getvData());
		elseif msg:getInstruction() == "TRGTR" then
			plyr_targ = msg:getData():getvData();
		elseif this:defaultMessageHandler(msg) == false then
			this:NPCDefaultMessageHandler(msg);
		end
	end
end

local function stateSeek(this, msgbus)
	--heading = AIMvmnt.Seek(this:getPos(), this:getTarget(), this:getSpeed());

	heading = AIMvmnt.Chase(this:getPos(), this:getTarget(), this:getVelocity(), plyr_targ, this:getHeading(), this:getSpeed(), 3);
	heading = AIMvmnt.capSpeed(heading, this:getSpeed());
	this:setVelocity(heading);

	playerdistance = AIMvmnt.getDistance(this:getPos(), this:getTarget());

	--print(playerdistance);

	playAnimationLoop(msgbus, this:getIdentifiers(), "run");

	if playerdistance < 200 then
		this:setState(0);
	end
end

local waittime = 0;
local attackcooldown = 0.0

local function stateWait(this, msgbus)
	--heading = AIMvmnt.Arrive(this:getPos(), this:getTarget(), this:getVelocity(), this:getSpeed(), 0.001, 150); 
	--heading = AIMvmnt.capSpeed(heading, this:getSpeed());
	this:setVelocity(vec3());

	waittime = waittime + time;
	if(attackcooldown > 0) then attackcooldown = attackcooldown - time; end
	
	if waittime > 2.0 then 
		if(attackcooldown <= 0.0) then
			waittime = 0.0;
			attackcooldown = 1.0;
			velocity = AIMvmnt.Seek(this:getPos(), this:getTarget(), this:getSpeed());
			playAnimationLoop(msgbus, this:getIdentifiers(), "attack");
			fireProjectile(this:getPos(), Math.normalize(velocity), "bullet", msgbus);
			playSoundatSource(msgbus, this:getIdentifiers(), "gunshot");
		end
	elseif attackcooldown <= 0 then
		playAnimationLoop(msgbus, this:getIdentifiers(), "stand");

		playerdistance = AIMvmnt.getDistance(this:getPos(), this:getTarget());

		if playerdistance > 250 then
			this:setState(1);
		end
	end
end

local function stateAttack(this, msgbus)
	velocity = AIMvmnt.Seek(this:getPos(), this:getTarget(), this:getSpeed());
	playAnimationOnce(msgbus, this:getIdentifiers(), "crattak");
	fireProjectile(this:getPos(), Math.normalize(velocity), "bullet", msgbus);
end

local function stateDIE(this, msgbus)
	--heading = AIMvmnt.Arrive(this:getPos(), this:getTarget(), this:getVelocity(), this:getSpeed(), 0.001, 150); 
	--heading = AIMvmnt.capSpeed(heading, this:getSpeed());
	this:setVelocity(vec3());

	playAnimationOnce(msgbus, this:getIdentifiers(), "death");

	this:setState(STATE_INACTIVE);
end

local function initEntity(this, msgbus)
	this:setSpeed(300);
	this:setHealth(100);
	this:setState(0);
	pos_table[this:getIdentifiers():getId()] = this:getPos();
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
	end

	if isnan(AIMvmnt.faceTarget(this:getPos(), this:getTarget())) == false then
		this:setLAngle(math.abs(AIMvmnt.faceTarget(this:getPos(), this:getTarget())));
		--print(tonumber(AIMvmnt.faceTarget(this:getPos(), this:getTarget())));
	end
	--this:lookAt(this:getTarget());

	--for i, j in pairs(pos_table) do 
	--print("Entity  at pos: " , this:getTarget():x() , " " , this:getTarget():y() , " " , this:getTarget():z());
	--end
end