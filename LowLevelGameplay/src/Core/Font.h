#pragma once
#include <Core/Asset.h>
#include <memory>

namespace sf
{
	class Font;
}

namespace LLGP
{
	class Font : public Asset
	{
	public:
		Font(std::string path);

		operator sf::Font* () { return _font.get(); }

		std::unique_ptr<sf::Font> _font;
	};
}

