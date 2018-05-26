require "./Resources/Scripts/helperfunctions";
require "./Resources/Scripts/consolehelperfunctions";

local menustate = 0;

local MENU_STATE_START			=			0
local MENU_STATE_FILE_DISPLAY	=			1

--X axis button params
local buttonstartx = -0.15; local buttonwidth = .3;

--Y axis button params
local buttonstarty = 0.1; local buttonoffsety = 0.025; local buttonheight = 0.05;

--Z axis button params
local buttonz = -1.5;

--Planes
local back = -2.5; local bminx = -1.85; local bxwidth = 3.7; local bminy = -1.1; local byheight = 2.2;

local middle = -2; local mminx = -1.4; local mxwidth = 2.8; local mminy = -.8; local mheight = 1.6;
local front = -1.75;

--Keep track of culminative time
local culmtime = 0; local consoleText = {};
consoleText[0] = "var Arya = ( betray(( -Jon - ( 1 ) )) )$def mislead(Sansa,Jon){$	COLS;$	Sansa$}$def mislead(Ygritte,y){$}$def foo(){$}$assert -630.78 : $'What do we say to the Lord of Death?''$def TABLE[foo()][k] {$	if(-0.71){$	--TABLE[protect(-1,( ( betray(dog,-1,dog) ) ))$ / ( -1 ) / -TABLE[ROWS]$[bar(( ( -( -COLS - Jon ) + y ) ))] + y$ / protect(COLS,TABLE[bar(Jon,Arya) + Ygritte][TABLE[ROWS]$[-98 + Ygritte] - ROWS])$ + -protect(( -0.68 )) * $TABLE[-630.205][TABLE[protect(0.86,Stark)][ROWS]]][Arya]$};$	y$}$assert --89 : 'Nothing burns like the cold.'$var Jon = Stark$def protect(x,y){$$}$def protect(y){$	-Arya * -560.478$}$var dog = ( -270.1214 )$assert --89 : 'Nothing burns like the cold.'$var Jon = Stark$def protect(x,y){$$}$def protect(y){$	-Arya * -560.478$}$var dog = ( -270.1214 )$";
consoleText[1] = "def destroy(Hodor){$dog *= -bar(-0.25 - COLS)$}$var Hodor = --mislead(-dog,-protect($rule(),-15 + foo(Hodor) / $mislead(bar(---( ROWS ))),( $rule(-51 * ( -0.72 ),( $-Ygritte )) ) - y)) + ( 57 )$def TABLE[COLS][i]$assert ( ( ( protect(ROWS,TABLE[( $-rule(COLS,mislead(( 0.73 ),--Sansa $+ COLS + betray(-ROWS,( Arya ),COLS),$var dog = Jon$def TABLE[bar(COLS * ( -betray(rule(1 * COLS / Sansa))$if(-x - y){$if(77){$if(dog)$};$Sansa += Hodor;$Hodor -= -0.85$Arya -= Arya;$( x )$}$assert ( ( ( ( Stark / $-betray(--1,Ygritte,Ygritte * 0.69) ) ) ) ) : $'Fear cuts deeper than swords.'$var Hodor = Arya$def TABLE[-( COLS )][i] {$Hodor += 18$}$assert protect() : $'A mind needs books as a sword needs a $whetstone, if it is to keep its edge.'$assert Arya / Stark : $'One can not simply parse himself'";
consoleText[2] = "def TABLE[-destroy(ROWS)$+ Stark][i] {$Sansa -= 40$}$assert -COLS : 'Who are we?'$def mislead(Sansa){$Stark /= -betray(ROWS) - bar()$}$def TABLE[foo(x,TABLE[( ( $mislead(800.846) ) )][mislead(Sansa)])][j] {$}$assert ( ( Jon ) )$def TABLE[foo(x,( 0.53 ) * ( y ),---92 - 1)][j] {$Jon /= destroy(TABLE[-( COLS )]$[( ( Sansa ) ) - -x],--bar(COLS) / x);$if(Stark){$dog /= ( ( Ygritte ) );$Stark -= betray(TABLE[( 1 )][-Sansa],betray(Ygritte))$};$if(-1){$if(-( protect(---1,COLS,66) )){$Ygritte -= -0$var Sansa = -19$var Arya = ( destroy(x,destroy(COLS,16,0.11$ - destroy(Stark,-0.25))) + -rule$(( betray(COLS) ),-Arya,( ROWS )) * --20.8 )$def TABLE[Arya][i] {$betray(( -0.8 ));$Jon -= Stark * -1;$0.95$var Arya = betray(( ( 1 ) * COLS )$ - bar(( -Jon ),--( ( ( y ) - $( -0.2 + -dog * protect(-39) ) ) )$,( Sansa )),1)$def destroy(Stark,dog){$--COLS$Stark *= 70;$destroy(-Sansa,ROWS,-0.76)$}"
local consoleTextCur = ""; local txtind = 0; local maxind = 3; local up = false;

