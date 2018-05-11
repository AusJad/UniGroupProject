#include "MenuObject.h"


MenuObject::MenuObject(Identifiers & id, vec3 pos, ResourceList & list) : GameObject(id, pos, list){
	visible = true;
}

void MenuObject::render() {
	if (!visible) return;

	if (resources.hasResource("renderfunc")) {
		RenderModuleStubb* tmp = Singleton<RenderModuleStubb>::getInstance();
		tmp->RenderFacingCamera();
		LSM->callFunction<MenuObject, MessagingBus>(resources.getResource("renderfunc"), *this, *(Singleton<MessagingBus>::getInstance()));
		tmp->StopRenderFacingCamera();
	}

	if (resources.hasResource("model") && model != NULL){
		RenderModuleStubb* tmp = Singleton<RenderModuleStubb>::getInstance();
		tmp->RenderFacingCamera();
		GameObject::model->render(this->pos);
		tmp->StopRenderFacingCamera();
	}
}

void MenuObject::update(float time) {
	if (resources.hasResource("model") && model != NULL) model->update(time);
	msgrcvr();

	if(resources.hasResource("updatefunc"))
		LSM->callFunction<MenuObject, MessagingBus>(resources.getResource("updatefunc"), *this, *(Singleton<MessagingBus>::getInstance()));

	MessagingBus* tmp = Singleton<MessagingBus>::getInstance();
	Message tmpm;

	while (tmp->hasMessage(id)) {

		tmpm = tmp->getMessage(id);

		if (tmpm.getInstruction() == DISPLAY) {
			this->visible = true;
		}
		else
		if (tmpm.getInstruction() == HIDE) {
			this->visible = false;
		}
		else
		if (tmpm.getInstruction() == TOGGLE) {
			this->visible = !this->visible;
		}
	}
}

vec3 MenuObject::getCenterOffset() {
	if (resources.hasResource("model") && model != NULL) {
		return vec3(0, abs(model->getMaxY()), 0);
	}

	return vec3(0, 0, 0);
}

bool MenuObject::isCollidable(){
	return false;
}

void MenuObject::setModel(Model* M) {
	model = M;
}

std::string MenuObject::toString()
{
	std::string towrite;

	towrite += GameObject::id.getName() + ",";
	towrite += "POS," + std::to_string(GameObject::pos.x()) + "," + std::to_string(GameObject::pos.y()) + "," + std::to_string(GameObject::pos.z()) + ",";
	if (visible)
		towrite += "VISIBLE,1";
	else
		towrite += "VISIBLE,0";

	return towrite;
}

bool MenuObject::fromstring(std::string toread)
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
		else if (linehead == "VISIBLE")
		{
			tmpf = stof(toread.substr(0, toread.find(',')));
			if (tmpf == 1)
				visible = true;
			else
				visible = false;
			toread.erase();
		}
	}
}