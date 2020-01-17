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
		bool Initialize(GameObject* object)override;
		// 更新する
		bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
		// 後始末をする
		bool Finalize()override;
};

