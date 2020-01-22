//======================================================
// File Name	: GameObjectManager.h
// Summary		: ゲームオブジェクトマネージャー
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

		// メンバ変数
		GameObjectList m_objects;
		GameObjectList m_objectQueue;
		// 追従カメラ
		std::unique_ptr<FollowCamera> m_camera;

	public:

		// コンストラクタ・デストラクタ
		GameObjectManager();
		~GameObjectManager();

		// メンバ関数
		void Update();
		void Render();
		void Add(GameObjectPtr&& object);
		std::vector<GameObject*> Find(const std::string& tag) const;
		std::vector<GameObject*> GetGameObjects()const;
		// アクセッサ
		FollowCamera* GetCamera()
		{
			return m_camera.get();
		}
};

