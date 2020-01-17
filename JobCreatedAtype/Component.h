//======================================================
// File Name	: Component.h
// Summary		: �R���|�[�l���g���N���X
// Date			: 2019/12/10
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include <string>

class GameObject;

class Component
{
	// �����o�ϐ�
	protected: 

		// �e�|�C���^
		GameObject* m_parent;

	public:
		// �R���X�g���N�^�E�f�X�g���N�^

		Component();
		virtual ~Component() = default;

		//�@�����o�֐�

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		// �A�N�Z�b�T

		void SetParent(GameObject* obj)
		{
			m_parent = obj;
		}

		GameObject* GetParent() const
		{
			return m_parent;
		}
};

