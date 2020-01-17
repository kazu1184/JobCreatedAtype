//======================================================
// File Name	: StandState.h
// Summary		: �Î~���
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
		// �v���C���[�|�C���^
		Player* m_player;

public:
		// �R���X�g���N�^�E�f�X�g���N�^
		StandState();
		~StandState();

		void Initialize(GameObject* obj)override;
		void Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)override;
		void Finalize()override;
};

