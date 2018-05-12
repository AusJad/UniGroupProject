#include "Bullet.h"

Bullet::Bullet(Identifiers & id, vec3 pos, ResourceList & list) {
	lifespan = 5.0f;
	timealive = 0.0f;
	inUse = true;
	speed = 500;
}

Bullet::Bullet() {
	lifespan = 5.0f;
	timealive = 0.0f;
	inUse = true;
	speed = 1000;
}

void Bullet::update(float time) {
	if (!inUse) return;
	msgrcvr();

	timealive += time;

	if (timealive >= lifespan) inUse = false;

	pos += target * speed * time;

}

void Bullet::setTarget(const vec3 target) {
	this->target = target;
	inUse = true;
	timealive = 0;
	this->pos += this->target * 10;
}

void Bullet::render() {
	if (!inUse) return;

	if (model != NULL) {
		GameObject::model->render(this->pos);
	}
	else {
		RNDR->DrawQuad(point(pos.x(), pos.y() + 1), point(pos.x() + 1, pos.y()), pos.z());
	}
}

bool Bullet::isVisible() {
	return inUse;
}

void Bullet::onCollide(vec3 & prevloc, const Identifiers & colgoid) {
	if (colgoid.getType() != "CAM") {
		Message tmpm;

		tmpm.setInstruction(DAMAGE);
		tmpm.setIData(15000);

		MSGBS->postMessage(tmpm, colgoid);

		this->inUse = false;
	}
}

bool Bullet::hasGravity() {
	return false;
}

Bullet::Bullet(const Bullet & tocpy) : GameObject(tocpy) {
	inUse = tocpy.inUse;
	lifespan = tocpy.lifespan;
	timealive = tocpy.timealive;
	speed = tocpy.speed;
}

GameObject* Bullet::create() {
	return new Bullet(*this);
}

