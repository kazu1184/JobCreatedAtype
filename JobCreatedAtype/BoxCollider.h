//======================================================
// File Name	: BoxCollider.h
// Summary		: �R���C�_�[(Box)
// Date			: 2019/12/13
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "Collider.h"

class SphereCollider;

class BoxCollider : public Collider
{
	private:
		DirectX::SimpleMath::Vector3 m_size;
	
	
	public:

		// �R���X�g���N�^�E�f�X�g���N�^

		BoxCollider(const DirectX::SimpleMath::Vector3& size = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
		~BoxCollider() = default;
	
		// �����o�֐�

		bool IsCollided(const Collider*       collider) const override;
		bool IsCollided(const SphereCollider* collider) const override;
		bool IsCollided(const BoxCollider*    collider) const override;
	
	
		// �A�N�Z�b�T

		void SetSize(const DirectX::SimpleMath::Vector3& size)
		{
			m_size = size;
		}
	
		const DirectX::SimpleMath::Vector3& GetSize() const
		{
			return m_size;
		}
};

