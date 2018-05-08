#include "Player.h"


Player::Player(Identifiers & id, vec3 pos, ResourceList & list) : GameObject(id, pos, list)
{

}

Player::Player() : GameObject() {

}

bool Player::isCollidable() {
	return false;
}

const vec3 & Player::getFront() {
	return front;
}


bool Player::playerDefaultMessageHandler(Message & tocheck) {
	if (tocheck.getInstruction() == GET_FRONT_RESPONSE) {
		front = tocheck.getData().vdata;
		return true;
	}
	else
	if (tocheck.getInstruction() == POS_RESPONSE) {
		pos = tocheck.getData().vdata;
		return true;
	}

	return false;
}


void Player::render() {

	if (resources.hasResource("renderfunc")) {
		RenderModuleStubb* tmp = Singleton<RenderModuleStubb>::getInstance();
		tmp->RenderFacingCamera();
		LSM->callFunction<Player, MessagingBus>(resources.getResource("renderfunc"), *this, *(Singleton<MessagingBus>::getInstance()));
		tmp->StopRenderFacingCamera();
	}
}

void Player::drawModel(vec3 & trans, float rot) {
	Singleton<RenderModuleStubb>::getInstance()->RenderFacingCamera();
	GeoStream << BEGIN_STREAM << trans_3(trans.x(), trans.y(), trans.z()) << rot_4(rot, 0, 1, 0);
	if (resources.hasResource("model") && model != NULL) GameObject::model->render(vec3(0, 0, 0));
	GeoStream << END_STREAM;
	Singleton<RenderModuleStubb>::getInstance()->StopRenderFacingCamera();
}

void Player::update(float time) {
	msgrcvr();

	if (resources.hasResource("msgrcvr"))
		LSM->callFunction<Player, MessagingBus>(resources.getResource("msgrcvr"), *this, *MSGBS);

	if (resources.hasResource("model") && model != NULL) model->update(time);

	MessagingBus* tmp = Singleton<MessagingBus>::getInstance();
	Message tmpm;

	tmpm.setFrom(id);

	if (resources.hasResource("camera")) {
		tmpm.setInstruction(GET_FRONT);
		tmp->postMessage(tmpm, Identifiers("", resources.getResource("camera")));
		
		tmpm.setInstruction(POS_REQUEST);
		tmp->postMessage(tmpm, Identifiers("", resources.getResource("camera")));

		while (tmp->hasMessage(id)) {

			tmpm = tmp->getMessage(id);


		}
	}
}

vec3 Player::getCenterOffset() {
	if (resources.hasResource("model") && model != NULL) {
		return vec3(0, abs(model->getMaxY()), 0);
	}

	return vec3(0, 0, 0);
}