#pragma once
#include "../ECS/Components.h"

class Collision
{
public:


	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const TileCollider& colA, const TileCollider& colB);


};
