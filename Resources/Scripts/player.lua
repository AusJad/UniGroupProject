require "./Resources/Scripts/helperfunctions";

local health;

function playerHUDRenderer(this, msgbus)
	playAnimationLoop(msgbus, this:getIdentifiers(), "crattak");

	--this:drawModel(vec3(2,-5,2), 90);
end