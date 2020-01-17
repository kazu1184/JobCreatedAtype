#pragma once
#include "CharacterState.h"

#include <Keyboard.h>

class GameObject;
class Player;

class KnockBackState : public CharacterState
{
	public: 
		// ���b�ԃm�b�N�o�b�N���邩
		static const float KNOCK_BACK_TIME;
	private:
		// �v���C���[�|�C���^
		Player* m_player;
		// �m�b�N�o�b�N�^�C��
		float m_time;
	public:
		// �R���X�g���N�^�E�f�X�g���N�^
		KnockBackState();
		~KnockBackState();

		bool Initialize(GameObject* obj)override;
		bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
		bool Finalize()override;
};

