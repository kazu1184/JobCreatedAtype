#pragma once
#include "GameObject.h"

#include "Model.h" 

class Building : public GameObject
{
	private:
		// �r�����f��
		std::unique_ptr<DirectX::Model> m_mapObjs;
		// �`��OFF�t���O
		bool m_drawFlag;

	public:
		// �R���X�g���N�^�E�f�X�g���N�^
		Building();
		~Building();

		void Update()override;
		void Render()override;
		// �����蔻��
		void OnCollision(GameObject* object)override;
};

