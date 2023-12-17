/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	���[���h�s����Q����
	------------------------------------
	Transform3d.cpp
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/08 ���� takagi
	�E2023/11/09 �ꕔ���C�� takagi
	�E2023/11/14 �p�x���Z takagi
	�E2023/12/05 �r���{�[�h�ɑΉ� takagi
	�E2023/12/17 �����Q�Ɖ� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Transform3d.h"	//���g�̃w�b�_

// =============== �萔��` ===================
const TPos3d<float> INIT_POS(0.0f, 0.0f, 0.0f);		//�����ʒu
const TTriType<float> INIT_SCALE(1.0f, 1.0f, 1.0f);	//�����g�k
const TTriType<float> INIT_RAD(0.0f, 0.0f, 0.0f);	//������]

/* ========================================
	�R���X�g���N�^
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
tagTransform3d::tagTransform3d()
	:tagTransform3d(INIT_POS, INIT_SCALE, INIT_RAD)
{
}

/* ========================================
	�R���X�g���N�^
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�Fconst TPos3d<float> & fPos�F�ʒu�f�[�^
	����2�Fconst TTriType<float> & fScale�F�g�k�{��
	����3�Fconst TTriType<float> & fRadian)�F�p
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
tagTransform3d::tagTransform3d(const TPos3d<float> & fPos, const TTriType<float> & fScale, const TTriType<float> & fRadian)
	:fPos(fPos)		//�ʒu
	,fScale(fScale)	//�g�k��
	,fRadian(fRadian)	//�p
{
}

/* ========================================
	�R�s�[�R���X�g���N�^
	-------------------------------------
	���e�F�R�s�[���ɍs������
	-------------------------------------
	����1�Fconst tagTransform3d & Obj�F��������f�[�^���̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
tagTransform3d::tagTransform3d(const tagTransform3d & Obj)
{
	// =============== ���� ===================
	this->fPos = Obj.fPos;			//�ʒu�R�s�[
	this->fScale = Obj.fScale;		//�g�k�R�s�[
	this->fRadian = Obj.fRadian;	//��]�p�R�s�[
}

/* ========================================
	�f�X�g���N�^
	-------------------------------------
	���e�F�j�����ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
tagTransform3d::~tagTransform3d()
{
}

/* ========================================
	TRS���[���h�s��擾�֐�
	-------------------------------------
	���e�FTRS�ϊ��������[���h�s����
	-------------------------------------
	����1�Fconst DirectX::XMMATRIX  & Inverse�F�r���{�[�h���̋t�s��	�f�t�H���g�����͊|���Ă��l���ς��Ȃ��P�ʍs��(=�r���{�[�h���g�p���Ȃ�)
	-------------------------------------
	�ߒl�F�쐬�����s��
=========================================== */
DirectX::XMFLOAT4X4 tagTransform3d::GetWorldMatrixTRS(const DirectX::XMMATRIX & Inverse)
{
	// =============== �ϐ��錾 ===================
	DirectX::XMFLOAT4X4 mat;	//�s��i�[�p
	
	// =============== ���[���h�s��̌v�Z ===================
	DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
		DirectX::XMMatrixTranslation(fPos.x, fPos.y, fPos.z)		//T:�ړ�
		* DirectX::XMMatrixRotationX(fRadian.x) * DirectX::XMMatrixRotationY(fRadian.y) 
		* DirectX::XMMatrixRotationZ(fRadian.z)						//R:��]
		* DirectX::XMMatrixScaling(fScale.x, fScale.y, fScale.z)	//S:�g�k
		* Inverse													//�t�s��
	));	//TRS�ϊ�

	// =============== �� ===================
	return mat;	//�s���
}

/* ========================================
	SRT���[���h�s��擾�֐�
	-------------------------------------
	���e�FSRT�ϊ��������[���h�s����
	-------------------------------------
	����1�Fconst DirectX::XMMATRIX & Inverse�F�r���{�[�h���̋t�s��	�f�t�H���g�����͊|���Ă��l���ς��Ȃ��P�ʍs��(=�r���{�[�h���g�p���Ȃ�)
	-------------------------------------
	�ߒl�F�쐬�����s��
=========================================== */
DirectX::XMFLOAT4X4 tagTransform3d::GetWorldMatrixSRT(const DirectX::XMMATRIX & Inverse)
{
	// =============== �ϐ��錾 ===================
	DirectX::XMFLOAT4X4 mat;	//�s��i�[�p

	// =============== ���[���h�s��̌v�Z ===================
	DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
		DirectX::XMMatrixScaling(fScale.x, fScale.y, fScale.z)	//S:�g�k
		* DirectX::XMMatrixRotationX(fRadian.x) * DirectX::XMMatrixRotationY(fRadian.y)
		* DirectX::XMMatrixRotationZ(fRadian.z)					//R:��]
		* Inverse												//�t�s��
		* DirectX::XMMatrixTranslation(fPos.x, fPos.y, fPos.z)	//T:�ړ�
	));	//SRT�ϊ�

	// =============== �� ===================
	return mat;	//�s���
}

