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

		void Initialize(GameObject* obj)override;
		void Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)override;
		void Finalize()override;
};

