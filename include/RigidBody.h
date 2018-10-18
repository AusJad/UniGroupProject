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
	void addRotationalImpulse(physvec3 point, physvec3 impulse);
	float getInvMass();
	
	void update(float time);

	void calcCOM();

	static void resolveCollision(RigidBody * rb1, RigidBody * rb2, CollisionManifold cm);

	// Gets + Sets
	void setVelo(const physvec3 & velo);
	void setForceAccum(const physvec3 & fa);
	void setMass(float m);
	void setCOR(float cor);
	void setCenter(const physvec3 & c);
	void setCOM(const physvec3 & com);
	void setAngularVelo(physvec3 & angularvelo);
	void setOrientation(const physvec3 & orien);
	void setTorques(const physvec3 & torq);
	void setInertTensor(const physmat4 & it);
	void setprevvel(const physvec3 & pv);
	void setprevangularvel(const physvec3 & pv);

	physvec3 getVelo();
	physvec3 getForceAccum();
	float getMass();
	float getCOR();
	physvec3 getCenter();
	physvec3 getCOM();
	physvec3 getAngularVelo();
	physvec3 getOrientation();
	physvec3 getTorques();
	physmat4 getIntertTensor();
	physvec3 getprevvel();
	physvec3 getprevangularvel();

private:
	static void linearImpulse(RigidBody * rb1, RigidBody * rb2, CollisionManifold cm);
	static void angularImpulse(RigidBody * rb1, RigidBody * rb2, CollisionManifold cm);

	physvec3 vel, prevvel, forceaccum; // Velocity and force accumulator
	float mass; // Mass of object
	float COR; // Coefficient of Restitution
	physvec3 center; // Center of box/object
	physvec3 COM; // Center of mass
	physvec3 angularvel, prevangularvel;
	physvec3 orientation;
	physvec3 torques;
	physmat4 intert_tensor;
};

