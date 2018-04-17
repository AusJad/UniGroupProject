#pragma once

/**
* @class Singleton
* @brief Class for creating a singleton data type
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
template <class T>
class Singleton
{
public:

	/**
	* @brief Get the instance of the data.
	*
	* @return T* - The data.
	*/
	static T* getInstance();

private:
	/// The Data.
	static T* instance;
	Singleton() {}; 
	~Singleton() {};
	Singleton(Singleton const&) {};
	Singleton& operator=(Singleton const&) {};
};

template <class T>
T* Singleton<T>::instance = NULL;

template <class T>
T* Singleton<T>::getInstance() {
	if (instance != NULL) {
		return instance;
	}
	else {
		instance = new T;
		return instance;
	}
}