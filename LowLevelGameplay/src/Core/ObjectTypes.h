#pragma once
#include <App/Bullet.h>
#include <App/Character.h>
#include <App/Enemy.h>
#include <App/Trap.h>
#include <App/Citizen.h>

namespace LLGP
{
	static enum class ObjectTypes
	{
		Player,
		Bullet,
		Enemy,
		Citizen,
		Trap
	};
}