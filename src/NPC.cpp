#include "NPC.h"


NPC::NPC(Identifiers & id, vec3 pos, ResourceList & list) : GameObject( id, pos, list )
{
	health = 0;
	speed = 0;
	lookangle = 0;
}

NPC::NPC() : GameObject(){
	health = 0;
	speed = 0;
	lookangle = 0;
}

NPC::~NPC()
{

}

void NPC::render() {

	RenderModuleStubb* tmp = Singleton<RenderModuleStubb>::getInstance();

	if (resources.hasResource("model") && model != NULL) {

		GeoStream << BEGIN_STREAM << trans_3(this->pos.x(), this->pos.y(), this->pos.z()) << rot_4(lookangle, 0, 1, 0);
		GameObject::model->render(this->pos);
		GeoStream << END_STREAM;
	}
	else {

		tmp->DrawQuad(point(pos.x(), pos.y() + 1), point(pos.x() + 1, pos.y()), pos.z());
	}
}

bool NPC::NPCDefaultMessageHandler(Message & message) {
	Identifiers tmp = message.getFrom();
	if (message.getInstruction() == VELOCITY_REQUEST) {
		message.setData(velocity);
		message.setFrom(id);
		message.setInstruction(VELOCITY_RESPONSE);
		Singleton<MessagingBus>::getInstance()->postMessage(message, tmp);
		return true;
	}

	return false;
}

void NPC::setLAngle(float nangle) {
	lookangle = nangle;
}

void NPC::update(float time) {
	LUAScriptManager* tmp = Singleton<LUAScriptManager>::getInstance();

	if (resources.hasResource("model") && model != NULL) model->update(time);

	msgrcvr();

	if(resources.hasResource("msgrcvr")) 
		tmp->callFunction<NPC, MessagingBus>(resources.getResource("msgrcvr"), *this, *(Singleton<MessagingBus>::getInstance()));

	if (resources.hasResource("updatefunc")) 
		tmp->callFunction<NPC, MessagingBus>(resources.getResource("updatefunc"), *this, *(Singleton<MessagingBus>::getInstance()));

	pos += velocity * time;

	if (velocity.getLength() > 0.0000001) {
		heading = velocity;
		heading.normailse();
	}

}

vec3 NPC::getCenterOffset() {
	if (resources.hasResource("model") && model != NULL) {
		return vec3(0, abs(model->getMaxY()), 0);
	}

	return vec3(0, 0, 0);
}

const vec3 &  NPC::getVelocity() {
	return velocity;
}

const float &  NPC::getHealth() {
	return health;
}

void NPC::setVelocity(const vec3 & velocity) {
	this->velocity = velocity;
}

void NPC::setHealth(float health) {
	this->health = health;
}

void NPC::setSpeed(float speed) {
	this->speed = speed;
}

float NPC::getSpeed() {
	return speed;
}

void NPC::stop() {
	velocity = vec3();
}

const vec3 & NPC::getHeading() {
	return heading;
}

void NPC::setHeading(const vec3 & heading) {
	this->heading = heading;
}