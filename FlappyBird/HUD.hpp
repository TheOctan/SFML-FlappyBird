#pragma once

#ifndef GAME_HUD_HPP
#define GAME_HUD_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include<SFML\Graphics.hpp>
#include"Game.hpp"

namespace Engine
{
	class HUD : public sf::Drawable
	{
	public:
		HUD(GameDataRef data);
		~HUD();

		void UpdateScore(int score);

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		GameDataRef _data;

		sf::Text	_scoreText;
	};

} // namespace Engine

#endif // !GAME_HUD_HPP


