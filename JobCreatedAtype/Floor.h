#pragma once
#include "GameObject.h"

#include "Model.h" 

class Floor : public GameObject
{
	private:
		// �����f��
		std::unique_ptr<DirectX::Model> m_mapObjs;

	public:
		// �R���X�g���N�^�E�f�X�g���N�^
		Floor();
		~Floor();
	
		void Update()override;
		void Render()override;
		// �����蔻��
		void OnCollision(GameObject* object)override;
};

