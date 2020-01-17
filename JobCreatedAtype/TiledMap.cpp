#include "pch.h"
#include "TiledMap.h"

#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>



// 文字列をint型配列に変換する
std::vector<int> TiledMap::Split(const std::string& line, const char separator) 
{
	std::stringstream stringStream(line);
	std::vector<int> elements;
	std::string element;

	// ストリームから1行分の文字列を読み込む
	while (getline(stringStream, element, separator))
	{
		// 文字列をint型の数値に変換して配列に追加する
		elements.emplace_back(stoi(element));
	}
	// int型配列を返す
	return elements;
}

// マップを読み込む
bool TiledMap::Load(const std::string& filename)
{
	// 入力ストリーム
	std::ifstream wifs;
	// ストリームから入力された文字列
	std::string line;

	// マップデータをオープンする
	wifs.open(filename);
	// マップをオープンできたかどうか検証する
	if (wifs.is_open())
	{
		// マップの行数を読み込む
		getline(wifs, line);
		// 行数を設定する
		m_rowNum = stoi(line);
		// マップの列数を読み込む
		getline(wifs, line);
		// 列数を設定する
		m_columnNum = stoi(line);
		// マップをリセットする
		ResetMap();
		// 行配列を確保する
		m_map.resize(m_rowNum);
		for (int row = 0; row < m_rowNum; row++)
		{
			// 列配列を確保する
			m_map[row].resize(m_columnNum);
		}
		// マップファイルからマップデータを読み込む
		for (int row = 0; row < m_rowNum; row++)
		{
			// 一行分のマップデータを宣言する
			std::vector<int> rowArray;
			// 一行分の文字列を読み込む
			getline(wifs, line);
			// 文字列をint型配列に変換する
			rowArray = Split(line, ',');
			// 読み込んだマップデータをチェックする
			if (rowArray.size() != m_columnNum)
				return false;
			for (int column = 0; column < m_columnNum; column++)
			{
				// マップ属性をmap[row][column]に代入する
				m_map[row][column] = rowArray[column];
			}
		}
		// ストリームをクローズする
		wifs.close();
		return true;
	}
	else
		return false;
}

// マップをリセットする
void TiledMap::ResetMap()
{
	// マップを破棄する
	m_map.clear();
}

TiledMap::TiledMap()
{

}

// デストラクタ
TiledMap::~TiledMap()
{
	// マップを破棄する
	m_map.clear();
}

