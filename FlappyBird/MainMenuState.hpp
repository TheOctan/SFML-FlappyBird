#pragma once

#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include<SFML\Graphics.hpp>
#include"State.hpp"
#include"Game.hpp"

namespace Engine
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);
		~MainMenuState() override;

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _title;
		sf::Sprite _playButton;
		sf::Sprite _cursor;
	};

} // namespace Engine

#endif // !MAIN_MENU_STATE_HPP


