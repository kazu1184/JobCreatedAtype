#include "pch.h"
#include "Goal.h"

#include "GameContext.h"
#include "DeviceResources.h"
#include "Effects.h" 
#include "CommonStates.h"
#include "Transform.h"
#include "FollowCamera.h"
#include "GameObjectManager.h"
#include "GameStateManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "ModelMap.h"
#include "MapPosition.h"
#include "Coin.h"
#include "Player.h"

#include "ADX2LE\Adx2Le.h"
#include "Resources\Audio\bgm_acf.h"

Goal::Goal()
	: GameObject("Goal")
{
	ID3D11Device* device = GameContext<DX::DeviceResources>::Get()->GetD3DDevice();
	// モデルの読み込み
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(device);
	// テクスチャの読み込みパス指定 
	factory->SetDirectory(L"Resources/Models");

	m_goalModel = DirectX::Model::CreateFromCMO(
		device, L"Resources/Models/Village_Gate.cmo",
		*factory
	);
	delete factory;

	m_flag = false;

	// 位置情報の追加
	m_transform = AddComponent<Transform>();
	m_transform->SetScale(DirectX::SimpleMath::Vector3(0.5f, 1.0f, 1.0f));
	m_transform->SetPosition(DirectX::SimpleMath::Vector3(10.0f, 0.0f, 10.0f));

	// 当たり判定の追加
	BoxCollider* box = AddComponent<BoxCollider>();
	box->SetSize(DirectX::SimpleMath::Vector3(3.0f, 5.0f, 1.0f));
	box->SetOffset(DirectX::SimpleMath::Vector3(0.0f, 2.0f, 0.0f));
	GameContext<CollisionManager>::Get()->Add(this->GetTag(), box);

}


Goal::~Goal()
{
}

void Goal::Update()
{
	if (!m_activeFlag)
		return;
	GameObject::Update();
}

void Goal::Render()
{
	if (!m_activeFlag)
		return;

	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();

	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	

	// 描画
	m_goalModel->Draw(deviceResources->GetD3DDeviceContext(), *GameContext<DirectX::CommonStates>::Get(),
		m_transform->GetWorld(), camera->GetView(), camera->GetProjection());
}

void Goal::OnCollision(GameObject * object)
{
	if (!m_activeFlag)
		return;

	if (static_cast<Player*>(object)->GetCoin() != nullptr)
	{
		if (!m_flag)
		{
			m_flag = true;
			GameContext<Adx2Le>::Get()->Play(CRI_BGM_ACF_AISACCONTROL_AISACCONTROL_03);
		}
		if (GameContext<Adx2Le>::Get()->IsPlayEndedByID(CRI_BGM_ACF_AISACCONTROL_AISACCONTROL_03))
			GameContext<GameStateManager>::Get()->RequestState("Result");
	}
}
