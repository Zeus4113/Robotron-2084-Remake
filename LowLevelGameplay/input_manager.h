#pragma once
#include "Event.h"
#include "InputAction.h"

namespace LLGP 
{
	class InputManager
	{
	private:

	public:
		Event<int> inputEvent;

		void BroadcastInput(int argument) {
			inputEvent(argument);
		}

	};
}