local infade = 1;

--menu items
local selected = 0; local numitems = 3;

--temp back oof
local tmpback = back; local tmpbup = true;

--side texture list
local sidetex = {}; sidetex[0] = "BGIMG1"; sidetex[1] = "BGIMG2";
local cursidetex = 0; local numsidetex = 2;

--file vars
local files = {}; local maxfile;

local function genFileList()
	File.readFileNames("./saveData", ".save");

	maxfile = 0;

	while(File.hasFiles()) do
		files[maxfile] = (File.getFile());
		maxfile = maxfile + 1;
	end
end

function loadMenuRes(AMAN)
	AMAN:addResource("./Resources/Textures/MainMenu/banner.tga", "TGA", "BANNER");
	AMAN:addResource("./Resources/Textures/MainMenu/skull.tga", "TGA", "BGIMG1");
	AMAN:addResource("./Resources/Textures/MainMenu/robot.tga", "TGA", "BGIMG2");
	AMAN:addResource("./Resources/Textures/MainMenu/buttonplayplain.tga", "TGA", "BPLAYP");
	AMAN:addResource("./Resources/Textures/MainMenu/buttonplayhighlight.tga", "TGA", "BPLAYH");
	AMAN:addResource("./Resources/Textures/MainMenu/buttonloadplain.tga", "TGA", "BLOADP");
	AMAN:addResource("./Resources/Textures/MainMenu/buttonloadhighlight.tga", "TGA", "BLOADH");
	AMAN:addResource("./Resources/Textures/MainMenu/buttonsaveplain.tga", "TGA", "BSAVEP");
	AMAN:addResource("./Resources/Textures/MainMenu/buttonsavehighlight.tga", "TGA", "BSAVEH");
	AMAN:addResource("./Resources/Textures/MainMenu/buttonexitplain.tga", "TGA", "BEXITP");
	AMAN:addResource("./Resources/Textures/MainMenu/buttonexithighlight.tga", "TGA", "BEXITH");
	AMAN:addResource("./Resources/Textures/MainMenu/return.tga", "TGA", "RETURN");

	--todo: move to player.lua
	AMAN:addResource("./Resources/Textures/scanline.tga", "TGA", "SCAN");
	AMAN:addResource("./Resources/Textures/target.tga", "TGA", "TARGET");
	AMAN:addResource("./Resources/Textures/targetinner.tga", "TGA", "TARGETINNER");
	AMAN:addResource("./Resources/Textures/ammo.tga", "TGA", "AMMO");
	AMAN:addResource("./Resources/Textures/robot.tga", "TGA", "ROBOT");

	AMAN:addSound("./Resources/Audio/menumusic.wav", "WAV", "MENUMUSIC", true);
	AMAN:addSound("./Resources/Audio/select.wav", "WAV", "MENUSELECT", false);
	
	genFileList();
end

local function init(this, msgbus)
	playSoundAtPlayer(msgbus, "MENUMUSIC");

	this:setState(0);
end

local function incString()
	if up == false then
		if(string.len(consoleTextCur) == string.len(consoleText[txtind])) then up = true;
		else consoleTextCur = string.sub(consoleText[txtind], 0, string.len(consoleTextCur) + 1); end
	else
		if string.len(consoleTextCur) < 3 then up = false;  txtind = txtind + 1; if(txtind >= maxind) then txtind = 0; end
		else consoleTextCur = string.sub(consoleText[txtind], 0, string.len(consoleTextCur) - 3); end
	end
end

