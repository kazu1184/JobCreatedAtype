//======================================================
// File Name	: GameObjectManager.h
// Summary		: �Q�[���I�u�W�F�N�g�}�l�[�W���[
// Date			: 2019/12/13
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include <list>
#include <SimpleMath.h>
#include <vector>
#include <functional>

class GameObject;
class FollowCamera;

class GameObjectManager final
{
	private:
		// Using
		using GameObjectPtr = std::unique_ptr<GameObject>;
		using GameObjectList = std::list<GameObjectPtr>;

		// �����o�ϐ�
		GameObjectList m_objects;
		GameObjectList m_objectQueue;
		// �Ǐ]�J����
		std::unique_ptr<FollowCamera> m_camera;

	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		GameObjectManager();
		~GameObjectManager();

		// �����o�֐�
		void Update();
		void Render();
		void Add(GameObjectPtr&& object);
		std::vector<GameObject*> Find(const std::string& tag) const;
		std::vector<GameObject*> GetGameObjects()const;
		// �A�N�Z�b�T
		FollowCamera* GetCamera()
		{
			return m_camera.get();
		}
};

