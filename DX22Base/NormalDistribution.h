/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	��l���z������`
	------------------------------------
	NormalDistribution.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/28 ���� takagi

========================================== */

#ifndef ___NORMAL_DISTRIBUTION_H___	//Random.h�C���N���[�h�K�[�h
#define ___NORMAL_DISTRIBUTION_H___

// =============== �C���N���[�h ===================
#include "Random.h"	//�e�̃w�b�_

// =============== �e���v���[�g�N���X��` ===================
template<class Random>
class TNormalDistribution :public CRandom	//����
{
public:
	TNormalDistribution(const Random& Min, const Random& Max);	//�R���X�g���N�^
private:
	const Random m_Min;	//�ŏ��l
	const Random m_Max;	//�ő�l
	Random Get();		//�����擾
};	//�e���v���[�g�N���X�F��l�����̗�������

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�Fconst Random & Min�F�����̍ŏ��l(�͈͓�)
	����2�Fconst Random & Max�F�����̓V��(�͈͊O)
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class Random>	//�e���v���[�g�֐�����
TNormalDistribution<Random>::TNormalDistribution(const Random & Min, const Random & Max)
	:m_Min(Min)	//�ŏ��l
	,m_Max(Max)	//�ő�l
{
}

/* ========================================
	�����擾�֐�
	-------------------------------------
	���e�F���z�ɏ]�����������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class Random>	//�e���v���[�g�֐�����
Random TNormalDistribution<Random>::Get()
{
	// =============== �� ===================
	return static_cast<Random>(std::normal_distribution{}(ms_Engine));	//��������
}

#endif // !___NORMAL_DISTRIBUTION_H___