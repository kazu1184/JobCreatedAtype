//======================================================
// File Name	: Component.h
// Summary		: コンポーネント基底クラス
// Date			: 2019/12/10
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include <string>

class GameObject;

class Component
{
	// メンバ変数
	protected: 

		// 親ポインタ
		GameObject* m_parent;

	public:
		// コンストラクタ・デストラクタ

		Component();
		virtual ~Component() = default;

		//　メンバ関数

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		// アクセッサ

		void SetParent(GameObject* obj)
		{
			m_parent = obj;
		}

		GameObject* GetParent() const
		{
			return m_parent;
		}
};

