#pragma once
#include "Event.h"
#include "input_manager.h"

namespace LLGP 
{
	class InputAction {
	public:

		InputManager* manager;

		InputAction(InputManager* _manager) : manager(_manager) { manager->inputEvent += std::bind(&InputAction::CallAction, this, std::placeholders::_1); }


		void CallAction(int in) {
			std::cout << "Event Called /" << " Data: " << in << "\n";
		}

	private:

};
}
