#pragma once

#include "ECS.h"





#include "../Src/Vector2D.h"
#include "../Src/Game.h"




class TransformComponent : public Component
{
public:

	
	Vector2D position;
	Vector2D velocity;
	const int gravity = -2;
	float jumpStrength = 40;
	float lateralJumpStrength = 20;
	bool isJumping = false;
	bool isAttacking = false;
	bool isFalling = false;
	bool isColliding = false;
	bool isbeingAnimated = false;
	bool isBlocking = false;
	bool isAlive = true;
	int minSpeed = -jumpStrength;

	float centeredXPos = 0;
	int maxHealth = 100;
	int currentHealth = 10;

	int speed = 12;
	int w = 32;
	int h = 32;
	int sc = 1;

	TransformComponent();


	TransformComponent(int scale);


	TransformComponent(int x, int y, int width, int height, int scale);
	TransformComponent(int x, int y, int width, int height, int scale, int Mspeed);

	void init() override;
	void update() override;
	void setPos(int x, int y);
	void collide();
	void Fall();
	void receivePunch();


};


