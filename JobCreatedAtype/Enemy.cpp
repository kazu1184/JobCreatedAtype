#include "pch.h"
#include "Enemy.h"

#include <Effects.h>
#include "DeviceResources.h"

#include "Transform.h"
#include "MapPosition.h"
#include "ModelMap.h"
#include "Player.h"
#include "GameContext.h"
#include "FollowCamera.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"

#include "CharacterState.h"
#include "Idling.h"
#include "Chasing.h"
#include "Searching.h"

Enemy::Enemy(Player * player)
	: GameObject("Enemy")
{
	// モデルデータの読み込み
	DirectX::EffectFactory fx(GameContext<DX::DeviceResources>::Get()->GetD3DDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_enemyModel = DirectX::Model::CreateFromCMO(GameContext<DX::DeviceResources>::Get()->GetD3DDevice(), L"Resources\\Models\\Enemy.cmo", fx);

	// Idlingオブジェクトを生成する
	m_idlingState = std::make_unique<Idling>();
	// Idlingオブジェクトを初期化する
	m_idlingState->Initialize(this);

	// Searchingオブジェクトを生成する
	m_searchingState = std::make_unique<Searching>();
	// Searchingオブジェクトを初期化する
	m_searchingState->Initialize(this);

	// Chasingオブジェクトを生成する
	m_chasingState = std::make_unique<Chasing>();
	// Chasingオブジェクトを初期化する
	m_chasingState->Initialize(this);

	// 現在の状態をアイドリング状態に設定する
	ChangeState(m_idlingState.get());
	
	// コンポーネントを追加
	m_transform = AddComponent<Transform>();
	m_startPosition = AddComponent<MapPosition>();
	m_endPosition = AddComponent<MapPosition>();
	// ポジションを補正する
	m_transform->SetPosition(DirectX::SimpleMath::Vector3(m_startPosition->GetX() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2, 0.0f, m_startPosition->GetY() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2));
	m_transform->SetScale(DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.1f));
	// プレイヤーポインタの代入
	m_target = player;

}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	// コンポーネントの更新
	GameObject::Update();

	//// 現在の状態を更新する
	//bool result = m_currentState->Update();

	//if (m_currentState == m_idlingState.get())
	//{
	//	// 開始位置の更新
	//	SetStartPosition(GetEndPosition());
	//	// 開始位置を取得する
	//	MapPosition* startPosition = GetStartPosition();
	//	// 敵の位置を設定する
	//	m_transform->SetPosition(DirectX::SimpleMath::Vector3(startPosition->GetX() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2, 0.0f, startPosition->GetY() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2));
	//	// 終了位置を設定する
	//	SetEndPosition(m_target->GetMapPosition());
	//	// 現在の状態をサーチ状態に設定する
	//	ChangeState(GetSearchingState());
	//}

	//// サーチ状態(最短経路の探索後)の更新後
	//if (m_currentState == m_searchingState.get())
	//{
	//	// サーチ状態が更新され、正常終了の場合
	//	if (result)
	//	{
	//		// 最短経路を取得する
	//		m_route = m_searchingState.get()->GetRoute();
	//		// 現在の状態を追跡状態に変更する
	//		ChangeState(m_chasingState.get());
	//	}
	//	else
	//	{
	//		// 現在の状態をアイドリング状態に変更する
	//		ChangeState(m_idlingState.get());
	//	}
	//}
	//// 追跡状態の更新後
	//else if (m_currentState == m_chasingState.get())
	//{
	//	// 追跡状態が更新され、正常終了の場合
	//	if (result)
	//	{
	//		// 追跡中(状態を変更しない)
	//	}
	//	else
	//	{
	//		// 追跡が終了したので現在の状態をアイドリング状態に変更する
	//		ChangeState(m_idlingState.get());
	//	}
	//}

}

void Enemy::Render()
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	// エネミーモデルの描画
	m_enemyModel->Draw(deviceResources->GetD3DDeviceContext(),
		*GameContext<DirectX::CommonStates>::Get(),
		m_transform->GetWorld(), camera->GetView(), camera->GetProjection());

}

void Enemy::OnCollision(GameObject * object)
{
}
