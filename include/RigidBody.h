#pragma once
#include "Geometry3D.h"
#include <vector>

#define GRAVITY physvec3(0.0f, -9.8f, 0.0f)

class RigidBody
{
public:
	RigidBody();
	~RigidBody();

	void applyForces();
	void addLinearImpulse(const physvec3 & impulse);
	void addRotationalImpulse(const physvec3 & point, const physvec3 & impulse);
	float getInvMass();
	
	void update(float time);

	static void resolveCollision(RigidBody * rb1, RigidBody * rb2, const CollisionManifold & cm);

	// Gets + Sets
	void setVelo(const physvec3 & velo);
	void setForceAccum(const physvec3 & fa);
	void setCOR(float cor);
	void setCenter(const physvec3 & c);
	void setAngularVelo(physvec3 & angularvelo);
	void setOrientation(const physvec3 & orien);
	void setTorques(const physvec3 & torq);
	void setInertTensor(const physmat4 & it);
	void setprevvel(const physvec3 & pv);
	void setprevangularvel(const physvec3 & pv);
	void setCOM(const physvec3 & com);
	void setTM(float tm);

	physvec3 getVelo();
	physvec3 getForceAccum();
	float getCOR();
	physvec3 getCenter();
	physvec3 getAngularVelo();
	physvec3 getOrientation();
	physvec3 getTorques();
	physmat4 getIntertTensor();
	physvec3 getprevvel();
	physvec3 getprevangularvel();
	physvec3 getCOM();
	float getTM();

private:
	static void linearImpulse(RigidBody * rb1, RigidBody * rb2, const CollisionManifold & cm);
	static void angularImpulse(RigidBody * rb1, RigidBody * rb2, const CollisionManifold & cm);

	physvec3 vel, prevvel, forceaccum; // Velocity and force accumulator
	float COR; // Coefficient of Restitution
	physvec3 center; // Center of box/object
	physvec3 CoM;
	physvec3 angularvel, prevangularvel;
	physvec3 orientation;
	physvec3 torques;
	physmat4 intert_tensor;
	float totalMass;
};