#include "Player.h"


Player::Player(Identifiers & id, vec3 pos, ResourceList & list) : GameObject(id, pos, list)
{
	ammo = -20;
	health = 0;
}

Player::Player() : GameObject() {
	ammo = -20;
	health = 0;
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

Player::Player(const Player & tocpy) : GameObject(tocpy) {
	front = tocpy.front;
	ammo = tocpy.ammo;
	health = tocpy.health;
}

GameObject* Player::create() {
	return new Player(*this);
}

std::string Player::toString()
{
	std::string towrite;

	towrite += GameObject::id.getName() + ",";
	towrite += "POS," + std::to_string(GameObject::getPos().x()) + "," + std::to_string(GameObject::getPos().y()) + "," + std::to_string(GameObject::getPos().z()) + ",";
	towrite += "HEALTH," + std::to_string(health) + ",";
	towrite += "AMMO," + std::to_string(ammo) + ",";
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
		else if (linehead == "HEALTH")
		{
			tmpf = stof(toread.substr(0, toread.find(',')));
			health = tmpf;
			toread.erase(0, toread.find(',') + delimlen);
		}
		else if (linehead == "AMMO")
		{
			tmpf = stof(toread.substr(0, toread.find(',')));
			ammo = tmpf;
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

void Player::setHealth(float nh) {
	health = nh;
}

void Player::setAmmo(int na) {
	ammo = na;
}

float Player::getHealth() {
	return health;
}

int Player::getAmmo() {
	return ammo;
}