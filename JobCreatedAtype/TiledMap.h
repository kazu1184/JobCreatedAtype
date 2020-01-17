#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string>

//#include "Node.h"

class TiledMap
{
	public: // 列挙隊の定義

			// マップ属性
		enum MAP_ATTRIBUTE 
		{
			O = 1,
			P = 0 
		};

	private:
		// マップ行数
		int m_rowNum;
		// マップ列数
		int m_columnNum;
		// int型のvector配列を宣言する
		std::vector<std::vector<int>> m_map;

	public: // メンバ関数

		// コンストラクタ
		TiledMap();
		// デストラクタ
		~TiledMap();

		// 文字列をint型配列に変換する
		std::vector<int> Split(const std::string& line, const char separator);
		// マップを読み込む
		bool Load(const std::string& filename);
		// マップをリセットする
		void ResetMap();


		// マップ行を取得する
		const int TiledMap::GetMapRow() const
		{
			return m_rowNum;
		}
	
		// マップ列を取得する
		const int TiledMap::GetMapColumn() const
		{
			return m_columnNum;
		}
	
		// マップへのポインタを取得する
		const std::vector<std::vector<int>>& GetMap() const
		{
			return m_map;
		}
};
