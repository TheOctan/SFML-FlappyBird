#include "Flash.hpp"
#include"DEFINITIONS.hpp"

namespace Engine
{
	Flash::Flash(GameDataRef data) : _data(data)
	{
		this->_shape.setSize(sf::Vector2f(this->_data->window.getSize()));
		this->_shape.setFillColor(sf::Color(255, 255, 255, 0));

		this->_flashOn = true;
	}

	Flash::~Flash()
	{

	}

	void Flash::Show(float dt)
	{
		if (this->_flashOn)
		{
			int alpha = int(_shape.getFillColor().a + (FLASH_SPEED * dt));

			if (alpha >= 255)
			{
				alpha = 255;
				this->_flashOn = false;
			}

			this->_shape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
		else
		{
			int alpha = int(_shape.getFillColor().a - (FLASH_SPEED * dt));

			if (alpha <= 0)
			{
				alpha = 0;
				this->_flashOn = false;
			}

			this->_shape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
	}

	void Flash::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(this->_shape);
	}

}


