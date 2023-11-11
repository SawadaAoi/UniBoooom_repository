/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���x�[�X �N���X��`
   ---------------------------------------
   SlimeManager.h

   �쐬�� �鑺 ����

   �ύX����
   �E2023/11/05 �X���C���}�l�[�W���[�N���X�쐬 suzumura
   �E2023/11/08 �X���C�����m���ڐG�����ۂ̕��򏈗����쐬(���򂵂���ɍs�������͖������@��TODO�����Ă�����)�� yamashita
   �E2023/11/08 �����������쐬(������̐��������͖����� Slime_2�`Slime_4���܂���������) yamashita
   �E2023/11/09 �X���C�������֐��̖��O�ύX sawada
   �E2023/11/09 �X���C���̂̐����������_���ɕύX yamashita
   �E2023/11/09 �v���C���[���W�擾�̌^��TPos3d<float>�ɕύX sawada

   ======================================== */
#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

// =============== �C���N���[�h ===================
#include "TriType.h"
#include "SlimeBase.h"
#include "ExplosionManager.h"
#include "Camera.h"
#include "ExplosionManager.h"

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

#else
const int MAX_SLIME_NUM = 30;	//�X���C���̍ő吶����
#endif
// =============== �N���X��` =====================
class CSlimeManager
{
public:
	// ===�v���g�^�C�v�錾===
	CSlimeManager();
	~CSlimeManager();

	void Update(CExplosionManager* pExpMng);
	void Draw();
	void Create(E_SLIME_LEVEL level);
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum,CExplosionManager* pExpMng);	//�X���C���̐ڐG���N�����ۂ̕��򏈗�
	void UnionSlime(E_SLIME_LEVEL level, TPos3d<float> pos);							//�X���C���̌�������
	void TouchExplosion(int DelSlime, CExplosionManager* pExpMng);	// �X���C���̔�������
	E_SLIME_LEVEL GetRandomLevel();									//�����_���ȃX���C���̃��x����Ԃ�(1�`3���׃�)

	//�Q�b�g�֐�
	CSlimeBase* GetSlimePtr(int num);

	void SetCamera(CCamera* pCamera);		//�X���C�����ڂ��J�����̃|�C���^���Z�b�g
	void SetPlayerPos(TPos3d<float> pos);
private:
	// ===�����o�ϐ��錾=====
	int GetRandom(int min, int max);

	CSlimeBase* m_pSlime[MAX_SLIME_NUM];
	CCamera* m_pCamera;

	TPos3d<float> m_pPlayerPos;	// �v���C���[�̍��W

	int m_CreateCnt;	// �����Ԋu�p�J�E���g


	
};

#endif // __SLIME_MANAGER_H__