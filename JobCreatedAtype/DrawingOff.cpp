#include "pch.h"
#include "DrawingOff.h"

#include "Player.h"
#include "RayCollider.h"
#include "Transform.h"
#include "GameContext.h"
#include "FollowCamera.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "DeviceResources.h"

const float DrawingOff::DROW_LENGTH = 30;

DrawingOff::DrawingOff(Player* player)
	: GameObject("DrawOff")
	, m_player(player)
{
	// プリミティブオブジェクト生成
	m_pLinePrimitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(GameContext <DX::DeviceResources>::Get()->GetD3DDeviceContext());

	m_transform = AddComponent<Transform>();

	m_ray = AddComponent<RayCollider>();
	m_ray->SetLength(FollowCamera::TARGET_TO_EYE_VEC.z);
	GameContext<CollisionManager>::Get()->Add(GetTag(), m_ray);
}


DrawingOff::~DrawingOff()
{
}

void DrawingOff::Update()
{
	if (!m_activeFlag)
		return;
	GameObject::Update();

	m_transform->SetPosition(m_player->GetTransform()->GetPosition());
	// カメラの更新
	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	// 当たり判定の更新
	m_ray->SetOffset(- camera->getEye() / 2);
	m_ray->SetStartRay(camera->getEye() + m_transform->GetPosition());
	m_ray->SetEndRay(-DirectX::SimpleMath::Vector3(camera->getEye().x,1.0f,camera->getEye().z));

	auto objVector = GameContext<GameObjectManager>::Get()->GetGameObjects();

	for (auto obj : objVector)
	{
		Transform* pos = obj->GetTransform();
		if (pos != nullptr && obj->GetTag() != "Coin")
		{
			float length = (pos->GetPosition() - m_player->GetTransform()->GetPosition()).Length();

			if (length <= DROW_LENGTH)
				obj->SetActive(true);
			else
				obj->SetActive(false);
		}
	}
}

void DrawingOff::Render()
{
	if (!m_activeFlag)
		return;
	m_pLinePrimitiveBatch->Begin();
	DirectX::VertexPositionColor a, b;
	a.position = m_ray->GetStartRay();
	b.position = m_transform->GetPosition();
	a.color = b.color = DirectX::SimpleMath::Vector4::Zero;

	m_pLinePrimitiveBatch->DrawLine(a, b);

	m_pLinePrimitiveBatch->End();

}

void DrawingOff::OnCollision(GameObject * object)
{
	if (!m_activeFlag)
		return;
}
