
#include "DebugDraw.h"
#include "Box2D/Box2D.h"
#include "Engine\Engine.h"
#include <stdio.h>


#include "Game\TargetBall.h"
#include "Game\GameController.h"


int main(int argc, char** argv)
{
	Engine::Initialize();

	Scene* scene = Engine::GetScene();

	//create the ground object
	GameObject* groundObject = scene->InstantiateGameObject<GameObject>("Floor");
	auto boxcollider = groundObject->AddComponent<BoxCollider2D>();
	boxcollider->SetBox(b2Vec2(10, 1), b2Vec2_zero, 0);
	auto groundBody = groundObject->AddComponent<Rigidbody2D>();
	groundBody->SetType(b2_staticBody);

	scene->InstantiateGameObject<TargetBall>(b2Vec2(0, 20),0);

	scene->InstantiateGameObject<GameController>();

	Engine::Run();

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.

	return 0;
}
