#pragma once
#include "GameObject.h"

#include "Model.h" 

class Floor : public GameObject
{
	private:
		// 床モデル
		std::unique_ptr<DirectX::Model> m_mapObjs;

	public:
		// コンストラクタ・デストラクタ
		Floor();
		~Floor();
	
		void Update()override;
		void Render()override;
		// 当たり判定
		void OnCollision(GameObject* object)override;
};

