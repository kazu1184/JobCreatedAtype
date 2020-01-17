//======================================================
// File Name	: CharacterState.h
// Summary		: Stateパターン（基底クラス）
// Date			: 2019/12/29
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameObject.h"

#include <Keyboard.h>

class CharacterState
{
	public:

		// コンストラクタ・デストラクタ
		CharacterState() = default;
		virtual ~CharacterState() = default;

		// メンバ関数
		virtual bool Initialize(GameObject* obj) = 0;
		virtual bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr) = 0;
		virtual bool Finalize() = 0;
};

