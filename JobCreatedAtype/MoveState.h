//======================================================
// File Name	: MoveState.h
// Summary		: �������
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
		// �v���C���[�X�s�[�h
		static const float PLAYER_SPEED;

	private:
		// �v���C���[�|�C���^
		Player* m_player;


	public:
		// �R���X�g���N�^�E�f�X�g���N�^
		MoveState();
		~MoveState();

		bool Initialize(GameObject* obj)override;
		bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
		bool Finalize()override;
};

