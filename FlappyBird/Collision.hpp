#pragma once

#ifndef GAME_COLLISION_HPP
#define GAME_COLLISION_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include<SFML\Graphics.hpp>

namespace Engine
{
	class Collision
	{
	public:
		Collision();
		~Collision();

		bool  CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2);
		bool  CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2, sf::Vector2f scale);

	};

} // namespace Engine

#endif // !GAME_COLLISION_HPP




