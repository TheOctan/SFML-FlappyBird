#pragma once

#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include<SFML\Graphics.hpp>
#include"State.hpp"
#include"Game.hpp"

namespace Engine
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, int score);
		~GameOverState();

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef	_data;

		sf::Sprite	_background;

		sf::Sprite	_gameOverTitle;
		sf::Sprite	_gameOverContainer;
		sf::Sprite	_retryButton;
		sf::Sprite	_medal;
		sf::Sprite _cursor;

		sf::Text	_scoreText;
		sf::Text	_highScoreText;

		int			_score;
		int			_highScore;
	};

} // namespace Engine

#endif // !GAME_OVER_STATE_HPP


