/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X���C���x�[�X �N���X��`
	---------------------------------------
	SlimeBase.h
	
	�쐬�� �鑺 ����
	
	�ύX����
	�E2023/11/04 �X���C���x�[�X�N���X�쐬 Suzumura
	�E2023/11/06 ������шړ��Ɛ�����шړ��֐����쐬 Yamashita
	�E2023/11/06 m_fSpped(�G�̈ړ����x)��m_fVecAngle(�G�̐�����ԕ���)�̃����o�ϐ���ǉ� Yamashita
	�E2023/11/06 �萔SPEED_DOWN_RATIO(�Ԃ�������̃X���C���ɑ��x��n���ۂɌ������銄��)��ǉ� Yamashita
	�E2023/11/06 �萔MOVE_RESIST(������шړ����̃X���C���̈ړ����x�ɖ��t���[�������錸�Z���l)��ǉ� Yamashita
	�E2023/11/07 HitBranch�֐�(�X���C���Ƃ̐ڐG���򏈗�)��SlimeManager�Ɉړ����邽�߂ɍ폜 Yamashita
	�E2023/11/08 �X���C���̃T�C�Y��\���񋓂��` Yamashita
	�E2023/11/08 �X���C���̃T�C�Y��Ԃ��֐����쐬 Yamashita
	�E2023/11/08 GetPos��GetSphere�ɖ��O��ύX Yamashita
	�E2023/11/08 �X���C���̈ړ����x���擾����֐����쐬 Yamashita
	�E2023/11/08 �萔��`���w�b�_�[�ɂ������̂�cpp�Ɉړ� Yamashita
	�E2023/11/08 Union��Explosion���폜(�}�l�[�W���[�Ɉړ��������̂�) Yamashita
	�E2023/11/08 m_bUse�An_playerDistance�Am_playerAngle���폜(�ꂩ���ł����g�p���Ă��Ȃ���) Yamashita
	�E2023/11/08 m_Player��ǉ� Yamashita
	�E2023/11/08 ���W��TPos<Pos>�ɕύX Yamashita
	�E2023/11/09 Update,NormalMove�̈����ύX Yamashita
	�E2023/11/08 �X���C���̈ړ����x�̒萔��cpp����h�Ɉړ� Yamashita
	�E2023/11/10 �J�����|�C���^��ǉ� Yamashita
	�E2023/11/10 ���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g����悤�ɂ��� Yamashita
	�E2023/11/12 m_Ry��ǉ��i�X���C���̌�����ς��鎞�Ɏg�p�j Yamamoto
	�E2023/11/13 GetScale�֐��̒ǉ� Suzumura
	�E2023/11/14 �񋓂�FLAME��ǉ��ANormalMove�����z�֐��� Suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� Takagi
	�E2023/11/15 Object�N���X���p�������̂ŏC���@yamamoto
	�E2023/11/26 �������瓦����t���O�A�ł��߂�����������ϐ����쐬�@yamashita
	�E2023/11/26 �X���C�����������瓦���鏈�����쐬�@yamashita
	�E2023/11/28 �e�̕`��ǉ� nieda
	�E2023/12/04 �񋓂Ƀq�[���X���C����ǉ� Tei
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi

========================================== */
#ifndef __SLIME_BASE_H__
#define __SLIME_BASE_H__

// =============== �C���N���[�h ===================
#include "Model.h"
#include "Shader.h"
#include "SphereInfo.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Camera.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#include "Object.h"
#include "Shadow.h"		// �e�\���p�w�b�_
#include "Timer.h"

// =============== �񋓒�` =======================
enum E_SLIME_LEVEL
{
	LEVEL_NONE,	//SlimeBase�Ő������Ă܂��|�����[�t�B�Y�����Ă��Ȃ����

	LEVEL_1,		//1�i�K��
	LEVEL_2,		//2�i�K��
	LEVEL_3,		//3�i�K��
	LEVEL_4,		//4�i�K��
	LEVEL_4x4,		//�ԃA��
	LEVEL_FLAME,			// �t���C���X���C��
	LEVEL_HEAL,				// �q�[���X���C��

	LEVEL_BOSS = 999,		// �{�X�X���C��	(�ŋ�)

	MAX_LEVEL = LEVEL_4	//�ő僌�x����ݒ�	(�X���C���̒i�K����������ύX)
};

// =============== �萔��` =======================
const int LEVEL_1_SCORE = 10;				// �X���C��_1�̃X�R�A
const int LEVEL_2_SCORE = 30;				// �X���C��_2�̃X�R�A
const int LEVEL_3_SCORE = 100;				// �X���C��_3�̃X�R�A
const int LEVEL_4_SCORE = 500;				// �X���C��_4�̃X�R�A
const int LEVEL_4x4_SCORE = 1000;			// �ԁX�̔����̃X�R�A
const int LEVEL_Boss_SCORE = 3000;			// �ԁX�̔����̃X�R�A
#if MODE_GAME_PARAMETER
#else
const float ENEMY_MOVE_SPEED = 0.01f;	//�G�̈ړ����x
const int FIRST_EXPLOSION_SCORE = 1000;		//�ԓ��m�̍ŏ��̔����̃X�R�A
#endif

// =============== �N���X��` =====================

class CSlimeBase
	: public CObject 
{
public:
	// ===�v���g�^�C�v�錾===
	CSlimeBase();
	~CSlimeBase();
	virtual void Update(tagTransform3d playerTransform, float fSlimeMoveSpeed); 
	virtual void Draw(const CCamera* pCamera);

	virtual void NormalMove();	// �ʏ펞�̈ړ�����
	void RandomMove();
	void HitMove();									//�X���C����������шړ���Ԃ̎��ɖ��t���[���Ăяo���Ĉړ�������
	void HitMoveStart(float speed, float angle);	//�X���C����������΂��ꂽ�Ƃ��ɑ��x�Ɗp�x�����߂�
	void Reflect();									//�X���C���ƂԂ����Đ�����΂����ۂɎ����̈ړ��ʂ����炷
	void Escape();

	// �Q�b�g�֐�
	float GetSpeed();					// �X���C���̈ړ����x���擾
	E_SLIME_LEVEL GetSlimeLevel();		// �X���C���̃��x�����擾
	bool GetHitMoveFlg();
	TPos3d<float> GetPos();
	bool GetEscapeFlag();
	int GetAttack();

	//�Z�b�g�֐�
	virtual void SetNormalSpeed() = 0;
	void SetCamera(const CCamera* pCamera);
	void SetExplosionPos(TPos3d<float> expPos);
	void SetEscapeFlag(bool bEscape);
protected:
	Model* m_pModel;				//3D���f��
	VertexShader* m_pVS;			//�o�[�e�b�N�X�V�F�[�_�[�̃|�C���^
	TTriType<float> m_move;			//�ړ���
	TPos3d<float> m_ExpPos;			//�ł��߂������̍��W
	float m_fSpeed;					//�X���C���̈ړ����x

	bool m_bHitMove;				//������ђ����ǂ���
	float m_fVecAngle;				//�G�̐�����ԕ���
	bool m_bEscape;					//�X���C�����������Ԃ��ǂ���
	int m_nEscapeCnt;				//�������ԂɂȂ�����

	E_SLIME_LEVEL m_eSlimeSize;		//�X���C���̑傫���̗�
	const CCamera* m_pCamera;		//�J�����̃|�C���^

	CShadow* m_pShadow;				//�e�̃|�C���^
	float m_fScaleShadow;			//�e�̑傫��
	
	DirectX::XMMATRIX m_Ry;			//��]

	int m_RanMoveCnt;				// �����_���ړ��̉��Z�l
	int m_nAttack;					// �U����

	tagTransform3d m_PlayerTran;	// �v���C���[�̕ό`���

};
#endif // __SLIME_BASE_H__