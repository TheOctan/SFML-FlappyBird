#include<sstream>
#include<iostream>
#include<fstream>

#include"GameOverState.hpp"
#include"DEFINITIONS.hpp"

#include"GameState.hpp"
//#include"MainMenuState.hpp"

namespace Engine
{
	GameOverState::GameOverState(GameDataRef data, int score)
		: _data(data),
		_score(score),
		_highScore(0)
	{
	}

	GameOverState::~GameOverState()
	{
#if DEBUG
		std::cout << "game over state is destruct" << std::endl;
#endif
	}

	void GameOverState::Init()
	{
		std::ifstream readFile;
		readFile.open("Saves/HighScore.bin", std::ifstream::binary);

		if (readFile.is_open())
		{
			readFile.read((char*)&this->_highScore, sizeof(int));
		}

		readFile.close();

		std::ofstream writeFile;
		writeFile.open("Saves/HighScore.bin", std::ofstream::binary);

		if (writeFile.is_open())
		{
			if (this->_score > this->_highScore)
			{
				_highScore = _score;
			}

			writeFile.write((char*)&this->_highScore, sizeof(int));
		}

		writeFile.close();

		// loading of textures
		this->_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
		this->_data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);

		this->_data->assets.LoadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
		this->_data->assets.LoadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
		this->_data->assets.LoadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
		this->_data->assets.LoadTexture("Platinum Medal", PLATINUM_MEDAL_FILEPATH);

		// setting of sprites
		this->_background.setTexture(this->_data->assets.GetTexture("Game Over Background"));
		this->_gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title"));
		this->_gameOverContainer.setTexture(this->_data->assets.GetTexture("Game Over Body"));
		this->_retryButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		this->_cursor.setTexture(this->_data->assets.GetTexture("Cursor"));

		this->_background.setPosition(0, -256);
		this->_cursor.setOrigin(
			this->_cursor.getGlobalBounds().width / 2,
			this->_cursor.getGlobalBounds().height / 2
		);

		// settings of positions of the sprites
		this->_gameOverContainer.setPosition(
			(this->_data->window.getSize().x / 2) - (this->_gameOverContainer.getGlobalBounds().width / 2),
			(this->_data->window.getSize().y / 2) - (this->_gameOverContainer.getGlobalBounds().height / 2)
		);
		this->_gameOverTitle.setPosition(
			(this->_data->window.getSize().x / 2) - (this->_gameOverTitle.getGlobalBounds().width / 2),
			_gameOverContainer.getPosition().y - (this->_gameOverTitle.getGlobalBounds().height * 1.2f)
		);
		this->_retryButton.setPosition(
			(this->_data->window.getSize().x / 2) - (this->_retryButton.getGlobalBounds().width / 2),
			this->_gameOverContainer.getPosition().y + this->_gameOverContainer.getGlobalBounds().height +
			(this->_retryButton.getGlobalBounds().height * 0.2f)
		);

		this->_background.setPosition(0, -256);

		//settings of text
		this->_scoreText.setFont(this->_data->assets.GetFont("Flappy Font"));
		this->_scoreText.setString(std::to_string(this->_score));
		this->_scoreText.setCharacterSize(56);
		this->_scoreText.setFillColor(sf::Color::White);
		this->_scoreText.setOrigin(this->_scoreText.getGlobalBounds().width / 2, this->_scoreText.getGlobalBounds().height / 2);
		this->_scoreText.setPosition(
			this->_data->window.getSize().x / 10 * 7.25f,
			this->_data->window.getSize().y / 2.20f//2.15
		);

		this->_highScoreText.setFont(this->_data->assets.GetFont("Flappy Font"));
		this->_highScoreText.setString(std::to_string(this->_highScore));
		this->_highScoreText.setCharacterSize(56);
		this->_highScoreText.setFillColor(sf::Color::White);
		this->_highScoreText.setOrigin(this->_highScoreText.getGlobalBounds().width / 2, this->_highScoreText.getGlobalBounds().height / 2);
		this->_highScoreText.setPosition(
			this->_data->window.getSize().x / 10 * 7.25f,
			this->_data->window.getSize().y / 1.72f//1.78
		);

		//score settings
		if (this->_score >= PLATINUM_MEDAL_SCORE)
		{
			this->_medal.setTexture(this->_data->assets.GetTexture("Platinum Medal"));
		}
		else if (this->_score >= GOLD_MEDAL_SCORE)
		{
			this->_medal.setTexture(this->_data->assets.GetTexture("Gold Medal"));
		}
		else if (this->_score >= SILVER_MEDAL_SCORE)
		{
			this->_medal.setTexture(this->_data->assets.GetTexture("Silver Medal"));
		}
		else if (this->_score >= BRONZE_MEDAL_SCORE)
		{
			this->_medal.setTexture(this->_data->assets.GetTexture("Bronze Medal"));
		}

		this->_medal.setPosition(175, 350);//175 465
	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				this->_data->window.close();
			}

			if(event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					this->_data->machine.AddState(StateRef(new GameState(this->_data)), true);
				}

			if(event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::R || event.key.code == sf::Keyboard::Return)
				{
					this->_data->machine.AddState(StateRef(new GameState(this->_data)), true);
				}
		}

		if (this->_data->input.IsSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->window))
		{
			this->_data->machine.AddState(StateRef(new GameState(this->_data)), true);
		}
	}

	void GameOverState::Update(float dt)
	{
		this->_cursor.setPosition(sf::Vector2f(this->_data->input.GetMousePosition(this->_data->window)));
	}

	void GameOverState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_gameOverTitle);
		this->_data->window.draw(this->_gameOverContainer);
		this->_data->window.draw(this->_retryButton);
		this->_data->window.draw(this->_scoreText);
		this->_data->window.draw(this->_highScoreText);
		this->_data->window.draw(this->_medal);
		this->_data->window.draw(this->_cursor);

		this->_data->window.display();
	}
}
