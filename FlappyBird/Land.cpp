#include "Land.hpp"
#include"DEFINITIONS.hpp"

namespace Engine
{
	Land::Land(GameDataRef data) : _data(data)
	{
		sf::Sprite land(this->_data->assets.GetTexture("Land"));
		sf::Sprite land2(this->_data->assets.GetTexture("Land"));

		land.setPosition(0, float(this->_data->window.getSize().y - land.getGlobalBounds().height + 70));//<=====
		land2.setPosition(land2.getGlobalBounds().width,
			float(this->_data->window.getSize().y - land.getGlobalBounds().height + 70)//<=====
		);

		this->_landSprites.push_back(land);
		this->_landSprites.push_back(land2);
	}

	Land::~Land()
	{

	}

	void Land::MoveLand(float dt)
	{
		for (sf::Sprite& land : this->_landSprites)
		{
			float movement = PIPE_MOVEMENT_SPEED * dt;

			land.move(-movement, 0.0f);

			if (land.getPosition().x < 0 - land.getGlobalBounds().width)
			{
				land.setPosition((float)this->_data->window.getSize().x, land.getPosition().y);
			}
		}
	}

	const SpriteHolder& Land::GetSprites() const
	{
		return this->_landSprites;
	}

	void Land::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		for (const sf::Sprite& land : this->_landSprites)
		{
			target.draw(land);
		}
	}

}
