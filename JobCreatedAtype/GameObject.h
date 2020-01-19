//======================================================
// File Name	: GameObject.h
// Summary		: �Q�[���I�u�W�F�N�g���N���X
// Date			: 2019/12/11
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include <SimpleMath.h>
#include <string>
#include <functional>
#include <list>

class Component;
class Transform;

class GameObject
{
	private:
		
		// �j��t���O
		bool m_deleteFlag;
		// �^�O
		std::string m_tag;

	protected:

		// �R���|�[�l���g���X�g
		std::list<Component*> m_componentList;
		// �ʒu�E�X�P�[��
		Transform* m_transform;
		// �A�N�e�B�u�t���O
		bool m_activeFlag;

	public:

	// �R���X�g���N�^�E�f�X�g���N�^

		GameObject(const std::string& tag);
		~GameObject();

	// �����o�֐�

		virtual void Update();
		virtual void Render();
		// �����蔻��
		virtual void OnCollision(GameObject* object);
		// �j��t���OON
		void Invalidate();

		// �A�N�Z�b�T

		// ���݂̃t���O���Q�b�g
		bool IsInvalid() const { return m_deleteFlag; }

		std::string GetTag() const { return m_tag; }

		void SetActive(bool flag) { m_activeFlag = flag; }

		Transform* GetTransform()const { return m_transform; }

		// �I�u�W�F�N�g�������Ă���R���|�[�l���g��ǉ�
		template<typename T>
		T* AddComponent()
		{
			T* buff = new T();
			buff->SetParent(this);
			m_componentList.push_back(buff);
			buff->Initialize();
			return buff;
		}

		// �I�u�W�F�N�g�������Ă���R���|�[�l���g���擾
		template<typename T>
		T* GetComponent()
		{
			for (Component* com : m_componentList)
			{
				//if (typeid(com) == typeid(T*))
				//{
				//	return com;
				//}
				T* buff = dynamic_cast<T*>(com);
				if (buff != nullptr)
					return buff;
			}
			return nullptr;
		}
};

