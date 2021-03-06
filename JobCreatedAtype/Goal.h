#pragma once
#include "GameObject.h"

#include "Model.h" 
#include <GeometricPrimitive.h>


class Goal : public GameObject
{
	private:
		// ゴールモデル
		std::unique_ptr<DirectX::Model> m_goalModel;
		std::unique_ptr<DirectX::GeometricPrimitive> m_player;
		bool m_flag;
	
	public:
		Goal();
		~Goal();

		void Update()override;
		void Render()override;
		// 当たり判定
		void OnCollision(GameObject* object)override;
};

