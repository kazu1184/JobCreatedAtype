#pragma once
#include "CharacterState.h"
#include "TiledMap.h"
#include "A_Star.h"
#include "StepTimer.h"

class MapPosition;
class Enemy;

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
			Searching(const std::string& mapFile);
			// 初期化する
			void Initialize(GameObject* object)override;
			// 更新する
			void Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)override;
			// 後始末をする
			void Finalize()override;

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

//
//class Searching : public IState
//{
//public:
//	// 開始位置を取得する
//	Position GetStartPosition()
//	{
//		return m_startPosition;
//	}
//	// 終了位置を取得する
//	Position GetEndPosition()
//	{
//		return m_endPosition;
//	}
//
//	// 最短経路を取得する
//	std::vector<Position> GetRoute() const
//	{
//		return m_route;
//	}
//
//	// コンストラクタ
//	Searching(const std::string& mapFile);
//	// 初期化する
//	int Initialize(Enemy* object)override;
//	// 更新する
//	int Update(const DX::StepTimer& timer)override;
//	// 描画する
//	void Render()override;
//	// 後始末をする
//	void Finalize()override;
//private:
//	// Enemyオブジェクトへのポインタ
//	Enemy* m_enemy;
//
//	// マップファイル
//	std::string m_mapFile;
//	// タイルドマップ
//	std::unique_ptr<TiledMap> m_tiledMap;
//	// 最短経路探索
//	std::unique_ptr<A_Star> m_pathFinding;
//	// 最短経路
//	std::vector<Position> m_route;
//	// 開始位置
//	Position m_startPosition;
//	// 終了位置
//	Position m_endPosition;
//};
//
//
