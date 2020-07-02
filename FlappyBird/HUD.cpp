#include "HUD.hpp"
#include"DEFINITIONS.hpp"

#include<string>

namespace Engine
{
	HUD::HUD(GameDataRef data) : _data(data)
	{
		this->_scoreText.setFont(this->_data->assets.GetFont("Flappy Font"));
		this->_scoreText.setString("0");
		this->_scoreText.setCharacterSize(128);
		this->_scoreText.setFillColor(sf::Color::White);
		this->_scoreText.setOrigin(
			this->_scoreText.getGlobalBounds().width / 2,
			this->_scoreText.getGlobalBounds().height / 2
		);

		this->_scoreText.setPosition(
			(float)this->_data->window.getSize().x / 2,
			(float)this->_data->window.getSize().y / 5
		);
	}

	HUD::~HUD()
	{

	}

	void HUD::UpdateScore(int score)
	{
		this->_scoreText.setString(std::to_string(score));
	}

	void HUD::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(this->_scoreText);
	}

}