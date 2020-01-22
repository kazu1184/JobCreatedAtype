#include "pch.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "FollowCamera.h"
#include "DebugFont.h"

GameObjectManager::GameObjectManager()
	: m_objects()
{
	m_camera = std::make_unique<FollowCamera>(DirectX::SimpleMath::Vector3::Zero);
}


GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Update()
{
	// カメラのアップデート
	m_camera->Update();
	// 条件に一致するすべての要素を削除
	m_objects.remove_if(std::mem_fn(&GameObject::IsInvalid));

	if (!m_objectQueue.empty())
	{
		// 要素の移動
		m_objects.splice(m_objects.end(), m_objectQueue);
	}

	for (GameObjectPtr& object : m_objects)
	{
		object->Update();
	}
}

void GameObjectManager::Render()
{
	// 描画
	for (GameObjectPtr& object : m_objects)
	{
		object->Render();
	}
}

void GameObjectManager::Add(GameObjectPtr && object)
{
	// 追加
	m_objectQueue.push_back(std::move(object));
}

std::vector<GameObject*> GameObjectManager::Find(const std::string & tag) const
{
	std::vector<GameObject*> result;

	// タグが同じなら
	for (const GameObjectPtr& object : m_objects)
	{
		if (object->GetTag() == tag)
		{
			result.push_back(object.get());
		}
	}

	for (const GameObjectPtr& object : m_objectQueue)
	{
		if (object->GetTag() == tag)
		{
			result.push_back(object.get());
		}
	}

	return result;
}