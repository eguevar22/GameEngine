#pragma once
#include "ECS.h"
#include "../Src/Vector2D.h"
#include "TransformComponent.h"

class SpriteComponent;


class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int sp, Vector2D vel);

	~ProjectileComponent();


	void init() override;




	void update() override;

	void checkCollision(Entity * enemy);




private:

	TransformComponent* transform;
	SpriteComponent* sprite;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;


};