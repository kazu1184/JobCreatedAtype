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
	, m_drawFlag(false)
{
	ID3D11Device* device = GameContext<DX::DeviceResources>::Get()->GetD3DDevice();
	// ���f���̓ǂݍ���
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(device);
	// �e�N�X�`���̓ǂݍ��݃p�X�w�� 
	factory->SetDirectory(L"Resources/Models");

	m_mapObjs = DirectX::Model::CreateFromCMO(
		device, L"Resources/Models/building.cmo",
		*factory
	);
	delete factory;

	// �ʒu���̒ǉ�
	m_transform = AddComponent<Transform>();
	// �����蔻��̒ǉ�
	BoxCollider* box = AddComponent<BoxCollider>();
	box->SetSize(DirectX::SimpleMath::Vector3(ModelMap::MAP_SIZE, 5.0f, ModelMap::MAP_SIZE));
	box->SetOffset(DirectX::SimpleMath::Vector3(0.0f,2.5f,0.0f));
	GameContext<CollisionManager>::Get()->Add(GetTag(), box);

	BoxCollider* rayCheck = AddComponent<BoxCollider>();
	rayCheck->SetSize(DirectX::SimpleMath::Vector3(2.5f, 5.0f, 2.5f));
	rayCheck->SetOffset(DirectX::SimpleMath::Vector3(0.0f, 2.5f, 0.0f));
	GameContext<CollisionManager>::Get()->Add("RayCheck", rayCheck);
}


Building::~Building()
{
}

void Building::Update()
{
	//m_activeFlag = true;
	if (!m_activeFlag)
		return;
	GameObject::Update();
	m_drawFlag = false;
}

void Building::Render()
{
	if (!m_activeFlag)
		return;
	GameObject::Render();
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();

	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	// �`��
	m_mapObjs->Draw(deviceResources->GetD3DDeviceContext(), *GameContext<DirectX::CommonStates>::Get(),
		m_transform->GetWorld(), camera->GetView(), camera->GetProjection(), m_drawFlag);

}

void Building::OnCollision(GameObject * object)
{
	if (object->GetTag() == "DrawOff")
		m_drawFlag = true;
}
