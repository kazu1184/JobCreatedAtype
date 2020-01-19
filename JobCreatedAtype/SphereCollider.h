//======================================================
// File Name	: SphereCollider.h
// Summary		: �R���C�_�[(Sphere)
// Date			: 2019/12/13
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{
	private:
		// �����o�ϐ�

		float m_radius;
	
	
	public:
		// �R���X�g���N�^�E�f�X�g���N�^
		SphereCollider( float radius = 1.0f);
		~SphereCollider() = default;
	
		// �����o�֐�
		bool IsCollided(const Collider*       collider) const override;
		bool IsCollided(const SphereCollider* collider) const override;
		bool IsCollided(const BoxCollider*    collider) const override;
		bool IsCollided(const RayCollider*    collider) const override;

	public:
		float GetRadius() const
		{
			return m_radius;
		}

		void  SetRadius(float radius)
		{
			m_radius = radius;
		}
};

