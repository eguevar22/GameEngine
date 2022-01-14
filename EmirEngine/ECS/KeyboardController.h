#pragma once
#include "Components.h"
#include "ECS.h"
#include "../Src/Game.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();

	}



	void moveHorizontal(int unitDirection)

	{

		transform->velocity.x = unitDirection;
		sprite->Play("Walk");
		sprite->lastAction = "Walk";

	}

	void moveVertical(int unitDirection)

	{

		transform->velocity.y = -unitDirection;
		sprite->Play("Walk");
		sprite->lastAction = "Walk";

	}

	void stayIdle(int x, int y)

	{

		transform->velocity.x *= x;
		transform->velocity.y *= y;

		if (!transform->isbeingAnimated)
		{
			sprite->Play("Idle");
			sprite->lastAction = "Idle";
		}

	}

	void Fall()
	{
		sprite->Play("Fall");
		sprite->lastAction = "Fall";
	}

	void Attack()
	{
		if (transform->isAttacking == false)
		{
			transform->isAttacking = true;
			sprite->aSpeed = 75;
			sprite->timeA = SDL_GetTicks() / sprite->aSpeed;
			//transform->velocity.x = 0;
			stayIdle(0, 1);
		}

	}


	void update() override
	{

		if (Game::event.type == SDL_KEYUP)
		{

			switch (Game::event.key.keysym.sym)
			{

			case SDLK_a:

				stayIdle(0, 1);

				break;
			case SDLK_d:

				stayIdle(0, 1);

				break;






			case SDLK_ESCAPE:
				//Game::isRunning = false;
				transform->position.y = 1;
				
				break;

			case SDLK_UP:
				//sprite->Play("Idle");
				break;

			case SDLK_SPACE:
				transform->isShooting = false;
			}
		}


		if (Game::event.type == SDL_KEYDOWN)
		{


			switch (Game::event.key.keysym.sym)
			{
			case SDLK_a:

				sprite->flip = SDL_FLIP_HORIZONTAL;
				moveHorizontal(-1);

				break;
			case SDLK_d:

				sprite->flip = SDL_FLIP_NONE;
				moveHorizontal(1);

				break;




			case SDLK_UP:
				transform->isJumping = true;
				sprite->Play("Jump");


				break;
			case SDLK_SPACE:

				if (!transform->isShooting)
				{
					sprite->Animate("Attack2", 75);

					sprite->ShootProjectile();
					transform->isShooting = true;
				}


				break;


			}




		}


	}

};