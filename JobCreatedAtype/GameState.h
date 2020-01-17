//======================================================
// File Name	: GameState.h
// Summary		: �X�e�C�g(�������z�N���X)
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

class GameState
{
	public: 

		// �R���X�g���N�^�E�f�X�g���N�^
		GameState() = default;
		virtual ~GameState() = default;

		// �����o�֐�
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Finalize() = 0;
};