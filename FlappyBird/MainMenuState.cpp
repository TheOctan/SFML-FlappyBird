#include<sstream>
#include<iostream>

#include"MainMenuState.hpp"
#include"DEFINITIONS.hpp"

#include"GameState.hpp"

namespace Engine
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{
	}

	MainMenuState::~MainMenuState()
	{
#if DEBUG
		std::cout << "main menu state is destruct" << std::endl;
#endif
	}

	void MainMenuState::Init()
	{
		// loading of textures
		this->_data->assets.LoadTexture("Main Menu Backgroud", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
		this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Cursor", GAME_CURSOR);

		// setting of sprites
		this->_background.setTexture(this->_data->assets.GetTexture("Main Menu Backgroud"));
		this->_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		this->_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		this->_cursor.setTexture(this->_data->assets.GetTexture("Cursor"));

		// settings of positions of the sprites
		this->_title.setPosition(
			(this->_data->window.getSize().x / 2) - (this->_title.getGlobalBounds().width / 2),
			this->_title.getGlobalBounds().height / 2
		);
		this->_playButton.setPosition(
			(this->_data->window.getSize().x / 2) - (this->_playButton.getGlobalBounds().width / 2),
			(this->_data->window.getSize().y / 2) - (this->_playButton.getGlobalBounds().height / 2)
		);

		this->_background.setPosition(0, -256);
		this->_cursor.setOrigin(
			this->_cursor.getGlobalBounds().width / 2,
			this->_cursor.getGlobalBounds().height / 2
		);
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window))
			{
				// swith to the game
				this->_data->machine.AddState(StateRef(new GameState(this->_data)), true);
			}
		}
	}

	void MainMenuState::Update(float dt)
	{
		this->_cursor.setPosition(sf::Vector2f(this->_data->input.GetMousePosition(this->_data->window)));
	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_title);
		this->_data->window.draw(this->_playButton);
		this->_data->window.draw(this->_cursor);

		this->_data->window.display();
	}
}
