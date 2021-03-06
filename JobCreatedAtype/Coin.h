#pragma once
#include "GameObject.h"

#include <Model.h>

class Coin : public GameObject
{
	private:
		// コインモデル
		std::unique_ptr<DirectX::Model> m_coinModel;

	public:
		Coin();
		~Coin();

		void Update()override;
		void Render()override;
		// 当たり判定
		void OnCollision(GameObject* object)override;
};

