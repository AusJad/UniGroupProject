#pragma once

#include <map>
#include <queue>
#include "Message.h"
#include "Identifiers.h"
#include "MessageTypes.h"
#include "Singleton.h"
#include <iostream>

#define MSGBS Singleton<MessagingBus>::getInstance()

/**
* @class MessagingBus
* @brief Class for Sending and receiving messages
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class MessagingBus
{
public:
	/**
	* @brief Send the message.
	*
	* @param topost - The message.
	* @param recipient - Where the message is going.
	*/
	void postMessage(const Message & topost, const Identifiers & recipient);

	/**
	* @brief Get the message that was sent.
	*
	* @param id - The identifier.
	*
	* @return Message - The message
	*/
	Message getMessage(const Identifiers & id);

	/**
	* @brief If the id has a message.
	*
	* @param id - The identifier.
	*
	* @return bool - If the id has a message.
	*/
	bool hasMessage(const Identifiers & id);

	/**
	* @brief Send a imessage
	*
	* @param topost - The message.
	* @param recipientid - The id of the recipient.
	*/
	void postIMessage(const Message & topost, unsigned recipientid);

	/**
	* @brief Get the imessage
	*
	* @param recipientid - The recipient id.
	*
	* @return Message - The message.
	*/
	Message getIMessage(unsigned recipientid);

	/**
	* @brief Get if the id has a message.
	*
	* @param recipientid - The recipient id.
	*
	* @return bool - If the id has a message.
	*/
	bool hasIMessage(unsigned recipientid);

private:
	/// A map of the messages.
	std::map<Identifiers, std::queue<Message> > messages;
	/// A map of the imessages.
	std::map<unsigned, std::queue<Message> > imessages;
};

