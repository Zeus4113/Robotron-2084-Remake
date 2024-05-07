#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

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

		static void StartRender();
		static void UpdateRender(float deltaTime);

		static sf::RenderWindow* GetWindow() { return _Window; }

	private:
		static std::vector<Sprite*> _Sprites;
		static std::vector<Animator*> _Animators;
		static sf::RenderWindow* _Window;
	};
}

