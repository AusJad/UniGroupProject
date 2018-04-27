#pragma once

#include "FontEngine.h"
#include <vector>
#include "ResourceList.h"
#include "SimpleString.h"
#include "LUAScriptManager.h"

const unsigned MAX_CMD_SIZE = 60;

#define CODE_SUCCESS -1
#define ERROR_CODE_UNKOWN_COMMAND 0
#define ERROR_CODE_INVALID_SYNTAX 1

class Console
{
public:
	Console();
	~Console();

	void update(float time);
	void render();

	void appendChar(char toadd);
	void popChar();
	void executeCurStatement();
	void loadFromHistory();
	void loadFromFuture();
	bool isActive();
	void toggle();
	void attachBehaviour(std::string toadd);

private: 
	void msgrcvr();
	std::vector<std::string> history;
	std::vector<std::string> future;
	std::string curline;
	bool active;
	int even;
	ResourceList resources;
};

