//======================================================
// File Name	: PauseState.h
// Summary		: ポーズステイト
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameState.h"

class PauseState :public GameState
{
	public:

		// コンストラクタ・デストラクタ
		PauseState();
		virtual ~PauseState();
	
		// メンバ関数
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Finalize() override;
};

