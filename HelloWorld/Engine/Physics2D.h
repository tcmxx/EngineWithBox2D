#pragma once

#include "Box2D\Box2D.h"
#include "Collider2D.h"
#include <vector>

//for now the settings are defined here
struct Physics2DSetting {
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	float32 timestep = 1.0f / 60;
};

struct CollisionInfo2D {
	b2Manifold manifold;
	Collider2D* other;
};

class Physics2D : public b2ContactListener,public b2QueryCallback {
public:
	Physics2D();
	void Step();
	b2World * GetWorld2D();
	void SetGravity(b2Vec2 gravity);
	
	///for now just return the overlayed colliders without other information
	std::vector<Collider2D*> SphereOverlay(b2Vec2 position, float32 radiu);

private:
	friend class Scene;

	// Define the gravity vector.
	const b2Vec2 DEFAULT_GRAVITY = b2Vec2(0.0f, -10.0f);

	Physics2DSetting physics2DSetting;
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	bool ReportFixture(b2Fixture* fixture) override;

	std::vector<b2Fixture*> tempFixturesHolder;

	// physics a world object, which will hold and simulate the rigid bodies.
	b2World world2D;
	
};

inline b2World* Physics2D::GetWorld2D() {
	return &world2D;
}
inline void Physics2D::SetGravity(b2Vec2 gravity) {
	world2D.SetGravity(gravity);
}