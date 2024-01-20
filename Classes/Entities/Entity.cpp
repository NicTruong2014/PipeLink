#include "Entity.h"

Entity* Entity::createEntity()
{
	return Entity::create();
}

bool Entity::init()
{
	if (!Node::init()) 
	{
		return false;
	}

	return true;
}

int Entity::UpdateScore(TypePipe cardType, int score)
{
	return score;
}