#include "NPC.h"
#include "NPCstates.h"



NPC::NPC(Identifiers & id, vec3 pos, ResourceList & list) : GameObject( id, pos, list )
{
	health = 0;
	speed = 0;
	lookangle = 0;
	evadetime = 0;
	canUpdate = true;
	canRender = true;
	canAttack = false;
	npcFSM=new stateMachine<NPC>(this);
	npcFSM->setCurrentState(wander_state::getInstance());
	npcFSM->setGlobalState(global_state::getInstance());
	totalmass = 1;
	scalex = 1;
	scaley = 1;
	scalez = 1;

	emotion = Emotions();
	this->generate_rnd_emotions();
	maxBench = 200;
}

NPC::NPC() : GameObject(){
	health = 0;
	speed = 0;
	lookangle = 0;
	evadetime = 0;
	canUpdate = true;
	canRender = true;
	canAttack = false;
	scalex = 1;
	scaley = 1;
	scalez = 1;
	npcFSM = new stateMachine<NPC>(this);
	npcFSM->setCurrentState(wander_state::getInstance());
	npcFSM->setGlobalState(global_state::getInstance());
	totalmass = 1;

	emotion = Emotions();
	this->generate_rnd_emotions();
	maxBench = 200;
}

NPC::~NPC()
{
	delete npcFSM;
}

bool NPC::isCollidable() {
	return canUpdate;
}

