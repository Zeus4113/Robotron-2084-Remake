#include <Core/Text.h>
#include <Core/GameObject.h>
#include <Core/RenderingManager.h>

namespace LLGP 
{
	Text::Text(GameObject* owner) : Component(owner) 
	{ 
		RenderingManager::RegisterText(this);

		sf::Font font;
		font.loadFromFile("fonts/robotron.ttf");
		_text.setFont(font);
	}

	Text::~Text() 
	{ 
		RenderingManager::UnregisterText(this); 
	}

	void Text::SetSize(int size)
	{
		_text.setCharacterSize(size);
	}

	void Text::SetFont(sf::Font font)
	{
		_text.setFont(font);
	}

	void Text::SetColor(sf::Color color)
	{
		_text.setColor(color);
	}

	void Text::SetPosition(Vector2f position) 
	{ 
		this->GetGameObject()->transform->position = Vector3f(position);
	}

	void Text::SetString(std::string string)
	{
		_text.setString(string);
	}

}