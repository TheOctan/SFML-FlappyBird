#include<sstream>
#include<iostream>

#include"SplashState.hpp"
#include"DEFINITIONS.hpp"

#include"MainMenuState.hpp"

namespace Engine
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{
	}

	SplashState::~SplashState()
	{
#if DEBUG
		std::cout << "splash state is destruct" << std::endl;
#endif
	}

	void SplashState::Init()
	{
		this->_data->assets.LoadTexture("Splash State Backgroud", SPLASH_SCENE_BACKGROUND_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Splash State Backgroud"));
	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				this->_data->window.close();
			}
		}
	}

	void SplashState::Update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			// swith to the Main Menu
			this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), true);
		}
	}

	void SplashState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);

		this->_data->window.display();
	}
}
