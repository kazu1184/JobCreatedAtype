#pragma once
#include "Node.h"
#include "TiledMap.h"
#include "vector"
#include "MapPosition.h"

class A_Star
{
	public:	// 定数の定義

		// 探索近隣行数
		static const int NEIGHBOR_ROW_NUM = 4;
		// 探索近隣列数
		static const int NEIGHBOR_COLUMN_NUM = 2;
		// 行列
		enum ROW_COLUMN { ROW = 0, COLUMN = 1 };
		// 行列オフセット
		const int OFFSET[NEIGHBOR_ROW_NUM][NEIGHBOR_COLUMN_NUM] = 
		{ 
			{ -1,  0 },
			{  0, -1 },
			{  0,  1 },
			{  1,  0 }
		};

	private: // メンバ変数

		// マップ行
		int m_mapRow;
		// マップ列
		int m_mapColumn;
		// オープンリスト
		std::vector<Node*> m_openList;
		// クローズドリスト
		std::vector<Node*> m_closedList;
	
		// TiledMapオブジェクトへのポインタ
		TiledMap* m_tiledMap;
		// Nodeオブジェクトへのポインタを格納するマップ配列
		std::vector<std::vector<Node*>> m_astarMap;

	public: // メンバ関数

		// コンストラクタ
		A_Star(TiledMap* tiledMap);
		// デストラクタ
		~A_Star();

		// 2点間の距離を計算する
		float Distance(MapPosition* position, MapPosition* position1);
		// 最短経路オブジェクトを初期化する
		bool Initialize();
		// Nodeオブジェクトマップをクリアする
		void ClearMap();
		// 最短経路アルゴリズムを実行する
		bool Search(MapPosition* startPosition, MapPosition* endPosition);
		// 最短経路を返す
		std::vector<MapPosition*> GetShortestPath(MapPosition* startPosition, MapPosition* endPosition);
		// 後始末をする
		void Finalize();
};

