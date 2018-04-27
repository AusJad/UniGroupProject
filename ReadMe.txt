Ingame Console, Text Rendering/Font Loading, Animations, and NPC Death

Press tilde (~) to toggle console

valid commands:
	die/close/quit - Exits game
	wireframe/wf - toggle wireframe/wf
	tfc - toggles free camera
	cs [sceneno] - changes scene to sceneno (if it exists)
	
Console logic written in LUA, so adding commands should be easy

The current implmentation of the AI is pretty weak, without collision awarness they quickly get stuck on stuff.

Bug in animation:	
	I parse out the list of animations from the MD2 file and aggragate them based on name;
	unfortinalty, multiple animations can have the same name. 
	So some animations loop go through the cycles of their neighbouring animations before ending.
	This can be seen on NPC death.
	
	Easy fix, but its there for the moment.
	
	