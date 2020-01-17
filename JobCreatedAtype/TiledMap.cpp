#include "pch.h"
#include "TiledMap.h"

#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>



// �������int�^�z��ɕϊ�����
std::vector<int> TiledMap::Split(const std::string& line, const char separator) 
{
	std::stringstream stringStream(line);
	std::vector<int> elements;
	std::string element;

	// �X�g���[������1�s���̕������ǂݍ���
	while (getline(stringStream, element, separator))
	{
		// �������int�^�̐��l�ɕϊ����Ĕz��ɒǉ�����
		elements.emplace_back(stoi(element));
	}
	// int�^�z���Ԃ�
	return elements;
}

// �}�b�v��ǂݍ���
bool TiledMap::Load(const std::string& filename)
{
	// ���̓X�g���[��
	std::ifstream wifs;
	// �X�g���[��������͂��ꂽ������
	std::string line;

	// �}�b�v�f�[�^���I�[�v������
	wifs.open(filename);
	// �}�b�v���I�[�v���ł������ǂ������؂���
	if (wifs.is_open())
	{
		// �}�b�v�̍s����ǂݍ���
		getline(wifs, line);
		// �s����ݒ肷��
		m_rowNum = stoi(line);
		// �}�b�v�̗񐔂�ǂݍ���
		getline(wifs, line);
		// �񐔂�ݒ肷��
		m_columnNum = stoi(line);
		// �}�b�v�����Z�b�g����
		ResetMap();
		// �s�z����m�ۂ���
		m_map.resize(m_rowNum);
		for (int row = 0; row < m_rowNum; row++)
		{
			// ��z����m�ۂ���
			m_map[row].resize(m_columnNum);
		}
		// �}�b�v�t�@�C������}�b�v�f�[�^��ǂݍ���
		for (int row = 0; row < m_rowNum; row++)
		{
			// ��s���̃}�b�v�f�[�^��錾����
			std::vector<int> rowArray;
			// ��s���̕������ǂݍ���
			getline(wifs, line);
			// �������int�^�z��ɕϊ�����
			rowArray = Split(line, ',');
			// �ǂݍ��񂾃}�b�v�f�[�^���`�F�b�N����
			if (rowArray.size() != m_columnNum)
				return false;
			for (int column = 0; column < m_columnNum; column++)
			{
				// �}�b�v������map[row][column]�ɑ������
				m_map[row][column] = rowArray[column];
			}
		}
		// �X�g���[�����N���[�Y����
		wifs.close();
		return true;
	}
	else
		return false;
}

// �}�b�v�����Z�b�g����
void TiledMap::ResetMap()
{
	// �}�b�v��j������
	m_map.clear();
}

TiledMap::TiledMap()
{

}

// �f�X�g���N�^
TiledMap::~TiledMap()
{
	// �}�b�v��j������
	m_map.clear();
}

