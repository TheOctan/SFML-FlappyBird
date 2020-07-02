#include "AssetManager.hpp"
#include<iostream>

namespace Engine
{
	AssetManager::AssetManager()
	{
	}
	
	AssetManager::~AssetManager()
	{
	}

	void AssetManager::LoadImage(std::string name, std::string fileName)
	{
		sf::Image img;

		if (img.loadFromFile(fileName))
		{
			this->_images.insert(ImageStore::value_type(name, img));
		}
	}

	sf::Image & AssetManager::GetImage(std::string name)
	{
		return this->_images.at(name);
	}

	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->_textures.insert(TextureStore::value_type(name, tex));
			this->_textures.at(name).setSmooth(true);
		}
	}

	sf::Texture& AssetManager::GetTexture(std::string name)
	{
		return this->_textures.at(name);
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts.insert(FontStore::value_type(name, font));
		}
	}

	sf::Font& AssetManager::GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}	
}
