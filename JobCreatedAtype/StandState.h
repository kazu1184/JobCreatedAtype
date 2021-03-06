//======================================================
// File Name	: StandState.h
// Summary		: 静止状態
// Date			: 2019/12/29
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once
#include "CharacterState.h"

#include <Keyboard.h>

class GameObject;
class Player;

class StandState : public CharacterState
{
	private:
		// プレイヤーポインタ
		Player* m_player;

public:
		// コンストラクタ・デストラクタ
		StandState();
		~StandState();

		bool Initialize(GameObject* obj)override;
		bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
		bool Finalize()override;
};

