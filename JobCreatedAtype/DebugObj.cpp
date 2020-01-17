#include "pch.h"

#include <Keyboard.h>

#include "DebugObj.h"
#include "Transform.h"
#include "GameContext.h"
#include "DeviceResources.h"
#include "Component.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "GameObjectManager.h"
#include "FollowCamera.h"

DebugObj::DebugObj()
	:GameObject("DebugObj")
{
	m_transform.reset(AddComponent<Transform>());
	GameContext<CollisionManager>::Get()->Add("Box", AddComponent<BoxCollider>());

	m_box = DirectX::GeometricPrimitive::CreateCube(GameContext<DX::DeviceResources>().Get()->GetD3DDeviceContext());

	m_transform->SetPosition(DirectX::SimpleMath::Vector3(2.f, 0.f, 0.f));

	flag = false;
}


DebugObj::~DebugObj()
{
}

void DebugObj::Update()
{
	GameContext<GameObjectManager>::Get()->GetCamera()->Update();

	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	GameObject::Update();

	flag = false;
}

void DebugObj::Render()
{
	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	if (flag)
		m_box->Draw(m_transform->GetWorld(), camera->GetView(), camera->GetProjection(), DirectX::Colors::Green);
	else
		m_box->Draw(m_transform->GetWorld(), camera->GetView(), camera->GetProjection(), DirectX::Colors::Red);
}

void DebugObj::OnCollision(GameObject * object)
{
	object;
	flag = true;
}
