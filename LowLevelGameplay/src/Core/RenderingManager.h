#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <Core/Text.h>

namespace LLGP 
{
	class Sprite;

	class Animator;

	static class RenderingManager
	{
	public:
		RenderingManager() {}
		~RenderingManager() {}

		static void RegisterSprite(Sprite* newSprite);
		static void UnregisterSprite(Sprite* oldSprite);

		static void RegisterAnimator(Animator* newAnimator);
		static void UnregisterAnimator(Animator* oldAnimator);

		static void RegisterText(Text* newText);
		static void UnregisterText(Text* oldText);

		static void StartRender();
		static void UpdateRender(float deltaTime);

		static sf::RenderWindow* GetWindow() { return _Window; }

	private:
		static std::vector<Sprite*> _Sprites;
		static std::vector<Animator*> _Animators;
		static std::vector<Text*> _Texts;

		static sf::RenderWindow* _Window;
	};
}

