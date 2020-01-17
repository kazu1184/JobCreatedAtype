//======================================================
// File Name	: MoveState.h
// Summary		: 動き状態
// Date			: 2019/12/29
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once
#include "CharacterState.h"

#include <Keyboard.h>

class GameObject;
class Player;

class MoveState : public CharacterState
{
	public:
		// プレイヤースピード
		static const float PLAYER_SPEED;

	private:
		// プレイヤーポインタ
		Player* m_player;


	public:
		// コンストラクタ・デストラクタ
		MoveState();
		~MoveState();

		bool Initialize(GameObject* obj)override;
		bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
		bool Finalize()override;
};

