#pragma once
#include "GameObject.h"

#include "Model.h" 

class Building : public GameObject
{
	private:
		// ビルモデル
		std::unique_ptr<DirectX::Model> m_mapObjs;
		// 描画OFFフラグ
		bool m_drawFlag;

	public:
		// コンストラクタ・デストラクタ
		Building();
		~Building();

		void Update()override;
		void Render()override;
		// 当たり判定
		void OnCollision(GameObject* object)override;
};

