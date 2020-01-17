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
		virtual void Initialize(GameObject* obj) = 0;
		virtual void Update(DirectX::Keyboard::KeyboardStateTracker* keyboard) = 0;
		virtual void Finalize() = 0;
};

