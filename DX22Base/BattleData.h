/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�퓬����`
	------------------------------------
	BattleData.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/12/07 ���� takagi
	�E2023/12/11 ���b�擾�ǉ� takagi

========================================== */
//TODO:�����悤�Ƀ����L���O�p�Ƃ������

#ifndef __BATTLE_DATA_H__	//BattleData.h�C���N���[�h�K�[�h
#define __BATTLE_DATA_H__

// =============== �C���N���[�h ===================
#include <string>	//�����񑀍�
#include <fstream>	//�t�@�C����p�X�g���[��

// =============== �\���̒�` ===================
typedef struct tagBattleData	//���[���h�s��Ɋւ����
{
public:
	// ===�����o�ϐ��錾===
	int nAliveTime;		//��������[s]
	int nKill;			//�|������
	int nTotalScore;	//�X�R�A���v�l
	int nStageNum;		//�v���C�����X�e�[�W�ԍ�
	std::string	sName;	//�v���C���[��
	// ===�v���g�^�C�v�錾===
	tagBattleData();																//�R���X�g���N�^
	tagBattleData(const int& nAliveTime, const int& nKill, const int& nTotalScore, const int & nStageNum);	//�����t���R���X�g���N�^
	tagBattleData(const tagBattleData& Obj);										//�R�s�[�R���X�g���N�^
	~tagBattleData();																//�f�X�g���N�^
	void Load();																	//�f�[�^�ǂݍ���
	void Save();																	//�f�[�^�ۑ�
	int GetMinute();																//���Q�b�^
	int GetSecond();																//�b�Q�b�^
	int GetCommaSecond();															//�~���b�Q�b�^
}BattleData;	//�����f�[�^

/* ========================================
	�ǂݍ��݉��Z�q
	------------------------------------ -
	���e�F�t�@�C���X�g���[������BattleData�^�̃f�[�^��ǂݍ���
	------------------------------------ -
	����1�Fstd::basic_fstream<CharT, Traits>& FileStream�F���͂���t�@�C���X�g���[��
	����2�FBattleData& Data�F���͂����f�[�^
	------------------------------------ -
	�ߒl�F�����̓��̓X�g���[���I�u�W�F�N�g
=========================================== */
template<typename CharT, typename Traits>	//�e���v���[�g�֐�����
std::basic_fstream<CharT, Traits>& operator>>(std::basic_fstream<CharT, Traits>& FileStream, BattleData& Data)
{
	// =============== �ǂݍ��� ===================
	FileStream >> Data.nAliveTime >> Data.nKill >> Data.nTotalScore >> Data.nStageNum;	//�錾���ɓǂݍ���

	// =============== �� ===================
	return FileStream;	//���͌��X�g���[��
}

/* ========================================
	�����o�����Z�q
	------------------------------------ -
	���e�F�t�@�C���X�g���[����BattleData�^�̃f�[�^�������o��
	------------------------------------ -
	����1�Fstd::basic_fstream<CharT, Traits>& FileStream�F�o�͂����t�@�C���X�g���[��
	����2�Fconst BattleData& Data�F�o�͂���f�[�^
	------------------------------------ -
	�ߒl�F�����̏o�̓X�g���[���I�u�W�F�N�g
=========================================== */
template<typename CharT, typename Traits>	//�e���v���[�g�֐�����
std::basic_fstream<CharT, Traits>& operator<<(std::basic_fstream<CharT, Traits>& FileStream, const BattleData& Data)
{
	// =============== �����o�� ===================
	FileStream << Data.nAliveTime << ' ' << Data.nKill << ' ' << Data.nTotalScore << ' ' << Data.nStageNum << std::endl;	//�錾���ɏ����o��

	// =============== �� ===================
	return FileStream;	//�o�͐�X�g���[��
}

#endif //!__BATTLE_DATA_H__