
function keys(key, action, MB)
	if key:equals("esc") then 
		if action:equals("press") then
			MB:postMessage(Message("SMF"), Identifiers("", "Camera"));
			MB:postMessage(Message("SML"), Identifiers("", "Camera"));
			MB:postMessage(Message("SMR"), Identifiers("", "Camera"));
			MB:postMessage(Message("SMB"), Identifiers("", "Camera"));
			MB:postMessage(Message("SLD"), Identifiers("", "Camera"));
			MB:postMessage(Message("SLU"), Identifiers("", "Camera"));
			tmpm = Message("CS");
			tmpm:setiData(1);
			MB:postMessage(tmpm, Identifiers("", "SM"));
		end 
	elseif key:equals("w") or key:equals("W") then 
		if(action:equals("press") or action:equals("repeat")) then
			MB:postMessage(Message("MVF"), Identifiers("", "Camera"));
		elseif(action:equals("release")) then
			MB:postMessage(Message("SMF"), Identifiers("", "Camera"));
		end 
	elseif key:equals("a") or key:equals("A") then
		if(action:equals("press") or action:equals("repeat")) then
			MB:postMessage(Message("MVL"), Identifiers("", "Camera"));
		elseif(action:equals("release")) then
			MB:postMessage(Message("SML"), Identifiers("", "Camera"));
		end 
	elseif key:equals("d") or key:equals("D") then
		if(action:equals("press") or action:equals("repeat")) then
			MB:postMessage(Message("MVR"), Identifiers("", "Camera"));
		elseif(action:equals("release")) then
			MB:postMessage(Message("SMR"), Identifiers("", "Camera"));
		end 
	elseif key:equals("s") or key:equals("S") then
		if(action:equals("press") or action:equals("repeat")) then
			MB:postMessage(Message("MVB"), Identifiers("", "Camera"));
		elseif(action:equals("release")) then
			MB:postMessage(Message("SMB"), Identifiers("", "Camera"));
		end 
	elseif key:equals("q") or key:equals("Q") then
		if(action:equals("press") or action:equals("repeat")) then
			MB:postMessage(Message("LD"), Identifiers("", "Camera"));
		elseif(action:equals("release")) then
			MB:postMessage(Message("SLD"), Identifiers("", "Camera"));
		end 
	elseif key:equals("e") or key:equals("E") then
		if(action:equals("press") or action:equals("repeat")) then
			MB:postMessage(Message("LU"), Identifiers("", "Camera"));
		elseif(action:equals("release")) then
			MB:postMessage(Message("SLU"), Identifiers("", "Camera"));
		end 
	elseif key:equals("m") or key:equals("M") then
		if action:equals("press") then
			MB:postMessage(Message("TG"), Identifiers("", "Guide"));
		end
	elseif key:equals("X") then
		if action:equals("press") then
			tmpm = Message("CS");
			tmpm:setiData(2);
			MB:postMessage(tmpm, Identifiers("", "SM"));
		end
	elseif key:equals("`") then
		if action:equals("press") then
			MB:postMessage(Message("SMF"), Identifiers("", "Camera"));
			MB:postMessage(Message("SML"), Identifiers("", "Camera"));
			MB:postMessage(Message("SMR"), Identifiers("", "Camera"));
			MB:postMessage(Message("SMB"), Identifiers("", "Camera"));
			MB:postMessage(Message("SLD"), Identifiers("", "Camera"));
			MB:postMessage(Message("SLU"), Identifiers("", "Camera"));
			tmpm = Message("TGL_C");
			MB:postMessage(tmpm, Identifiers("", "SM"));
		end
	end
end

function mouse(x, y, MB)
	topost = Message("LX");
	topost:setfData(prevx - x:toDouble());
	MB:postMessage(topost, Identifiers("", "Camera"));

	topost = Message("LY");
	topost:setfData(prevy - y:toDouble());
	MB:postMessage(topost, Identifiers("", "Camera"));
end

function exitGameControls(button, action, MB)
	if button:equals("left") and action:equals("press") then
		MB:postMessage(Message("KILL"), Identifiers("", "RM"));
	end
end

function playerAttack(button, action, MB)
	if button:equals("left") and action:equals("press") then
		MB:postMessage(Message("FIRE"), Identifiers("", "Player"));
	end
end

function skipCutScene(key, action, MB)
	if key:equals("enter") and action:equals("press") then
		MB:postMessage(Message("END_CUT"), Identifiers("", cutsceneid));
	end
end