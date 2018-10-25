#include "NPC.h"


NPC::NPC(Identifiers & id, vec3 pos, ResourceList & list) : GameObject( id, pos, list )
{
	health = 0;
	speed = 0;
	lookangle = 0;
	evadetime = 0;
	canUpdate = false;
	canRender = false;
	canAttack = false;
}

NPC::NPC() : GameObject(){
	health = 0;
	speed = 0;
	lookangle = 0;
	evadetime = 0;
	canUpdate = false;
	canRender = false;
	canAttack = false;
}

NPC::~NPC()
{

}

bool NPC::isCollidable() {
	return canUpdate;
}

void NPC::render() {

	if (!canRender) return;

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
		
	}
	else
	if (message.getInstruction() == SET_HIDDEN) {
		canRender = false;
		return true;
	}
	else
	if(message.getInstruction() == SET_NOUPDATE){
		canUpdate = false;
		return true;
	}
	else
	if (message.getInstruction() == SET_STATE) {
		state = message.getiData();
	}
	else
	if (message.getInstruction() ==  PING) {
		Identifiers tmp = message.getFrom();
		message.setFrom(id);
		MSGBS->postMessage(message, tmp);
		return true;
	}
	else
	if (message.getInstruction() == SET_POS) {
		pos = message.getvData();
		target = vec3(0, 0, 0);
		velocity = vec3(0, 0, 0);
	}

	return false;
}

void NPC::setLAngle(float nangle) {
	lookangle = nangle;
}

void NPC::checkUpdateRndrChange() {
	Message tmp;
	
	while (MSGBS->hasMessage(id)) {
		tmp = MSGBS->getMessage(id);

		if (tmp.getInstruction() == SET_UPDATEABLE) {
			canUpdate = true;
		}
		else
		if (tmp.getInstruction() == SET_VISIBLE) {
			canRender = true;
		}
		else
		if (tmp.getInstruction() == SET_HIDDEN) {
			canRender = false;
		}
		else
		if (tmp.getInstruction() == SET_NOUPDATE) {
			canUpdate = false;
		}
		else
		if (tmp.getInstruction() == SET_STATE) {
			state = tmp.getiData();
		}
		else
		if (tmp.getInstruction() == SET_POS) {
			pos = tmp.getvData();
			target = vec3(0, 0, 0);
			velocity = vec3(0, 0, 0);
		}
	}
}

void NPC::onCollide(vec3 & prevloc, const Identifiers & colgoid) {
	if(colgoid.getType() != "BLT" && state != 2) state = -2;
}

