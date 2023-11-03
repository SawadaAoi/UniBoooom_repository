//TriType.h
//�����^���R���e���v���[�g�N���X���`

//���X�V����
//2023/10/26	����
//2023/10/31	�p���ɑΉ��E�R�����g�C���E�ׂ���ǉ�
//2023/11/02	�ׂ��������Z�q�ǉ��Epow�̒��g�𖾎��I�Ɍ^�L���X�g�E�ׂ���̈�����double��float
				//�E������const�s���������E���x(����������)�ӎ��ň������Q�ƕ����ɕύX�E�R�����g�C��
//2023/11/03	%���Z�q�g�p���ɁA�v�Z�Ɏg�p����l�������^�łȂ����Ƃ���������C���ETotal()�֐���ǉ�
//2023/11/04	.cpp/.h����



//���C���N���[�h�K�[�h
#ifndef ___TRI_TYPE_H___
#define ___TRI_TYPE_H___

//���C���N���[�h��
#include <math.h>	//�v�Z�֐�

//���e���v���[�g�N���X��`
template<class TriType>
class TTriType	//�e���v���[�g�N���X�F�����^�̕ϐ��R��
{
public:
	//���ϐ��錾
	TriType x;	//�P�߂̕ϐ�
	TriType y;	//�Q�߂̕ϐ�
	TriType z;	//�R�߂̕ϐ�
	//���v���g�^�C�v�錾
	TTriType();														//�R���X�g���N�^
	TTriType(const TriType& x, const TriType& y, const TriType& z);	//�����t���R���X�g���N�^
	TTriType(const TTriType& Obj);									//�R�s�[�R���X�g���N�^
	virtual ~TTriType();											//�f�X�g���N�^
	virtual TriType Total();										//���v
	virtual TTriType& operator=(const TTriType& Obj);				//"="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator+(const TTriType& Obj);				//"+"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator+=(const TTriType& Obj);				//"+="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator-(const TTriType& Obj);				//"-"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator-=(const TTriType& Obj);				//"-="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator*(const TTriType& Obj);				//"*"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator*=(const TTriType& Obj);				//"*="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator/(const TTriType& Obj);				//"/"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator/=(const TTriType& Obj);				//"/="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator%(const TTriType& Obj);				//"%"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator%=(const TTriType& Obj);				//"%="���Z�q�̃I�[�o�[���[�h
	virtual TTriType operator^(const double& dIndex);				//"^"���Z�q�̃I�[�o�[���[�h
	virtual TTriType& operator^=(const double& dIndex);				//"^="���Z�q�̃I�[�o�[���[�h
};	//�^�e���v���[�g

#endif // !___TRI_TYPE_H___