#include "Player.h"


Player::Player(Identifiers & id, vec3 pos, ResourceList & list) : GameObject(id, pos, list)
{

}

Player::Player() : GameObject() {

}

bool Player::isCollidable() {
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

			if (tmpm.getInstruction() == GET_FRONT_RESPONSE) {
				front = tmpm.getData().vdata;
			}
			else
			if (tmpm.getInstruction() == POS_RESPONSE) {
				pos = tmpm.getData().vdata;
			}
			else
			if (tmpm.getInstruction() == FIRE_WEAPON) {
				tmpm = Message(ADD_TMP_OBJ);
				tmpm.getData().mvdata.push_back(pos);
				tmpm.getData().mvdata.push_back(front);
				if(resources.hasResource("projmodel")) tmpm.getData().sdata = resources.getResource("projmodel");
				tmp->postMessage(tmpm, Identifiers("", "GOH"));
				if(resources.hasResource("projsnd")) {
					tmpm.setInstruction(PLY_SND_SRC_REQUEST);
					if (resources.hasResource("projsnd")) tmpm.getData().sdata = resources.getResource("projsnd");
					tmpm.getData().idata = -1;
					tmp->postMessage(tmpm, Identifiers("", "AE"));
				}
			}
		}
	}
}

vec3 Player::getCenterOffset() {
	if (resources.hasResource("model") && model != NULL) {
		return vec3(0, abs(model->getMaxY()), 0);
	}

	return vec3(0, 0, 0);
}