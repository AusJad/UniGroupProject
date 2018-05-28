#pragma once
#include <stack>
#include "vec3.h"

class SimpleStack
{
public:
	SimpleStack::SimpleStack() {};
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
	void SimpleStack::pop() {
		if (internalStack.size() > 0) {
			internalStack.pop();
		}
	}
	vec3 & SimpleStack::top() {
		if (internalStack.size() > 0) {
			return internalStack.top();
		}
		return vec3();
	}
	bool SimpleStack::empty() const { return internalStack.empty(); };
	int size() {
		return internalStack.size();
	}
	void SimpleStack::dup(SimpleStack & rhs) { internalStack = rhs.internalStack; };

private:
	std::stack<vec3> internalStack;
};
