/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���x�[�X �N���X��`
   ---------------------------------------
   SlimeBase.h

   �쐬�� �鑺 ����

   �ύX����
   �E2023/11/04 �X���C���x�[�X�N���X�쐬 /�鑺 ����
   �E2023/11/08 �X���C���̃T�C�Y��\���񋓂��`�@�ύX�ҁF�R�����C
   �E2023/11/08 �X���C���̃T�C�Y��Ԃ��֐����쐬�@�ύX�ҁF�R�����C
   �E2023/11/08 GetPos��GetSphere�ɖ��O��ύX / �R�����C
   �E2023/11/08 �X���C���̈ړ����x���擾����֐����쐬 / �R�����C

   ======================================== */

#ifndef __SLIME_BASE_H__
#define __SLIME_BASE_H__


#include "Model.h"
#include "Shader.h"
//#include "TriType.h"
#include "SphereInfo.h"

const float ENEMY_MOVE_SPEED = 0.01f;
const float SPEED_DOWN_RATIO = 0.6f;
const float MOVE_RESIST = 0.05f;

// =============== �񋓒�` =======================
enum E_SLIME_LEVEL
{
	LEVEL_NONE,

	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4,

	MAX_LEVEL = LEVEL_4
};


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
	virtual void HitBranch() = 0;

	//setter
	//void SetPos(TTriType<float> pos);
	void SetPos(CSphereInfo::Sphere sphere);
	void SetUse(bool onoff);
	void SetPlayer(CSphereInfo::Sphere player);

	//getter
	//TTriType<float> GetPos();
	CSphereInfo::Sphere GetSphere();
	bool GetUse();
	E_SLIME_LEVEL GetSlimeLevel();	//�X���C���̃T�C�Y���擾
	float GetSlimeSpeed();			//�X���C���̈ړ����x���擾

protected:
	Model* m_pModel;
	VertexShader* m_pVS;

	//TTriType<float> m_pos;
	CSphereInfo::Sphere m_sphere;
	TTriType<float> m_move;
	TTriType<float> m_scale;
	float m_fVecAngle;
	bool m_bUse;	//�g�p�����t���O
	float m_fSpeed;
	E_SLIME_LEVEL m_eSlimeSize;

	float m_distancePlayer;	//�v���C���[�܂ł̋���
	float m_anglePlayer;	//�v���C���[����G�l�~�[�̃A�[�N�^���W�F���g
	bool m_bHitMove;	//������ђ����ǂ���

	// ��
	//TTriType<float> m_playerPos;
	CSphereInfo::Sphere m_playerSphere;

private:

};


#endif // __SLIME_BASE_H__