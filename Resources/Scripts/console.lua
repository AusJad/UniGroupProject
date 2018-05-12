require "./Resources/Scripts/helperfunctions";
require "./Resources/Scripts/consolehelperfunctions";

local CODE_SUCCESS = -1; 
local ERROR_CODE_UNKOWN_COMMAND = 0;
local ERROR_CODE_INVALID_SYNTAX = 1;
local CODE_RETURN = 2;

local res;

local function handleMultiPartCMD(cmd, option, msgbus)
	if(cmd == "CS" or cmd == "CHANGESCENE") then
		changeScene(msgbus, option[1]);
		return CODE_SUCCESS;
	elseif(cmd == "OUT" or cmd == "PRINT" or cmd == "ECHO") then
		print(option);
		return CODE_SUCCESS;
	elseif(cmd == "PS" or cmd == "PLAYSOUND") then
		playSoundAtPlayer(msgbus, option[1]);
		return CODE_SUCCESS;
	elseif(cmd == "CF" or cmd == "CHANGEFONT") then
		changeFont(msgbus, option[1]);
		return CODE_SUCCESS;
	elseif(cmd == "LISTOBJ") then
		getObjectList(msgbus, option[1]);
		return CODE_SUCCESS;
	elseif(cmd == "CHANGEMODEL") then
		changeModel(msgbus, option);
		return CODE_SUCCESS;
	elseif(cmd == "SAVEGAME" or cmd == "SAVE") then
		saveGame(msgbus, option[1]);
		return CODE_SUCCESS;
	elseif(cmd == "LOADGAME" or cmd == "LOAD") then
		loadGame(msgbus, option[1]);
		return CODE_SUCCESS;
	end
	
	return ERROR_CODE_UNKOWN_COMMAND; 
end

local function handleCMD(cmd, msgbus)

	if(cmd == "WIREFRAME" or cmd == "WF") then
		toggleWireFrame(msgbus);
		return CODE_SUCCESS;
	elseif(cmd == "TFC") then
		toggleFreeCam(msgbus);
		pushChanges(msgbus);
		return CODE_SUCCESS;
	elseif(cmd == "DIE" or cmd == "QUIT" or cmd == "CLOSE") then 
		quit(msgbus);
		return CODE_SUCCESS;
	elseif(cmd == "LISTOBJ") then
		getObjectList(msgbus, "");
		return CODE_SUCCESS;
	elseif(cmd == "CLEARSCREEN" or cmd == "CLEAR") then
		clearScreen(msgbus);
		return CODE_SUCCESS;
	end

	--Multpart commands; require arguments
	if(cmd == "CS" or cmd == "CHANGESCENE" or cmd == "OUT" or cmd == "PRINT" or cmd == "ECHO") then
		return ERROR_CODE_INVALID_SYNTAX;
	end

	return ERROR_CODE_UNKOWN_COMMAND;
end

function consoleEntryPoint(command, ret, msgbus)
	datastring = command:getData();

	linehead = nil;
	lineend = nil;
	result = nil;

	if(datastring:find(" ") ~= nil) then 
		linehead = datastring:sub(0, datastring:find(" ") - 1);
		
		datastring = datastring:sub(datastring:find(" ") + 1);

		lineend = {};

		while datastring:find(" ") ~= nil do
			table.insert(lineend, datastring:sub(0, datastring:find(" ") - 1));
			datastring = datastring:sub(datastring:find(" ") + 1);
		end
		
		table.insert(lineend, datastring);

		result = handleMultiPartCMD(linehead, lineend, msgbus);
	else
		linehead = datastring;
		result = handleCMD(linehead, msgbus);
	end

	if(result == CODE_RETURN) then 
		ret:setData(tostring(res));
	end

	--print(ret:getData());

	command:setData(tostring(result));
end
