//======================================================
// File Name	: Transform.h
// Summary		: ポジション・ローテーション・スケール
// Date			: 2019/12/11
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once
#include "Component.h"

#include <SimpleMath.h>

class Transform : public Component
{
	// メンバ変数
	private:

		// マトリクス
		DirectX::SimpleMath::Matrix m_world;
		// ポジション
		DirectX::SimpleMath::Vector3 m_position;
		// ローテーション
		DirectX::SimpleMath::Vector3 m_rotation;
		// スケール
		DirectX::SimpleMath::Vector3 m_scale;

	public:
		// コンストラクタ・デストラクタ

		Transform();
		~Transform();

		// メンバ関数
		void Initialize()override;
		void Update()override;

		// アクセッサ

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



