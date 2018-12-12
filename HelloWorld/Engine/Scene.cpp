#include "Scene.h"

Scene::Scene(float tickRate):gameTime(tickRate), world2D(DEFAULT_GRAVITY)
{
}


Scene::~Scene()
{
	GameObject* currentObj = gameObjectFirst;
	while (currentObj != nullptr) {
		GameObject* tempPtr = currentObj;
		currentObj = currentObj->next;
		delete tempPtr;
	}
}



void Scene::DestroyGameObjectImmediately(GameObject* gameObject) {
	if (gameObject->next == nullptr && gameObject->prev == nullptr) {
		gameObjectLast = nullptr;
		gameObjectFirst = nullptr;
		delete gameObject;
	}
	else if (gameObject->next == nullptr) {
		gameObjectLast = gameObject->prev;
		gameObjectLast->next = nullptr;
	}
	else if (gameObject->prev != nullptr) {
		gameObjectFirst = gameObject->next;
		gameObjectFirst->prev = nullptr;
	}
	else {
		gameObject->prev->next = gameObject->next;
		gameObject->next->prev = gameObject->prev;
	}
}


void Scene::FixedUpdate() {
	GameObject* currentObj = gameObjectFirst;
	float32 interval = gameTime.GetTickInterval();

	//step the physics2D world
	world2D.Step(interval, physics2DSetting.velocityIterations, physics2DSetting.positionIterations);

	//step the game objects
	while (currentObj != nullptr) {
		currentObj->InnerFixedUpdate(interval);
		currentObj = currentObj->next;
	}
}

b2World* Scene::GetWorld2D() {
	return &world2D;
}
void Scene::SetGravity(b2Vec2 gravity) {
	world2D.SetGravity(gravity);
}