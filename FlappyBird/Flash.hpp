#pragma once

#ifndef GAME_FLASH_HPP
#define GAME_FLASH_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include<SFML\Graphics.hpp>
#include"Game.hpp"

namespace Engine
{
	class Flash : public sf::Drawable
	{
	public:
		Flash(GameDataRef data);
		~Flash();

		void Show(float dt);

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		GameDataRef			_data;

		sf::RectangleShape	_shape;

		bool				_flashOn;
	};

} // namespace Engine

#endif // !GAME_FLASH_HPP


