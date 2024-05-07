#pragma once
#include <SFML/Graphics.hpp>
#include <Core/Component.h>
#include <Core/vector2.h>

namespace LLGP {

	class Sprite : public Component {
	public:
		Sprite(GameObject* owner);
		~Sprite();

		void SetSize(Vector2f size) { _spriteShape.setSize(size); _spriteShape.setOrigin(size / 2); }
		void SetTexture(std::string filePath, Vector2f spriteAmount);
		void SetColor(sf::Color color) { _spriteShape.setFillColor(color); }

		void UpdateTexture(int row, int collumn);
		void UpdateRender();

		sf::RectangleShape GetShape() { return _spriteShape; }
		Vector2f GetTextureSize() { return Vector2f(_spriteTexture.getSize()); }
		float GetSpriteSize() { return _spriteTexture.getSize().x / _spritesInSheet.x; }

	private:
		sf::RectangleShape _spriteShape;
		Vector2f _spriteSize;

		Vector2f _spritesInSheet;
		sf::Texture _spriteTexture;
	};

}