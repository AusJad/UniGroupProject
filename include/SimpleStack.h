#pragma once
#include <stack>
#include "vec3.h"
/**
* @class SimpleStack
* @brief Fascade class for a stack of vec3's
*
* @author Mat De Vene
* @version 01
* @date 24/05/2018
*/

class SimpleStack
{
public:
	/**
	* @brief Constructor.
	*
	*/
	SimpleStack::SimpleStack() {};
	/**
	* @brief Push an object onto the stack.
	*
	* @param stuff, vec3 to push
	*/	
	bool SimpleStack::push(const vec3 &stuff) {
		bool okay = true;
		try {
			internalStack.push(stuff);
		}
		catch (...) {
			okay = false;
		}
		return okay;
	}
	/**
	* @brief Pop an object from the stack.
	*
	*/
	void SimpleStack::pop() {
		if (internalStack.size() > 0) {
			internalStack.pop();
		}
	}
	/**
	* @brief Look at item on top of stack.
	*
	* @return vec3
	*/
	vec3 & SimpleStack::top() {
		if (internalStack.size() > 0) {
			return internalStack.top();
		}
		return vec3();
	}
	/**
	* @brief Is stack empty
	*
	* @return bool
	*/
	bool SimpleStack::empty() const { return internalStack.empty(); };
	int size() {
		return internalStack.size();
	}
	/**
	* @brief duplicate stack
	*
	* @return SimpleStack
	*/
	void SimpleStack::dup(SimpleStack & rhs) { internalStack = rhs.internalStack; };

private:
	/// internal STL stack
	std::stack<vec3> internalStack;
};
