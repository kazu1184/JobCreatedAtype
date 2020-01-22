//======================================================
// File Name	: BoxCollider.h
// Summary		: コライダー(Box)
// Date			: 2019/12/13
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "Collider.h"
#include <GeometricPrimitive.h>

class SphereCollider;

class BoxCollider : public Collider
{
	private:
		DirectX::SimpleMath::Vector3 m_size;
		std::unique_ptr<DirectX::GeometricPrimitive> m_debug;

	public:

		// コンストラクタ・デストラクタ

		BoxCollider(const DirectX::SimpleMath::Vector3& size = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
		~BoxCollider() = default;
	
		// メンバ関数
		void Render()override;
		bool IsCollided(const Collider*       collider) const override;
		bool IsCollided(const SphereCollider* collider) const override;
		bool IsCollided(const BoxCollider*    collider) const override;
		bool IsCollided(const RayCollider*    collider) const override;
	
		// アクセッサ

		void SetSize(const DirectX::SimpleMath::Vector3& size)
		{
			m_size = size;
		}
	
		const DirectX::SimpleMath::Vector3& GetSize() const
		{
			return m_size;
		}
};

