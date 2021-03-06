#pragma once

#include "Identifiers.h"

#define FDATA 'F'
#define CDATA 'C'
#define IDATA 'I'
#define SDATA 'S'
#define VDATA 'V'

#include <string>
#include <vector>
//#include "vec3.h"
#include "Maths.h"

/**
* @struct Struct for holding all message data
* @brief Class for handling collision
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
struct Data{
public:
	float fdata;
	char cdata;
	int idata;
	std::string sdata;
	vec3 vdata;
	std::vector<vec3> mvdata;
	const vec3 & getvData() { return vdata; }
};

/**
* @class Message
* @brief Class for creating messages
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class Message
{
public:
	Message();
	Message(std::string instruction);

	/**
	* @brief Set the instructions.
	*
	* @param string - The new instructions.
	*/
	void setInstruction(std::string instruuction);
	
	/**
	* @brief Get the instructions
	*
	* @return string - The instructions.
	*/
	std::string getInstruction();

	/**
	* @brief Get where the message came from.
	*
	* @return identifier - id for the message.
	*/
	Identifiers & getFrom();

	/**
	* @brief Set the identifier of the message.
	*
	* @param nid - The new identifier.
	*/
	void setFrom(const Identifiers & nid);

	/**
	* @brief Set the float data.
	*
	* @param data - The float data.
	*/
	void setfData(float data);

	/**
	* @brief Set the char data.
	*
	* @param data - The char data.
	*/
	void setData(char data);

	/**
	* @brief Set the int data.
	*
	* @param data - The int data.
	*/
	void setData(int data);

	/**
	* @brief Set the string data.
	*
	* @param data - The string data.
	*/
	void setData(std::string data);

	/**
	* @brief Set the vec3 data.
	*
	* @param data - The vec3 data.
	*/
	void setData(const vec3 & data);

	/**
	* @brief Get the Data
	*
	* @return Data - The data.
	*/
	Data & getData();

	/**
	* @brief Get the data type.
	*
	* @return char - The data type.
	*/
	char getDType();

	/**
	* @brief Set int data.
	*
	* @param idata - Int data.
	*/
	void setIData(int idata);

	/**
	* @brief Set string data.
	*
	* @param data - String data.
	*/
	void setsData(std::string data);

	/**
	* @brief Get string data.
	*
	* @return string - The data.
	*/
	std::string getsData();

	int getiData();

	/**
	* @brief Add vec3 data.
	*
	* @param toadd - The vec3.
	*/
	void addmvData(const vec3 & toadd);

	vec3 & getvData();
	void setvData(const vec3 & toset);

private:
	/// The data type.
	char dtype;
	/// The instructions.
	std::string instruction;
	/// The message data.
	Data mdata;
	/// The identifier to locate where the message is from.
	Identifiers from;

};

