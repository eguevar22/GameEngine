#pragma once
#include "Components.h"
#include "../Src/Vector2D.h"

class AutoController : public Component
{
private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	//CharacterCollider* collider;
	int movementDist;
	int originPos = 0;
	Entity* target;
	SDL_Rect collider;




public:

	AutoController() = default;
	AutoController(int mdst, Entity* mTarget);

	void init() override;
	void Attack();
	void stayIdle(int x, int y);
	void update() override;
	void PatrollingMode();
	void AttackingMode();
	bool NearTarget();
	int colliderX;





};