/* ========================================
	�p�x���Z�֐�
	----------------------------------------
	���e�F�����Ƃ̊p�x���擾
	----------------------------------------
	����1�F���肽�������Sphere�\����
	----------------------------------------
	�ߒl�F�p�x
======================================== */
float tagTransform3d::Angle(const tagTransform3d& Obj)
{
	// =============== �� =============
	return static_cast<float>(atan2((Obj.fPos.z - this->fPos.z) , (Obj.fPos.x - this->fPos.x)));	//���߂��p�x
}

/* ========================================
	������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɑ���������s��
	------------------------------------ -
	����1�Fconst tagTransform3d & Obj�F�������l�̎Q��
	------------------------------------ -
	�ߒl�F������s��ꂽ�������g
=========================================== */
tagTransform3d& tagTransform3d::operator=(const tagTransform3d & Obj)
{
	// =============== ���� ===================
	this->fPos = Obj.fPos;			//�ʒu�R�s�[
	this->fScale = Obj.fScale;		//�g�k�R�s�[
	this->fRadian = Obj.fRadian;	//��]�p�R�s�[

	// =============== �� ===================
	return	*this;	//���g�̎Q��
}

/* ========================================
	���Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɉ��Z�������s��
	------------------------------------ -
	����1�Fconst tagTransform3d & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g�ƈ����̉��Z����
=========================================== */
tagTransform3d tagTransform3d::operator+(const tagTransform3d & Obj)
{
	// =============== �� ===================
	return { this->fPos + Obj.fPos, this->fScale + Obj.fScale, this->fScale + Obj.fScale };	//���Z����
}

/* ========================================
	���Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɉ��Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst tagTransform3d & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���������Z���ꂽ�������g
=========================================== */
tagTransform3d & tagTransform3d::operator+=(const tagTransform3d & Obj)
{
	// =============== �� ===================
	return (*this = *this + Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	���Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��Ɍ��Z�������s��
	------------------------------------ -
	����1�Fconst tagTransform3d & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g - �����̌���
=========================================== */
tagTransform3d tagTransform3d::operator-(const tagTransform3d & Obj)
{
	// =============== �� ===================
	return { this->fPos - Obj.fPos, this->fScale - Obj.fScale, this->fRadian - Obj.fRadian };	//���Z����
}

/* ========================================
	���Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��Ɍ��Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst tagTransform3d & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���������Z���ꂽ�������g
=========================================== */
tagTransform3d & tagTransform3d::operator-=(const tagTransform3d & Obj)
{
	// =============== �� ===================
	return (*this = *this - Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	��Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�Z�������s��
	------------------------------------ -
	����1�Fconst tagTransform3d & Obj�F��Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g�ƈ����̏�Z����
=========================================== */
tagTransform3d tagTransform3d::operator*(const tagTransform3d & Obj)
{
	// =============== �� ===================
	return { this->fPos * Obj.fPos, this->fScale * Obj.fScale, this->fRadian * Obj.fRadian };	//��Z����
}

/* ========================================
	��Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ�Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst tagTransform3d & Obj�F��Z����l�̎Q��
	------------------------------------ -
	�ߒl�F��������Z���ꂽ�������g
=========================================== */
tagTransform3d & tagTransform3d::operator*=(const tagTransform3d & Obj)
{
	// =============== �� ===================
	return (*this = *this * Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}

/* ========================================
	���Z���Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ��Z�������s��
	------------------------------------ -
	����1�Fconst tagTransform3d & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���g / �����̌���
=========================================== */
tagTransform3d tagTransform3d::operator/(const tagTransform3d & Obj)
{
	// =============== �� ===================
	return { this->fPos / Obj.fPos, this->fScale / Obj.fScale, this->fRadian / Obj.fRadian };	//���Z����
}

/* ========================================
	���Z������Z�q
	------------------------------------ -
	���e�F�Ɨ������R�̃����o�[�ϐ��ɑ΂��Ă��ꂼ��ɏ��Z�������s�������̂�������
	------------------------------------ -
	����1�Fconst tagTransform3d & Obj�F���Z����l�̎Q��
	------------------------------------ -
	�ߒl�F���������Z���ꂽ�������g
=========================================== */
tagTransform3d & tagTransform3d::operator/=(const tagTransform3d & Obj)
{
	// =============== �� ===================
	return (*this = *this / Obj);	//�����ω��Z�q���g�p���ď������s���A���g�̎Q�Ƃ�Ԃ�
}