#pragma once
#include "StepTimer.h"
#include "CharacterState.h"

class Enemy;

class Idling :public CharacterState
{
	private: // メンバ変数

		Enemy* m_enemy;

	public: // メンバ関数

		// コンストラクタ
		Idling();

		// 初期化する
		void Initialize(GameObject* object)override;
		// 更新する
		void Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)override;
		// 後始末をする
		void Finalize()override;
};
