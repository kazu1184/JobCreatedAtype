#pragma once
#include "CharacterState.h"

#include <Keyboard.h>

class GameObject;
class Player;

class KnockBackState : public CharacterState
{
	public: 
		// 何秒間ノックバックするか
		static const float KNOCK_BACK_TIME;
	private:
		// プレイヤーポインタ
		Player* m_player;
		// ノックバックタイム
		float m_time;
	public:
		// コンストラクタ・デストラクタ
		KnockBackState();
		~KnockBackState();

		bool Initialize(GameObject* obj)override;
		bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
		bool Finalize()override;
};

