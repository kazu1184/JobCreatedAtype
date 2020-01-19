//======================================================
// File Name	: PlayState.h
// Summary		: �v���C�X�e�C�g
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameState.h"

#include "Model.h" 

class GameObjectManager;
class CollisionManager;
class Adx2Le;

class PlayState : public GameState
{
	private:

		// �����o�ϐ�

		// �I�u�W�F�N�g�}�l�[�W���[
		std::unique_ptr<GameObjectManager> m_objectManager;
		// �R���W�����}�l�[�W���[
		std::unique_ptr<CollisionManager> m_collisionManager;
		//�X�J�C�h�[��
		std::unique_ptr<DirectX::Model>   m_pSkyDoom;
		// �I�[�f�B�I
		std::unique_ptr<Adx2Le> m_audio;

	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		PlayState();
		virtual ~PlayState();

		// �����o�֐�
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Finalize() override;
};

