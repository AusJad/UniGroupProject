#include "Identifiers.h"



Identifiers::Identifiers()
{
	id = -1;
	name = "";
	type = "";
	objectname = "";
}

Identifiers::Identifiers(std::string type) {
	this->id = -1;
	name = "";
	this->type = type;
	objectname = "";
}

Identifiers::Identifiers(std::string type, std::string name) {
	this->id = -1;
	this->name = name;
	this->type = type;
	objectname = "";
}

Identifiers::Identifiers(std::string type, std::string name, std::string objectname) {
	this->id = -1;
	this->name = name;
	this->type = type;
	this->objectname = objectname;
}

void Identifiers::setId(int id) {
	this->id = id;
}

void Identifiers::setType(std::string type) {
	this->type = type;
}

void Identifiers::setName(std::string name) {
	this->name = name;
}

void Identifiers::setObjectname(std::string objectname) {
	this->objectname = objectname;
}

int Identifiers::getId() const{
	return id;
}

std::string Identifiers::getType() const{
	return type;
}

std::string Identifiers::getName() const{
	return name;
}

std::string Identifiers::getObjectname() const{
	return objectname;
}

bool Identifiers::operator == (const Identifiers & rhs) const {
	if (this->id != -1 && rhs.id != -1)
		if (this->id == rhs.id) return true;

	if (this->name.empty() == false && rhs.name.empty() == false)
		if (this->name == rhs.name) return true;

	if (this->type.empty() == false && rhs.type.empty() == false)
		if (this->type == rhs.type) return true;

	if (this->objectname.empty() == false && rhs.objectname.empty() == false)
		if (this->objectname == rhs.objectname) return true;

	return false;
}

bool Identifiers::operator < (const Identifiers & rhs) const {

	return this->name < rhs.name;
}