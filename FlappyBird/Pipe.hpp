#pragma once

#ifndef GAME_PIPE_HPP
#define GAME_PIPE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include<SFML\Graphics.hpp>
#include"Game.hpp"

namespace Engine
{
	class Pipe : public sf::Drawable
	{
	public:
		Pipe(GameDataRef data);
		~Pipe();

		void SpawnBottomPipe();
		void SpawnTopPipe();
		void SpawnInvisiblePipe();
		void SpawnScoringPipe();
		void MovePipes(float dt);
		void RandomisePipeOffset();

		const SpriteHolder& GetSprites() const;
		SpriteHolder& GetScoringSprites();

		int count();

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		GameDataRef		_data;
		SpriteHolder	_pipeSprites;
		SpriteHolder	_scoringPipes;

		int				_landHeight;
		int				_pipeSpawnYOffset;
	};

} // namespace Engine

#endif // !GAME_PIPE_HPP


