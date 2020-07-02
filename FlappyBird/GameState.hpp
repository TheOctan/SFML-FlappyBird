#pragma once

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>

#include"State.hpp"
#include"Game.hpp"
#include"Collision.hpp"
#include"Pipe.hpp"
#include"Land.hpp"
#include"Bird.hpp"
#include"Flash.hpp"
#include"HUD.hpp"

namespace Engine
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);
		~GameState();

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef	_data;

		sf::Sprite	_background;
		Pipe*		pipe;
		Land*		land;
		Bird*		bird;
		Flash*		flash;
		HUD*		hud;

		Collision	collision;
		GameStates	_gameState;
		sf::Clock	_clock;
		
		int			_score;

		sf::SoundBuffer _hitSoundBuffer;
		sf::SoundBuffer _wingSoundBuffer;
		sf::SoundBuffer _pointSoundBuffer;

		sf::Sound _hitSound;
		sf::Sound _wingSound;
		sf::Sound _pointSound;
	};

} // namespace Engine

#endif // !GAME_STATE_HPP


