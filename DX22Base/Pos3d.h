/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�O�����ʒu���W���Ǘ�����e���v���[�g�N���X���`
	------------------------------------
	Pos3d.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/10/31 ���� takagi
	�E2023/11/02 �����v�Z�֐���return���ɕs�����Ă���'('��Y�� takagi
					�E������const�s���������E���x(����������)�ӎ��ň������Q�ƕ����ɕύX�E�R�����g�C�� takagi
	�E2023/11/03 Distance()�֐��̕s����C�� takagi
	�E2023/11/04 .cpp/.h�������������� takagi
	�E2023/11/07 �R�[�f�B���O�K��K�p takagi
	�E2023/11/09 �ϊ��R���X�g���N�^�쐬 takagi

========================================== */

#ifndef ___POS_3D_H___
#define ___POS_3D_H___

// =============== �C���N���[�h ===================
#include "TriType.h"	//�R�̓����^�����^

// =============== �e���v���[�g�N���X��` ===================
template<class Pos3d>
struct TPos3d :public TTriType<Pos3d>	//�e���v���[�g�N���X�F�ʒu
{
public:
	// ===�����o�֐��錾===
	TPos3d();												//�R���X�g���N�^
	TPos3d(const Pos3d& x, const Pos3d& y, const Pos3d& z);	//�����t���R���X�g���N�^
	TPos3d(const TTriType<Pos3d>& Tri);						//�ϊ��R���X�g���N�^
	TPos3d(const TPos3d& Obj);								//�R�s�[�R���X�g���N�^
	~TPos3d();												//�f�X�g���N�^
	Pos3d Distance(const TPos3d& Obj);						//�����v�Z
};	//�^�e���v���[�g

/* ========================================
	�R���X�g���N�^
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class Pos3d>	//�e���v���[�g�֐�����
TPos3d<Pos3d>::TPos3d()
	:TTriType<Pos3d>()	//�Ϗ�
{
}

/* ========================================
	�R���X�g���N�^
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�Fconst Pos3d & x�Fx����̈ʒu�̎Q��
	����2�Fconst Pos3d & y�Fy����̈ʒu�̎Q��
	����3�Fconst Pos3d & z�Fz����̈ʒu�̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class Pos3d>	//�e���v���[�g�֐�����
TPos3d<Pos3d>::TPos3d(const Pos3d & x, const Pos3d & y, const Pos3d & z)
	:TTriType<Pos3d>(x, y, z)	//�Ϗ�
{
}

/* ========================================
	�ϊ��R���X�g���N�^
	-------------------------------------
	���e�F�e�̌^����̃L���X�g���Z�q
	-------------------------------------
	����1�Fconst TTriType<Pos3d> & Tri�F�ϊ����̌^
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class Pos3d>
TPos3d<Pos3d>::TPos3d(const TTriType<Pos3d> & Tri)
{
	// =============== �i�[ ===================
	*this = Tri;	//�^�ϊ�
}

/* ========================================
	�R�s�[�R���X�g���N�^
	-------------------------------------
	���e�F�R�s�[���ɍs������
	-------------------------------------
	����1�Fconst TPos3d & Obj�F��������f�[�^���̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class Pos3d>	//�e���v���[�g�֐�����
TPos3d<Pos3d>::TPos3d(const TPos3d & Obj)
	:TTriType<Pos3d>(Obj)	//�Ϗ�
{
}

/* ========================================
	�f�X�g���N�^
	------------------------------------ -
	���e�F�j�����ɍs������
	------------------------------------ -
	����1�F�Ȃ�
	------------------------------------ -
	�ߒl�F�Ȃ�
=========================================== */
template<class Pos3d>	//�e���v���[�g�֐�����
TPos3d<Pos3d>::~TPos3d()
{
}

/* ========================================
	�����v�Z
	------------------------------------ -
	���e�F��_�̈ʒu�������Ƃɋ��������߂�
	------------------------------------ -
	����1�Fconst TPos3d & Obj�F���������߂�l�̎Q��
	------------------------------------ -
	�ߒl�F���g�ƈ����̋���
=========================================== */
template<class Pos3d>	//�e���v���[�g�֐�����
Pos3d TPos3d<Pos3d>::Distance(const TPos3d & Obj)
{
	// =============== �ϐ��錾 =======================
	TPos3d Temp((*this - Obj) ^ 2);	//�����Z�̌���

	// =============== �� =======================
	return (Pos3d)(pow((double)Temp.Total(), 0.5));	//�v�Z����
}

#endif // !___POS_3D_H___



//--- �������牺�͎��^�](cpp�ɂ����Ȃ��Ɠ����Ȃ��̂ŁA���������ꍇ���̃w�b�_��all�R�s�[����cpp�ɓ\��t���Ă�������) ---//
	//�I�F ������main�֐�������ꍇ�͕ʃv���W�F�N�g�Ŏ������A�ꎞ�I�ɃR�����g�A�E�g���Ă��������B
//#include <iostream>
//#include <string>
//
//int main()
//{
//	TPos3d<int> a;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//0,0,0�̃n�Y
//
//	a = TPos3d<int>(1, 1, 1);
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;
//
//	a = { 2, 2, 2 };
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;
//
//	a.x = 3;
//	a.y = 3;
//	a.z = 3;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;
//
//	TPos3d<int> b(4, 4, 4);
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;
//
//	a + b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//3,3,3�̃n�Y
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4�̃n�Y
//
//	a = b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//4,4,4�̃n�Y
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4�̃n�Y
//
//	a -= b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//8,8,8�̃n�Y
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4�̃n�Y
//
//	a ^= 2;	//�Öق̌^�L���X�g
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//64,64,64�̃n�Y
//
//	a ^= 0.5;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//8,8,8�̃n�Y
//
//	//std::cout << std::to_string(a.Distance(b)) << std::endl;	//12�̃n�Y
//
//	std::cin.get();
//
//	return 0;
//}