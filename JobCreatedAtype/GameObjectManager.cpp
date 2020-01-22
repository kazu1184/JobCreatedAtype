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
	// �J�����̃A�b�v�f�[�g
	m_camera->Update();
	// �����Ɉ�v���邷�ׂĂ̗v�f���폜
	m_objects.remove_if(std::mem_fn(&GameObject::IsInvalid));

	if (!m_objectQueue.empty())
	{
		// �v�f�̈ړ�
		m_objects.splice(m_objects.end(), m_objectQueue);
	}

	for (GameObjectPtr& object : m_objects)
	{
		object->Update();
	}
}

void GameObjectManager::Render()
{
	// �`��
	for (GameObjectPtr& object : m_objects)
	{
		object->Render();
	}
}

void GameObjectManager::Add(GameObjectPtr && object)
{
	// �ǉ�
	m_objectQueue.push_back(std::move(object));
}

std::vector<GameObject*> GameObjectManager::Find(const std::string & tag) const
{
	std::vector<GameObject*> result;

	// �^�O�������Ȃ�
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