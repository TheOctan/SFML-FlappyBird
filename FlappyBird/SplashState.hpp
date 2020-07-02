#pragma once

#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include<SFML\Graphics.hpp>
#include"State.hpp"
#include"Game.hpp"

namespace Engine
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);
		~SplashState() override;

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef _data;

		sf::Clock _clock;
		sf::Sprite _background;
	};

} // namespace Engine

#endif // !SPLASH_STATE_HPP


