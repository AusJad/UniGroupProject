#include "Console.h"



Console::Console()
{
	active = false;
	even = 0;
}

Console::~Console()
{
}

bool Console::isActive() {
	return active;
}

void Console::update(float time) {
	msgrcvr();
}

void Console::render() {
	float maxy = 1.0f;
	float cury = FNT_SIZE_SMALL;

	RNDR->RenderFacingCamera();

	GeoStream << ENFORCE_POLYGON_MODE_SOLID << START_ATTRIB << color_3(0, 0, 0);

	RNDR->DrawQuad(point(-1.5, maxy), point(1.5, 0), -1.7);

	GeoStream << END_ATTRIB << RESTORE_POLYGON_MODE;

	RNDR->StopRenderFacingCamera();

	if (even % 2 == 0) FNT_ENG->RenderString(curline, FNT_SIZE_SMALL, 30, 30, -1.1, 0, -1.5);
	else FNT_ENG->RenderString(curline + "_", FNT_SIZE_SMALL, 30, 30, -1.1, 0, -1.5);

	even = (even + 1) % 3;

	if (history.size() > 0)
		for (int i = (int)(history.size() - 1); cury < maxy && i >= 0; i--) {
			FNT_ENG->RenderString(history.at(i), FNT_SIZE_SMALL, 30, 30, -1.1, cury, -1.5);
			cury += FNT_SIZE_SMALL;
		}
}

void Console::toggle() {
	active = !active;
}

void Console::appendChar(char toadd) {\
	if(curline.size() < MAX_CMD_SIZE) curline += toadd;
}

void Console::executeCurStatement() {
	history.push_back(curline);

	if (resources.hasResource("behaviour")) {
		SimpleString tmp(curline);

		LSM->callFunction<SimpleString, MessagingBus>(resources.getResource("behaviour"), tmp, *MSGBS);
		
		int rescode = tmp.toInt();

		switch (rescode) {
			case ERROR_CODE_UNKOWN_COMMAND:
				history.push_back("ERROR: Unknown Command");
				break;
			case ERROR_CODE_INVALID_SYNTAX:
				history.push_back("ERROR: Invalid Syntax");
				break;
		}
		
	}
	else history.push_back("ERROR: No Console Behaviour Defined");

	curline.clear();
	future.clear();
}

void Console::loadFromHistory() {
	if (history.size() > 0) {
		future.push_back(curline);
		curline = history.at(history.size() - 1);
		history.pop_back();
	}
}

void Console::attachBehaviour(std::string toadd) {
	resources.addResource("behaviour", toadd);
}

void Console::loadFromFuture() {
	if (future.size() > 0) {
		history.push_back(curline);
		curline = future.at(future.size() - 1);
		future.pop_back();
	}
}

void Console::popChar() {
	if(curline.size() !=0) curline.pop_back();
}

void Console::msgrcvr() {
	Message tmp;

	while (MSGBS->hasIMessage(CONSOLE_ID)) {
		tmp = MSGBS->getIMessage(CONSOLE_ID);

		if (tmp.getInstruction() == C_INPUT) {
			if (tmp.getData().sdata == "space") tmp.setsData(" ");
			else
			if (tmp.getData().sdata == "enter" && tmp.getData().idata == PRESS) executeCurStatement();
			else
			if (tmp.getData().sdata == "backspace" && tmp.getData().idata == PRESS || tmp.getData().idata == REPEAT) popChar();
			else
			if(tmp.getData().sdata == "up" && tmp.getData().idata == PRESS || tmp.getData().idata == REPEAT) loadFromHistory();
			else
			if (tmp.getData().sdata == "down" && tmp.getData().idata == PRESS || tmp.getData().idata == REPEAT) loadFromFuture();

			if (tmp.getData().sdata.size() == 1) {
				if (tmp.getData().sdata.at(0) == '`' && (tmp.getData().idata == PRESS)) MSGBS->postMessage(Message("TGL_C"), Identifiers("", "SM"));
				else
				if (FNT_ENG->fontHasChar(tmp.getData().sdata.at(0)) && (tmp.getData().idata == PRESS || tmp.getData().idata == REPEAT)) {
					appendChar(tmp.getData().sdata.at(0));
				}
			}
		}
	}
}
