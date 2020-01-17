#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string>

//#include "Node.h"

class TiledMap
{
	public: // �񋓑��̒�`

			// �}�b�v����
		enum MAP_ATTRIBUTE 
		{
			O = 1,
			P = 0 
		};

	private:
		// �}�b�v�s��
		int m_rowNum;
		// �}�b�v��
		int m_columnNum;
		// int�^��vector�z���錾����
		std::vector<std::vector<int>> m_map;

	public: // �����o�֐�

		// �R���X�g���N�^
		TiledMap();
		// �f�X�g���N�^
		~TiledMap();

		// �������int�^�z��ɕϊ�����
		std::vector<int> Split(const std::string& line, const char separator);
		// �}�b�v��ǂݍ���
		bool Load(const std::string& filename);
		// �}�b�v�����Z�b�g����
		void ResetMap();


		// �}�b�v�s���擾����
		const int TiledMap::GetMapRow() const
		{
			return m_rowNum;
		}
	
		// �}�b�v����擾����
		const int TiledMap::GetMapColumn() const
		{
			return m_columnNum;
		}
	
		// �}�b�v�ւ̃|�C���^���擾����
		const std::vector<std::vector<int>>& GetMap() const
		{
			return m_map;
		}
};
