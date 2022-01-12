#pragma once


#include "SDL.h"
#include "../Src/TextureManager.h"
#include "Components.h"
//#include "ECS.h"
#include "TransformComponent.h"
//#include "ColliderComponent.h"
#include "Projectile.h"
#include "Animation.h"
#include <map> 
#include"../Src/Game.h"
#include "../Src/AssetManager.h"
#include <string>

class CharacterCollider;

extern Manager manager;



class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	std::string mId;





	int frames = 0;
	bool animated = false;



public:
	SDL_Rect sRec, dRec;
	int speed = 0;
	Uint32 aSpeed = 75;
	Uint32 bSpeed = 125;

	Uint32 timeA = 0;
	int animIndex = 0;
	const char* lastAction = "Idle";
	const char* attackType = "Attack";
	const char* animationType = "Hurt";
	std::map<const char*, Animation> animations;
	SDL_RendererFlip flip = SDL_FLIP_NONE;



	SpriteComponent() = default;

	SpriteComponent(std::string id)
	{
		setTex(id);

	}

	SpriteComponent(std::string id, bool isAnimated)
	{


		animated = isAnimated;
		Animation idle = Animation(0, 4, 125);
		Animation walk = Animation(1, 6, 100);
		Animation attack = Animation(2, 6, 25);
		Animation jump = Animation(3, 7, 50);
		Animation fall = Animation(4, 2, 50);
		Animation attack2 = Animation(5, 7, 50);
		Animation hurt = Animation(6, 4, 150);
		Animation die = Animation(7, 6, 150);

		//create new animation here: jump
		//create fall animation

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		animations.emplace("Attack", attack);
		animations.emplace("Jump", jump);
		animations.emplace("Fall", fall);
		animations.emplace("Attack2", attack2);
		animations.emplace("Hurt", hurt);
		animations.emplace("Die", die);
		//emplace jump animation
		//emplace fall animation


		Play("Idle");
		setTex(id);
		mId = id;


	}

	~SpriteComponent()
	{
		//SDL_DestroyTexture(texture);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sRec.x = sRec.y = 0;
		sRec.w = transform->w;
		sRec.h = transform->h;
	}

	void draw() override
	{
		TextureManager::Draw(texture, sRec, dRec, flip);


	}

	void  setTex(std::string mID)
	{

		texture = Game::assets->GetTexture(mID);

	}

	void Play(const char* animName)
	{

		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;


	}



	void AnimateAttack()
	{
		aSpeed = 75;
		Uint32 delta = (SDL_GetTicks() / aSpeed) - timeA;
		//std::cout << "timeA is " << timeA << std::endl;
		//std::cout << "current is " << (SDL_GetTicks() / speed) << std::endl;

		//std::cout <<"delta is "<< delta << std::endl;

		if (delta >= frames - 1)
		{
			transform->isAttacking = false;
			Play(lastAction);


		}

		else
		{
			sRec.x = sRec.w*delta;
			Play(attackType);
		}

	}


	void VideoAnimate(const char* animation)
	{



		Uint32 delta = (SDL_GetTicks() / aSpeed) - timeA;
		//std::cout << "timeA is " << timeA << std::endl;
		//std::cout << "current is " << (SDL_GetTicks() / speed) << std::endl;

		//std::cout <<"delta is "<< delta << std::endl;

		if (delta >= frames - 1)
		{


			if (!transform->isAlive)
			{
				std::cout << "the entity " << mId << "destroyed" << std::endl;
				entity->delGroup(Game::groupEnemies);
				entity->destroy();
				//entity->isActive = true;
				return;

			}
			transform->isbeingAnimated = false;
			Play(lastAction);


		}

		else
		{
			sRec.x = sRec.w*delta;
			Play(animationType);
		}

	}

	void Animate(const char* animation, Uint32 mSpeed)
	{
		animationType = animation;
		if (transform->isbeingAnimated == false)
		{
			transform->isbeingAnimated = true;
			aSpeed = mSpeed;
			timeA = SDL_GetTicks() / aSpeed;
			//transform->velocity.x = 0;

		}
	}

	void update() override
	{

		if (transform->isJumping)
		{
			Play("Jump");
		}

		else if (transform->isFalling)
		{
			Play("Fall");
		}

		else if (!transform->isAttacking && !transform->isbeingAnimated)
		{
			//std::cout << "last action is" << lastAction;
			Play(lastAction);
		}


		if (animated)
		{


			if (transform->isbeingAnimated)
			{
				transform->isJumping = false;
				//transform->isAttacking = false;

				VideoAnimate(animationType);
				//transform->velocity.x = 0;
			}

			else if (transform->isAttacking)
			{
				transform->isJumping = false;
				AnimateAttack();
				//transform->velocity.x = 0;
			}



			else
			{
				sRec.x = sRec.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

			}




		}



		sRec.y = transform->h * animIndex;

		dRec.x = static_cast<int>(transform->position.x) - Game::camera.x;

		dRec.y = static_cast<int>(transform->position.y) - Game::camera.y;
		dRec.w = transform->w * transform->sc;
		dRec.h = transform->h * transform->sc;







	}

	void ShootProjectile()
	{

		auto& arrow(manager.addEntity());
		std::cout << arrow.isActive() << std::endl;
		Vector2D vel{ 1,0 };
		int xOfsset = 105;
		int yOffset = 90;
		if (flip == SDL_FLIP_NONE)
		{
			vel.x = 2;

		}

		else
		{
			xOfsset = 25;
			vel.x = -2;
			//xOfsset *= -1;
		}


		Vector2D playerPos = transform->position;
		arrow.addComponent<TransformComponent>(playerPos.x + xOfsset, playerPos.y + yOffset, 16, 8, 3);
		//arrow.addComponent<TransformComponent>(100,100, 16, 8, 2);
		arrow.addComponent<SpriteComponent>("arrow", false);
		arrow.addComponent<ProjectileComponent>(100, 1, vel);
		arrow.getComponent<SpriteComponent>().flip = flip;
		arrow.addComponent<CharacterCollider>("arrow", playerPos.x + xOfsset, playerPos.y + yOffset, 3 * 16, 3 * 8);
		arrow.addGroup(Game::groupProjectiles);




	}


};