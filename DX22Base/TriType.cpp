//TriType.cpp
//�����^���R���e���v���[�g�N���X������

//���X�V����
//2023/10/26	����
//2023/10/31	�p���ɑΉ��E�R�����g�C���E�ׂ���ǉ�
//2023/11/02	�ׂ��������Z�q�ǉ��Epow�̒��g�𖾎��I�Ɍ^�L���X�g�E�ׂ���̈�����double��float
				//�E������const�s���������E���x(����������)�ӎ��ň������Q�ƕ����ɕύX�E�R�����g�C��
//2023/11/03	%���Z�q�g�p���ɁA�v�Z�Ɏg�p����l�������^�łȂ����Ƃ���������C���ETotal()�֐���ǉ�
//2023/11/04	.cpp/.h����



//���C���N���[�h��
#include "TriType.h"	//���g�̃w�b�_

/////
//���R���X�g���N�^
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//�T�v�F�������ɍs������
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType>::TTriType()
	:TTriType((TriType)0, (TriType)0, (TriType)0)	//�Ϗ�
{
}

/////
//���R���X�g���N�^
//�����P�Fconst TriType & x�F�P�߂̒l�̎Q��
//�����Q�Fconst TriType & y�F�Q�߂̒l�̎Q��
//�����R�Fconst TriType & z�F�R�߂̒l�̎Q��
//�߂�l�F�Ȃ�
//�T�v�F�������ɍs������
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType>::TTriType(const TriType & x, const TriType & y, const TriType & z)
{
	//��������
	this->x = x;	//�P�ߏ�����
	this->y = y;	//�Q�ߏ�����
	this->z = z;	//�R�ߏ�����
}

/////
//���R�s�[�R���X�g���N�^
//�����Fconst TTriType & Obj�F��������f�[�^���̎Q��
//�߂�l�F�Ȃ�
//�T�v�F�R�s�[���ɍs������
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType>::TTriType(const TTriType & Obj)
{
	//������
	this->x = Obj.x;	//�P�߂̃f�[�^�R�s�[
	this->y = Obj.y;	//�Q�߂̃f�[�^�R�s�[
	this->z = Obj.z;	//�R�߂̃f�[�^�R�s�[
}

/////
//���f�X�g���N�^
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//�T�v�F�j�����ɍs������
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType>::~TTriType()
{
}

/////
//�����v�֐�
//�����F�Ȃ�
//�߂�l�F�R�̃����o�[�ϐ��̍��v�l
//�T�v�F���g�̎��R�̃����o�[�ϐ������v����
/////
template<class TriType>	//�e���v���[�g�֐�����
TriType TTriType<TriType>::Total()
{
	//����
	return (this->x + this->y + this->z);	//���Z����
}

/////
//��������Z�q
//�����Fconst TTriType & Obj�F�������l�̎Q��
//�߂�l�F������s��ꂽ�������g
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɑ���������s��
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType>& TTriType<TriType>::operator=(const TTriType & Obj)
{
	//������
	this->x = Obj.x;	//�P�߂̃f�[�^�R�s�[
	this->y = Obj.y;	//�Q�߂̃f�[�^�R�s�[
	this->z = Obj.z;	//�R�߂̃f�[�^�R�s�[

	//����
	return	*this;	//���g�̎Q��
}

/////
//�����Z���Z�q
//�����Fconst TTriType & Obj�F���Z����l�̎Q��
//�߂�l�F���g�ƈ����̉��Z����
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɉ��Z�������s��
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator+(const TTriType & Obj)
{
	//����
	return { this->x + Obj.x, this->y + Obj.y, this->z + Obj.z };	//���Z����
}

