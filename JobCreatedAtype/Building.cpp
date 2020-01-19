#include "pch.h"
#include "Building.h"

#include "GameContext.h"
#include "DeviceResources.h"
#include "Effects.h" 
#include "CommonStates.h"
#include "Transform.h"
#include "FollowCamera.h"
#include "GameObjectManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "ModelMap.h"
#include "MapPosition.h"

Building::Building()
	: GameObject("Building")
{
	m_activeFlag = false;
	ID3D11Device* device = GameContext<DX::DeviceResources>::Get()->GetD3DDevice();
	// モデルの読み込み
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(device);
	// テクスチャの読み込みパス指定 
	factory->SetDirectory(L"Resources/Models");

	m_mapObjs = DirectX::Model::CreateFromCMO(
		device, L"Resources/Models/building.cmo",
		*factory
	);
	delete factory;

	// 位置情報の追加
	m_transform = AddComponent<Transform>();
	// 当たり判定の追加
	BoxCollider* box = AddComponent<BoxCollider>();
	box->SetSize(DirectX::SimpleMath::Vector3(ModelMap::MAP_SIZE, ModelMap::MAP_SIZE, ModelMap::MAP_SIZE));
	box->SetOffset(m_transform->GetPosition());
	GameContext<CollisionManager>::Get()->Add(GetTag(), box);
}


Building::~Building()
{
}

void Building::Update()
{
	GameObject::Update();
}

void Building::Render()
{
	if (!m_activeFlag)
		return;
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();

	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	// 描画
	m_mapObjs->Draw(deviceResources->GetD3DDeviceContext(), *GameContext<DirectX::CommonStates>::Get(),
		m_transform->GetWorld(), camera->GetView(), camera->GetProjection());

}

void Building::OnCollision(GameObject * object)
{
}
