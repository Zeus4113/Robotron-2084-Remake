#include <App/ScoreManager.h>
#include <App/GameManager.h>
#include <SFML/Graphics.hpp>
#include <Core/RenderingManager.h>
#include <Core/ObjectPool.h>
#include <Core/GameObject.h>
#include <Core/Text.h>
#include <Core/AssetManager.h>
#include <Core/Font.h>
#include <string>

namespace LLGP 
{

	void ScoreManager::SetupManager(GameManager* gm)
	{
		_gm = gm;
		_scoreReadout = new GameObject();
		_livesReadout = new GameObject();
		
		std::vector<GameObject*> enemyObjects = ObjectPool::GetAllObjectsOfType(ObjectTypes::Enemy);

		for (GameObject* o : enemyObjects)
		{
			o->GetComponent<Enemy>()->OnEnemyDead += std::bind(&ScoreManager::EnemyKilled, this, std::placeholders::_1);
		}

		std::vector<GameObject*> citizenObjects = ObjectPool::GetAllObjectsOfType(ObjectTypes::Citizen);

		for (GameObject* o : citizenObjects)
		{
			o->GetComponent<Citizen>()->OnCitizenRescued += std::bind(&ScoreManager::CitizenRescued, this, std::placeholders::_1);
			o->GetComponent<Citizen>()->OnCitizenCaptured += std::bind(&ScoreManager::CitizenCaptured, this, std::placeholders::_1);
		}

		GameObject* object = ObjectPool::GetObjectRef(ObjectTypes::Player);

		object->GetComponent<Character>()->onPlayerDead += std::bind(&ScoreManager::PlayerDied, this, std::placeholders::_1);

		Text* textComp = _scoreReadout->AddComponent<Text>();
		Text* textComp2 = _livesReadout->AddComponent<Text>();

		this->SetScore(0);
		textComp->SetString("Score: 0");
		textComp->SetPosition(Vector2f(20, 10));
		textComp->SetColor(sf::Color::White);
		textComp->SetSize(16);

		textComp2->SetString("Lives: 3");
		textComp2->SetPosition(Vector2f(RenderingManager::GetWindow()->getSize().x - 100, 10));
		textComp2->SetColor(sf::Color::White);
		textComp2->SetSize(16);

	}

	void ScoreManager::SetLives(int newLives) 
	{
		_livesRemaining = newLives;
		_livesReadout->GetComponent<Text>()->SetString("Lives: " + std::to_string(_livesRemaining));
	}

	void ScoreManager::SetScore(int newScore) 
	{
		_currentScore = newScore;
		_scoreReadout->GetComponent<Text>()->SetString("Score: " + std::to_string(_currentScore));
	}

	void ScoreManager::EnemyKilled(int eventInput)
	{
		_enemiesToKill--;
		//std::cout << "Enemies Remaining: " << _enemiesToKill << std::endl;

		_currentScore += _scorePerEnemy;

		this->SetScore(_currentScore + _scorePerCitizen);

		CheckConditions();
	}

	void ScoreManager::CitizenRescued(int eventInput)
	{
		_citizensToRescue--;
		//std::cout << "Citizens Remaining: " << _citizensToRescue << std::endl;

		this->SetScore(_currentScore + _scorePerCitizen);

		CheckConditions();
	}

	void ScoreManager::CitizenCaptured(int eventInput) 
	{
		_citizensToRescue--;

		CheckConditions();
	}

	void ScoreManager::PlayerDied(int eventInput)
	{
		SetLives(_livesRemaining - 1);

		if (_livesRemaining <= 0) 
		{
			_gm->RestartGame(true);
			_livesRemaining = 3;
			_currentScore = 0;
			_scoreReadout->GetComponent<Text>()->SetString("Score: " + std::to_string(_currentScore));
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

