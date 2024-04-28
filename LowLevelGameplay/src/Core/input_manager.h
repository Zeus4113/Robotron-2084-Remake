#pragma once
#include <Core/Event.h>
#include <Core/vector2.h>
#include <vector>

namespace LLGP 
{
	static class InputManager
	{
	private:
		static Vector2f movementVectorObserver;
		static Vector2f shootingVectorObserver;
	public:
		static Event<int> inputEvent;
		static Event<Vector2f> onMovementPerformed;
		static Event<Vector2f> onMovementCancelled;
		static Event<Vector2f> onMovementStarted;

		static Event<Vector2f> onShootingPerformed;
		static Event<Vector2f> onShootingCancelled;
		static Event<int> onShoot;

		static Event<bool> onRestart;
		static Event<bool> onPause;

		static bool isPressed;

		static void CheckInput();
	};
}
