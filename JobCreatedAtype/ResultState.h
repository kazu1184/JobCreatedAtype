//======================================================
// File Name	: ResultState.h
// Summary		: リザルトステイト
// Date			: 2019/01/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameState.h"

class ResultState : public GameState
{
	private:
		// Debugカウント
		int m_count;
	
	public:
		// コンストラクタ・デストラクタ
		ResultState();
		virtual ~ResultState();

		// メンバ関数
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Finalize() override;
};

