#pragma once
#include "StepTimer.h"
#include <SimpleMath.h>
#include "CharacterState.h"
#include <vector>

class MapPosition;
class Enemy;

class Chasing : public CharacterState
{
	private: // メンバ変数

		// Enemyのポインタ
		Enemy* m_enemy;
		// 位置
		DirectX::SimpleMath::Vector3 m_position;
		// 最短経路
		std::vector<MapPosition*> m_route;
		// インデックス
		int m_index;
		float m_sum_translation;
	public:
		// コンストラクタ
		Chasing();
		~Chasing() = default;
		// 初期化する
		void Initialize(GameObject* object)override;
		// 更新する
		void Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)override;
		// 後始末をする
		void Finalize()override;
};
