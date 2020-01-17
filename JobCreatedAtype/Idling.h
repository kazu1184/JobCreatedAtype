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
		void Initialize(GameObject* object)override;
		// �X�V����
		void Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)override;
		// ��n��������
		void Finalize()override;
};
