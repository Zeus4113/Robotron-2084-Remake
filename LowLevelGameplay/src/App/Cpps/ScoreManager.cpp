#include <App/ScoreManager.h>
#include <App/GameManager.h>
#include <SFML/Graphics.hpp>
#include <Core/RenderingManager.h>
#include <Core/ObjectPool.h>
#include <Core/GameObject.h>
#include <Core/Text.h>
#include <Core/AssetManager.h>
#include <Core/Font.h>

namespace LLGP 
{

	void ScoreManager::SetupManager(GameManager* gm)
	{
		_gm = gm;
		
		std::vector<GameObject*> enemyObjects = ObjectPool::GetAllObjectsOfType(ObjectTypes::Enemy);

		for (GameObject* o : enemyObjects)
		{
			o->GetComponent<Enemy>()->OnEnemyDead += std::bind(&ScoreManager::EnemyKilled, this, std::placeholders::_1);
		}

		std::vector<GameObject*> citizenObjects = ObjectPool::GetAllObjectsOfType(ObjectTypes::Citizen);

		for (GameObject* o : citizenObjects)
		{
			o->GetComponent<Citizen>()->OnCitizenRescued += std::bind(&ScoreManager::CitizenRescued, this, std::placeholders::_1);
		}

		GameObject* object = ObjectPool::GetObjectRef(ObjectTypes::Player);

		object->GetComponent<Character>()->onPlayerDead += std::bind(&ScoreManager::PlayerDied, this, std::placeholders::_1);

		GameObject* scoreReadout = new GameObject();
		Text* textComp = scoreReadout->AddComponent<Text>();

		textComp->SetString("Score Readout: " + 0);
		textComp->SetPosition(Vector2f(100, 100));
		textComp->SetColor(sf::Color::Red);
		textComp->SetSize(24);

	}

	void ScoreManager::SetLives(int newLives) 
	{
		_livesRemaining = newLives;
	}

	void ScoreManager::EnemyKilled(int eventInput)
	{
		_enemiesToKill--;
		std::cout << "Enemies Remaining: " << _enemiesToKill << std::endl;

		_currentScore += _scorePerEnemy;

		CheckConditions();
	}

	void ScoreManager::CitizenRescued(int eventInput)
	{
		_citizensToRescue--;
		std::cout << "Citizens Remaining: " << _citizensToRescue << std::endl;

		_currentScore += _scorePerCitizen;

		CheckConditions();
	}

	void ScoreManager::PlayerDied(int eventInput)
	{
		_livesRemaining--;
		std::cout << "Lives Remaining: " << _livesRemaining << std::endl;

		if (_livesRemaining <= 0) 
		{
			_gm->RestartGame(true);
			_livesRemaining = 3;
		}
		else 
		{
			_gm->RestartLevel();
		}
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

