#include "ECS.h"

void Entity::addGroup(Group mGroup)
{
	manager.AddToGroup(this, mGroup);
	groupBitSet[mGroup] = true;
}
