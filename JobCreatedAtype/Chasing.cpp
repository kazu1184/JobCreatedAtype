#include "pch.h"
#include "Chasing.h"
#include "Enemy.h"
#include "MapPosition.h"
#include "ModelMap.h"
#include "Transform.h"

// コンストラクタ
Chasing::Chasing() : m_index(0), m_sum_translation(0.0f), m_position(DirectX::SimpleMath::Vector3::Zero)
{

}

bool Chasing::Initialize(GameObject * object)
{
	// Enemyオブジェクトでキャストする
	m_enemy = static_cast<Enemy*>(object);
	return true;
}

bool Chasing::Update(DirectX::Keyboard::KeyboardStateTracker * keyboard)
{
	// 前方方向の速度
	DirectX::SimpleMath::Vector3 Forward(0.1f, 0.0f, 0.0f);

	// 最短経路配列が0の場合
	if (m_route.size() == 0)
	{
		// 開始位置を取得する
		MapPosition* position = m_enemy->GetStartPosition();
		// 位置を補正する
		m_position = DirectX::SimpleMath::Vector3((float)position->GetX()* ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2, 0.0f, (float)position->GetY()* ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2);
		// 最短経路を取得する
		m_route = m_enemy->GetRoute();
	}

	// 現在の位置と次の位置の差を計算する
	DirectX::SimpleMath::Vector2 direction((float)m_route[m_index + 1]->GetX() - m_route[m_index]->GetX(),
		(float)m_route[m_index + 1]->GetY() - m_route[m_index]->GetY());
	// 向きを計算する
	float angle = -atan2(direction.y, direction.x);
	// 回転角を計算する
	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateRotationY(angle);
	// 速度を計算する
	DirectX::SimpleMath::Vector3 velocity = DirectX::SimpleMath::Vector3::TransformNormal(Forward, rotation);
	// 移動ベクトルを積算する
	m_sum_translation += velocity.Length();
	// 移動ベクトルを位置に加算する
	m_position += velocity;
	// 敵の位置を設定する
	m_enemy->GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(m_position.x , 0.0f, m_position.z));
	// 移動ベクトルの積算
	if (m_sum_translation >= ModelMap::MAP_SIZE)
	{
		// 移動ベクトルの積算をリセットする
		m_sum_translation = 0.0f;
		// インデックスが配列数を超えない場合
		if (m_index < (int)m_route.size() - 2)
		{
			// インデックスを加算する
			m_index++;
		}
		else
		{
			// 初期値に戻す
			m_index = 0;
			// 終了位置まで到達したら最短経路配列をクリアする
			m_route.clear();
			return false;
		}
	}
	return true;
}

// 後始末をする
bool Chasing::Finalize()
{
	return true;
}
