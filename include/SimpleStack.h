#pragma once
#include <stack>

template <class T>
class SimpleStack
{
public:
	SimpleStack() {};
	bool push(const T &stuff);
	void pop();
	T top();
	bool empty() const { return internalStack.empty(); };
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
void SimpleStack<T>::pop() {
	if (internalStack.size() > 0) {
		internalStack.pop();
	}
}

template <class T>
int SimpleStack<T>::size() {
	return internalStack.size();
}

template <class T>
T SimpleStack<T>::top() {
	if (internalStack.size() > 0) {
		return internalStack.top();
	}
}

