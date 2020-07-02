#include<sstream>
#include<iostream>

#include"GameState.hpp"
#include"DEFINITIONS.hpp"

#include"GameOverState.hpp"

namespace Engine
{
	GameState::GameState(GameDataRef data) : _data(data)
	{
	}

	GameState::~GameState()
	{
#if DEBUG
		std::cout << "game state is destruct" << std::endl;
#endif

		delete this->pipe;
		delete this->land;
		delete this->bird;
		delete this->flash;
		delete this->hud;
	}

	void GameState::Init()
	{
		this->_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH);
		this->_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH);
		this->_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH);

		this->_hitSound.setBuffer(this->_hitSoundBuffer);
		this->_wingSound.setBuffer(this->_wingSoundBuffer);
		this->_pointSound.setBuffer(this->_pointSoundBuffer);

		// loading of textures
		this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		this->_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		this->_data->assets.LoadTexture("Land", LAND_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
		this->_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
		this->_data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

		// setting of the game
		this->pipe = new Pipe(this->_data);
		this->land = new Land(this->_data);
		this->bird = new Bird(this->_data);
		this->flash = new Flash(this->_data);
		this->hud = new HUD(this->_data);

		// setting of sprites
		this->_background.setTexture(this->_data->assets.GetTexture("Game Background"));


		// settings of positions of the sprites	

		this->_background.setPosition(0, -256);

		this->_score = 0;
		this->hud->UpdateScore(this->_score);
		this->_gameState = GameStates::Ready;
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				this->_data->window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (this->_gameState != GameStates::GameOver)
					{
						this->_gameState = GameStates::Playing;
						bird->Tap();
						this->_wingSound.play();
					}
				}


			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up)
				{
					if (this->_gameState != GameStates::GameOver)
					{
						this->_gameState = GameStates::Playing;
						bird->Tap();
						this->_wingSound.play();
					}
				}
		}
	}

	void GameState::Update(float dt)
	{
		if (this->_gameState != GameStates::GameOver)
		{
			bird->Animate(dt);
			land->MoveLand(dt);
		}

		if (this->_gameState == GameStates::Playing)
		{
			pipe->MovePipes(dt);

			if (this->_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				pipe->RandomisePipeOffset();

				//pipe->SpawnInvisiblePipe();
				pipe->SpawnBottomPipe();
				pipe->SpawnTopPipe();
				pipe->SpawnScoringPipe();

				this->_clock.restart();
			}

			bird->Update(dt);

			if (this->bird->GetSprite().getGlobalBounds().top + 10 < 0) 
			{
				this->_hitSound.play();
				this->_gameState = GameStates::GameOver;
			}

			SpriteHolder landSprites = land->GetSprites();

			for (size_t i = 0; i < landSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), landSprites.at(i), sf::Vector2f(0.7f, 1.0f)))
				{
					this->_gameState = GameStates::GameOver;
					this->_hitSound.play();

					this->_clock.restart();
				}
			}

			SpriteHolder pipeSprites = pipe->GetSprites();

			for (size_t i = 0; i < pipeSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), pipeSprites.at(i), sf::Vector2f(0.625f, 1.0f)))
				{
					this->_gameState = GameStates::GameOver;
					this->_hitSound.play();

					this->_clock.restart();
				}
			}

			SpriteHolder& scoringSprites = pipe->GetScoringSprites();

			for (size_t i = 0; i < scoringSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), scoringSprites.at(i), sf::Vector2f(0.5f, 0.5f)))
				{
					this->_score++;
					this->_pointSound.play();

					this->hud->UpdateScore(this->_score);

					scoringSprites.erase(scoringSprites.begin());
				}
			}
		}

		if (this->_gameState == GameStates::GameOver)
		{
			this->flash->Show(dt);

			if (this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
			{
				this->_data->machine.AddState(StateRef(new GameOverState(this->_data, this->_score)), true);
			}
		}
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(*this->pipe);
		this->_data->window.draw(*this->land);
		this->_data->window.draw(*this->bird);
		this->_data->window.draw(*this->hud);
		this->_data->window.draw(*this->flash);

		this->_data->window.display();
	}

}
