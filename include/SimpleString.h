#pragma once

#include <string>

/**
* @class SimpleString
* @brief Simplified std:::string for use with lua - simplifies binding process by only including essential behaviour
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class SimpleString
{
public:
	SimpleString();
	SimpleString(std::string in) : data(in) {};

	/**
	* @brief Find if the string are equal.
	*
	* @param comparator - The second string.
	*
	* @return bool - If the strings are equal.
	*/
	bool equals(std::string comparator);

	/**
	* @brief Convert the string to a double.
	*
	* @return double - The converted string.
	*/
	double toDouble();

	/**
	* @brief Get the data from the string.
	*
	* @return string - The string data.
	*/
	std::string getData();

private:	
	/// String data.
	std::string data;
};

