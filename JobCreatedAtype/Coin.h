#pragma once
#include "GameObject.h"

#include <Model.h>

class Coin : public GameObject
{
	private:
		// �R�C�����f��
		std::unique_ptr<DirectX::Model> m_coinModel;
		// �R�C���Q�b�g�t���O
		bool m_getFlag;

	public:
		Coin();
		~Coin();

		void Update()override;
		void Render()override;
		// �����蔻��
		void OnCollision(GameObject* object)override;

		bool GetFlag() { return m_getFlag; }
};

