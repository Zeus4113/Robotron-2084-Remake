#pragma once

namespace LLGP 
{

	class GameManager;

	static class ScoreManager
	{
	public:
		ScoreManager() {}
		~ScoreManager() {}

		static void SetGameManager(GameManager* gm);

		static void EnemyKilled();

		static void CitizenRescued();

		static void SetLevelRequirements(int enemyAmount, int citizenAmount);

		static void CheckConditions();

	private:
		static int _enemiesToKill;
		static int _citizensToRescue;

		static GameManager* _gm;
	};
}

