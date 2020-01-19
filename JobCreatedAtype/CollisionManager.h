//======================================================
// File Name	: CollisionManager.h
// Summary		: �R���W�����}�l�[�W���[
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
class RayCollider;

class CollisionManager final
{
	private:
		// using
	
		using ColliderList = std::vector<Collider*>;
		using ColliderGroupList = std::unordered_map<std::string, ColliderList>;
		using CollisionGroup = std::pair<std::string, std::string>;
		using CollisionGroupList = std::list<CollisionGroup>;
	
		// �����o�ϐ�

		ColliderGroupList  m_colliderGroups;
		CollisionGroupList m_collisionGroups;

	public:

		//	�R���X�g���N�^�E�f�X�g���N�^

		CollisionManager();
		~CollisionManager();

		//	�����o�֐�

		// �R���C�_�[�̓o�^
		void Add(const std::string& groupName, Collider* collider);
		// �Փˋ���
		void AllowCollision(const std::string& groupName1, const std::string& groupName2);
		// �����蔻��i�ʂ��j
		void DetectCollision();
		void DetectCollision(const ColliderList& colliders);
		void DetectCollision(const ColliderList& colliders1, const ColliderList& colliders2);
		// ���ꂼ��̓����蔻��(�v�Z����)
		static bool IsCollided(const SphereCollider* collider1, const SphereCollider* collider2);
		static bool IsCollided(const BoxCollider*    collider1, const BoxCollider*    collider2);
		static bool IsCollided(const SphereCollider* collider1, const BoxCollider*    collider2);
		static bool IsCollided(const BoxCollider*    collider1, const SphereCollider* collider2);
		static bool IsCollided(const BoxCollider*    collider1, const RayCollider*    collider2);
		static bool IsCollided(const RayCollider*    collider1, const BoxCollider*    collider2);
		static bool IsCollided(const SphereCollider* collider1, const RayCollider*    collider2);
		static bool IsCollided(const RayCollider*    collider1, const SphereCollider* collider2);

		static float SqDistPointBox(const DirectX::SimpleMath::Vector3 & p, const BoxCollider * b);
		static float SqDistPointSegment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c);
		// �Q�̐����̍ŒZ�����̕�����Ԃ��֐� 
		static float ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1,
			DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2,
			float &s, float &t, DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2);
		// �N�����v�֐�
		static float Clamp(float n, float min, float max);
};

