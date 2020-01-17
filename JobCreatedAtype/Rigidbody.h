//======================================================
// File Name	: Rigidbody.h
// Summary		: リジットボディ
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
		// 位置情報
		Transform* m_parentTransform;
		// マックススピード
		float maxSpeed;
		// 加速度
		DirectX::SimpleMath::Vector3 m_acc;
		// 速度
		DirectX::SimpleMath::Vector3 m_vel;

	public:
		Rigidbody();
		~Rigidbody();

		void Initialize()override;
		void Update()override;

		// 力を加える関数
		void AddForce(float angle, float force);
		void AddForce(DirectX::SimpleMath::Vector3 rotY, float force);

		// 速度
		const DirectX::SimpleMath::Vector3& GetVelocity()
		{
			return m_vel;
		}

		// 最大スピード
		void SetMaxSpeed(float speed)
		{
			maxSpeed = speed;
		}
};

