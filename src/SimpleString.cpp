#include "SimpleString.h"

SimpleString::SimpleString()
{
}

bool SimpleString::equals(std::string comparator) {
	return data == comparator;
}

double SimpleString::toDouble() {
	return atof(data.c_str());
}

std::string SimpleString::getData() {
	return data;
}
