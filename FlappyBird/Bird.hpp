#pragma once

#ifndef GAME_BIRD_HPP
#define GAME_BIRD_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include<SFML\Graphics.hpp>
#include"Game.hpp"

namespace Engine
{
	class Bird : public sf::Drawable
	{
	public:
		Bird(GameDataRef data);
		~Bird();

		void Animate(float dt);
		void Update(float dt);
		void Tap();
		const sf::Sprite& GetSprite() const;

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		GameDataRef		_data;

		sf::Sprite		_birdSprite;
		TextureHolder	_anumationFrames;
		sf::Uint32		_animtionIterator;

		sf::Clock		_clock;
		//sf::Clock		_movementClock;

		BirdState		_state;

		float			_rotation;
		float			_dy;
	};

} // namespace Engine

#endif // !GAME_BIRD_HPP

