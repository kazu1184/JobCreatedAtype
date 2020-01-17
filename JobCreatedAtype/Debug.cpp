#include "pch.h"

#include <Keyboard.h>

#include "Debug.h"
#include "Transform.h"
#include "GameContext.h"
#include "DeviceResources.h"
#include "Component.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "GameObjectManager.h"
#include "FollowCamera.h"

Debug::Debug()
	:GameObject("Debug")
{
	m_transform.reset(AddComponent<Transform>());
	GameContext<CollisionManager>::Get()->Add("Sphere",AddComponent<SphereCollider>());

	m_box = DirectX::GeometricPrimitive::CreateSphere(GameContext<DX::DeviceResources>().Get()->GetD3DDeviceContext());

	flag = false;
}


Debug::~Debug()
{
}

void Debug::Update()
{
	GameContext<GameObjectManager>::Get()->GetCamera()->Update();

	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	DirectX::SimpleMath::Vector3 vel;

	if (keyState.IsKeyDown(DirectX::Keyboard::Left))
	{
		vel.x -= 0.1f;
	}

	if (keyState.IsKeyDown(DirectX::Keyboard::Right))
	{
		vel.x += 0.1f;
	}

	m_transform->SetPosition(m_transform->GetPosition() + vel);

	GameObject::Update();

	flag = false;
}

void Debug::Render()
{
	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	if(flag)
		m_box->Draw(m_transform->GetWorld(), camera->GetView(),camera->GetProjection(),DirectX::Colors::Green);
	else
		m_box->Draw(m_transform->GetWorld(), camera->GetView(), camera->GetProjection(), DirectX::Colors::Red);
}

void Debug::OnCollision(GameObject * object)
{
	object;
	flag = true;
}
