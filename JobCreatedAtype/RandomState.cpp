#include "pch.h"
#include "RandomState.h"

#include "Enemy.h"
#include "ModelMap.h"
#include "MapPosition.h"
#include "Transform.h"
#include "GameObjectManager.h"
#include "GameContext.h"

#include <random>

const int RandomState::THINKING_INTERVAL = 60;

RandomState::RandomState()
	: m_count(0.0f)
	, m_velocity(0.f, 0.f, 0.f)
{
}

// 初期化する
bool RandomState::Initialize(GameObject * object)
{
	m_enemy = static_cast<Enemy*>(object);
	m_map = static_cast<ModelMap*>(GameContext<GameObjectManager>::Get()->Find("Map")[0]);
	m_currentMapPos = m_enemy->GetComponent<MapPosition>();
	return true;
}

bool RandomState::Update(DirectX::Keyboard::KeyboardStateTracker * keyboard)
{	
	if (m_count == 0)
	{
		// カウントの初期化
		m_count = 0;
		// ランダムシード値の生成
		std::random_device seedGenerator;
		std::mt19937 randomGenerator(seedGenerator());
		std::uniform_int_distribution<int> direction(0, 3);

		m_direction = direction(randomGenerator);

		m_velocity = DirectX::SimpleMath::Vector3::Zero;

		switch (m_direction)
		{
		case 0:
			if (m_map->GetTiledMap()->GetMap()[m_currentMapPos->GetX() - 1][m_currentMapPos->GetY()] == 0)
			{
				m_currentMapPos->SetX(m_currentMapPos->GetX() - 1);
				m_velocity.x = -ModelMap::MAP_SIZE;
			}
			break;
		case 1:
			if (m_map->GetTiledMap()->GetMap()[m_currentMapPos->GetX() + 1][m_currentMapPos->GetY()] == 0)
			{
				m_currentMapPos->SetX(m_currentMapPos->GetX() + 1);
				m_velocity.x = ModelMap::MAP_SIZE;
			}
			break;
		case 2:
			if (m_map->GetTiledMap()->GetMap()[m_currentMapPos->GetX()][m_currentMapPos->GetY() - 1] == 0)
			{
				m_currentMapPos->SetY(m_currentMapPos->GetY() - 1);
				m_velocity.z = -ModelMap::MAP_SIZE;
			}
			break;
		case 3:
			if (m_map->GetTiledMap()->GetMap()[m_currentMapPos->GetX()][m_currentMapPos->GetY() + 1] == 0)
			{
				m_currentMapPos->SetY(m_currentMapPos->GetY() + 1);
				m_velocity.z = ModelMap::MAP_SIZE;
			}
			break;
		default:
			break;
		}

		if (FloatEquals(m_velocity.x, 0.0f) == false || FloatEquals(m_velocity.z, 0.0f) == false)
		{
			m_count = THINKING_INTERVAL;
		}
	}

	// 移動状態の時の処理
	if (m_count > 0)
	{
		DirectX::SimpleMath::Vector3 temp = m_enemy->GetTransform()->GetPosition();
		temp.x += m_velocity.x / THINKING_INTERVAL;
		temp.z += m_velocity.z / THINKING_INTERVAL;

		m_enemy->GetTransform()->SetPosition(temp);
		m_count--;
	}

	return false;
}

bool RandomState::Finalize()
{
	return true;
}

