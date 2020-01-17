//======================================================
// File Name	: CollisionManager.h
// Summary		: コリジョンマネージャー
// Date			: 2019/12/13
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include <vector>
#include <SimpleMath.h>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Collider.h"

class SphereCollider;
class BoxCollider;

class CollisionManager final
{
	private:
		// using
	
		using ColliderList = std::vector<Collider*>;
		using ColliderGroupList = std::unordered_map<std::string, ColliderList>;
		using CollisionGroup = std::pair<std::string, std::string>;
		using CollisionGroupList = std::list<CollisionGroup>;
	
		// メンバ変数

		ColliderGroupList  m_colliderGroups;
		CollisionGroupList m_collisionGroups;

	public:

		//	コンストラクタ・デストラクタ

		CollisionManager();
		~CollisionManager();

		//	メンバ関数

		// コライダーの登録
		void Add(const std::string& groupName, Collider* collider);
		// 衝突許可
		void AllowCollision(const std::string& groupName1, const std::string& groupName2);
		// 当たり判定（別け）
		void DetectCollision();
		void DetectCollision(const ColliderList& colliders);
		void DetectCollision(const ColliderList& colliders1, const ColliderList& colliders2);
		// それぞれの当たり判定(計算部分)
		static bool IsCollided(const SphereCollider* collider1, const SphereCollider* collider2);
		static bool IsCollided(const BoxCollider*    collider1, const BoxCollider*    collider2);
		static bool IsCollided(const SphereCollider* collider1, const BoxCollider*    collider2);
		static bool IsCollided(const BoxCollider*    collider1, const SphereCollider* collider2);
		static float SqDistPointBox(const DirectX::SimpleMath::Vector3 & p, const BoxCollider * b);
};

