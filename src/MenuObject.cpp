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

MenuObject::MenuObject(const MenuObject & tocpy) : GameObject(tocpy) {
	visible = tocpy.visible;
}

GameObject* MenuObject::create() {
	return new MenuObject(*this);    
}
