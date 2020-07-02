#include"Game.hpp"
#include"MainMenuState.hpp"

#include<cstdlib>
#include<ctime>

//#include"DEFINITIONS.hpp"

namespace Engine
{
	Game::Game(int width, int height, std::string title)
		: dt(1.0f / 120.0f)
	{
		srand(unsigned(time(NULL)));

		_data = std::make_shared<GameData>();

		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		_data->window.setPosition(sf::Vector2i(_data->window.getPosition().x, 0));
		//_data->window.setFramerateLimit(60);

		sf::Image icon;
		icon.loadFromFile("Resources/images/FlappyBird.png");
		_data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		_data->machine.AddState(StateRef(new MainMenuState(this->_data)));

		_data->window.setMouseCursorVisible(false);
		_data->window.setKeyRepeatEnabled(false);

		this->Run();
	}

	void Game::Run()
	{
		float newTime, frameTime, interpolation;
		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->_data->window.isOpen())
		{
			//==========================================================//

			this->_data->machine.ProcessStateChange();		// change of game state

			newTime = this->_clock.getElapsedTime().asSeconds();

			//end of cycle
			//////////////////////////////////////////////////////////////

			frameTime = newTime - currentTime;				// frame duration
			if (frameTime > 0.25f) frameTime = 0.25f;		// frame duration limitation

			//////////////////////////////////////////////////////////////
			//start of cycle

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->_data->machine.GetActiveState()->HandleInput();		// controlling the game
				this->_data->machine.GetActiveState()->Update(dt);			// updating the logic of the game

				accumulator -= dt;
			}

			interpolation = accumulator / dt;					// ratio coefficient of unworked time to frame
			this->_data->machine.GetActiveState()->Draw(interpolation);		// rendering of graphics of the game

			//==========================================================//
		}
	}
}
