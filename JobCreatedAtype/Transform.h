//======================================================
// File Name	: Transform.h
// Summary		: �|�W�V�����E���[�e�[�V�����E�X�P�[��
// Date			: 2019/12/11
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once
#include "Component.h"

#include <SimpleMath.h>

class Transform : public Component
{
	// �����o�ϐ�
	private:

		// �}�g���N�X
		DirectX::SimpleMath::Matrix m_world;
		// �|�W�V����
		DirectX::SimpleMath::Vector3 m_position;
		// ���[�e�[�V����
		DirectX::SimpleMath::Vector3 m_rotation;
		// �X�P�[��
		DirectX::SimpleMath::Vector3 m_scale;

	public:
		// �R���X�g���N�^�E�f�X�g���N�^

		Transform();
		~Transform();

		// �����o�֐�
		void Initialize()override;
		void Update()override;

		// �A�N�Z�b�T

		const DirectX::SimpleMath::Matrix GetWorld()
		{
			return m_world;
		}

		void SetWorld(const DirectX::SimpleMath::Matrix world)
		{
			m_world = world;
		}


		const DirectX::SimpleMath::Vector3 GetPosition()
		{
			return m_position;
		}

		void SetPosition(const DirectX::SimpleMath::Vector3 pos)
		{
			m_position = pos;
		}

		const DirectX::SimpleMath::Vector3 GetRotation()
		{
			return m_rotation;
		}

		void SetRotation(const DirectX::SimpleMath::Vector3 rotation)
		{
			m_rotation = rotation;
		}

		const DirectX::SimpleMath::Vector3 GetScale()
		{
			return m_scale;
		}

		void SetScale(const DirectX::SimpleMath::Vector3 scale)
		{
			m_scale = scale;
		}
};



