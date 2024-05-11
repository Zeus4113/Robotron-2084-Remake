#include <Core/RenderingManager.h>
#include <Core/Sprite.h>
#include <Core/GameObject.h>
#include <Core/Animator.h>
#include <Core/Text.h>

namespace LLGP 
{
	std::vector<Sprite*> RenderingManager::_Sprites;
	sf::RenderWindow* RenderingManager::_Window;
	std::vector<Animator*> RenderingManager::_Animators;
	std::vector<Text*> RenderingManager::_Texts;

	void RenderingManager::StartRender() 
	{
		_Window = new sf::RenderWindow(sf::VideoMode(660, 540), "ROBOTRON 2084");
	}

	void RenderingManager::RegisterSprite(Sprite* newSprite)
	{
		_Sprites.push_back(newSprite);
	}

	void RenderingManager::UnregisterSprite(Sprite* oldSprite)
	{
		for (int i = 0; i < _Sprites.size(); ++i)
		{
			if (_Sprites[i] == oldSprite)
			{
				_Sprites.erase(_Sprites.begin() + i);
			}
		}
	}

	void RenderingManager::RegisterAnimator(Animator* newAnimator)
	{
		_Animators.push_back(newAnimator);
	}

	void RenderingManager::UnregisterAnimator(Animator* oldAnimator)
	{
		for (int i = 0; i < _Animators.size(); ++i)
		{
			if (_Animators[i] == oldAnimator)
			{
				_Animators.erase(_Animators.begin() + i);
			}
		}
	}

	void RenderingManager::RegisterText(Text* newText)
	{
		_Texts.push_back(newText);
	}

	void RenderingManager::UnregisterText(Text* oldText)
	{
		for (int i = 0; i < _Texts.size(); ++i)
		{
			if (_Texts[i] == oldText)
			{
				_Texts.erase(_Texts.begin() + i);
			}
		}
	}

	void RenderingManager::UpdateRender(float deltaTime)
	{
		_Window->clear();

		for (Animator* a : _Animators)
		{
			if (a->GetGameObject()->GetActive())
			{
				a->UpdateSprite(deltaTime);
			}
		}

		for (Sprite* s : _Sprites) 
		{
			if (s->GetGameObject()->GetActive()) 
			{
				s->UpdateRender();
				_Window->draw(s->GetShape());
			}
		}


		for (Text* t : _Texts)
		{
			if (t != nullptr) 
			{
				//_Window->draw(t->GetText());
			}
		}

		_Window->display();
	}
}