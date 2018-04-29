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
		Model* tmp = Singleton<ModelManger>::getInstance()->useModel(message.getsData(), id.getName());

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
	if (model != NULL) delete model;
	
	model = M;

	//model->centerOnPoint(vec3(pos.x(), 0, pos.z()));
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

void GameObject::onCollide(vec3 & prevloc, const Identifiers & colgoid) {
	pos = prevloc;

	stop();
}

bool GameObject::hasGravity() {
	return true;
}