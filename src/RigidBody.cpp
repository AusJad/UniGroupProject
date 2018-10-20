#include "RigidBody.h"

RigidBody::RigidBody()
{
	vel = physvec3();
	prevvel = physvec3();
	forceaccum = physvec3();
	COR = 1.0f;
	center = physvec3();
	CoM = physvec3();
	angularvel = physvec3();
	prevangularvel = physvec3();
	orientation = physvec3();
	torques = physvec3();
	intert_tensor = physmat4();
	totalMass = 1;
}

RigidBody::~RigidBody()
{

}

void RigidBody::applyForces() {
	forceaccum = GRAVITY * totalMass;
}

void RigidBody::addLinearImpulse(const physvec3 & impulse) {
	vel = vel + impulse;
}

void RigidBody::addRotationalImpulse(const physvec3 & point, const physvec3 & impulse) {
	physvec3 torque = Cross(point - center, impulse); // mm - changed obb.position to center due to vector change
	physvec3 angularacel = MultiplyVector(torque, Inverse(intert_tensor));
	angularvel += angularacel;
}

float RigidBody::getInvMass() {
	if (totalMass == 0.0f) return 0;
	return 1.0f / totalMass;
}

void RigidBody::update(float time) {
	const float dampening = 1.0f;
	physvec3 acceleration = forceaccum * getInvMass();
	vel += acceleration * time;
	vel *= dampening;
}

void RigidBody::resolveCollision(RigidBody * rb1, RigidBody * rb2, const CollisionManifold & cm)
{
	linearImpulse(rb1, rb2, cm);
	angularImpulse(rb1, rb2, cm);
}

void RigidBody::linearImpulse(RigidBody * rb1, RigidBody * rb2, const CollisionManifold & cm)
{
	float total_inv_mass = rb1->getInvMass() + rb2->getInvMass();

	if (total_inv_mass == 0)
	{
		return;
	}

	physvec3 relativeVelo = rb2->vel - rb1->vel;
	physvec3 relativeNormal = cm.normal;
	Normalize(relativeNormal);

	if (Dot(relativeVelo, relativeNormal) > 0) // Objects are already moving away from each other
	{
		return;
	}

	float minCOR = fminf(rb1->COR, rb2->COR);

	float magnitude = 1 / total_inv_mass;

	if (cm.contacts.size() > 0.0f && magnitude != 0.0f) // If there is a collision and it has a magnitude
		magnitude /= (float)cm.contacts.size();

	physvec3 impulse = relativeNormal * magnitude;

	rb1->prevvel = rb1->vel;
	rb2->prevvel = rb2->vel;

	rb1->vel -= impulse * rb1->getInvMass();
	rb2->vel += impulse * rb2->getInvMass();
}

void RigidBody::angularImpulse(RigidBody * rb1, RigidBody * rb2, const CollisionManifold & cm)
{
	float total_inv_mass = rb1->getInvMass() + rb2->getInvMass();

	if (total_inv_mass == 0)
	{
		return;
	}

	physvec3 PoC1 = cm.contacts[0] - rb1->getCOM(); // Point of contact relative to the center of mass
	physvec3 PoC2 = cm.contacts[0] - rb2->getCOM();

	physmat4 IIT1 = Inverse(rb1->intert_tensor); // Inverse Inertia Tensor
	physmat4 IIT2 = Inverse(rb2->intert_tensor);

	physvec3 relativeVelo = (rb2->vel + Cross(rb2->angularvel, PoC2)) - (rb1->vel + Cross(rb1->angularvel, PoC1));
	physvec3 relativeNormal = cm.normal;
	Normalize(relativeNormal);

	if (Dot(relativeVelo, relativeNormal) > 0.0f)
	{
		return;
	}

	float minCOR = fminf(rb1->getCOR(), rb2->getCOR());

	physvec3 tmp1 = Cross(PoC1, relativeNormal);
	physvec3 tmp2 = MultiplyVector(tmp2, IIT2);
	physvec3 tmp3 = Cross(tmp2, PoC1);

	physvec3 d1 = Cross(MultiplyVector(Cross(PoC1, relativeNormal), IIT2), PoC1);
	physvec3 d2 = Cross(MultiplyVector(Cross(PoC2, relativeNormal), IIT1), PoC2);

	float denominator = total_inv_mass + Dot(relativeNormal, d1 + d2);

	float magnitude = 1.0f;

	float numerator = (-(1.0f + minCOR) * Dot(relativeVelo, relativeNormal));

	if (cm.contacts.size() > 0 && denominator != 0)
	{
		magnitude = (numerator / denominator) / (float)cm.contacts.size();
	}
	else
	{
		return; // Nothing happens.
	}

	physvec3 impulse = relativeNormal * magnitude;

	rb1->prevangularvel = rb1->angularvel;
	rb2->prevangularvel = rb2->angularvel;

	rb1->angularvel -= MultiplyVector(Cross(PoC1, impulse), IIT1);
	rb2->angularvel += MultiplyVector(Cross(PoC2, impulse), IIT2);
}

void RigidBody::setVelo(const physvec3 & velo) { vel = velo; }

void RigidBody::setForceAccum(const physvec3 & fa) { forceaccum = fa; }

void RigidBody::setCOR(float cor) { COR = cor; }

void RigidBody::setCenter(const physvec3 & c) { center = c; }

void RigidBody::setCOM(const physvec3 & com) { CoM = com; }

void RigidBody::setAngularVelo(physvec3 & angularvelo) { angularvelo = angularvelo; }

void RigidBody::setOrientation(const physvec3 & orien) { orientation = orien; }

void RigidBody::setTorques(const physvec3 & torq) { torques = torq; }

void RigidBody::setInertTensor(const physmat4 & it) { intert_tensor = it; }

void RigidBody::setTM(float tm) { totalMass = tm; }

physvec3 RigidBody::getVelo() { return vel; }

physvec3 RigidBody::getForceAccum() { return forceaccum; }

float RigidBody::getCOR() { return COR; }

physvec3 RigidBody::getCenter() { return center; }

physvec3 RigidBody::getCOM() { return CoM; }

physvec3 RigidBody::getAngularVelo() { return angularvel; }

physvec3 RigidBody::getOrientation() { return orientation; }

physvec3 RigidBody::getTorques() { return torques; }

physmat4 RigidBody::getIntertTensor() { return intert_tensor; }

float RigidBody::getTM() { return totalMass; }

void RigidBody::setprevvel(const physvec3 & pv)
{
	prevvel = pv;
}

void RigidBody::setprevangularvel(const physvec3 & pv)
{
	prevangularvel = pv;
}

physvec3 RigidBody::getprevvel()
{
	return prevvel;
}

physvec3 RigidBody::getprevangularvel()
{
	return prevangularvel;
}