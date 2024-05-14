#pragma once
#include <Core/Component.h>
#include <Core/vector2.h>
#include <SFML/Graphics.hpp>
#include <memory>

namespace LLGP 
{
	class Font;

	class Text : public Component
	{
	public:
		Text(GameObject* owner);
		~Text();

		void SetSize(int size);
		void SetFont(sf::Font font);
		void SetColor(sf::Color color);
		void SetPosition(Vector2f position);
		void SetString(std::string string);

		sf::Text GetText() { return _text; }

	private:
		sf::Text _text;
		std::shared_ptr<LLGP::Font> _font;
	};
}



