/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�q�b�g�X�g�b�v��`
	------------------------------------
	HitStop.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/17 �쐬 takagi
	�E2023/11/21 �ÓI�ɕύX�E�R�����g�ǉ� takagi
	�E2024/01/16 ����̂��߁A�C���N���[�h�K�[�h��___��__�ɕύX	takagi

========================================== */

#ifndef __HIT_STOP_H__	//HitStop.h�C���N���[�h�K�[�h
#define __HIT_STOP_H__

// =============== �N���X��` =====================
class CHitStop	//�V�X�e��
{
public:
	// ===�񋓒�`===========
	enum HIT_STOP
	{
		E_BIT_FLAG_STOP_SOFT = 0x01,	//�X�g�b�v�F�y
		E_BIT_FLAG_STOP_NORMAL = 0x02,	//�X�g�b�v�F��
		E_BIT_FLAG_STOP_HEAVY = 0x04,	//�X�g�b�v�F�d
		E_BIT_FLAG_STOP_DEATH = 0x08,	//�X�g�b�v�F���@������Ȃ̎g����
		E_BIT_FLAG_5 = 0x10,			//
		E_BIT_FLAG_6 = 0x20,			//
		E_BIT_FLAG_7 = 0x40,			//
		E_BIT_FLAG_8 = 0x80,			//

		E_BIT_FLAG_HIT_STOP = 0x0F,		//�q�b�g�X�g�b�v���̓I���A����ȊO�̓I�t
		E_BIT_FLAG_MAX = 4,				//�v�f��(�����ł��I)
	};	//�t���O(�D��x��)
public:
	// ===�v���g�^�C�v�錾===
	CHitStop();												//�R���X�g���N�^
	~CHitStop();											//�f�X�g���N�^
	static void Update();									//�X�V
	static void UpFlag(const unsigned char& ucBitFlag);		//�t���O�I��
	static void DownFlag(const unsigned char& ucBitFlag);	//�t���O�I�t
	static void SetFlag(const unsigned char& ucBitFlag);	//�t���O���]
	static bool IsStop();									//�q�b�g�X�g�b�v����
private:
	// ===�����o�ϐ��錾=====
	static unsigned char ms_ucFlag;	//�t���O	char:1�o�C�g(8�r�b�g)
	static int ms_nFrame;			//�t���[�����J�E���^
	// ===�v���g�^�C�v�錾===
	static void CallHitStop(int(*CallBack)(const int&));	//�q�b�g�X�g�b�v����
};	//�q�b�g�X�g�b�v

#endif // !__HIT_STOP_H__