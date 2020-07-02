#include "InputManager.hpp"

namespace Engine
{
	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
	}

	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow & window) const
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			sf::IntRect tempRect(							//local rect
				(int)object.getPosition().x,					//coordinate X
				(int)object.getPosition().y,					//coordinate Y
				(int)object.getGlobalBounds().width,			//width of rect
				(int)object.getGlobalBounds().height			//height of rect
			);

			if (tempRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}
		return false;
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow & window) const
	{
		return sf::Mouse::getPosition(window);
	}
}
