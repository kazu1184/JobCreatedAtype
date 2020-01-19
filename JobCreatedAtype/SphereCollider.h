//======================================================
// File Name	: SphereCollider.h
// Summary		: コライダー(Sphere)
// Date			: 2019/12/13
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{
	private:
		// メンバ変数

		float m_radius;
	
	
	public:
		// コンストラクタ・デストラクタ
		SphereCollider( float radius = 1.0f);
		~SphereCollider() = default;
	
		// メンバ関数
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

