/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �����Ǘ��w�b�_�[
   ---------------------------------------
   ExplosionManager.h

   �쐬�� �A �F��

   �ύX����
	�E2023/11/06 �����}�l�[�W���[�N���X�쐬 tei
	�E2023/11/09 �����z���Ԃ������̒ǉ� sawada
	�E2023/11/10 ���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g����悤�ɂ��� yamashita

	

========================================== */
#ifndef __EXPLOSION_MANAGER_H__	//ExplosionManager.h�C���N���[�h�K�[�h
#define __EXPLOSION_MANAGER_H__
// =============== �C���N���[�h ===================
#include "TriType.h"			//�����^���R���e���v���[�g�N���X��`�w�b�_�[
#include "Explosion.h"			//���������w�b�_�[
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const int MAX_EXPLOSION_NUM = 20;	//�ő唚����
#endif
// =============== �N���X��` =====================
class CExplosionManager
{
public:
	// ===�����o�֐��錾===
	CExplosionManager();		//�R���X�g���N�^
	~CExplosionManager();		//�f�X�g���N�^

	void Update();		 		//�X�V�֐�
	void Draw();		 		//�`��֐�
	
	void Create(TTriType<float> pos,float size);   	//���������֐�
	void DeleteCheck();							   	//���Ԃ�蔚�����폜�֐�

	CExplosion* GetExplosionPtr(int num);

	void SetCamera(const CCamera* pCamera);	//���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g
protected:
	// ===�����o�ϐ��錾===
	CExplosion* m_pExplosion[MAX_EXPLOSION_NUM];	//�����̔z��
	const CCamera* m_pCamera;
private:
};

#endif // __EXPLOSION_MANAGER_H__