function mainMenuUpdate(this, msgbus)
	if(this:getState() == -1) then init(this, msgbus); end

	if(time ~= nil) then culmtime = culmtime + time; end

	genFileList();

	incString();
end

local sidefade = 1; local fadedir = true;

local function drawSide()
	MenuTools.drawTSquare(vec2(.4, .4), vec2(1.6, -.8), middle, sidetex[cursidetex], true);
	if(fadedir) then if(sidefade <= 0.1) then fadedir = false; sidefade = 0.1; else MenuTools.fadeIn(vec2(.4, .4), vec2(1.6, -.8), middle, sidefade, time); sidefade = sidefade - time/16; end
	else if(sidefade >= .96) then fadedir = true; sidefade = 1; cursidetex = cursidetex + 1; if cursidetex >= numsidetex then cursidetex = 0; end MenuTools.fadeOut(vec2(.4, .4), vec2(1.6, -.8), middle, sidefade, time); else MenuTools.fadeOut(vec2(.4, .4), vec2(1.6, -.8), middle, sidefade, time); sidefade = sidefade + time/8; end end
end

local exitind = 3;

local cansave = false;

local function drawButtons()
	--Draw Buttons 
	yoff = buttonstarty;

	if(selected == 0) then
		MenuTools.drawTSquare(vec2(buttonstartx, yoff), vec2(buttonstartx + buttonwidth, yoff - buttonheight), buttonz, "BPLAYH", true);
	else
		MenuTools.drawTSquare(vec2(buttonstartx, yoff), vec2(buttonstartx + buttonwidth, yoff - buttonheight), buttonz, "BPLAYP", true);
	end

	yoff = yoff - buttonoffsety - buttonheight;
	
	if(selected == 1) then
		MenuTools.drawTSquare(vec2(buttonstartx, yoff), vec2(buttonstartx + buttonwidth, yoff - buttonheight), buttonz, "BLOADH", true);
	else
		MenuTools.drawTSquare(vec2(buttonstartx, yoff), vec2(buttonstartx + buttonwidth, yoff - buttonheight), buttonz, "BLOADP", true);
	end
	
	if (prevscene == level1) then
		yoff = yoff - buttonoffsety - buttonheight;
		
		cansave = true;

		if(selected == 2) then
			MenuTools.drawTSquare(vec2(buttonstartx, yoff), vec2(buttonstartx + buttonwidth, yoff - buttonheight), buttonz, "BSAVEH", true);
		else
			MenuTools.drawTSquare(vec2(buttonstartx, yoff), vec2(buttonstartx + buttonwidth, yoff - buttonheight), buttonz, "BSAVEP", true);
		end

		numitems = 3;
		exitind = 3;
	else
		cansave = false;

		numitems = 2;
		exitind = 2;
	end
	
	yoff = yoff - buttonoffsety - buttonheight;
	
	if(selected == exitind) then
		MenuTools.drawTSquare(vec2(buttonstartx, yoff), vec2(buttonstartx + buttonwidth, yoff - buttonheight), buttonz, "BEXITH", true);
	else
		MenuTools.drawTSquare(vec2(buttonstartx, yoff), vec2(buttonstartx + buttonwidth, yoff - buttonheight), buttonz, "BEXITP", true);
	end

end

local state2selected = 0;
local st = 0; local fin = 5;

local function listFiles()
	local yoff = buttonstarty - .1;

	if maxfile < 5 then
		st = 0;
		fin = maxfile -1;
	elseif maxfile > 5 then
		if state2selected > 0 then
			st = state2selected;
		else
			st = 0;
		end

		fin = st + 5;
	end

	if maxfile > 0 then
		for i = st, fin do
			if(files[i] ~= nil) then
				if(state2selected == i) then
					MenuTools.renderTextF(vec2(buttonstartx - .25, yoff), buttonz, 0.052, files[i], "CONSOLEFONTBLUE");
					MenuTools.renderTextF(vec2(-10,-10), 0, 0.005, "", "CONSOLEFONT");
				else
					MenuTools.renderText(vec2(buttonstartx - .25, yoff), buttonz, 0.052, files[i]);
				end
		
				yoff = yoff - buttonoffsety - buttonheight;
			end
		end
	else
		MenuTools.renderTextF(vec2(buttonstartx-.03, yoff), buttonz, 0.052, "No Saves Found!", "CONSOLEFONTBLUE");
		MenuTools.renderTextF(vec2(-10,-10), 0, 0.005, "", "CONSOLEFONT");
		yoff = yoff - buttonoffsety - buttonheight;
	end

	MenuTools.drawTSquare(vec2(buttonstartx - buttonwidth*.5, -.45), vec2(buttonstartx + buttonwidth*1.5, -.45 - buttonheight*2), buttonz, "RETURN", true);

