#pragma once
#include "StepTimer.h"
#include <SimpleMath.h>
#include "CharacterState.h"
#include <vector>

class Enemy;
class MapPosition;

class Chasing : public CharacterState
{
	private: // �����o�ϐ�

		// Enemy�̃|�C���^
		Enemy* m_enemy;
		// �ʒu
		DirectX::SimpleMath::Vector3 m_position;
		// �ŒZ�o�H
		std::vector<MapPosition*> m_route;
		// �C���f�b�N�X
		int m_index;
		float m_sum_translation;

	public:
		// �R���X�g���N�^
		Chasing();
		~Chasing() = default;
		// ����������
		bool Initialize(GameObject* object)override;
		// �X�V����
		bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
		// ��n��������
		bool Finalize()override;
		// ���[�g���N���A
		void ClearRoute();
};
