#pragma once
#include <stack>

template <class T>
class SimpleStack
{
public:
	SimpleStack() {};
	bool push(const T &stuff);
	bool pop(T &stuff);
	bool empty() const { return internalStack.empty() };
	int size();

private:
	std::stack<T> internalStack;
};

template <class T>
bool SimpleStack<T>::push(const T &stuff) {
	bool okay = true;
	try {
		internalStack.push(stuff);
	}
	catch (...) {
		okay = false;
	}
	return okay;
}

template <class T>
bool SimpleStack<T>::pop(T &stuff) {
	if (internalStack.size() > 0 ){
		stuff = internalStack.top();
		internalStack.pop();
		return true;
	}
	else{
		return false;
	}
}

template <class T>
int SimpleStack<T>::size() {
	return internalStack.size();
}


