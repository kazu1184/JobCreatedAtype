//======================================================
// File Name	: GameState.h
// Summary		: �X�e�C�g(�������z�N���X)
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once
// �C���N���[�h
#include <functional>
#include <memory>
#include <deque>
#include <string>
#include <unordered_map>

// �O���錾
class GameState;

class GameStateManager final
{
	// using

	private:
		// �V�[���̃X�^�b�N
		using GameStateStack = std::deque<std::unique_ptr<GameState>>;
		// �֐��I�u�W�F�N�g
		using GameStateFactory = std::function<std::unique_ptr<GameState>()>;
		// �֐��I�u�W�F�N�g�̓o�^
		using GameStateFactoryList = std::unordered_map<std::string, GameStateFactory>;

	// �����o�ϐ�

		// �֐��̔z��(�R���e�i)
		GameStateFactoryList m_stateFactories;
		// ���݂̃X�e�C�g
		GameStateStack       m_states;
		// �|�b�v�J�E���g
		int                  m_popCount;
		// ���̃V�[���̖��O
		std::string          m_nextStateName;

	// �����o�֐��i�v���C�x�[�g�j

		// �X�e�C�g�̐���
		template<typename State>
		static std::unique_ptr<GameState> CreateState();

		// �X�e�C�g�̕ύX
		void ChangeState();

	// �R���X�g���N�^�E�f�X�g���N�^
	public:
		GameStateManager();
		~GameStateManager();

	// �����o�֐��i�p�u���b�N�j
		
		// �X�e�C�g�̓o�^
		template<typename State>
		void RegisterState(const std::string& stateName);
		// �X�V
		void Update(float elapsedTime);
		// �`��
		void Render();
		// �X�e�C�g�̃��N�G�X�g
		void RequestState(const std::string& stateName);
		// �X�e�C�g�̃v�b�V��
		void PushState(const std::string& stateName);
		// �X�e�C�g�̃|�b�v
		void PopState(int count = 1);
};

template<typename State>
inline std::unique_ptr<GameState> GameStateManager::CreateState()
{
	return std::make_unique<State>();
}

template<typename State>
inline void GameStateManager::RegisterState(const std::string & stateName)
{
	m_stateFactories.insert(std::make_pair(stateName, CreateState<State>));
}
