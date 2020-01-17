#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"

GameObject::GameObject(const std::string& tag)
	: m_componentList()
	, m_deleteFlag(false)
	, m_tag(tag)
	, m_transform()
{
}


GameObject::~GameObject()
{
	for (Component* com : m_componentList)
	{
		if (com != nullptr)
			delete com;
	}
	m_componentList.clear();

	m_transform = nullptr;
}

void GameObject::Update()
{
	// Update中はAddの効果を受けない
	auto com = m_componentList;
	// コンポーネントの更新
	for (Component* component : com)
	{
		component->Update();
	}
}

void GameObject::Render()
{
	// コンポーネントの描画
	for (Component* component : m_componentList)
	{
		component->Render();
	}
}

void GameObject::OnCollision(GameObject * object)
{
	object;
}

void GameObject::Invalidate()
{
	m_deleteFlag = true;
}
