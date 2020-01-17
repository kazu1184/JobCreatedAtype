#pragma once
#include "GameObject.h"

#include "TiledMap.h"
#include "Model.h" 

class ModelMap : public GameObject
{
	public: 
	
		// マップサイズ
		static const float MAP_SIZE;
	
	private: 
	
		// TiledMap
		std::unique_ptr<TiledMap> m_tiledMap;
	
	public: 
		
		// コンストラクタ・デストラクタ
		ModelMap();
		~ModelMap();
		
		void Update()override;
		void Render()override;
		// 当たり判定
		void OnCollision(GameObject* object)override;

		// アクセッサ
		TiledMap* GetTiledMap() { return m_tiledMap.get(); }
};

