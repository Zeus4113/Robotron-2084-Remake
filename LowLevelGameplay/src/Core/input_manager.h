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
	public:
		static Event<int> inputEvent;
		static Event<Vector2f> onMovementPerformed;
		static Event<Vector2f> onMovementCancelled;
		static Event<Vector2f> onMovementStarted;

		static void CheckInput();
	};
}
