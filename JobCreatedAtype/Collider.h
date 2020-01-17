//======================================================
// File Name	: Collider.h
// Summary		: コライダー基底クラス
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
	
		// メンバ変数
	
		DirectX::SimpleMath::Vector3 m_offset;
	
	public:
	
		// コンストラクタ・デストラクタ
	
		Collider();
		virtual ~Collider() = default;
	
		// メンバ関数
		virtual bool IsCollided(const Collider*       collider) const = 0;
		virtual bool IsCollided(const SphereCollider* collider) const = 0;
		virtual bool IsCollided(const BoxCollider*    collider) const = 0;

		void OnCollision(Collider* object);
	
		// アクセッサ

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