void NPC::update(float time) {
	LUAScriptManager* tmp = Singleton<LUAScriptManager>::getInstance();

	if (resources.hasResource("model") && model != NULL) model->update(time);

	if (!canUpdate || !canRender) {
		checkUpdateRndrChange();
		return;
	}

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

NPC::NPC(const NPC & tocpy) : GameObject(tocpy) {
	velocity = tocpy.velocity;
	heading = tocpy.heading;
	lookangle = tocpy.lookangle;
	health = tocpy.health;
	speed = tocpy.speed;
	canUpdate = tocpy.canUpdate;
	canRender = tocpy.canRender;
	canAttack = tocpy.canAttack;
}

void NPC::setUpdatable(bool toset) {
	canUpdate = toset;
}

GameObject* NPC::create() {
	return new NPC(*this);
}

std::string NPC::toString()
{
	std::string towrite;

	//Best to centralise the code handling common attributes to GameObject
	towrite = GameObject::toString();

	/*
		No need to write these two out -- can be easily recomputed in LUA (not worth the overhead loading them)
		
		towrite += "VELOCITY," + std::to_string(velocity.x()) + "," + std::to_string(velocity.y()) + "," + std::to_string(velocity.z()) + ",";
		towrite += "HEADING," + std::to_string(heading.x()) + "," + std::to_string(heading.y()) + "," + std::to_string(heading.z()) + ",";
	*/
	towrite += "HEALTH," + std::to_string(health) + ",";
	towrite += "SPEED," + std::to_string(speed) + ",";
	towrite += "CANUPDATE,";
	if(canUpdate == true && health > 0) towrite += "1,";
	else towrite += "0,";
	towrite += "CANRENDER,";
	if (canUpdate == true && health > 0) towrite += "1,";
	else towrite += "0,";
	towrite += "CANATTACK,";
	towrite += (canAttack) ? "1," : "0,";
	towrite += "LOOKANGLE," + std::to_string(lookangle);

	return towrite;
}

bool NPC::fromstring(std::string toread)
{
	float tmpf;
	int tmpi;
	std::string linehead;

	int delimlen = 1;

	while (!toread.empty())
	{
		linehead = toread.substr(0, toread.find(','));
		toread.erase(0, toread.find(',') + delimlen);

		//std::cout << linehead << std::endl;

		if (!GameObject::fromstring(linehead, toread))
		if (linehead == "HEALTH")
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
		else if (linehead == "CANUPDATE")
		{
			tmpi = atoi(toread.substr(0, toread.find(',')).c_str());
			if (tmpi == 1) canUpdate = true;
			else canUpdate = false;

			toread.erase(0, toread.find(',') + delimlen);
		}
		else if (linehead == "CANRENDER")
		{
			tmpi = atoi(toread.substr(0, toread.find(',')).c_str());
			if (tmpi == 1) canRender = true;
			else canRender = false;

			toread.erase(0, toread.find(',') + delimlen);
		}
		else if (linehead == "CANATTACK")
		{
			tmpi = atoi(toread.substr(0, toread.find(',')).c_str());
			if (tmpi == 1) canAttack = true;
			else canAttack = false;

			toread.erase(0, toread.find(',') + delimlen);
		}
	}

	velocity = vec3();
	heading = vec3();
	target = vec3();

	return true;
}

bool NPC::getCanAttack() {
	return canAttack;
}

void NPC::setCanAttack(bool nval) {
	canAttack = nval;
}

void NPC::setEvadeTime(float toset) {
	evadetime = toset;
}

void NPC::onCollide2(vec3 & prevloc, const vec3 & colpos) {
	evadetarget = colpos;
}

float NPC::getEvadeTime() {
	return evadetime;
}

const vec3 & NPC::getEvadeTarget() {
	return evadetarget;
}

void NPC::setEvadeTarget(const vec3 & toset) {
	evadetarget = toset;
}

//mm
std::map<std::string, std::map<int, bool>> NPC::getAffordances()
{
	return Affordances;
}

void NPC::GenerateAffordances(std::vector<GameObject*> GOs)
{
	for (int i = 0; i < GOs.size(); i++)
	{
		Affordances["SIT"][GOs[i]->getID()] = canSit(GOs[i]);
		Affordances["MOVE"][GOs[i]->getID()] = canMove(GOs[i]);
		Affordances["PICKUP"][GOs[i]->getID()] = canPick_up(GOs[i]);
	}
}

/*
void NPC::GenerateAffordances(GameObject * GO)
{
	Affordances["SIT"][GO->getID()] = canSit(GO);
	Affordances["MOVE"][GO->getID()] = canMove(GO);
	Affordances["PICKUP"][GO->getID()] = canPick_up(GO);
}
*/

bool NPC::canSit(GameObject *go)
{
	// Assumption: You can only sit on objects greater than 20% of your height but less than 40%.
	if (go->getDimentions().y > getDimentions().y * 0.2 && go->getDimentions().y < getDimentions().y * 0.4);
	{
		return true;
	}
	return false;
}

bool NPC::canMove(GameObject *go)
{
	// Assumption: Anything can be moved if its total weight is less than the force behind the object acting on it.
	if (maxBench < go->getTotalMass())
		return true;
	return false;
}

bool NPC::canPick_up(GameObject *go)
{
	// Assumption: You can only pick up objects if they weigh less than you can carry and if their y is half or less of your height and if the x and z are the same of less than yours.
	if (maxBench > go->getTotalMass())
	{
		if (go->getDimentions().y < getDimentions().y * 0.5 && go->getDimentions().x <= getDimentions().x && go->getDimentions().z <= getDimentions().z);
		{
			return true;
		}
	}

	return false;
}

physvec3 NPC::getDimentions()
{
	return physvec3(model->getMaxTX() - model->getMinTX(), model->getMaxTY() - model->getMinTY(), model->getMaxTY() - model->getMinTY());
}

/*
+x = Exstasy
-x = Grief

+y = Admiration
-y = Loathing

+z = Vigilance
-z = Amazement

+w = Rage
-w = Terror
*/
void NPC::findNextState()
{
	char spoke = 'x';
	float max = abs(Emotion.x());

	if (max < abs(Emotion.y()))
	{
		spoke = 'y';
		max = abs(Emotion.y());
	}

	if (max < abs(Emotion.z()))
	{
		spoke = 'z';
		max = abs(Emotion.z());
	}

	if (max < abs(Emotion.w()))
	{
		spoke = 'w';
		max = abs(Emotion.w());
	}

	switch (spoke)
	{
	case 'x':
		if (Emotion.x() > 0)
		{
			//exstasy
		}
		else
		{
			//grief
		}
		break;

	case 'y':
		if (Emotion.y() > 0)
		{
			//Admiration
		}
		else
		{
			//Loathing
		}
		break;

	case 'z':
		if (Emotion.z() > 0)
		{
			//Vigilance
		}
		else
		{
			//Amazement
		}
		break;

	case 'w':
		if (Emotion.w() > 0)
		{
			//Rage
		}
		else
		{
			//terror
		}
		break;
	}
}

void NPC::addMod(Mods* m)
{
	all_Emo_Mods.push_back(m);
}

void NPC::addDef(Defs* d)
{
	all_Emo_Defs.push_back(d);
}

void NPC::normaliseEmotion()
{
	if (Emotion.x() != DefaultEmotion.x())
	{
		if (Emotion.x() < DefaultEmotion.x())
		{
			Emotion.sx(Emotion.x() + 0.1);
		}
		else
		{
			Emotion.sx(Emotion.x() - 0.1);
		}
	}

	if (Emotion.y() != DefaultEmotion.y())
	{
		if (Emotion.y() < DefaultEmotion.y())
		{
			Emotion.sy(Emotion.y() + 0.1);
		}
		else
		{
			Emotion.sy(Emotion.y() - 0.1);
		}
	}

	if (Emotion.z() != DefaultEmotion.z())
	{
		if (Emotion.z() < DefaultEmotion.z())
		{
			Emotion.sz(Emotion.z() + 0.1);
		}
		else
		{
			Emotion.sz(Emotion.z() - 0.1);
		}
	}

	if (Emotion.w() != DefaultEmotion.w())
	{
		if (Emotion.w() < DefaultEmotion.w())
		{
			Emotion.sw(Emotion.w() + 0.1);
		}
		else
		{
			Emotion.sw(Emotion.w() - 0.1);
		}
	}
}

void NPC::stateUpdate()
{
	// state changes need to be done here
}

void NPC::addEmotions(vec4 emo)
{
	// Use traits to find modifer of emotion
	for (int i = 0; i < all_Emo_Mods.size(); i++)
	{
		emo *= all_Emo_Mods[i]->getMod();
	}

	// Use normalisation matrix to calc effect single emotion has on others
	char max = 'x';
	float maxval = emo.x();

	if (max < emo.y())
	{
		max = 'y';
		maxval = emo.y();
	}

	if (max < emo.z())
	{
		max = 'z';
		maxval = emo.z();
	}

	if (max < emo.w())
	{
		max = 'w';
		maxval = emo.w();
	}

	switch (max)
	{
	case 'x':
		emo *= vec4(EmotionNormalisation[0], EmotionNormalisation[1], EmotionNormalisation[2], EmotionNormalisation[3]); // 1st row
		break;
	case 'y':
		emo *= vec4(EmotionNormalisation[4], EmotionNormalisation[5], EmotionNormalisation[6], EmotionNormalisation[7]); // 2nd row
		break; 
	case 'z':
		emo *= vec4(EmotionNormalisation[8], EmotionNormalisation[9], EmotionNormalisation[10], EmotionNormalisation[11]); // 3rd row
		break;
	case 'w':
		emo *= vec4(EmotionNormalisation[12], EmotionNormalisation[13], EmotionNormalisation[14], EmotionNormalisation[15]); // 4th row
		break;
	}

	Emotion += emo;
}

void NPC::ApplyTraits()
{
	for (int i = 0; i < all_Emo_Defs.size(); i++)
	{
		DefaultEmotion += all_Emo_Defs[i]->getDef();
	}
}