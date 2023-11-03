//Pos.cpp
//�ʒu���W���Ǘ�����e���v���[�g�N���X������

//���X�V����
//2023/10/31	����
//2023/11/02	�����v�Z�֐���return���ɕs�����Ă���'('��Y��
				//�E������const�s���������E���x(����������)�ӎ��ň������Q�ƕ����ɕύX�E�R�����g�C��
//2023/11/03	Distance()�֐��̕s����C��
//2023/11/04	.cpp/.h����



//���C���N���[�h��
#include "Pos.h"	//���g�̃w�b�_

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