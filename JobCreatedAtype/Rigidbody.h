//======================================================
// File Name	: Rigidbody.h
// Summary		: ���W�b�g�{�f�B
// Date			: 2019/01/08
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once
#include "Component.h"

#include <SimpleMath.h>

class Transform;

class Rigidbody : public Component
{
	private:
		// �ʒu���
		Transform* m_parentTransform;
		// �}�b�N�X�X�s�[�h
		float maxSpeed;
		// �����x
		DirectX::SimpleMath::Vector3 m_acc;
		// ���x
		DirectX::SimpleMath::Vector3 m_vel;

	public:
		Rigidbody();
		~Rigidbody();

		void Initialize()override;
		void Update()override;

		// �͂�������֐�
		void AddForce(float angle, float force);
		void AddForce(DirectX::SimpleMath::Vector3 rotY, float force);

		// ���x
		const DirectX::SimpleMath::Vector3& GetVelocity()
		{
			return m_vel;
		}

		// �ő�X�s�[�h
		void SetMaxSpeed(float speed)
		{
			maxSpeed = speed;
		}
};

