#include "Console.h"



Console::Console()
{
	active = false;
	even = 0;
	editind = 0;
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

	RNDR->DrawQuad(point(-1.5f, maxy), point(1.5f, 0.0f), -1.7f);

	GeoStream << END_ATTRIB << RESTORE_POLYGON_MODE;

	RNDR->StopRenderFacingCamera();

	std::string tmp;

	if ((editind == curline.size())) {
		if (even % 2 == 0)  FNT_ENG->RenderString(curline, FNT_SIZE_SMALL, 30, 30, -1.1f, 0.0f, -1.5f);
		else FNT_ENG->RenderString(curline + "_", FNT_SIZE_SMALL, 30, 30, -1.1f, 0.0f, -1.5f);
	}
	else{
		tmp = curline;
		if(even %2 == 0) tmp.insert(editind, "_");
		else  tmp.insert(editind, " ");
		FNT_ENG->RenderString(tmp, FNT_SIZE_SMALL, 30, 30, -1.1f, 0.0f, -1.5f);
	}

	even = (even + 1) % 3;

	if (history.size() > 0)
		for (int i = (int)(history.size() - 1); cury < maxy && i >= 0; i--) {
			FNT_ENG->RenderString(history.at(i), FNT_SIZE_SMALL, 30, 30, -1.1f, cury, -1.5f);
			cury += FNT_SIZE_SMALL;
		}
}

void Console::toggle() {
	active = !active;
}

void Console::adjustEditInd(int offset) {
	if (offset == -1) {
		if (editind > 0) editind -= 1;
	}
	else {
		if (editind < (int) curline.size()) editind += 1;
	}
}

void Console::appendChar(char toadd) {
	if (editind == curline.size()) {
		if (curline.size() < MAX_CMD_SIZE) curline += toadd;
		editind++;
	}
	else {
		std::string tmp;
		tmp.push_back(toadd);
		if (curline.size() < MAX_CMD_SIZE) curline.insert(editind, tmp);
		editind += 1;
	}
}

void Console::executeCurStatement() {
	history.push_back(curline);

	if (resources.hasResource("behaviour")) {
		SimpleString tmp(curline);
		SimpleString ret;

		
		LSM->callFunction<SimpleString, MessagingBus>(resources.getResource("behaviour"), tmp, ret, *MSGBS);
		
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

	editind = 0;
	curline.clear();
	future.clear();
}

void Console::loadFromHistory() {
	if (history.size() > 0) {
		future.push_back(curline);
		curline = history.at(history.size() - 1);
		history.pop_back();
		editind = curline.size();
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
		editind = curline.size();
	}
}

void Console::popChar() {
	if (editind == curline.size()) {
		if (curline.size() > 0) editind--;
		if (curline.size() > 0) curline.pop_back();
	}
	else {
		if (editind > 1) curline.erase(editind - 1, 1);
		editind--;
	}
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
			if (tmp.getData().sdata == "backspace" && tmp.getData().idata == PRESS) popChar();
			else
			if(tmp.getData().sdata == "up" && tmp.getData().idata == PRESS) loadFromHistory();
			else
			if (tmp.getData().sdata == "down" && tmp.getData().idata == PRESS) loadFromFuture();
			else
			if (tmp.getData().sdata == "left" && tmp.getData().idata == PRESS) adjustEditInd(-1);
			else
			if (tmp.getData().sdata == "right" && tmp.getData().idata == PRESS) adjustEditInd(+1);

			if (tmp.getData().sdata.size() == 1) {
				if (tmp.getData().sdata.at(0) == '`' && (tmp.getData().idata == PRESS)) MSGBS->postMessage(Message("TGL_C"), Identifiers("", "SM"));
				else
				if (FNT_ENG->fontHasChar(tmp.getData().sdata.at(0)) && (tmp.getData().idata == PRESS || tmp.getData().idata == REPEAT)) {
					appendChar(tmp.getData().sdata.at(0));
				}
			}
		}
		else
		if (tmp.getInstruction() == OBJECT_LIST_RESPONSE) {
			while (tmp.getData().sdata.find(",") != std::string::npos) {
				history.push_back(
					tmp.getData().sdata.substr(0, tmp.getData().sdata.find(","))
				);
				tmp.getData().sdata = tmp.getData().sdata.substr(tmp.getData().sdata.find(",") + 1);
			}
		}
		else
		if (tmp.getInstruction() == CL_SCR) {
			history.clear();
		}
	}
}
