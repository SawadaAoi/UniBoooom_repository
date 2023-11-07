/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���x�[�X �N���X��`
   ---------------------------------------
   SlimeBase.h

   �쐬�� �鑺 ����

   �ύX����
   �E2023/11/04 �X���C���x�[�X�N���X�쐬 /�鑺 ����
   �E2023/11/06 ������шړ��Ɛ�����шړ��֐����쐬 �ύX�Җ��F�R�����C
   �E2023/11/06 m_fSpped(�G�̈ړ����x)��m_fVecAngle(�G�̐�����ԕ���)�̃����o�ϐ���ǉ� �ύX�Җ��F�R�����C
   �E2023/11/06 �萔SPEED_DOWN_RATIO(�Ԃ�������̃X���C���ɑ��x��n���ۂɌ������銄��)��ǉ� �ύX�Җ��F�R�����C
   �E2023/11/06 �萔MOVE_RESIST(������шړ����̃X���C���̈ړ����x�ɖ��t���[�������錸�Z���l)��ǉ� �ύX�Җ��F�R�����C
   �E2023/11/07 HitBranch�֐�(�X���C���Ƃ̐ڐG���򏈗�)��SlimeManager�Ɉړ����邽�߂ɍ폜 �ύX�Җ��F�R�����C

   ======================================== */

#ifndef __SLIME_BASE_H__
#define __SLIME_BASE_H__


#include "Model.h"
#include "Shader.h"
//#include "TriType.h"
#include "SphereInfo.h"

const float ENEMY_MOVE_SPEED = 0.01f;
const float SPEED_DOWN_RATIO = 0.6f;	//�X���C������X���C���̐�����шړ���
const float MOVE_RESIST = 0.1f;		//������шړ����̃X���C���̈ړ����x�ɖ��t���[�������錸�Z���l

/*
enum E_SLIME_LEVEL
{
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4
};
*/

class CSlimeBase
{
public:
	CSlimeBase();
	~CSlimeBase();
	void Update();
	void Draw();

	virtual void Union() = 0;
	virtual void Explosion() = 0;
	void HitMove();
	void HitMoveStart(float speed, float angle);

	//setter
	//void SetPos(TTriType<float> pos);
	void SetPos(CSphereInfo::Sphere sphere);
	void SetUse(bool onoff);
	void SetPlayer(CSphereInfo::Sphere player);

	//getter
	//TTriType<float> GetPos();
	CSphereInfo::Sphere GetPos();
	bool GetUse();

protected:
	Model* m_pModel;
	VertexShader* m_pVS;

	//TTriType<float> m_pos;
	CSphereInfo::Sphere m_sphere;
	TTriType<float> m_move;
	TTriType<float> m_scale;
	float m_fVecAngle;	//�G�̐�����ԕ���
	bool m_bUse;	//�g�p�����t���O
	float m_fSpeed;	//�G�̈ړ����x

	float m_distancePlayer;	//�v���C���[�܂ł̋���
	float m_anglePlayer;	//�v���C���[����G�l�~�[�̃A�[�N�^���W�F���g
	bool m_bHitMove;	//������ђ����ǂ���

	// ��
	//TTriType<float> m_playerPos;
	CSphereInfo::Sphere m_playerSphere;

private:

};


#endif // __SLIME_BASE_H__