//Pos.h
//�ʒu���W���Ǘ�����e���v���[�g�N���X���`

//���X�V����
//2023/10/31	����
//2023/11/02	�����v�Z�֐���return���ɕs�����Ă���'('��Y��
				//�E������const�s���������E���x(����������)�ӎ��ň������Q�ƕ����ɕύX�E�R�����g�C��
//2023/11/03	Distance()�֐��̕s����C��
//2023/11/04	.cpp/.h����



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

#endif // !___POS_H___