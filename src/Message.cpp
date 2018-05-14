#include "Message.h"

Message::Message(){
	dtype = 'N';
}

Message::Message(std::string instruction) {
	this->instruction = instruction;
}

char Message::getDType() {
	return dtype;
}

void Message::setIData(int idata) {
	mdata.idata = idata;
}

void Message::setInstruction(std::string instruuction) {
	this->instruction = instruuction;
}

std::string Message::getInstruction() {
	return instruction;
}

void Message::setfData(float data) {
	mdata.fdata = data;
	dtype = FDATA;
}

void Message::setData(char data) {
	mdata.cdata = data;
	dtype = CDATA;
}

void Message::setData(int data) {
	mdata.idata = data;
	dtype = IDATA;
}

void Message::setData(std::string data) {
	mdata.sdata = data;
	dtype = SDATA;
}

void Message::setData(const vec3 & data) {
	mdata.vdata = data;
	dtype = VDATA;
}


void Message::setsData(std::string data) {
	mdata.sdata = data;
}

Data & Message::getData() {
	return mdata;
}

Identifiers & Message::getFrom() {
	return from;
}

void Message::setFrom(const Identifiers & nid) {
	from = nid;
}

std::string Message::getsData() {
	return mdata.sdata;
}

void Message::addmvData(const vec3 & toadd) {
	mdata.mvdata.push_back(toadd);
}

int Message::getiData() {
	return mdata.idata;
}