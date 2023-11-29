/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	����������`
	------------------------------------
	Random.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/28 ���� takagi

========================================== */
/* ========================================
	���݈Ӌ`
	------------------------------------
	��{#include <random>�̋@�\�����̂܂܎g�����A
	�s�m���(=�V�[�h�l�ɂ���Ċm�肵�Ȃ�)����������ł���std::random_device��()���Z�q�������𐶐�����Ƃ��������d���Ȃ�̂ŁA
	������g�p���č��^�������������std::mt19937��ÓI�Ɋm�ۂ��Ă������߂ɑ��݁B
========================================== */
//MIGHT_DO:�V�[�h�V�[�P���X�̓K�p�H

#ifndef ___RANDOM_H___	//Random.h�C���N���[�h�K�[�h
#define ___RANDOM_H___

// =============== �C���N���[�h ===================
#include <random>	//��������

// =============== �N���X��` ===================
class CRandom
{
public:
	static std::mt19937& GetEngine();	//������擾
private:
	static std::random_device ms_Seed;	//�񌈒�I�ɃV�[�h�l����
	static std::mt19937 ms_Engine;		//�V�[�h�l�ɂ��������č쐬����闐��
};	//��������

#endif // !___RANDOM_H___