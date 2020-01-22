#pragma once
#include "Collider.h"

class BoxCollider;
class SphereCollider;

class RayCollider : public Collider
{
	private:
		// スタートポジション
		DirectX::SimpleMath::Vector3 m_rayStart;
		// エンドポジション
		DirectX::SimpleMath::Vector3 m_rayVec;
		// 当たり判定の範囲
		float m_checkLength;

	public:
		RayCollider();
		~RayCollider() = default;

		void Render()override;

		// メンバ関数
		bool IsCollided(const Collider*       collider) const override;
		bool IsCollided(const SphereCollider* collider) const override;
		bool IsCollided(const BoxCollider*    collider) const override;
		bool IsCollided(const RayCollider*    collider) const override;

		// アップデートでセットしてあげる
		void SetEndRay(const DirectX::SimpleMath::Vector3& end) { m_rayVec = end; }
		void SetStartRay(const DirectX::SimpleMath::Vector3& start) { m_rayStart = start; }
		void SetLength(float length) { m_checkLength = length; }

		const DirectX::SimpleMath::Vector3& GetEndRay() const { return m_rayVec; }
		const DirectX::SimpleMath::Vector3& GetStartRay() const { return m_rayStart; }
		const float GetLength() const { return m_checkLength; }
};

