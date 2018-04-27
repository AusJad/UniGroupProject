
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
	print(tonumber(data));
	tmpm = Message("TGL_C");
	msgbus:postMessage(tmpm, Identifiers("", "SM"));
	tmpm = Message("TGL_C");
	msgbus:postMessage(tmpm, Identifiers("", "SM"));
end