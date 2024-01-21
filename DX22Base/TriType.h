/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�����^���R���e���v���[�g�N���X���`
	------------------------------------
	TriType.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/10/26 ���� takagi
	�E2023/10/31 �p���ɑΉ��E�R�����g�C���E�ׂ���ǉ� takagi
	�E2023/11/02 �ׂ��������Z�q�ǉ��Epow�̒��g�𖾎��I�Ɍ^�L���X�g�E�ׂ���̈�����double��float
					�E������const�s���������E���x(����������)�ӎ��ň������Q�ƕ����ɕύX�E�R�����g�C�� takagi
	�E2023/11/03 %���Z�q�g�p���ɁA�v�Z�Ɏg�p����l�������^�łȂ����Ƃ���������C���ETotal()�֐���ǉ� takagi
	�E2023/11/04 .cpp/.h�������������� takagi
	�E2023/11/07 �R�[�f�B���O�K��K�p takagi
	�E2023/11/08 �ꕔ�֐���const�C���q�t�^ takagi
	�E2023/11/09 �s�v�������E�N���X���struct�̂ق����@�\�̈Ӗ��Ƃ��Đ������̂ŏC�� takagi
	�E2023/11/14 �P�̒l�����̃R���X�g���N�^������ takagi
	�E2024/01/16 ����̂��߁A�C���N���[�h�K�[�h��___��__�ɕύX	takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __TRI_TYPE_H__	//TriType.h�C���N���[�h�K�[�h
#define __TRI_TYPE_H__

// =============== �C���N���[�h ===================
#include <math.h>	//�v�Z�֐�

// =============== �e���v���[�g�N���X��` ===================
template<class TriType>
struct TTriType	//�e���v���[�g�N���X�F�����^�̕ϐ��R��
{
public:
	// ===�����o�ϐ��錾===
	TriType x;	//�P�߂̕ϐ�
	TriType y;	//�Q�߂̕ϐ�
	TriType z;	//�R�߂̕ϐ�

	// ===�����o�֐��錾===
	TTriType();														//�R���X�g���N�^
	TTriType(const TriType& x, const TriType& y, const TriType& z);	//�����t���R���X�g���N�^
	TTriType(const TriType& Tri);									//�����t���R���X�g���N�^
	TTriType(const TTriType& Obj);									//�R�s�[�R���X�g���N�^
	virtual ~TTriType();											//�f�X�g���N�^
	virtual TriType Total() const;									//���v
	virtual TTriType& operator=(const TTriType& Obj);				//"="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator+(const TTriType& Obj) const;			//"+"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator+=(const TTriType& Obj);				//"+="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator-(const TTriType& Obj) const;			//"-"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator-=(const TTriType& Obj);				//"-="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator*(const TTriType& Obj) const;			//"*"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator*=(const TTriType& Obj);				//"*="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator/(const TTriType& Obj) const;			//"/"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator/=(const TTriType& Obj);				//"/="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator%(const TTriType& Obj) const;			//"%"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator%=(const TTriType& Obj);				//"%="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator^(const double& dIndex) const;			//"^"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator^=(const double& dIndex);				//"^="���Z�q�̃I�[�o�[���[�h
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
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType>::TTriType()
	:TTriType((TriType)0)	//�Ϗ�
{
}

/* ========================================
	�R���X�g���N�^
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�Fconst TriType & x�F�P�߂̒l�̎Q��
	����2�Fconst TriType & y�F�Q�߂̒l�̎Q��
	����3�Fconst TriType & z�F�R�߂̒l�̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType>::TTriType(const TriType & x, const TriType & y, const TriType & z)
{
	// =============== ������ ===================
	this->x = x;	//�P�ߏ�����
	this->y = y;	//�Q�ߏ�����
	this->z = z;	//�R�ߏ�����
}

/* ========================================
	�R���X�g���N�^
	-------------------------------------
	���e�F�������ɍs������(�P�̒l���R�̕ϐ��Ɋi�[)
	-------------------------------------
	����1�Fconst TriType & Tri�F����������l�̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class TriType>
inline TTriType<TriType>::TTriType(const TriType& Tri)
	:TTriType(Tri, Tri, Tri)	//�Ϗ�
{
}

/* ========================================
	�R�s�[�R���X�g���N�^
	-------------------------------------
	���e�F�R�s�[���ɍs������
	-------------------------------------
	����1�Fconst TTriType & Obj�F��������f�[�^���̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType>::TTriType(const TTriType & Obj)
{
	// =============== ���� ===================
	this->x = Obj.x;	//�P�߂̃f�[�^�R�s�[
	this->y = Obj.y;	//�Q�߂̃f�[�^�R�s�[
	this->z = Obj.z;	//�R�߂̃f�[�^�R�s�[
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
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType>::~TTriType()
{
}

/* ========================================
	���v�֐�
	------------------------------------ -
	���e�F���g�̎��R�̃����o�[�ϐ������v����
	------------------------------------ -
	����1�F�Ȃ�
	------------------------------------ -
	�ߒl�F�R�̃����o�[�ϐ��̍��v�l
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TriType TTriType<TriType>::Total() const
{
	// =============== �� ===================
	return (this->x + this->y + this->z);	//���Z����
}

/* ========================================
	������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɑ���������s��
	------------------------------------ -
	����1�Fconst TTriType & Obj�F�������l�̎Q��
	------------------------------------ -
	�ߒl�F������s��ꂽ�������g
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType>& TTriType<TriType>::operator=(const TTriType & Obj)
{
	// =============== ���� ===================
	this->x = Obj.x;	//�P�߂̃f�[�^�R�s�[
	this->y = Obj.y;	//�Q�߂̃f�[�^�R�s�[
	this->z = Obj.z;	//�R�߂̃f�[�^�R�s�[

	// =============== �� ===================
	return	*this;	//���g�̎Q��
}

/* ========================================
	���Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɉ��Z�������s��
	------------------------------------ -
	����1�Fconst TTriType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g�ƈ����̉��Z����
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator+(const TTriType & Obj) const
{
	// =============== �� ===================
	return { this->x + Obj.x, this->y + Obj.y, this->z + Obj.z };	//���Z����
}

/* ========================================
	���Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɉ��Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst TTriType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���������Z���ꂽ�������g
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> & TTriType<TriType>::operator+=(const TTriType & Obj)
{
	// =============== �� ===================
	return (*this = *this + Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	���Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��Ɍ��Z�������s��
	------------------------------------ -
	����1�Fconst TTriType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g - �����̌���
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator-(const TTriType & Obj) const
{
	// =============== �� ===================
	return { this->x - Obj.x, this->y - Obj.y, this->z - Obj.z };	//���Z����
}

/* ========================================
	���Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��Ɍ��Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst TTriType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���������Z���ꂽ�������g
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> & TTriType<TriType>::operator-=(const TTriType & Obj)
{
	// =============== �� ===================
	return (*this = *this - Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	��Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�Z�������s��
	------------------------------------ -
	����1�Fconst TTriType & Obj�F��Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g�ƈ����̏�Z����
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator*(const TTriType & Obj) const
{
	// =============== �� ===================
	return { this->x * Obj.x, this->y * Obj.y, this->z * Obj.z };	//��Z����
}

/* ========================================
	��Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst TTriType & Obj�F��Z����l�̎Q��
	------------------------------------ -
	�ߒl�F��������Z���ꂽ�������g
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> & TTriType<TriType>::operator*=(const TTriType & Obj)
{
	// =============== �� ===================
	return (*this = *this * Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	���Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ��Z�������s��
	------------------------------------ -
	����1�Fconst TTriType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g / �����̌���
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator/(const TTriType & Obj) const
{
	// =============== �� ===================
	return { this->x / Obj.x, this->y / Obj.y, this->z / Obj.z };	//���Z����
}

/* ========================================
	���Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ��Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst TTriType & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���������Z���ꂽ�������g
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> & TTriType<TriType>::operator/=(const TTriType & Obj)
{
	// =============== �� ===================
	return (*this = *this / Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	��]���Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�]���Z�������s��
	------------------------------------ -
	����1�Fconst TTriType & Obj�F��]���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g�ƈ����̏�]���Z����
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator%(const TTriType & Obj) const
{
	// =============== �� ===================
	return { static_cast<TriType>(static_cast<int>(this->x) % static_cast<int>(Obj.x)), static_cast<TriType>((int)this->y % (int)Obj.y), static_cast<TriType>((int)this->z % (int)Obj.z) };	//��]���Z����
}

/* ========================================
	��]������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�]���Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst TTriType & Obj�F��]���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F�����ŏ�]���Z���ꂽ�������g
=========================================== */
/////
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> & TTriType<TriType>::operator%=(const TTriType & Obj)
{
	// =============== �� ===================
	return (*this = *this % Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	�ׂ��扉�Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɂׂ��揈�����s��
	------------------------------------ -
	����1�Fconst double & dIndex�F�w���̎Q��
	------------------------------------ -
	�ߒl�F���g�������łׂ��悵�����Z����
=========================================== */
template<class TriType>	//�e���v���[�g�֐�����
TTriType<TriType> TTriType<TriType>::operator^(const double & dIndex) const
{
	// =============== �� ===================
	return { (TriType)pow((double)this->x, dIndex), (TriType)pow((double)this->y, dIndex), (TriType)pow((double)this->z, dIndex) };	//�ׂ��扉�Z����
}

/* ========================================
	�ׂ��������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɂׂ��揈�����s�������̂�������
	------------------------------------ -
	����1�Fconst double & dIndex�F�w���̎Q��
	------------------------------------ -
	�ߒl�F�������ׂ��悳�ꂽ�������g
=========================================== */
template<class TriType>
TTriType<TriType> & TTriType<TriType>::operator^=(const double & dIndex)
{
	// =============== �� ===================
	return (*this = *this ^ dIndex);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

#endif	//!__TRI_TYPE_H__