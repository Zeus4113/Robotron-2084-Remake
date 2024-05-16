#pragma once
#include <SFML/Graphics.hpp>
#include <Core/Text.h>

namespace LLGP 
{
	class GameObject;

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

		void CitizenCaptured(int eventInput);

		void PlayerDied(int eventInput);

		void SetLevelRequirements(int enemyAmount, int citizenAmount);

		void CheckConditions();

		void SetScore(int newScore);

	private:
		int _enemiesToKill;
		int _citizensToRescue;

		int _currentScore = 0;
		int _livesRemaining = 3;

		const int _scorePerEnemy = 200;
		const int _scorePerCitizen = 150;

		GameObject* _scoreReadout;

		GameObject* _livesReadout;
		
		GameManager* _gm;
	};
}

