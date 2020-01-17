#pragma once
#include "StepTimer.h"
#include <SimpleMath.h>
#include "CharacterState.h"
#include <vector>

class MapPosition;
class Enemy;

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
		void Initialize(GameObject* object)override;
		// �X�V����
		void Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)override;
		// ��n��������
		void Finalize()override;
};
