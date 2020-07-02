#include "Pipe.hpp"
#include"DEFINITIONS.hpp"

namespace Engine
{
	Pipe::Pipe(GameDataRef data) : _data(data)
	{
		this->_landHeight = this->_data->assets.GetTexture("Land").getSize().y;
		this->_pipeSpawnYOffset = 0;
	}

	Pipe::~Pipe()
	{

	}

	void Pipe::SpawnBottomPipe()
	{
		sf::Sprite pipe(this->_data->assets.GetTexture("Pipe Up"));
		pipe.setPosition(
			float(this->_data->window.getSize().x),
			float(this->_data->window.getSize().y - pipe.getGlobalBounds().height - this->_pipeSpawnYOffset + 128)//<======
		);

		this->_pipeSprites.push_back(pipe);
	}

	void Pipe::SpawnTopPipe()
	{
		sf::Sprite pipe(this->_data->assets.GetTexture("Pipe Down"));
		pipe.setPosition((float)this->_data->window.getSize().x, float(-this->_pipeSpawnYOffset - 128));//<======

		this->_pipeSprites.push_back(pipe);
	}

	void Pipe::SpawnInvisiblePipe()
	{
		sf::Sprite pipe(this->_data->assets.GetTexture("Pipe Up"));
		pipe.setPosition((float)this->_data->window.getSize().x, 0);
		pipe.setColor(sf::Color::Transparent);

		this->_pipeSprites.push_back(pipe);
	}

	void Pipe::SpawnScoringPipe()
	{
		sf::Sprite pipe(this->_data->assets.GetTexture("Scoring Pipe"));
		pipe.setPosition((float)this->_data->window.getSize().x, 0);

		this->_scoringPipes.push_back(pipe);
	}

	void Pipe::MovePipes(float dt)
	{
		for (sf::Sprite& pipe : this->_pipeSprites)
		{
			if (pipe.getPosition().x < 0 - pipe.getGlobalBounds().width)
			{
				_pipeSprites.erase(_pipeSprites.begin());
			}
			else
			{
				float movement = PIPE_MOVEMENT_SPEED * dt;
				pipe.move(-movement, 0);
			}
		}

		for (sf::Sprite& pipe : this->_scoringPipes)
		{
			if (pipe.getPosition().x < 0 - pipe.getGlobalBounds().width)
			{
				_pipeSprites.erase(_scoringPipes.begin());
			}
			else
			{
				float movement = PIPE_MOVEMENT_SPEED * dt;
				pipe.move(-movement, 0);
			}
		}
	}

	void Pipe::RandomisePipeOffset()
	{
		this->_pipeSpawnYOffset = rand() % (this->_landHeight + 1);
	}

	const SpriteHolder& Pipe::GetSprites() const
	{
		return this->_pipeSprites;
	}

	SpriteHolder& Pipe::GetScoringSprites()
	{
		return this->_scoringPipes;
	}

	int Pipe::count()
	{
		return this->_pipeSprites.size();
	}

	void Pipe::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		for (const sf::Sprite& pipe : this->_pipeSprites)
		{
			target.draw(pipe);
		}
	}

}
