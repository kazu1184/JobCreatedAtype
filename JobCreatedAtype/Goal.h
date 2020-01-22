#pragma once
#include "GameObject.h"

#include "Model.h" 
#include <GeometricPrimitive.h>


class Goal : public GameObject
{
	private:
		// �S�[�����f��
		std::unique_ptr<DirectX::Model> m_goalModel;
		std::unique_ptr<DirectX::GeometricPrimitive> m_player;
		bool m_flag;
	
	public:
		Goal();
		~Goal();

		void Update()override;
		void Render()override;
		// �����蔻��
		void OnCollision(GameObject* object)override;
};

