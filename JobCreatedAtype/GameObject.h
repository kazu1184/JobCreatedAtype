//======================================================
// File Name	: GameObject.h
// Summary		: ゲームオブジェクト基底クラス
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
		
		// 破壊フラグ
		bool m_deleteFlag;
		// タグ
		std::string m_tag;

	protected:

		// コンポーネントリスト
		std::list<Component*> m_componentList;
		// 位置・スケール
		Transform* m_transform;
		// アクティブフラグ
		bool m_activeFlag;

	public:

	// コンストラクタ・デストラクタ

		GameObject(const std::string& tag);
		~GameObject();

	// メンバ関数

		virtual void Update();
		virtual void Render();
		// 当たり判定
		virtual void OnCollision(GameObject* object);
		// 破壊フラグON
		void Invalidate();

		// アクセッサ

		// 現在のフラグをゲット
		bool IsInvalid() const { return m_deleteFlag; }

		std::string GetTag() const { return m_tag; }

		void SetActive(bool flag) { m_activeFlag = flag; }

		Transform* GetTransform()const { return m_transform; }

		// オブジェクトが持っているコンポーネントを追加
		template<typename T>
		T* AddComponent()
		{
			T* buff = new T();
			buff->SetParent(this);
			m_componentList.push_back(buff);
			buff->Initialize();
			return buff;
		}

		// オブジェクトが持っているコンポーネントを取得
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