void NPC::render() {
	

	if (!canRender) return;
	
	//std::cout << "NPC render function" << std::endl;

	RenderModuleStubb* tmp = Singleton<RenderModuleStubb>::getInstance();
	//resources.hasResource("model") &&

	if ( model != NULL) {
		//std::cout << "Attempting to render NPC" << std::endl;
		GeoStream << BEGIN_STREAM << trans_3(this->trans.x(), this->trans.y(), this->trans.z()) << rot_4(lookangle, 0, 1, 0);
		GameObject::model->render(this->trans);
		GeoStream << END_STREAM;
	}
	else {
		//std::cout << "Drawing a box" << std::endl;
		tmp->DrawQuad(point(trans.x(), trans.y() + 1), point(trans.x() + 1, trans.y()), trans.z());
	}

	physvec3 rot;
	if (this->hasMultiObb()) {
		GeoStream << START_ATTRIB << color_3(0.6f, 1.0f, 0.0f);
		OBB tmpobb;
		for (int i = 0; i < this->getNumOBBs(); i++) {
			RNDR->enableWireframe();
			tmpobb = this->getOBB(i);
			rot = Decompose(tmpobb.orientation);
			GeoStream << BEGIN_STREAM << trans_3(tmpobb.position.x, tmpobb.position.y, tmpobb.position.z) << rot_4(RAD2DEG(rot.x), 1, 0, 0) << rot_4(RAD2DEG(rot.y), 0, 1, 0) << rot_4(RAD2DEG(rot.z), 0, 0, 1);
			RNDR->DrawRectangularPrism(vec3(), tmpobb.size.x, tmpobb.size.y, tmpobb.size.z);
			GeoStream << END_STREAM;
			RNDR->disableWireFrame();
			RNDR->DrawRectangularPrism(vec3(tmpobb.position.x, tmpobb.position.y, tmpobb.position.z), 3, 3, 3);

		}
		GeoStream << END_ATTRIB;
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
	
	//std::cout << "Entering update loop" << std::endl;
	npcFSM->update();

	
	LUAScriptManager* tmp = Singleton<LUAScriptManager>::getInstance();

	if (resources.hasResource("model") && model != NULL) model->update(time);

	if (!canUpdate || !canRender) {
		checkUpdateRndrChange();
		return;
	}

	msgrcvr();

	if (resources.hasResource("msgrcvr"))
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

bool NPC::canSit(GameObject *go)
{
	// Assumption: You can only sit on objects greater than 20% of your height but less than 40%.
	if (go->getDimentions().y > getDimentions().y * 0.2 && go->getDimentions().y < getDimentions().y * 0.4);
	{
		std::cout << "SIT: " << go->getID() << ": True" << std::endl;
		return true;
	}
	std::cout << "SIT: " << go->getID() << ": False" << std::endl;
	return false;
}

bool NPC::canMove(GameObject *go)
{
	// Assumption: Anything can be moved if its total weight is less than the force behind the object acting on it.
	if (maxBench < go->getTotalMass())
	{
		std::cout << "MOVE: " << go->getID() << ": True" << std::endl;
		return true;
	}
	std::cout << "MOVE: " << go->getID() << ": False" << std::endl;
	return false;
}

bool NPC::canPick_up(GameObject *go)
{
	// Assumption: You can only pick up objects if they weigh less than you can carry and if their y is half or less of your height and if the x and z are the same of less than yours.
	if (maxBench > go->getTotalMass())
	{
		if (go->getDimentions().y < getDimentions().y * 0.5 && go->getDimentions().x <= getDimentions().x && go->getDimentions().z <= getDimentions().z);
		{
			std::cout << "PICKUP: " << go->getID() << ": True" << std::endl;
			return true;
		}
	}
	std::cout << "PICKUP: " << go->getID() << ": False" << std::endl;
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
	float max = abs(emotion.x());

	if (max < abs(emotion.y()))
	{
		spoke = 'y';
		max = abs(emotion.y());
	}

	if (max < abs(emotion.z()))
	{
		spoke = 'z';
		max = abs(emotion.z());
	}

	if (max < abs(emotion.w()))
	{
		spoke = 'w';
		max = abs(emotion.w());
	}

	switch (spoke)
	{
	case 'x':
		if (emotion.x() > 0)
		{
			//exstasy
		}
		else
		{
			//grief
		}
		break;

	case 'y':
		if (emotion.y() > 0)
		{
			//Admiration
		}
		else
		{
			//Loathing
		}
		break;

	case 'z':
		if (emotion.z() > 0)
		{
			//Vigilance
		}
		else
		{
			//Amazement
		}
		break;

	case 'w':
		if (emotion.w() > 0)
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

void NPC::stateUpdate()
{
	// state changes need to be done here
}

void NPC::calcMass()
{
	if (this->hasMultiObb())
	{
		for (int i = 0; i < obbs.size(); i++)
		{
			totalmass += obbs[i].mass;
		}
	}
	else
	{
		totalmass = obb.mass;
	}
}

//obb stuff
bool NPC::addMultiObb(std::vector<OBB> & in) {
	this->obbsConfig = in;
	this->obbs = this->obbsConfig;
	return true;
};

OBB NPC::getOBB() {
	return obb;
}

OBB NPC::getOBB(unsigned int index) {
	if (index < obbs.size())
		return obbs[index];
}

std::vector<OBB> NPC::getOBBs() {
	return obbs;
};

OBB NPC::getOBBConfig(unsigned int index) {
	if (index < obbsConfig.size()) {
		return obbsConfig[index];
	}
}

bool NPC::hasMultiObb() {
	if (obbsConfig.size() > 0) { return true; }
	else { return false; }
};

int NPC::getNumOBBs() {
	return obbsConfig.size();
};

OBB NPC::getOBB(int obbNum) {
	return obbs.at(obbNum);
};

void NPC::setScaleX(float nscalex) {
	scalex = nscalex;
}

void NPC::setScaleY(float nscaley) {
	scaley = nscaley;
}

void NPC::setScaleZ(float nscalez) {
	scalez = nscalez;
}
bool NPC::addMultiObb(OBB in) {
	obbs.push_back(in);
		return true;
}

void NPC::updateBounds() {
	if (model != NULL) {
		model->setScale(vec3(scalex, scaley, scalez));
		std::vector<vec3> minmax = model->computeMMax();
		if (this->hasMultiObb()) {
			std::cout << model->getName() << " has multi-obb" << std::endl;
			for (int i = 0; i < obbs.size(); i++) {
				//obbs[i].position = physvec3((trans.x() + obbsConfig[i].position.x * (scalex)), trans.y() + obbsConfig[i].position.y * (scaley), trans.z() + obbsConfig[i].position.z * (scalez));
				obbs[i].size.x = obbsConfig[i].size.x * scalex;
				obbs[i].size.y = obbsConfig[i].size.y * scaley;
				obbs[i].size.z = obbsConfig[i].size.z * scalez;
				//rotate around origin
				//physvec3 tmp = MultiplyPoint(((obbs[i].position - obbsConfig[i].position) * physvec3(scalex, scaley, scalez)), Rotation(anglex, angley, anglez));
				obbs[i].position = trans;
				physvec3 tmp2 = physvec3(obbsConfig[i].position.x, obbsConfig[i].position.y, obbsConfig[i].position.z) * physvec3(scalex, scaley, scalez);
				physvec3 tmp = MultiplyPoint(tmp2, Rotation(anglex, angley, anglez));
				obbs[i].position += tmp;
				//std::cout << "tmp.x: " << tmp.x << " tmp.y: " << tmp.y << " tmp.z: " << tmp.z << std::endl;



				// = trans + tmp;
				//obbs[i].position.x = tmp.x;
				//obbs[i].position.y = tmp.y;
				//obbs[i].position.z = tmp.z;
				//obbs[i].position = physvec3((trans.x() + obbsConfig[i].position.x * (scalex)), trans.y() + obbsConfig[i].position.y * (scaley), trans.z() + obbsConfig[i].position.z * (scalez));
				obbs[i].orientation = Rotation3x3(anglex, angley, anglez);
				//obbs[i].position -= physvec3((obbsConfig[i].position.x * (scalex)), obbsConfig[i].position.y * (scaley), obbsConfig[i].position.z * (scalez));

				this->calcMass(); //mm
			}
		}
		else {
			std::cout << model->getName() << " does not have multi-obb, no OBB on NPC object" << std::endl;
			//obb.position = physvec3(trans.x(), trans.y(), trans.z());
			//obb.size = physvec3((minmax.at(1).x() - minmax.at(0).x()) / 2,
			//	(minmax.at(1).y() - minmax.at(0).y()) / 2,
			//	(minmax.at(1).z() - minmax.at(0).z()) / 2);
			//obb.orientation = Rotation3x3(anglex, angley, anglez);

			this->calcMass(); //mm
		}
		
	}
}

void NPC::generate_rnd_emotions()
{
	vec4 emo, mod, def;
	int rng;
	float value;

	srand(time(NULL));

	/* Emotion */
	rng = rand() %99 - 0;
	value = (float)rng / 100.f;
	emo.sx(value);

	rng = rand() % 99 - 0;
	value = (float)rng / 100.f;
	emo.sy(value);

	rng = rand() % 99 - 0;
	value = (float)rng / 100.f;
	emo.sz(value);

	rng = rand() % 99 - 0;
	value = (float)rng / 100.f;
	emo.sw(value);

	/* Modifiers */
	rng = rand() % 99 - 0;
	value = (float)rng / 100.f;
	mod.sx(value);

	rng = rand() % 99 - 0;
	value = (float)rng / 100.f;
	mod.sy(value);

	rng = rand() % 99 - 0;
	value = (float)rng / 100.f;
	mod.sz(value);

	rng = rand() % 99 - 0;
	value = (float)rng / 100.f;
	mod.sw(value);

	/* Defaults */
	rng = rand() % 99 - 0;
	value = (float)rng / 100.f;
	def.sx(value);

	rng = rand() % 99 - 0;
	value = (float)rng / 100.f;
	def.sy(value);

	rng = rand() % 99 - 0;
	value = (float)rng / 100.f;
	def.sz(value);

	rng = rand() % 99 - 0;
	value = (float)rng / 100.f;
	def.sw(value);

	/* Sets */
	emotion.setEmotions(emo);
	emotion.setModifiers(mod);
	emotion.setDefaults(def);

	std::cout << "Emotion: " << emotion.x() << " " << emotion.y() << " " << emotion.z() << " " << emotion.w() << std::endl;
	std::cout << "Modifiers: " << emotion.getModifiers().x() << " " << emotion.getModifiers().y() << " " << emotion.getModifiers().z() << " " << emotion.getModifiers().w() << std::endl;
	std::cout << "Defaults: " << emotion.getDefaults().x() << " " << emotion.getDefaults().y() << " " << emotion.getDefaults().z() << " " << emotion.getDefaults().w() << std::endl;
}

void NPC::addemotion(vec4 emo)
{
	emotion.add_emotion(emo);
}

vec4 NPC::getemotion()
{
	return emotion.getEmotions();
}

vec4 NPC::getdefault()
{
	return emotion.getDefaults();
}

void NPC::generateWaypoints(vec3 targetpos)
{
	waypoints = pathFinder::findpath(all_GOs, pos, targetpos);
}

SimpleStack NPC::getWaypoint()
{
	return waypoints;
}

void NPC::popWaypoint()
{
	waypoints.pop();
}

void NPC::setWaypoint(SimpleStack wp)
{
	waypoints = wp;
}