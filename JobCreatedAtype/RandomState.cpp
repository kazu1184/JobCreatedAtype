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
		// 方向のランダム
		m_direction = direction(randomGenerator);
		// ヴェロシティの初期化
		m_velocity = DirectX::SimpleMath::Vector3::Zero;
		// 方向で進めるかを確認
		switch (m_direction)
		{
		case 0:
			if (m_map->GetTiledMap()->GetMap()[m_currentMapPos->GetX() - 1][m_currentMapPos->GetY()] == 0)
			{
				m_velocity.x = -ModelMap::MAP_SIZE;
			}
			break;
		case 1:
			if (m_map->GetTiledMap()->GetMap()[m_currentMapPos->GetX() + 1][m_currentMapPos->GetY()] == 0)
			{
				m_velocity.x = ModelMap::MAP_SIZE;
			}
			break;
		case 2:
			if (m_map->GetTiledMap()->GetMap()[m_currentMapPos->GetX()][m_currentMapPos->GetY() - 1] == 0)
			{
				m_velocity.z = -ModelMap::MAP_SIZE;
			}
			break;
		case 3:
			if (m_map->GetTiledMap()->GetMap()[m_currentMapPos->GetX()][m_currentMapPos->GetY() + 1] == 0)
			{
				m_velocity.z = ModelMap::MAP_SIZE;
			}
			break;
		default:
			break;
		}
		// 速度の数値が入っていれば移動中に移す
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

	// 移動完了ならTrueを返す
	if (m_count == 0)
		return true;
	else
		return false;
}

bool RandomState::Finalize()
{
	return true;
}

