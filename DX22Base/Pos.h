//Pos.h
//�ʒu���W���Ǘ�����e���v���[�g�N���X���`

//���X�V����
//2023/10/31	����
//2023/11/02	�����v�Z�֐���return���ɕs�����Ă���'('��Y��
				//�E������const�s���������E���x(����������)�ӎ��ň������Q�ƕ����ɕύX�E�R�����g�C��
//2023/11/03	Distance()�֐��̕s����C��
//2023/11/04	.cpp/.h��������������



//���C���N���[�h�K�[�h
#ifndef ___POS_H___
#define ___POS_H___

//���C���N���[�h��
#include "TriType.h"	//�R�̓����^�����^

//���e���v���[�g�N���X��`
template<class Pos>
class TPos :public TTriType<Pos>	//�e���v���[�g�N���X�F�ʒu
{
public:
	//���v���g�^�C�v�錾
	TPos();											//�R���X�g���N�^
	TPos(const Pos& x, const Pos& y, const Pos& z);	//�����t���R���X�g���N�^
	TPos(const TPos& Obj);							//�R�s�[�R���X�g���N�^
	~TPos();										//�f�X�g���N�^
	Pos Distance(const TPos& Obj);					//�����v�Z
};	//�^�e���v���[�g

/////
//���R���X�g���N�^
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//�T�v�F�������ɍs������
/////
template<class Pos>	//�e���v���[�g�֐�����
TPos<Pos>::TPos()
	:TTriType<Pos>()	//�Ϗ�
{
}

/////
//���R���X�g���N�^
//�����P�Fconst Pos & x�Fx����̈ʒu�̎Q��
//�����Q�Fconst Pos & y�Fy����̈ʒu�̎Q��
//�����R�Fconst Pos & z�Fz����̈ʒu�̎Q��
//�߂�l�F�Ȃ�
//�T�v�F�������ɍs������
/////
template<class Pos>	//�e���v���[�g�֐�����
TPos<Pos>::TPos(const Pos & x, const Pos & y, const Pos & z)
	:TTriType<Pos>(x, y, z)	//�Ϗ�
{
}

/////
//���R�s�[�R���X�g���N�^
//�����Fconst TPos & Obj�F��������f�[�^���̎Q��
//�߂�l�F�Ȃ�
//�T�v�F�R�s�[���ɍs������
/////
template<class Pos>	//�e���v���[�g�֐�����
TPos<Pos>::TPos(const TPos & Obj)
	:TTriType<Pos>(Obj)	//�Ϗ�
{
}

/////
//���f�X�g���N�^
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//�T�v�F�j�����ɍs������
/////
template<class Pos>	//�e���v���[�g�֐�����
TPos<Pos>::~TPos()
{
}

/////
//�������v�Z
//�����Fconst TPos & Obj�F���������߂�l�̎Q��
//�߂�l�F���g�ƈ����̋���
//�T�v�F��_�̈ʒu�������Ƃɋ��������߂�
/////
template<class Pos>	//�e���v���[�g�֐�����
Pos TPos<Pos>::Distance(const TPos & Obj)
{
	//���ϐ��錾
	TPos Temp(*this - *Obj);
	//����
	return (Pos)(pow((double)Temp.Total(), 0.5));	//�v�Z����
}

#endif // !___POS_H___



//--- �������牺�͎��^�](cpp�ɂ����Ȃ��Ɠ����Ȃ��̂ŁA���������ꍇ���̃w�b�_��all�R�s�[����cpp�ɓ\��t���Ă�������) ---//
	//�I�F ������main�֐�������ꍇ�͕ʃv���W�F�N�g�Ŏ������A�ꎞ�I�ɃR�����g�A�E�g���Ă��������B
//#include <iostream>
//#include <string>
//
//int main()
//{
//	TPos<int> a;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//0,0,0�̃n�Y
//
//	a = TPos<int>(1, 1, 1);
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
//	TPos<int> b(4, 4, 4);
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