#include <Core/Font.h>
#include <SFML/Graphics.hpp>

namespace LLGP
{
	Font::Font(std::string path) : Asset(path)
	{
		_font = std::make_unique<sf::Font>();
		_font->loadFromFile(path);
	}
}