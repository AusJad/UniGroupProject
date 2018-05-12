
function playSoundatSource(msgbus, self_id, sound)
	msg = Message("PSS");
	msg:setiData(self_id:getId());
	msg:setsData(sound);
	msgbus:postMessage(msg, Identifiers("", "AE"));
end

function playSoundAtPlayer(msgbus, sound)
	msg = Message("PSS");
	msg:setiData(-1);
	msg:setsData(sound);
	msgbus:postMessage(msg, Identifiers("", "AE"));
end

function playAnimationLoop(msgbus, self_id, animation)
	msg = Message("PLYA");
	msg:setiData(1);
	msg:setsData(animation);
	msgbus:postMessage(msg, Identifiers("", tostring(self_id:getId())));
end

function playAnimationOnce(msgbus, self_id, animation)
	msg = Message("PLYA");
	msg:setiData(-1);
	msg:setsData(animation);
	msgbus:postMessage(msg, Identifiers("", tostring(self_id:getId())));
end

function checkDamage(message)
	if(message:getInstruction() == "DMG") then
		return message:getiData();
	else
		return -1;
	end
end

function fireProjectile(start, velocity, model, msgbus)
	tmpm = Message("ATO");
	tmpm:addmvData(start); 
	tmpm:addmvData(velocity);
	tmpm:setsData(model);
	msgbus:postMessage(tmpm, Identifiers("", "GOH"));
end

function mod(x, y)
	return x - math.floor(x/y)*y;
end

function addTmpObject(msgbus, objtype, model)
	
end

function requestPosition(msgbus, self_id, target_id)

end

