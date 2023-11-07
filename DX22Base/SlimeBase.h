/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���x�[�X �N���X��`
   ---------------------------------------
   SlimeBase.h

   �쐬�� �鑺 ����

   �ύX����
   �E2023/11/04 �X���C���x�[�X�N���X�쐬 /�鑺 ����


   ======================================== */

#ifndef __SLIME_BASE_H__
#define __SLIME_BASE_H__


#include "Model.h"
#include "Shader.h"
//#include "TriType.h"
#include "SphereInfo.h"


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
	bool m_bUse;	//�g�p�����t���O
	float m_fSpeed;

	float m_distancePlayer;	//�v���C���[�܂ł̋���
	float m_anglePlayer;	//�v���C���[����G�l�~�[�̃A�[�N�^���W�F���g

	// ��
	//TTriType<float> m_playerPos;
	CSphereInfo::Sphere m_playerSphere;

private:

};


#endif // __SLIME_BASE_H__