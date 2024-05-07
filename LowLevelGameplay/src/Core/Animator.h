#pragma once
#include <Core/Component.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <Core/vector2.h>

namespace LLGP 
{
	class Animator : public Component
	{
	public:
		Animator(GameObject* owner);
		~Animator();

		//void SetTexture(std::string filePath, Vector2f spriteAmount);
		void UpdateSprite(float deltaTime);
		
	private:
		sf::Texture _spriteSheet;
		Vector2f _spritesInSheet;
		Vector2f _sheetSize;
		sf::IntRect _rectCutout;

		float _updateTime;
		float _frameTime = 0.1f;

		int _currentRow = 0;
		int _currentCollumn = 0;

	};
}


