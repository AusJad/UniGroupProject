require "./Resources/Scripts/helperfunctions";

local function stateSeek(this, msgbus)
	heading = AIMvmnt.Seek(this:getPos(), this:getTarget(), this:getSpeed());
	heading = AIMvmnt.capSpeed(heading, this:getSpeed());
	this:setVelocity(heading);

	playerdistance = AIMvmnt.getDistance(this:getPos(), this:getTarget());

	playAnimationLoop(msgbus, this:getIdentifiers(), "run");

	if playerdistance < 200 then
		this:setState(0);
	end
end

local function stateWait(this, msgbus)
	this:setVelocity(vec3());
	
	playAnimationLoop(msgbus, this:getIdentifiers(), "stand");	

	playerdistance = AIMvmnt.getDistance(this:getPos(), this:getTarget());

	if playerdistance > 250 then
		this:setState(1);
	end
end

function hmsgrcvr(this, msgbus)
	msg = Message("POS");
	msg:setFrom(this:getIdentifiers());
	msgbus:postMessage(msg, Identifiers("", "Camera"));
	 
	while msgbus:hasMessage(this:getIdentifiers()) do
		msg = msgbus:getMessage(this:getIdentifiers());

		if msg:getInstruction() == "PR" then
			this:setTarget(msg:getData():getvData());
		elseif this:defaultMessageHandler(msg) == false then
			this:NPCDefaultMessageHandler(msg);
		end
	end
end

local function hinit(this, msgbus)
	this:setSpeed(300);
	this:setState(1);
end

function hupdate(this, msgbus)
	if(this:getState() == -1) then
		hinit(this, msgbus);
	elseif(this:getState() == 0) then
		stateWait(this, msgbus);
	else
		stateSeek(this, msgbus);
	end

	if isnan(AIMvmnt.faceTarget(this:getPos(), this:getTarget())) == false then
		this:setLAngle(math.abs(AIMvmnt.faceTarget(this:getPos(), this:getTarget())));
	end
end


local function init(this, msgbus)
	msgbus:postMessage(Message("S_VIS"), Identifiers("",  "GUY"));
	msgbus:postMessage(Message("S_UD"), Identifiers("",  "GUY"));
end

function level2Update(this, msgbus)
	if(this:getState() == -1) then init(this, msgbus); end
end