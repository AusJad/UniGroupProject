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

int SimpleString::toInt() {
	return atoi(data.c_str());
}

void SimpleString::setData(std::string toset) {
	data = toset;
}