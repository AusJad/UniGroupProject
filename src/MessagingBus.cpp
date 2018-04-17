#include "MessagingBus.h"

void MessagingBus::postMessage(const Message & topost, const Identifiers & recipient) {
	if (messages.count(recipient) == 0) {
		std::queue<Message> tmp;
		messages[recipient] = tmp;
	}

	messages.at(recipient).push(topost);
}

Message MessagingBus::getMessage(const Identifiers & id) {
	Message tmp = messages.at(id).front();
	messages.at(id).pop();
	return tmp;
}

bool MessagingBus::hasMessage(const Identifiers & id) {
	if (messages.count(id) == 1) {
		if (messages.at(id).size() > 0) return true;
	}

	return false;
}

void MessagingBus::postIMessage(const Message & topost, unsigned recipientid) {
	if (imessages.count(recipientid) == 0) {
		std::queue<Message> tmp;
		imessages[recipientid] = tmp;
	}

	imessages.at(recipientid).push(topost);
}

Message MessagingBus::getIMessage(unsigned recipientid) {
	Message tmp = imessages.at(recipientid).front();
	imessages.at(recipientid).pop();
	return tmp;
}

bool MessagingBus::hasIMessage(unsigned recipientid) {
	if (imessages.count(recipientid) == 1) {
		if (imessages.at(recipientid).size() > 0) return true;
	}

	return false;
}