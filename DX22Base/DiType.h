/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�����^���Q���e���v���[�g�N���X���`
	------------------------------------
	DiType.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/07 Tri����R�s�y�����C takagi
	�E2023/11/08 �ꕔ�֐���const�C���q�t�^ takagi
	�E2023/11/09 �R�����g���� takagi
	�E2023/11/17 �P�̒l�����̃R���X�g���N�^������ takagi

========================================== */

#ifndef ___DI_TYPE_H___
#define ___DI_TYPE_H___

// =============== �C���N���[�h ===================
#include <math.h>	//�v�Z�֐�

// =============== �e���v���[�g�N���X��` ===================
template<class DiType>
struct TDiType	//�e���v���[�g�N���X�F�����^�̕ϐ��Q��
{
public:
	// ===�����o�ϐ��錾===
	DiType x;	//�P�߂̕ϐ�
	DiType y;	//�Q�߂̕ϐ�

	// ===�����o�֐��錾===
	TDiType();												//�R���X�g���N�^
	TDiType(const DiType& x, const DiType& y);				//�����t���R���X�g���N�^
	TDiType(const DiType& Di);								//�����t���R���X�g���N�^
	TDiType(const TDiType& Obj);							//�R�s�[�R���X�g���N�^
	virtual ~TDiType();										//�f�X�g���N�^
	virtual DiType Total() const;							//���v
	virtual TDiType& operator=(const TDiType& Obj);			//"="���Z�q�̃I�[�o�[���[�h
	virtual TDiType operator+(const TDiType& Obj) const;	//"+"���Z�q�̃I�[�o�[���[�h
	virtual TDiType& operator+=(const TDiType& Obj);		//"+="���Z�q�̃I�[�o�[���[�h
	virtual TDiType operator-(const TDiType& Obj) const;	//"-"���Z�q�̃I�[�o�[���[�h
	virtual TDiType& operator-=(const TDiType& Obj);		//"-="���Z�q�̃I�[�o�[���[�h
	virtual TDiType operator*(const TDiType& Obj) const;	//"*"���Z�q�̃I�[�o�[���[�h
	virtual TDiType& operator*=(const TDiType& Obj);		//"*="���Z�q�̃I�[�o�[���[�h
	virtual TDiType operator/(const TDiType& Obj) const;	//"/"���Z�q�̃I�[�o�[���[�h
	virtual TDiType& operator/=(const TDiType& Obj);		//"/="���Z�q�̃I�[�o�[���[�h
	virtual TDiType operator%(const TDiType& Obj) const;	//"%"���Z�q�̃I�[�o�[���[�h
	virtual TDiType& operator%=(const TDiType& Obj);		//"%="���Z�q�̃I�[�o�[���[�h
	virtual TDiType operator^(const double& dIndex) const;	//"^"���Z�q�̃I�[�o�[���[�h
	virtual TDiType& operator^=(const double& dIndex);		//"^="���Z�q�̃I�[�o�[���[�h
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
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType>::TDiType()
	:TDiType((DiType)0, (DiType)0)	//�Ϗ�
{
}

/* ========================================
	�R���X�g���N�^
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�Fconst DiType & x�F�P�߂̒l�̎Q��
	����2�Fconst DiType & y�F�Q�߂̒l�̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType>::TDiType(const DiType & x, const DiType & y)
{
	// =============== ������ ===================
	this->x = x;	//�P�ߏ�����
	this->y = y;	//�Q�ߏ�����
}

/* ========================================
	�R���X�g���N�^
	-------------------------------------
	���e�F�������ɍs������(�P�̒l���Q�̕ϐ��Ɋi�[)
	-------------------------------------
	����1�Fconst DiType & Di�F����������l�̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class DiType>
inline TDiType<DiType>::TDiType(const DiType & Di)
	:TDiType(Di, Di)	//�Ϗ�
{
}

/* ========================================
	�R�s�[�R���X�g���N�^
	-------------------------------------
	���e�F�R�s�[���ɍs������
	-------------------------------------
	����1�Fconst TDiType & Obj�F��������f�[�^���̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType>::TDiType(const TDiType & Obj)
{
	// =============== ���� ===================
	this->x = Obj.x;	//�P�߂̃f�[�^�R�s�[
	this->y = Obj.y;	//�Q�߂̃f�[�^�R�s�[
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
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType>::~TDiType()
{
}

/* ========================================
	���v�֐�
	------------------------------------ -
	���e�F���g�̎��Q�̃����o�[�ϐ������v����
	------------------------------------ -
	����1�F�Ȃ�
	------------------------------------ -
	�ߒl�F�Q�̃����o�[�ϐ��̍��v�l
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
DiType TDiType<DiType>::Total() const
{
	// =============== �� ===================
	return (this->x + this->y);	//���Z����
}

/* ========================================
	������Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɑ���������s��
	------------------------------------ -
	����1�Fconst TDiType & Obj�F�������l�̎Q��
	------------------------------------ -
	�ߒl�F������s��ꂽ�������g
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType>& TDiType<DiType>::operator=(const TDiType & Obj)
{
	// =============== ���� ===================
	this->x = Obj.x;	//�P�߂̃f�[�^�R�s�[
	this->y = Obj.y;	//�Q�߂̃f�[�^�R�s�[

	// =============== �� ===================
	return	*this;	//���g�̎Q��
}

/* ========================================
	���Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɉ��Z�������s��
	------------------------------------ -
	����1�Fconst TDiType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g�ƈ����̉��Z����
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType> TDiType<DiType>::operator+(const TDiType & Obj) const
{
	// =============== �� ===================
	return { this->x + Obj.x, this->y + Obj.y };	//���Z����
}

/* ========================================
	���Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɉ��Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst TDiType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���������Z���ꂽ�������g
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType> & TDiType<DiType>::operator+=(const TDiType & Obj)
{
	// =============== �� ===================
	return (*this = *this + Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	���Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��Ɍ��Z�������s��
	------------------------------------ -
	����1�Fconst TDiType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g - �����̌���
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType> TDiType<DiType>::operator-(const TDiType & Obj) const
{
	// =============== �� ===================
	return { this->x - Obj.x, this->y - Obj.y };	//���Z����
}

/* ========================================
	���Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��Ɍ��Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst TDiType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���������Z���ꂽ�������g
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType> & TDiType<DiType>::operator-=(const TDiType & Obj)
{
	// =============== �� ===================
	return (*this = *this - Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	��Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�Z�������s��
	------------------------------------ -
	����1�Fconst TDiType & Obj�F��Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g�ƈ����̏�Z����
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType> TDiType<DiType>::operator*(const TDiType & Obj) const
{
	// =============== �� ===================
	return { this->x * Obj.x, this->y * Obj.y };	//��Z����
}

/* ========================================
	��Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst TDiType & Obj�F��Z����l�̎Q��
	------------------------------------ -
	�ߒl�F��������Z���ꂽ�������g
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType> & TDiType<DiType>::operator*=(const TDiType & Obj)
{
	// =============== �� ===================
	return (*this = *this * Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	���Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ��Z�������s��
	------------------------------------ -
	����1�Fconst TDiType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g / �����̌���
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType> TDiType<DiType>::operator/(const TDiType & Obj) const
{
	// =============== �� ===================
	return { this->x / Obj.x, this->y / Obj.y };	//���Z����
}

/* ========================================
	���Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ��Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst TDiType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���������Z���ꂽ�������g
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType> & TDiType<DiType>::operator/=(const TDiType & Obj)
{
	// =============== �� ===================
	return (*this = *this / Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	��]���Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�]���Z�������s��
	------------------------------------ -
	����1�Fconst TDiType & Obj�F��]���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g�ƈ����̏�]���Z����
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType> TDiType<DiType>::operator%(const TDiType & Obj) const
{
	// =============== �� ===================
	return { static_cast<DiType>(static_cast<int>(this->x) % static_cast<int>(Obj.x)), static_cast<DiType>((int)this->y % (int)Obj.y) };	//��]���Z����
}

/* ========================================
	��]������Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�]���Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst TDiType & Obj�F��]���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F�����ŏ�]���Z���ꂽ�������g
=========================================== */
/////
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType> & TDiType<DiType>::operator%=(const TDiType & Obj)
{
	// =============== �� ===================
	return (*this = *this % Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	�ׂ��扉�Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɂׂ��揈�����s��
	------------------------------------ -
	����1�Fconst double & dIndex�F�w���̎Q��
	------------------------------------ -
	�ߒl�F���g�������łׂ��悵�����Z����
=========================================== */
template<class DiType>	//�e���v���[�g�֐�����
TDiType<DiType> TDiType<DiType>::operator^(const double & dIndex) const
{
	// =============== �� ===================
	return { (DiType)pow((double)this->x, dIndex), (DiType)pow((double)this->y, dIndex) };	//�ׂ��扉�Z����
}

/* ========================================
	�ׂ��������Z�q
	------------------------------------ -
	���e�F�Ɨ������Q�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɂׂ��揈�����s�������̂�������
	------------------------------------ -
	����1�Fconst double & dIndex�F�w���̎Q��
	------------------------------------ -
	�ߒl�F�������ׂ��悳�ꂽ�������g
=========================================== */
template<class DiType>
TDiType<DiType> & TDiType<DiType>::operator^=(const double & dIndex)
{
	// =============== �� ===================
	return (*this = *this ^ dIndex);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

#endif // !___DI_TYPE_H___




//--- �������牺�͎��^�](cpp�ɂ����Ȃ��Ɠ����Ȃ��̂ŁA���������ꍇ���̃w�b�_��all�R�s�[����cpp�ɓ\��t���Ă�������) ---//
	//�I�F ������main�֐�������ꍇ�͕ʃv���W�F�N�g�Ŏ������A�ꎞ�I�ɃR�����g�A�E�g���Ă��������B
//#include <iostream>
//#include <string>
//
//int main()
//{
//	TDiType<int> a;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;	//0,0�̃n�Y
//
//	a = TDiType<int>(1, 1);
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;
//
//	a = { 2, 2 };
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;
//
//	a.x = 3;
//	a.y = 3;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;
//
//	TDiType<int> b(4, 4);
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << std::endl;
//
//	a + b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;	//3,3�̃n�Y
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << std::endl;	//4,4�̃n�Y
//
//	a = b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;	//4,4�̃n�Y
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << std::endl;	//4,4�̃n�Y
//
//	a += b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;	//8,8�̃n�Y
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << std::endl;	//4,4�̃n�Y
//	std::cin.get();
//
//
//	return 0;
//}