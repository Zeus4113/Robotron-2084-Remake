#pragma once
#include <SFML/Graphics.hpp>

namespace LLGP 
{

	class GameManager;

	class ScoreManager
	{
	public:
		ScoreManager() {}
		~ScoreManager() {}

		void SetupManager(GameManager* gm);

		void SetLives(int newLives);

		void EnemyKilled(int eventInput);

		void CitizenRescued(int eventInput);

		void PlayerDied(int eventInput);

		void SetLevelRequirements(int enemyAmount, int citizenAmount);

		void CheckConditions();

	private:
		int _enemiesToKill;
		int _citizensToRescue;

		int _currentScore = 0;
		int _livesRemaining = 3;

		const int _scorePerEnemy = 200;
		const int _scorePerCitizen = 150;

		GameManager* _gm;
	};
}

