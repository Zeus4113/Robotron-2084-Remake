#pragma once
#include <Core/Component.h>
#include <Core/vector2.h>
#include <SFML/Graphics.hpp>

namespace LLGP 
{

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
	};
}



