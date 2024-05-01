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
		void SetColor(sf::Color color) { _spriteShape.setFillColor(color); }
		void UpdateRender();
		sf::RectangleShape GetShape() { return _spriteShape; }

	private:
		sf::RectangleShape _spriteShape;
		Vector2f _spriteSize;
	};

}