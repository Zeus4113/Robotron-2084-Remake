#pragma once

namespace LLGP
{
	class GameManager
	{
	public:
		GameManager() {}
		~GameManager() {}

		void Initialise();

		void SetupLevel();

		void StartGame();

		void NextLevel();

		void RestartGame(bool isTrue);

	private:
		int _DifficultyLevel = 1;
		const int _EnemyMultiplier = 5;
		const int _CitizenMultiplier = 2;
		const int _TrapMultiplier = 4;
	};
}

