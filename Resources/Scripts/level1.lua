

function level1Update(this, msgbus)

end

local objective = "Objective: Defeat Enemies";
local curtext = "";
local wait = false;
local waittime = 0;

local function 	renderObjective()
	if (wait == false) then
		if(string.len(curtext) < string.len(objective)) then
			curtext = string.sub(objective, 0, string.len(curtext) + 1);
		else
			waittime = 4.5;
			wait = true;
		end
	else
		waittime = waittime - time;
		if(waittime <= 0) then wait = false; curtext = ""; objective = ""; end
	end

	MenuTools.renderText(vec2(0, 0.65), -2, 0.1, curtext);
end

local function newObjective()
	if(string.len(objective) > 0) then return true;
	else return false; end
end	

function level1Render(this, msgbus)
	if(newObjective()) then renderObjective(); end
end