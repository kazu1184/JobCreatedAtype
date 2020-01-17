//======================================================
// File Name	: Collider.h
// Summary		: �R���C�_�[���N���X
// Date			: 2019/12/12
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include <SimpleMath.h>

#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

class BoxCollider;
class SphereCollider;


class Collider : public Component
{
	protected:
	
		// �����o�ϐ�
	
		DirectX::SimpleMath::Vector3 m_offset;
	
	public:
	
		// �R���X�g���N�^�E�f�X�g���N�^
	
		Collider();
		virtual ~Collider() = default;
	
		// �����o�֐�
		virtual bool IsCollided(const Collider*       collider) const = 0;
		virtual bool IsCollided(const SphereCollider* collider) const = 0;
		virtual bool IsCollided(const BoxCollider*    collider) const = 0;

		void OnCollision(Collider* object);
	
		// �A�N�Z�b�T

		const DirectX::SimpleMath::Vector3 GetOffset()const
		{
			return m_offset;
		}

		void SetOffset(const DirectX::SimpleMath::Vector3 offset)
		{
			m_offset = offset;
		}

		const DirectX::SimpleMath::Vector3 GetPosition()const
		{
			return GetParent()->GetComponent<Transform>()->GetPosition() + m_offset;
		}
};
