#include "ScoreManager.h"
#include <App/GameManager.h>

namespace LLGP 
{
	int ScoreManager::_enemiesToKill;
	int ScoreManager::_citizensToRescue;

	GameManager* ScoreManager::_gm;

	void ScoreManager::SetGameManager(GameManager* gm)
	{
		_gm = gm;
	}

	void ScoreManager::EnemyKilled()
	{
		_enemiesToKill--;
		std::cout << "Enemies Remaining: " << _enemiesToKill << std::endl;
		CheckConditions();
	}

	void ScoreManager::CitizenRescued()
	{
		_citizensToRescue--;
		std::cout << "Citizens Remaining: " << _citizensToRescue << std::endl;
		CheckConditions();
	}

	void ScoreManager::SetLevelRequirements(int enemyAmount, int citizenAmount)
	{
		_enemiesToKill = enemyAmount;
		_citizensToRescue = citizenAmount;
	}

	void ScoreManager::CheckConditions() 
	{
		if (_enemiesToKill <= 0 && _citizensToRescue <= 0) 
		{
			_gm->NextLevel();
		}
	}
}

