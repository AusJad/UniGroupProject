
function toggleWireFrame(msgbus)
	msgbus:postMessage(Message("WF"), Identifiers("", "RM"));
end

function toggleFreeCam(msgbus)
	msgbus:postMessage(Message("SVM"), Identifiers("", "Camera"));
end

function pushChanges(msgbus)
	msgbus:postMessage(Message("PSH_C"), Identifiers("", "SM"));
	msgbus:postMessage(Message("PSH_C"), Identifiers("", "SM"));
end

function quit(msgbus)
	msgbus:postMessage(Message("KILL"), Identifiers("", "RM"));
end

function changeFont(msgbus, option)
	tmp = Message("CNG_F");
	tmp:setsData(option)
	msgbus:postMessage(tmp, Identifiers("", "FE"));
end

function getObjectList(msgbus, option)
	msg = Message("G_O_L");
	id = Identifiers("", "CONSOLE");
	msg:setFrom(id);
	msgbus:postMessage(msg, Identifiers("", "GOH"));
	pushChanges(msgbus);
end

function changeModel(msgbus, option)
	msg = Message("C_M");
	msg:setsData(option[1]);
	msgbus:postMessage(msg, Identifiers("", option[2]));
	pushChanges(msgbus);
end

function changeScene(msgbus, data)
	msgbus:postMessage(Message("SMF"), Identifiers("", "Camera"));
	msgbus:postMessage(Message("SML"), Identifiers("", "Camera"));
	msgbus:postMessage(Message("SMR"), Identifiers("", "Camera"));
	msgbus:postMessage(Message("SMB"), Identifiers("", "Camera"));
	msgbus:postMessage(Message("SLD"), Identifiers("", "Camera"));
	msgbus:postMessage(Message("SLU"), Identifiers("", "Camera"));
	tmpm = Message("CS");
	tmpm:setiData(tonumber(data));
	msgbus:postMessage(tmpm, Identifiers("", "SM"));
	tmpm = Message("TGL_C");
	msgbus:postMessage(tmpm, Identifiers("", "SM"));
	tmpm = Message("TGL_C");
	msgbus:postMessage(tmpm, Identifiers("", "SM"));
end

function clearScreen(msgbus)
	msgbus:postIMessage(Message("CLS"), 1000002);
end

function saveGame(msgbus, file, scene)
	if(scene == nil) then scene = level1 end
	msg = Message("SV_GM");
	msg:setsData(file);
	msg:setiData(scene);
	print(scene)
	msgbus:postMessage(msg, Identifiers("", "SM"));
	pushChanges(msgbus);
end

function loadGame(msgbus, file)
	msg = Message("LD_GM");
	msg:setsData(file);
	msgbus:postMessage(msg, Identifiers("", "SM"));
	pushChanges(msgbus);
end