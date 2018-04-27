#include "NPC.h"


NPC::NPC(Identifiers & id, vec3 pos, ResourceList & list) : GameObject( id, pos, list )
{
	health = 0;
	speed = 0;
	lookat = false;
}

NPC::NPC() : GameObject(){
	health = 0;
	speed = 0;
	lookat = false;
}

NPC::~NPC()
{

}

void NPC::render() {

	RenderModuleStubb* tmp = Singleton<RenderModuleStubb>::getInstance();

	if (resources.hasResource("model") && model != NULL) {
		if(lookat) tmp->pushMatrix(lookmat);
		GameObject::model->render(this->pos);
		if (lookat) { tmp->popMatrix(); lookat = false; }
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

void NPC::lookAt(vec3 target) {
	target.normailse();
	lookat = true;
	vec3 up = vec3(0.0f, 1.0f, 0.0f);
	
	vec3 foward = ( target - pos).normailse();
	vec3 left = up.cross(foward).normailse();
	up = foward.cross(left).normailse();

	lookmat[0] = left.x();		lookmat[1] = up.x();		lookmat[2] = foward.x();		lookmat[3] = 0.0f;
	lookmat[4] = left.y();		lookmat[5] = up.y();		lookmat[6] = foward.y();		lookmat[7] = 0.0f;
	lookmat[8] = left.z();		lookmat[9] = up.z();		lookmat[10] = foward.z();			lookmat[11] = 0.0f;
	lookmat[12] = 0.0f;			lookmat[13] = 0.0f;			lookmat[14] = 0.0f;				lookmat[15] = 1.0f;
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