end

function mainMenuRender(this, msgbus)
	--Draw backdrop
	MenuTools.drawSquare(vec2(bminx, bminy + byheight), vec2(bminx + bxwidth, bminy), back, vec4(0,0,0,1));

	--Draw scrolling code
	if(tmpbup) then
		if(tmpback < back + 0.05 - .01) then tmpbup = false;
		else tmpback = tmpback - (0.005 * time); end
	else
		if(tmpback > back + 0.05 + .05) then tmpbup = true;
		else tmpback = tmpback + (0.005 * time); end
	end

	MenuTools.renderText(vec2(bminx + 0.1, bminy - 0.15 + byheight), tmpback, 0.052, consoleTextCur);
	

	if (menustate == MENU_STATE_START) then
		drawButtons();
	elseif (menustate == MENU_STATE_FILE_DISPLAY) then
		listFiles();
	end

	--draw button underlay
	MenuTools.drawSquare(vec2(buttonstartx*2.35, buttonstarty + .3), vec2(buttonstartx*2.35 + buttonwidth*2.35, buttonstarty + yoff - (buttonheight * 4)), middle, vec4(0,0,0,.7));

	--Draw side image
	if(infade < 0) then drawSide(); end

	--Draw Banner
	MenuTools.drawTSquare(vec2(-.8, .8), vec2(.8, 0), middle, "BANNER", true);

	--Render fades (if any)
	if(infade > 0) then infade = MenuTools.fadeIn(vec2(bminx, bminy + byheight), vec2(bminx + bxwidth, bminy), -1, infade, time); end
end

local loadind = 1;

local function doSelected(MB)
	if (selected == 0) then
		tmpm = Message("CS");
		tmpm:setiData(level1);
		MB:postMessage(tmpm, Identifiers("", "SM"));
	elseif(selected == loadind) then
		menustate = MENU_STATE_FILE_DISPLAY;
	elseif(selected == 2 and cansave) then
		print("here");
		saveGame(MB, "Save_" .. tostring(os.date("%m-%d-%Y-") .. tostring(os.time())), level1); 
	elseif(selected == exitind) then
		MB:postMessage(Message("KILL"), Identifiers("", "RM"));
	end
end

local function MainControls(key, action, MB)
	if key:equals("enter") and action:equals("press") then
		doSelected(MB); 
	elseif key:equals("down") and action:equals("press") then
		if(selected < numitems) then selected = selected + 1; playSoundAtPlayer(MB, "MENUSELECT"); end
	elseif key:equals("up") and action:equals("press") then
		if(selected > 0) then selected = selected - 1; playSoundAtPlayer(MB, "MENUSELECT"); end
	end
end

local function loadFile(file, msgbus)
	print(file);
	loadGame(msgbus, file);
	pushChanges(msgbus);
	incScene(msgbus);
end

local function fileBrowseControls(key, action, MB)
	if key:equals("enter") and action:equals("press") then
		menustate = MENU_STATE_START;
		loadFile(files[state2selected], MB); 
	elseif key:equals("down") and action:equals("press") then
		if(state2selected < maxfile - 1) then state2selected = state2selected + 1; playSoundAtPlayer(MB, "MENUSELECT"); end
	elseif key:equals("up") and action:equals("press") then
		if(state2selected > 0) then state2selected = state2selected - 1; playSoundAtPlayer(MB, "MENUSELECT"); end
	elseif key:equals("backspace") and action:equals("press") then
		menustate = MENU_STATE_START;
	end
end

function MenuControls(key, action, MB)
	if menustate == MENU_STATE_START then
		MainControls(key, action, MB)
	elseif menustate == MENU_STATE_FILE_DISPLAY then
		fileBrowseControls(key, action, MB);
	end
end