#pragma once
#include "GameObject.h"

#include "TiledMap.h"
#include "Model.h" 

class ModelMap : public GameObject
{
	public: 
	
		// �}�b�v�T�C�Y
		static const float MAP_SIZE;
	
	private: 
	
		// TiledMap
		std::unique_ptr<TiledMap> m_tiledMap;
	
	public: 
		
		// �R���X�g���N�^�E�f�X�g���N�^
		ModelMap();
		~ModelMap();
		
		void Update()override;
		void Render()override;
		// �����蔻��
		void OnCollision(GameObject* object)override;

		// �A�N�Z�b�T
		TiledMap* GetTiledMap() { return m_tiledMap.get(); }
};

