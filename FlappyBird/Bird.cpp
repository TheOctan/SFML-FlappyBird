#include "Bird.hpp"
#include"DEFINITIONS.hpp"

namespace Engine
{
	Bird::Bird(GameDataRef data) : _data(data)
	{
		this->_animtionIterator = 0;

		this->_anumationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 1"));
		this->_anumationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 2"));
		this->_anumationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 3"));
		this->_anumationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 4"));

		this->_birdSprite.setTexture(this->_anumationFrames.at(this->_animtionIterator));

		this->_birdSprite.setPosition(
			(this->_data->window.getSize().x / 4) - (this->_birdSprite.getGlobalBounds().width / 2),
			(this->_data->window.getSize().y / 2) - (this->_birdSprite.getGlobalBounds().height / 2)
		);

		this->_state = BirdState::Still;

		this->_birdSprite.setOrigin(
			this->_birdSprite.getGlobalBounds().width / 2,
			this->_birdSprite.getGlobalBounds().height / 2
		);

		this->_rotation = 0;
	}

	Bird::~Bird()
	{

	}

	void Bird::Animate(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / this->_anumationFrames.size())
		{
			if (this->_animtionIterator < this->_anumationFrames.size() - 1)
			{
				this->_animtionIterator++;
			}
			else
			{
				this->_animtionIterator = 0;
			}

			this->_birdSprite.setTexture(this->_anumationFrames.at(this->_animtionIterator));

			this->_clock.restart();
		}
	}

	void Bird::Update(float dt)
	{
		this->_dy += GRAVITY;

		this->_birdSprite.move(0, this->_dy * dt);

		if (this->_dy > 0)
		{
			this->_rotation += ROTATION_SPEED * dt;

			if (this->_rotation > 25.0f)
			{
				this->_rotation = 25.0f;
			}
		}
		else
		{
			this->_rotation -= ROTATION_SPEED * dt;

			if (this->_rotation < -25.0f)
			{
				this->_rotation = -25.0f;
			}
		}
		
		this->_birdSprite.setRotation(this->_rotation);
		
		/*if (this->_state == BirdState::Falling)
		{
			this->_birdSprite.move(0, GRAVITY * dt);
			this->_rotation += ROTATION_SPEED * dt;

			if (this->_rotation > 25.0f)
			{
				this->_rotation = 25.0f;
			}

			this->_birdSprite.setRotation(this->_rotation);
		}
		else if (this->_state == BirdState::Flying)
		{
			this->_birdSprite.move(0, -FLYING_SPEED * dt);
			this->_rotation -= ROTATION_SPEED * dt;

			if (this->_rotation < -25.0f)
			{
				this->_rotation = -25.0f;
			}

			this->_birdSprite.setRotation(this->_rotation);
		}*/

		//if (this->_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
		//{
		//	//this->_movementClock.restart();
		//	this->_state = BirdState::Falling;
		//}
	}

	void Bird::Tap()
	{
		//this->_movementClock.restart();
		//this->_state = BirdState::Flying;
		this->_dy = -FLYING_SPEED;
	}

	const sf::Sprite& Bird::GetSprite() const
	{
		return this->_birdSprite;
	}

	void Bird::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(this->_birdSprite);
	}

}
