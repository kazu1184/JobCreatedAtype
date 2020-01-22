#include "pch.h"
#include "Coin.h"

#include <Effects.h>
#include "DeviceResources.h"

#include "Transform.h"
#include "Player.h"
#include "MapPosition.h"
#include "ModelMap.h"
#include "GameContext.h"
#include "SphereCollider.h"
#include "FollowCamera.h"
#include "CollisionManager.h"
#include "GameObjectManager.h"
#include "GameStateManager.h"

#include "ADX2LE\Adx2Le.h"
#include "Resources\Audio\bgm_acf.h"

Coin::Coin()
	: GameObject("Coin")
{
	ID3D11Device* device = GameContext<DX::DeviceResources>::Get()->GetD3DDevice();
	// モデルデータの読み込み
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(device);
	// テクスチャの読み込みパス指定 
	factory->SetDirectory(L"Resources/Models");

	m_coinModel = DirectX::Model::CreateFromCMO(device, L"Resources\\Models\\coin.cmo", *factory);
	delete factory;

	MapPosition* pos = AddComponent<MapPosition>();
	pos->SetMapPosition(1, 16);
	m_transform = AddComponent<Transform>();
	m_transform->SetPosition(DirectX::SimpleMath::Vector3(pos->GetX() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2, 2.0f, pos->GetY() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2));
	m_transform->SetRotation(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 90.0f));
	m_transform->SetScale(DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.1f));

	SphereCollider* sphere = AddComponent<SphereCollider>();
	sphere->SetRadius(3.0f);
	GameContext<CollisionManager>::Get()->Add("Coin", sphere);
}


Coin::~Coin()
{
}

void Coin::Update()
{
	if (!m_activeFlag)
		return;
	// コンポーネントの更新
	GameObject::Update();
}

void Coin::Render()
{
	if (!m_activeFlag)
		return;

	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();

	// プレイヤーモデルの描画
	m_coinModel->Draw(deviceResources->GetD3DDeviceContext(),
		*GameContext<DirectX::CommonStates>::Get(),
		m_transform->GetWorld(), camera->GetView(), camera->GetProjection());
}

void Coin::OnCollision(GameObject * object)
{
	if (!m_activeFlag)
		return;

	m_activeFlag = false;
	static_cast<Player*>(object)->SetCoin(this);
	GameContext<Adx2Le>::Get()->Play(CRI_BGM_ACF_AISACCONTROL_AISACCONTROL_02);
	GetComponent<SphereCollider>()->SetRadius(0.0f);
}
