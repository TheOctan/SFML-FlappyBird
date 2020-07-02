#pragma once

#ifndef GAME_LAND_HPP
#define GAME_LAND_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include<SFML\Graphics.hpp>
#include"Game.hpp"


namespace Engine
{
	class Land : public sf::Drawable
	{
	public:
		Land(GameDataRef data);
		~Land();

		void MoveLand(float dt);

		const SpriteHolder& GetSprites() const;

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		GameDataRef		_data;
		SpriteHolder	_landSprites;

	};

} // namespace Engine

#endif // !GAME_LAND_HPP


