#pragma once

#include <string>

/**
* @class Identifiers
* @brief Class for handling identification of different objects and data types
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class Identifiers
{
public:
	Identifiers();
	Identifiers(std::string type);
	Identifiers(std::string type, std::string name);
	Identifiers(std::string type, std::string name, std::string objectname);

	/**
	* @brief Set the id.
	*
	* @param id - The new id.
	*/
	void setId(int id);

	/**
	* @brief Set the type.
	*
	* @param type - The new type.
	*/
	void setType(std::string type);

	/**
	* @brief Set the name.
	*
	* @param name - The new name.
	*/
	void setName(std::string name);

	/**
	* @brief Set the object name.
	*
	* @param objectname - The new object name.
	*/
	void setObjectname(std::string objectname);

	/**
	* @brief Get the id.
	*
	* @return int - The id.
	*/
	int getId() const;

	/**
	* @brief Get the type.
	*
	* @return string - The type.
	*/
	std::string getType() const;

	/**
	* @brief Get the name.
	*
	* @return string - The name.
	*/
	std::string getName() const;

	/**
	* @brief Get the object name.
	*
	* @return string - The object name.
	*/
	std::string getObjectname() const;

	/**
	* @brief Overload function for the < operator.
	*
	* @param rhs - The identifier for comparison.
	*
	* @return bool - Result of the comparison.
	*/
	bool operator < (const Identifiers & rhs) const;

	/**
	* @brief Overload function for the == operator.
	*
	* @param rhs - The identifier for comparison.
	*
	* @return bool - Result of the comparison.
	*/
	bool operator == (const Identifiers & rhs) const;

private:
	/// The id.
	int id;
	/// The type of object.
	std::string type;
	/// The name of the identifier.
	std::string name;
	/// The name of the object.
	std::string objectname;
};

