require "./Resources/Scripts/helperfunctions";
require "./Resources/Scripts/consolehelperfunctions";

local CODE_SUCCESS = -1; 
local ERROR_CODE_UNKOWN_COMMAND = 0;
local ERROR_CODE_INVALID_SYNTAX = 1;

local function handleMultiPartCMD(cmd, option, msgbus)
	functionfound = false;
	invalidsyntaxflag = false;
	
	if(cmd == "CS" or cmd == "CHANGESCENE") then
		changeScene(msgbus, option);
		functionfound = true;
	end
	if(cmd == "OUT" or cmd == "PRINT" or cmd == "ECHO") then
		print(option);
		functionfound = true;
	end
	
	if(invalidsyntaxflag) then return ERROR_CODE_INVALID_SYNTAX; end
	if(functionfound) then return CODE_SUCCESS;
	else return ERROR_CODE_UNKOWN_COMMAND; end
end

local function handleCMD(cmd, msgbus)
	functionfound = false;
	invalidsyntaxflag = false;

	if(cmd == "WIREFRAME" or cmd == "WF") then
		toggleWireFrame(msgbus);
		functionfound = true;
	elseif(cmd == "TFC") then
		toggleFreeCam(msgbus);
		pushChanges(msgbus);
		functionfound = true;
	elseif(cmd == "DIE" or cmd == "QUIT" or cmd == "CLOSE") then 
		quit(msgbus);
		functionfound = true;
	end

	--Multpart commands; require arguments
	if(cmd == "CS" or cmd == "CHANGESCENE" or cmd == "OUT" or cmd == "PRINT" or cmd == "ECHO") then
		invalidsyntaxflag = true;
	end

	if(invalidsyntaxflag) then return ERROR_CODE_INVALID_SYNTAX; end
	if(functionfound) then return CODE_SUCCESS;
	else return ERROR_CODE_UNKOWN_COMMAND; end
end

function consoleEntryPoint(command, msgbus)
	datastring = command:getData();

	linehead = nil;
	lineend = nil;
	result = nil;

	if(datastring:find(" ") ~= nil) then 
		linehead = datastring:sub(0, datastring:find(" ") - 1);
		lineend = datastring:sub(datastring:find(" ") + 1);
		result = handleMultiPartCMD(linehead, lineend, msgbus);
	else
		linehead = datastring;
		result = handleCMD(linehead, msgbus);
	end

	command:setData(tostring(result));
end
