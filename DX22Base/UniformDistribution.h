/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	��l���z������`
	------------------------------------
	UniformDistribution.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/28 ���� takagi

========================================== */

#ifndef ___UNIFORM_DISTRIBUTION_H___	//Random.h�C���N���[�h�K�[�h
#define ___UNIFORM_DISTRIBUTION_H___

// =============== �C���N���[�h ===================
#include "Random.h"	//�e�̃w�b�_

// =============== �e���v���[�g�N���X��` ===================
template<class Random>
class TUniformDistribution :public CRandom	//����
{
public:
	TUniformDistribution(const Random& Min, const Random& Max);	//�R���X�g���N�^
private:
	const Random m_Min;	//�ŏ��l
	const Random m_Max;	//�ő�l
	Random Get();		//�����擾
};	//�e���v���[�g�N���X�F��l�����̗�������

// =============== ����e���v���[�g�N���X��` ===================
template<>
class TUniformDistribution<int> :public CRandom<int>	//����
{
public:
	TUniformDistribution(const int& Min, const int& Max);	//�R���X�g���N�^
private:
	const int m_Min;	//�ŏ��l
	const int m_Max;	//�ő�l
	int Get();			//�����擾
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
TUniformDistribution<Random>::TUniformDistribution(const Random & Min, const Random & Max)
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
Random TUniformDistribution<Random>::Get()
{
	// =============== �� ===================
	return static_cast<Random>(std::uniform_real_distribution{ Min, Max }(ms_Engine));	//��������
}

#endif // !___UNIFORM_DISTRIBUTION_H___