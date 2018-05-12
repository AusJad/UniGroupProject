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
#define CODE_RETURN 2

/**
* @class Console
* @brief A class to provide a interface in the game for command line prompts.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
class Console
{
public:
	Console();
	~Console();

	/**
	* @brief The update function for the console.
	*
	* @param time - The system time.
	*/
	void update(float time);

	/**
	* @brief The render function for the console.
	*/
	void render();

	/**
	* @brief Append the text on screen when user types something in.
	*
	* @param toadd - The character the user just typed.
	*/
	void appendChar(char toadd);

	/**
	* @brief Take a character off the screen.
	*/
	void popChar();

	/**
	* @brief Check the statement the user just entered against all known commands and then execute it if valid.
	*/
	void executeCurStatement();

	/**
	* @brief Load a command from history.
	*/
	void loadFromHistory();

	/**
	* @brief Load a command that hasn't been entered yet.
	*/
	void loadFromFuture();

	/**
	* @brief Find out if the console is active.
	*
	* @return bool - If the console is active.
	*/
	bool isActive();

	/**
	* @brief Turn the console on or off.
	*/
	void toggle();

	/**
	* @brief Attach any special behaviours to the console.
	*
	* @param toadd - The behaviour.
	*/
	void attachBehaviour(std::string toadd);

	/**
	* @brief Adjust the edit index.
	*
	* @param offset - The offset of the index.
	*/
	void adjustEditInd(int offset);

	/**
	* @brief Add a texture.
	*
	* @param tex - The texture.
	*/
	void addTex(std::string tex);
private: 
	/**
	* @brief A message receiver.
	*/
	void msgrcvr();
	/// A vector of commands previously executed.
	std::vector<std::string> history;
	/// A vector of commands to be executed.
	std::vector<std::string> future;
	/// The current line in the console.
	std::string curline;
	/// If the console is active.
	bool active;
	/// Even.
	int even;
	/// The resources for the console.
	ResourceList resources;
	/// The edit index for the space between the letters.
	int editind;
};

