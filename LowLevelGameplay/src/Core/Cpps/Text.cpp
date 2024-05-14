#include <Core/Text.h>
#include <Core/GameObject.h>
#include <Core/RenderingManager.h>
#include <Core/AssetManager.h>
#include <Core/Font.h>

namespace LLGP 
{
	Text::Text(GameObject* owner) : Component(owner) 
	{ 
		RenderingManager::RegisterText(this);

		_font = AssetManager::GetAsset<LLGP::Font>("fonts/robotron.ttf");
		_text.setFont(*_font->_font.get());
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
		_text.setPosition(position);
	}

	void Text::SetString(std::string string)
	{
		_text.setString(string);
	}

}