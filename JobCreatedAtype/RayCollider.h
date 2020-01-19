#pragma once
#include "Collider.h"

class BoxCollider;
class SphereCollider;

class RayCollider : public Collider
{
	private:
		// �X�^�[�g�|�W�V����
		DirectX::SimpleMath::Vector3 m_rayStart;
		// �G���h�|�W�V����
		DirectX::SimpleMath::Vector3 m_rayEnd;

	public:
		RayCollider();
		~RayCollider() = default;

		// �����o�֐�

		bool IsCollided(const Collider*       collider) const override;
		bool IsCollided(const SphereCollider* collider) const override;
		bool IsCollided(const BoxCollider*    collider) const override;
		bool IsCollided(const RayCollider*    collider) const override;

		// �A�b�v�f�[�g�ŃZ�b�g���Ă�����
		void SetEndRay(const DirectX::SimpleMath::Vector3& end) { m_rayEnd = end; }
		void SetStartRay(const DirectX::SimpleMath::Vector3& start) { m_rayStart = start; }

		const DirectX::SimpleMath::Vector3& GetEndRay() const { return m_rayEnd - m_rayStart; }
		const DirectX::SimpleMath::Vector3& GetStartRay() const { return m_rayStart; }
};

