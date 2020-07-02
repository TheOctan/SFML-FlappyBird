#include "Collision.hpp"

namespace Engine
{
	Collision::Collision()
	{

	}

	Collision::~Collision()
	{

	}

	bool Collision::CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2)
	{
		sf::FloatRect rect1 = sprite1.getGlobalBounds();
		sf::FloatRect rect2 = sprite2.getGlobalBounds();

		if (rect1.intersects(rect2))
		{
			return true;
		}
		return false;
	}

	bool Collision::CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2, sf::Vector2f scale)
	{
		sprite1.setScale(scale.x, scale.x);
		sprite2.setScale(scale.y, scale.y);

		sf::FloatRect rect1 = sprite1.getGlobalBounds();
		sf::FloatRect rect2 = sprite2.getGlobalBounds();

		if (rect1.intersects(rect2))
		{
			return true;
		}
		return false;
	}
}


