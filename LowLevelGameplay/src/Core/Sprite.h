#pragma once
#include <SFML/Graphics.hpp>
#include <Core/Component.h>
#include <Core/vector2.h>

namespace LLGP {

	class Sprite : public Component {
	public:
		Sprite(GameObject* owner) : Component(owner) {}
		~Sprite() {}

		void SetSize(Vector2f size) { _spriteShape.setSize(size); _spriteShape.setOrigin(size / 2); }
		void UpdateRender() { _spriteShape.setPosition( _GameObject->transform->position.x, _GameObject->transform->position.y); }
		sf::RectangleShape GetShape() { return _spriteShape; }

	private:
		sf::RectangleShape _spriteShape;
		Vector2f _spriteSize;
	};

}