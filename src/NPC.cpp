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

//mm
std::string NPC::toString()
{
	std::string towrite;

	towrite += GameObject::id.getName() + ",";
	towrite += "POS," + std::to_string(GameObject::pos.x()) + "," + std::to_string(GameObject::pos.y()) + "," + std::to_string(GameObject::pos.z()) + ",";
	towrite += "TARGET," + std::to_string(GameObject::target.x()) + "," + std::to_string(GameObject::target.y()) + "," + std::to_string(GameObject::target.z()) + ",";
	towrite += "TARGETLOOK," + std::to_string(GameObject::targetlook.x()) + "," + std::to_string(GameObject::targetlook.y()) + "," + std::to_string(GameObject::targetlook.z()) + ",";
	towrite += "VELOCITY," + std::to_string(velocity.x()) + "," + std::to_string(velocity.y()) + "," + std::to_string(velocity.z()) + ",";
	towrite += "HEADING," + std::to_string(heading.x()) + "," + std::to_string(heading.y()) + "," + std::to_string(heading.z()) + ",";
	towrite += "HEALTH," + std::to_string(health) + ",";
	towrite += "SPEED," + std::to_string(speed) + ",";
	towrite += "LOOKANGLE," + std::to_string(lookangle);

	return towrite;
}

bool NPC::fromstring(std::string toread)
{
	float tmpf;
	std::string linehead;

	int delimlen = 1;

	while (!toread.empty())
	{
		linehead = toread.substr(0, toread.find(','));
		toread.erase(0, toread.find(',') + delimlen);

		if (linehead == "POS" || linehead == ",POS")
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
		else if (linehead == "TARGET")
		{
			tmpf = stof(toread.substr(0, toread.find(',')));
			GameObject::target.sx(tmpf);
			toread.erase(0, toread.find(',') + delimlen);

			tmpf = stof(toread.substr(0, toread.find(',')));
			GameObject::target.sy(tmpf);
			toread.erase(0, toread.find(',') + delimlen);

			tmpf = stof(toread.substr(0, toread.find(',')));
			GameObject::target.sz(tmpf);
			toread.erase(0, toread.find(',') + delimlen);
		}
		else if (linehead == "TARGETLOOK")
		{
			tmpf = stof(toread.substr(0, toread.find(',')));
			GameObject::targetlook.sx(tmpf);
			toread.erase(0, toread.find(',') + delimlen);

			tmpf = stof(toread.substr(0, toread.find(',')));
			GameObject::targetlook.sy(tmpf);
			toread.erase(0, toread.find(',') + delimlen);

			tmpf = stof(toread);
			GameObject::targetlook.sz(tmpf);
			toread.erase(0, toread.find(',') + delimlen);
		}
		else if (linehead == "VELOCITY")
		{
			tmpf = stof(toread.substr(0, toread.find(',')));
			velocity.sx(tmpf);
			toread.erase(0, toread.find(',') + delimlen);

			tmpf = stof(toread.substr(0, toread.find(',')));
			velocity.sy(tmpf);
			toread.erase(0, toread.find(',') + delimlen);

			tmpf = stof(toread.substr(0, toread.find(',')));
			velocity.sz(tmpf);
			toread.erase(0, toread.find(',') + delimlen);
		}
		else if (linehead == "HEADING")
		{
			// Had problem with some heading variables where it was empty.
			if (toread.substr(0, toread.find(',')) == "-nan(ind)")
				heading.sx(0);
			else
			{
				tmpf = stof(toread.substr(0, toread.find(',')));
				heading.sx(tmpf);
			}
			toread.erase(0, toread.find(',') + delimlen);

			if (toread.substr(0, toread.find(',')) == "-nan(ind)")
				heading.sy(0);
			else
			{
				tmpf = stof(toread.substr(0, toread.find(',')));
				heading.sx(tmpf);
			}
			toread.erase(0, toread.find(',') + delimlen);

			if (toread.substr(0, toread.find(',')) == "-nan(ind)")
				heading.sx(0);
			else
			{
				tmpf = stof(toread.substr(0, toread.find(',')));
				heading.sy(tmpf);
			}
			toread.erase(0, toread.find(',') + delimlen);
		}
		else if (linehead == "HEALTH")
		{
			tmpf = stof(toread.substr(0, toread.find(',')));
			health = tmpf;
			toread.erase(0, toread.find(',') + delimlen);
		}
		else if (linehead == "SPEED")
		{
			tmpf = stof(toread.substr(0, toread.find(',')));
			speed = tmpf;
			toread.erase(0, toread.find(',') + delimlen);
		}
		else if (linehead == "LOOKANGLE")
		{
			tmpf = stof(toread);
			lookangle = tmpf;
			toread.erase();
		}
	}
	return true;
}
