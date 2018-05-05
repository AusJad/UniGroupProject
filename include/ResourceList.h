#pragma once

#include <map>
#include <string>

/**
* @class ResourceList
* @brief Class for handling loaded resources
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class ResourceList
{
	public:
		ResourceList();	
		ResourceList(std::string k1, std::string v1);
		ResourceList(std::string k1, std::string v1, std::string k2, std::string v2);
		ResourceList(std::string k1, std::string v1, std::string k2, std::string v2, std::string k3, std::string v3);
		ResourceList(std::string k1, std::string v1, std::string k2, std::string v2, std::string k3, std::string v3, std::string k4, std::string v4);

		/**
		* @brief If the object has data.
		*
		* @param key - The key for the resource list.
		*
		* @return bool - If there is data.
		*/
		bool hasResource(std::string key);

		/**
		* @brief Get the resource from the list.
		*
		* @param key - The key for the resource list.
		*
		* @return string - The resource.
		*/
		std::string getResource(std::string key);

		/**
		* @brief Add a resource to the list.
		*
		* @param k1 - The first key for the resource list.
		* @param k2 - The second key for the resource list.
		*
		* @return bool - If the resource was added.
		*/
		bool addResource(std::string k1, std::string v1);

	private:
		/// The resource maps.
		std::map<std::string, std::string> resources;
};

