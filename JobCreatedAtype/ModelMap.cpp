#include "pch.h"
#include "ModelMap.h"

#include "GameContext.h"
#include "Transform.h"
#include "GameObjectManager.h"
#include "Building.h"
#include "Floor.h"
#include "MapPosition.h"

const float ModelMap::MAP_SIZE = 5.0f;

ModelMap::ModelMap()
	: GameObject("Map")
{
	// タイルマップの作成
	m_tiledMap = std::make_unique<TiledMap>();
	// マップデータのロード
	m_tiledMap->Load("Resources/StageData/map.csv");


	// マップの配置
	// 初期の固定値
	float offsetX = -MAP_SIZE / 2;
	float offsetY = 0;
	float offsetZ = -MAP_SIZE / 2;

	GameObjectManager* objManager = GameContext<GameObjectManager>::Get();

	for (int i = 0; i < m_tiledMap->GetMapRow(); i++)
	{
		for (int j = 0; j < m_tiledMap->GetMapColumn(); j++)
		{
			// データの取得
			int tileId = m_tiledMap->GetMap()[j][i];

			// 位置の計算
			float x = i * MAP_SIZE - offsetX;
			float z = j * MAP_SIZE - offsetZ;
		
			if (tileId == TiledMap::MAP_ATTRIBUTE::O)
			{
				std::unique_ptr<Building> buil = std::make_unique<Building>();
				buil->GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(x, offsetY, z));
				MapPosition* pos = buil->AddComponent<MapPosition>();
				pos->SetMapPosition(i, j);
				objManager->Add(std::move(buil));
			}
			else if (tileId == TiledMap::MAP_ATTRIBUTE::P)
			{
				std::unique_ptr<Floor> floor = std::make_unique<Floor>();
				floor->GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(x, offsetY, z));
				MapPosition* pos = floor->AddComponent<MapPosition>();
				pos->SetMapPosition(i, j);
				objManager->Add(std::move(floor));
			}
		}
	}


}


ModelMap::~ModelMap()
{
}

void ModelMap::Update()
{
}

void ModelMap::Render()
{
}

void ModelMap::OnCollision(GameObject * object)
{
}