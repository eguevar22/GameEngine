#include "TransformComponent.h"
#include "Components.h"

TransformComponent::TransformComponent()
{
	position.Zero();
}

TransformComponent::TransformComponent(int scale)
{
	setPos(400, 320);

	sc = scale;

}

TransformComponent::TransformComponent(int x, int y, int width, int height, int scale)
{
	setPos(x, y);
	h = height;;
	w = width;
	sc = scale;
}

TransformComponent::TransformComponent(int x, int y, int width, int height, int scale, int Mspeed)
{
	setPos(x, y);
	h = height;;
	w = width;
	sc = scale;
	speed = Mspeed;
}

void TransformComponent::init()
{

	velocity.Zero();


}

void TransformComponent::update()
{

	if (isJumping || isFalling)
	{
		position.y -= jumpStrength;
		jumpStrength += gravity;
	}

	if (jumpStrength <= -5)

	{
		isFalling = true;
		isJumping = false;

	}

	if (jumpStrength < minSpeed)
	{
		jumpStrength = minSpeed;
		//isFalling = false;
	}

	position.x += velocity.x * static_cast<float>(speed);
	position.y += velocity.y * static_cast<float>(speed);
	centeredXPos = position.x + ((w * sc) / 2);
	//std::cout << position.x << " + " << w << " + " << " sc " << "==" << centeredXPos << std::endl;

}

void TransformComponent::setPos(int x, int y)
{
	position.x = static_cast<float>(x);
	position.y = static_cast<float>(y);
}


void TransformComponent::collide()
{
	//isJumping = false;
	isFalling = false;
	isColliding = true;
	jumpStrength = -minSpeed;


}
void TransformComponent::Fall()
{
	isColliding = false;
	if (!isFalling && !isJumping)
	{

		jumpStrength = -5;
	}

	
}
