#include "pch.h"
#include "Searching.h"
#include "Enemy.h"
#include "ModelMap.h"
#include "MapPosition.h"
#include "GameObjectManager.h"
#include "GameContext.h"

// コンストラクタ
Searching::Searching()
{
}


bool Searching::Initialize(GameObject* object)
{
	m_enemy = static_cast<Enemy*>(object);
	m_startPosition = new MapPosition(0, 0);
	m_endPosition = new MapPosition(0, 0);
	// マップの検索
	ModelMap* map = static_cast<ModelMap*>(GameContext<GameObjectManager>::Get()->Find("Map")[0]);
	// AStarオブジェクトを生成する
	m_pathFinding = std::make_unique<A_Star>(map->GetTiledMap());
	// AStarオブジェクトを初期化する
	m_pathFinding->Initialize();

	return true;
}

// 更新する
bool Searching::Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)
{
	MapPosition* sMap = m_enemy->GetStartPosition();
	MapPosition* eMap = m_enemy->GetEndPosition();
	// 開始位置を取得する
	m_startPosition->SetMapPosition(sMap->GetX(),sMap->GetY());
	// 終了位置を取得する
	m_endPosition->SetMapPosition(eMap->GetX(), eMap->GetY());
	// 最短経路を探索する
	if (m_pathFinding->Search(m_startPosition, m_endPosition) == false)
		return false;
	// 最短経路を取得する
	m_route = m_pathFinding->GetShortestPath(m_startPosition, m_endPosition);
	// マップをクリアする
	m_pathFinding->ClearMap();
	// エラーをチェックする
	if (m_route.size() == 0)
		return false;
	else
		return true;
}

// 後始末をする
bool Searching::Finalize() 
{
	// マップをクリアする
	m_pathFinding->ClearMap();
	// AStarオブジェクトを解放する
	m_pathFinding.reset();
	// Mapオブジェクトを解放する
	m_tiledMap.reset();
	// 開始位置と終了ポインタの削除
	delete m_startPosition;
	delete m_endPosition;

	return true;
}
