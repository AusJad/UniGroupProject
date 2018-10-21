#include "GameObject.h"


GameObject::GameObject() 
{
	state = -1;
	model = NULL;
}

GameObject::GameObject(Identifiers & id, vec3 pos, ResourceList & list) {
	this->id = id;
	this->pos = pos;
	this->resources = list;
	state = -1;
	model = NULL;
}

GameObject::~GameObject() {
	if (model != NULL) delete model;

	model = NULL;
}

const Identifiers  & GameObject::getIdentifiers() {
	return id;
}

void GameObject::setTarget(const vec3 target) {
	this->target = target;
}

const vec3 & GameObject::getTarget() {
	return this->target;
}

int GameObject::getState() {
	return state;
}

void GameObject::setState(int state) {
	this->state = state;
}

void GameObject::setID(int id){
	this->id.setId(id);
}

int GameObject::getID() const{
	return id.getId();
}

void GameObject::setPos(vec3 pos){
	this->pos = pos;
}

const vec3 & GameObject::getPos() const{
	return pos;
}

std::string GameObject::getType(){
	return id.getType();
}

void GameObject::stop() {
	target = vec3();
}

void GameObject::msgrcvr() {
	MessagingBus* tmpmsgbus = Singleton<MessagingBus>::getInstance();

	Message tmpmsg;

	Message tmprmsg;

	while (tmpmsgbus->hasIMessage(this->id.getId())) {
		tmpmsg = tmpmsgbus->getIMessage(this->id.getId());
		if (tmpmsg.getInstruction() == "POS" || tmpmsg.getInstruction() == "LPOS") {
			tmprmsg.setFrom(this->id);
			tmprmsg.setData(this->pos);
			if (tmpmsg.getInstruction() == "POS") tmprmsg.setInstruction("PR");
			else tmprmsg.setInstruction("LPR");
			tmprmsg.setData(tmpmsg.getData().sdata);
			tmpmsgbus->postIMessage(tmprmsg, tmpmsg.getFrom().getId());
		}
	}
}

bool GameObject::defaultMessageHandler(Message & message) {
	Identifiers tmpf = message.getFrom();
	if (message.getInstruction() == TARGET_REQUEST) {
		message.setData(target);
		message.setFrom(id);
		message.setInstruction(TARGET_RESPONSE);
		Singleton<MessagingBus>::getInstance()->postMessage(message, tmpf);
		return true;
	}
	else
	if (message.getInstruction() == POS_REQUEST) {
		message.setData(pos);
		message.setFrom(id);
		message.setInstruction(POS_RESPONSE);
		Singleton<MessagingBus>::getInstance()->postMessage(message, tmpf);
		return true;
	}
	else
	if (message.getInstruction() == CHNGE_MDL) {
		Model* tmp = Singleton<ModelManger>::getInstance()->useModel(message.getsData(), std::to_string(id.getId()));

		if (tmp != NULL) {
			setModel(tmp);
		}
	}

	return false;
}

bool GameObject::isVisible() {
	return true;
}

void GameObject::setModel(Model* M) {
	if (model != NULL) {
		std::cout << "Here" << std::endl;
		delete model;
	}

	model = M;

	model->centerOnPoint(vec3(0, 0, 0));
}

Model*  GameObject::getModel() {
	return model;
}

vec3 GameObject::getCenterOffset() {
	return vec3(0, 0, 0);
}

bool GameObject::isCollidable() {
	return true;
}

// mm - update movement here?
void GameObject::onCollide(vec3 & prevloc, const Identifiers & colgoid) {
	pos = prevloc;

	stop();
}

bool GameObject::hasGravity() {
	return true;
}

GameObject::GameObject(const GameObject & tocpy) {

	state = tocpy.state;
	pos = tocpy.pos;
	target = tocpy.target;
	targetlook = tocpy.targetlook;
	id = tocpy.id;
	resources = tocpy.resources;

	if (tocpy.model != NULL) {
		model = tocpy.model->create();
		model->setName(std::to_string(id.getId()));
	}
	else {
		model = NULL;
	}
}

std::string GameObject::toString()
{
	// Always save object name first followed by ','[DATANAME],[DATA],...[DATANAME],[DATA]
	std::string towrite;

	towrite += id.getName() + ",";
	towrite += "STATE," + std::to_string(state) + ",";
	towrite += "POS," + std::to_string(pos.x()) + "," + std::to_string(pos.y()) + "," + std::to_string(pos.z()) + ",";
	towrite += "TARGET," + std::to_string(target.x()) + "," + std::to_string(target.y()) + "," + std::to_string(target.z()) + ",";
	towrite += "TARGETLOOK," + std::to_string(targetlook.x()) + "," + std::to_string(targetlook.y()) + "," + std::to_string(targetlook.z()) + ",";

	return towrite;
}

bool GameObject::fromstring(std::string toread) {
	std::string linehead;
	int delimlen = 1;

	while (!toread.empty())
	{
		linehead = toread.substr(0, toread.find(','));
		toread.erase(0, toread.find(',') + delimlen);

		fromstring(linehead, toread);
	}

	return true;
}

bool GameObject::fromstring(std::string linehead, std::string & toread)
{
	float tmpf;
	int delimlen = 1;
	
	if (linehead == "STATE")
	{
		state = atoi(toread.substr(0, toread.find(',')).c_str());
		toread.erase(0, toread.find(',') + delimlen);
	}
	else if (linehead == "POS")
	{
		tmpf = stof(toread.substr(0, toread.find(',')));
		pos.sx(tmpf);
		toread.erase(0, toread.find(',') + delimlen);

		tmpf = stof(toread.substr(0, toread.find(',')));
		pos.sy(tmpf);
		toread.erase(0, toread.find(',') + delimlen);

		tmpf = stof(toread.substr(0, toread.find(',')));
		pos.sz(tmpf);
		toread.erase(0, toread.find(',') + delimlen);
		return true;
	}
	else if (linehead == "TARGET")
	{
		tmpf = stof(toread.substr(0, toread.find(',')));
		target.sx(tmpf);
		toread.erase(0, toread.find(',') + delimlen);

		tmpf = stof(toread.substr(0, toread.find(',')));
		target.sy(tmpf);
		toread.erase(0, toread.find(',') + delimlen);

		tmpf = stof(toread.substr(0, toread.find(',')));
		target.sz(tmpf);
		toread.erase(0, toread.find(',') + delimlen);
		return true;
	}
	else if (linehead == "TARGETLOOK")
	{
		tmpf = stof(toread.substr(0, toread.find(',')));
		targetlook.sx(tmpf);
		toread.erase(0, toread.find(',') + delimlen);

		tmpf = stof(toread.substr(0, toread.find(',')));
		targetlook.sy(tmpf);
		toread.erase(0, toread.find(',') + delimlen);

		tmpf = stof(toread);
		targetlook.sz(tmpf);
		toread.erase(0, toread.find(',') + delimlen);

		return true;
	}

	return false;
}

int GameObject::getNumOBBs() { return 0; };

// mm
physvec3 GameObject::getAngularVel() { return angularvel; }
physvec3 GameObject::getVel() { return vel; }
physmat4 GameObject::getIntert_tensor() { return intert_tensor; }
float GameObject::getTotalMass() { return totalmass; }

void GameObject::setAngularVel(physvec3 angvel) { angularvel = angvel; }
void GameObject::setVel(physvec3 v) { vel = v; }
void GameObject::setIntert_tensor(physmat4 it) { intert_tensor = it; }
void GameObject::setTotalMass(float tm) { totalmass = tm; }