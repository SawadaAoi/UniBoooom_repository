/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �����Ǘ��w�b�_�[
   ---------------------------------------
   ExplosionManager.h

   �쐬�� �A �F��

   �ύX����
   �E2023/11/06 �����}�l�[�W���[�N���X�쐬 /�A�@�F��

========================================== */
#ifndef __EXPLOSION_MANAGER_H__	//ExplosionManager.h�C���N���[�h�K�[�h
#define __EXPLOSION_MANAGER_H__
// =============== �C���N���[�h ===================
#include "TriType.h"		//�����^���R���e���v���[�g�N���X��`�w�b�_�[
#include "Explosion.h"		//���������w�b�_�[

// =============== �萔��` =======================
const int MAX_EXPLOSION_NUM = 20;	//�ő唚����

// =============== �N���X��` =====================
class CExplosionManager
{
public:
	// ===�����o�֐��錾===
	CExplosionManager();		//�R���X�g���N�^
	~CExplosionManager();		//�f�X�g���N�^

	void Update();				//�X�V�֐�
	void Draw();				//�`��֐�


	void Create(TTriType<float> pos);	//���������֐�
	void DeleteCheck();					//���Ԃ�蔚�����폜�֐�
protected:
	// ===�����o�ϐ��錾===
	CExplosion* m_pExplosion[MAX_EXPLOSION_NUM];	//�����̔z��
private:
};

#endif // __EXPLOSION_MANAGER_H__