/////
//�����Z������Z�q
//�����Fconst TTriType & Obj�F���Z����l�̎Q��
//�߂�l�F���������Z���ꂽ�������g
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɉ��Z�������s�������̂�������
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> & TTriType<TriType>::operator+=(const TTriType & Obj)
{
	//����
	return (*this = *this + Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/////
//�����Z���Z�q
//�����Fconst TTriType & Obj�F���Z����l�̎Q��
//�߂�l�F���g - �����̌���
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��Ɍ��Z�������s��
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator-(const TTriType & Obj)
{
	//����
	return { this->x - Obj.x, this->y - Obj.y, this->z - Obj.z };	//���Z����
}

/////
//�����Z������Z�q
//�����Fconst TTriType & Obj�F���Z����l�̎Q��
//�߂�l�F���������Z���ꂽ�������g
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��Ɍ��Z�������s�������̂�������
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> & TTriType<TriType>::operator-=(const TTriType & Obj)
{
	//����
	return (*this = *this - Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/////
//����Z���Z�q
//�����Fconst TTriType & Obj�F��Z����l�̎Q��
//�߂�l�F���g�ƈ����̏�Z����
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�Z�������s��
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator*(const TTriType & Obj)
{
	//����
	return { this->x * Obj.x, this->y * Obj.y, this->z * Obj.z };	//��Z����
}

/////
//����Z������Z�q
//�����Fconst TTriType & Obj�F��Z����l�̎Q��
//�߂�l�F��������Z���ꂽ�������g
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�Z�������s�������̂�������
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> & TTriType<TriType>::operator*=(const TTriType & Obj)
{
	//����
	return (*this = *this * Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/////
//�����Z���Z�q
//�����Fconst TTriType & Obj�F���Z����l�̎Q��
//�߂�l�F���g / �����̌���
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ��Z�������s��
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator/(const TTriType & Obj)
{
	//����
	return { this->x / Obj.x, this->y / Obj.y, this->z / Obj.z };	//���Z����
}

/////
//�����Z������Z�q
//�����Fconst TTriType & Obj�F���Z����l�̎Q��
//�߂�l�F���������Z���ꂽ�������g
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ��Z�������s�������̂�������
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> & TTriType<TriType>::operator/=(const TTriType & Obj)
{
	//����
	return (*this = *this / Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/////
//����]���Z�q
//�����Fconst TTriType & Obj�F��]���Z����l�̎Q��
//�߂�l�F���g�ƈ����̏�]���Z����
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�]���Z�������s��
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator%(const TTriType & Obj)
{
	//����
	return { static_cast<TriType>(static_cast<int>(this->x) % static_cast<int>(Obj.x)), static_cast<TriType>((int)this->y % (int)Obj.y), static_cast<TriType>((int)this->z % (int)Obj.z) };	//��]���Z����
}

/////
//����]������Z�q
//�����Fconst TTriType & Obj�F��]���Z����l�̎Q��
//�߂�l�F��������]���Z���ꂽ�������g
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�]���Z�������s�������̂�������
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> & TTriType<TriType>::operator%=(const TTriType & Obj)
{
	//����
	return (*this = *this % Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/////
//���ׂ��扉�Z�q
//�����Fconst double & dIndex�F�w���̎Q��
//�߂�l�F���g�������łׂ��悵�����Z����
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɂׂ��揈�����s��
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator^(const double & dIndex)
{
	//����
	return { (TriType)pow((double)this->x, dIndex), (TriType)pow((double)this->y, dIndex), (TriType)pow((double)this->z, dIndex) };	//�ׂ��扉�Z����
}

/////
//���ׂ��������Z�q
//�����Fconst double & dIndex�F�w���̎Q��
//�߂�l�F�������ׂ��悳�ꂽ�������g
//�T�v�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɂׂ��揈�����s�������̂�������
/////
template<class TriType>
TTriType<TriType> & TTriType<TriType>::operator^=(const double & dIndex)
{
	//����
	return (*this = *this ^ dIndex);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}



//--- �������牺�͎��^�](cpp�ɂ����Ȃ��Ɠ����Ȃ��̂ŁA���������ꍇ���̃w�b�_��all�R�s�[����cpp�ɓ\��t���Ă�������) ---//
	//�I�F ������main�֐�������ꍇ�͕ʃv���W�F�N�g�Ŏ������A�ꎞ�I�ɃR�����g�A�E�g���Ă��������B
//#include <iostream>
//#include <string>
//
//int main()
//{
//	TTriType<int> a;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//0,0,0�̃n�Y
//
//	a = TTriType<int>(1, 1, 1);
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
//	TTriType<int> b(4, 4, 4);
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
//	a += b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//8,8,8�̃n�Y
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4�̃n�Y
//
//
//	a %= b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//0,0,0�̃n�Y
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4�̃n�Y
//
//	b ^= 2.0;
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//16,16,16�̃n�Y
//
//	b ^= 0.5;
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4�̃n�Y
//
//	b ^= 0.25;
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//1,1,1�̃n�Y
//
//	std::cin.get();
//
//	return 0;
//}