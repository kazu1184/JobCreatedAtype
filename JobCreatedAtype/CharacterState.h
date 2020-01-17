//======================================================
// File Name	: CharacterState.h
// Summary		: State�p�^�[���i���N���X�j
// Date			: 2019/12/29
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameObject.h"

#include <Keyboard.h>

class CharacterState
{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		CharacterState() = default;
		virtual ~CharacterState() = default;

		// �����o�֐�
		virtual bool Initialize(GameObject* obj) = 0;
		virtual bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr) = 0;
		virtual bool Finalize() = 0;
};

