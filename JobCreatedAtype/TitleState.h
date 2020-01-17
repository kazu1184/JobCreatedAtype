//======================================================
// File Name	: TitleState.h
// Summary		: タイトルステイト
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameState.h"

class TitleState : public GameState
{
	private: 

		// Debugカウント
		int m_count;

	public:

		// コンストラクタ・デストラクタ
		TitleState();
		virtual ~TitleState();

		// メンバ関数
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Finalize() override;
};

