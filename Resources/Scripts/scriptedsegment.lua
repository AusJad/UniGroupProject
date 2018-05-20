require "./Resources/Scripts/helperfunctions";

--start of classes

A_Battle = {};

A_Battle.__index = A_Battle;

function A_Battle:create(Etities, num_ent)	
	local battle = {};

	setmetatable(battle, A_Battle);
	
	battle.entities = Etities;

	battle.num_ent = num_ent;

	battle.num_alive = num_ent;

	battle.tocheck = {};

	battle.started = -1;
	
	battle.id = Identifiers("", tostring(math.random()));

	battle.done = false;

	battle.graceperiod = 3.0;

	return battle;
end

function A_Battle:init(msgbus)
	local msg = Message("S_STATE");
	msg:setiData(-1);

	for i = 1,self.num_ent,1
	do
		msgbus:postMessage(Message("S_VIS"), Identifiers("", self.entities[i]));
		msgbus:postMessage(Message("S_UD"), Identifiers("", self.entities[i]));
		msgbus:postMessage(msg, Identifiers("", self.entities[i]));
		self.tocheck[i] = 0;
	end

	self.started = 0;
end

function A_Battle:Get_Living(msgbus)
	local msg = Message("PING");
	msg:setFrom(self.id);

	for i = 1, self.num_ent,1
	do
		if(self.entities[i] ~= nil) then
			msgbus:postMessage(msg, Identifiers("", self.entities[i]));
			self.tocheck[i] = self.tocheck[i] + 1;
		end
	end

	while (msgbus:hasMessage(self.id)) do
		msg = msgbus:getMessage(self.id);
		for i = 1, self.num_ent,1
		do
			if(self.entities[i] ~= nil) then
				if(msg:getFrom():getName() == self.entities[i]) then
					self.tocheck[i] = 0;
				end
			end
		end
	end

	for i = 1, self.num_ent
	do
		if(self.tocheck[i] ~= nil) then
			if(self.tocheck[i] > 5) then
				self.entities[i] = nil;
				self.tocheck[i] = nil;
				self.num_alive = self.num_alive - 1;
			end
		end
	end
end

function A_Battle:Do(msgbus)
	if self.num_alive == 0 then return; end
	if(self.started == -1) then self:init(msgbus); end
	
	if(self.graceperiod > 0) then self.graceperiod = self.graceperiod - time; return; end

	self:Get_Living(msgbus);

end

function A_Battle:Render()
	MenuTools.renderText(vec2(.8, -0.6), -1.95, 0.1, "Alive: " .. tostring(self.num_alive));
end

function A_Battle:Check_Done(msgbus)
	return self.num_alive == 0;
end

--Conversation Action
A_Conv = {};

A_Conv.__index = A_Conv;

function A_Conv:create(image, text, sound, instant)	
	local conv = {};

	setmetatable(conv, A_Conv);

	conv.image = image;
	conv.text = text;
	conv.sound = sound;

	conv.curtext = "";
	conv.wait = false;
	conv.waittime = 0;

	conv.id = Identifiers("", tostring(math.random()));

	conv.started = -1;

	conv.done = false;

	conv.graceperiod = 4.0;

	if(instant == nil) then conv.instant = false;
	else conv.instant = instant; end

	return conv;
end

function A_Conv:init(msgbus)
	playSoundAtPlayer(msgbus, self.sound);
	self.started = 0;
	if(self.instant) then self.done = true; end
end

function A_Conv:Do(msgbus)
	if self.done then return; end
	if(self.started == -1) then self:init(msgbus); end

	if self.graceperiod > 0 then self.graceperiod = self.graceperiod - time 
	else
		
		testSoundPlaying(msgbus, self.id, self.sound);

		while msgbus:hasMessage(self.id) do
			local msg = msgbus:getMessage(self.id);

			if testSoundDone(msg) == -1 then
				self.done = true;
			end
		end
	end	
end

function A_Conv:Render_Text()
	if string.len(self.text) == "" then return; end

	if (self.wait == false) then
		if(string.len(self.curtext) < string.len(self.text)) then
			self.curtext = string.sub(self.text, 0, string.len(self.curtext) + 1);
		else
			self.waittime = 1000;
			self.wait = true;
		end
	else
		self.waittime = self.waittime - time;
		if(self.waittime <= 0) then self.wait = false; self.curtext = ""; self.text = ""; end
	end

	MenuTools.fadeIn(vec2(.05, -0.55), vec2(1.1, -.7), -2, 0.5, time); 
	MenuTools.renderText(vec2(.1, -0.6), -1.95, 0.05, self.curtext);
end

function A_Conv:Render_Image()
	MenuTools.drawTSquare(vec2(1.1, -.55), vec2(1.25, -.7), -2, self.image, false);
end

function A_Conv:Render()
	if(self.text ~= nil) then self:Render_Text(); end
	if(self.image ~= nil) then self:Render_Image(); end
end

function A_Conv:Check_Done(msgbus)
	return self.done;
end

--Scripted Segment Class

S_Seg = {};

S_Seg.__index = S_Seg;

function S_Seg:create(objective)
	local s_seg = {};
	setmetatable(s_seg, S_Seg);
	s_seg.events = {};
	s_seg.nextind = 0;
	s_seg.curevent = -1;
	s_seg.maxevent = 0;

	s_seg.objective = objective;
	s_seg.curtext = "";
	s_seg.wait = false;
	s_seg.waittime = 0;

	return s_seg;
end

function S_Seg:Add_Event(Event)
	self.events[self.nextind] = Event;
	self.nextind = self.nextind + 1;
	if self.curevent == -1 then self.curevent = 0; end
	self.maxevent = self.maxevent + 1;
end

function S_Seg:Do(msgbus)
	if self.curevent == -1 then return; end

	if self.events[self.curevent]:Check_Done(msgbus) then
		self:Inc_Event(msgbus);
	end

	if self.curevent == -1 then return; end

	self.events[self.curevent]:Do(msgbus);
end

function S_Seg:Render_Objective()
	if string.len(self.objective) == "" then return; end

	if (self.wait == false) then
		if(string.len(self.curtext) < string.len(self.objective)) then
			self.curtext = string.sub(self.objective, 0, string.len(self.curtext) + 1);
		else
			self.waittime = 8;
			self.wait = true;
		end
	else
		self.waittime = self.waittime - time;
		if(self.waittime <= 0) then self.wait = false; self.curtext = ""; self.objective = ""; end
	end

	MenuTools.renderText(vec2(-0.4, 0.65), -2, 0.1, self.curtext);
end

function S_Seg:Render()
	if self.curevent == -1 then return; end

	self:Render_Objective();

	self.events[self.curevent]:Render(msgbus);
end

function S_Seg:Check_Done(msgbus)
	if(self.curevent == -1) then return true; 
	else return false end

end

function S_Seg:Inc_Event(msgbus)
	self.curevent = self.curevent + 1;
	if self.curevent == self.maxevent then self.curevent = -1; end
end

function S_Seg:Write()
	return SimpleString(tostring(self.curevent));
end

--Scripted Segment End