#include "pch.h"
#include "Searching.h"
#include "Enemy.h"
#include "ModelMap.h"
#include "MapPosition.h"

// コンストラクタ
Searching::Searching(const std::string& mapFile)
	: 
	m_mapFile(mapFile) 										// マップファイル
{
}

bool Searching::Initialize(GameObject* object)
{
	m_enemy = static_cast<Enemy*>(object);
	m_startPosition = new MapPosition(0, 0);
	m_endPosition = new MapPosition(0, 0);


	// TiledMapオブジェクトを生成する
	m_tiledMap = std::make_unique<TiledMap>();
	// TiledMapオブジェクトを初期化する
	m_tiledMap->Load(m_mapFile);
	// AStarオブジェクトを生成する
	m_pathFinding = std::make_unique<A_Star>(m_tiledMap.get());
	// AStarオブジェクトを初期化する
	m_pathFinding->Initialize();

	return true;
}

// 更新する
bool Searching::Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)
{
	// 開始位置を取得する
	m_startPosition = m_enemy->GetStartPosition();
	// 終了位置を取得する
	m_endPosition = m_enemy->GetEndPosition();
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

	return true;
}
