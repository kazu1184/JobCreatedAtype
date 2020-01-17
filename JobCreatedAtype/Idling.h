#pragma once
#include "StepTimer.h"
#include "CharacterState.h"

class Enemy;

class Idling :public CharacterState
{
	private: // �����o�ϐ�

		Enemy* m_enemy;

	public: // �����o�֐�

		// �R���X�g���N�^
		Idling();

		// ����������
		bool Initialize(GameObject* object)override;
		// �X�V����
		bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
		// ��n��������
		bool Finalize()override;
};

