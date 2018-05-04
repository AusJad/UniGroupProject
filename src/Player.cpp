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
	Singleton<RenderModuleStubb>::getInstance()->RenderFacingCamera();
	if (resources.hasResource("model") && model != NULL) GameObject::model->render(vec3(0,0,0));
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

std::string Player::toString()
{
	std::string towrite;

	towrite += GameObject::id.getName() + ",";
	towrite += "POS," + std::to_string(GameObject::getPos().x()) + "," + std::to_string(GameObject::getPos().y()) + "," + std::to_string(GameObject::getPos().z()) + ",";
	towrite += "FRONT," + std::to_string(front.x()) + "," + std::to_string(front.y()) + "," + std::to_string(front.z());

	return towrite;
}

bool Player::fromstring(std::string toread)
{
	float tmpf;
	std::string linehead;
	int delimlen = 1;

	while (!toread.empty())
	{
		linehead = toread.substr(0, toread.find(','));
		toread.erase(0, toread.find(',') + delimlen);

		if (linehead == "POS")
		{
			tmpf = stof(toread.substr(0, toread.find(',')));
			GameObject::pos.sx(tmpf);
			toread.erase(0, toread.find(',') + delimlen);

			tmpf = stof(toread.substr(0, toread.find(',')));
			GameObject::pos.sy(tmpf);
			toread.erase(0, toread.find(',') + delimlen);

			tmpf = stof(toread.substr(0, toread.find(',')));
			GameObject::pos.sz(tmpf);
			toread.erase(0, toread.find(',') + delimlen);
		}
		else if (linehead == "FRONT")
		{
			tmpf = stof(toread.substr(0, toread.find(',')));
			front.sx(tmpf);
			toread.erase(0, toread.find(',') + delimlen);

			tmpf = stof(toread.substr(0, toread.find(',')));
			front.sy(tmpf);
			toread.erase(0, toread.find(',') + delimlen);

			tmpf = stof(toread.substr(0, toread.find(',')));
			front.sz(tmpf);
			toread.erase();
		}
	}
	return true;
}