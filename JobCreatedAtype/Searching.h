#pragma once
#include "TiledMap.h"
#include "A_Star.h"
#include "StepTimer.h"
#include "CharacterState.h"

class Enemy;
class MapPosition;

class Searching : public CharacterState
{
	private: // メンバ関数

		// Enemyオブジェクトへのポインタ
		Enemy* m_enemy;
	
		// マップファイル
		std::string m_mapFile;
		// タイルドマップ
		std::unique_ptr<TiledMap> m_tiledMap;
		// 最短経路探索
		std::unique_ptr<A_Star> m_pathFinding;
		// 最短経路
		std::vector<MapPosition*> m_route;
		// 開始位置
		MapPosition* m_startPosition;
		// 終了位置
		MapPosition* m_endPosition;

	public: // メンバ関数
		
			// コンストラクタ
			Searching();
			// 初期化する
			bool Initialize(GameObject* object)override;
			// 更新する
			bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
			// 後始末をする
			bool Finalize()override;

			// 開始位置を取得する
			MapPosition* GetStartPosition()
			{
				return m_startPosition;
			}
			// 終了位置を取得する
			MapPosition* GetEndPosition()
			{
				return m_endPosition;
			}

			// 最短経路を取得する
			std::vector<MapPosition*> GetRoute() const
			{
				return m_route;
			}
};