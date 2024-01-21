/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�X���C��2��`
	------------------------------------
	Slime_Boss_2.h
	------------------------------------
	�쐬��	sawada

	�ύX����
	�E2023/12/11 �N���X�쐬 sawada
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __SLIME_BOSS_2_H__	//Slime_Boss_2.h��`
#define __SLIME_BOSS_2_H__

// =============== �C���N���[�h ===================
#include "Slime_BossBase.h"


// =============== �N���X��` =====================
class CSlime_Boss_2 :
	public CSlime_BossBase
{
public:
	// =============== �񋓒�` ===================
	enum MOVE_STATE
	{
		NORMAL = 0,
		JUMP_CHARGE,
		JUMP,
		TARGET_SHADOW,
		DROP,
		DROP_RIGID,

		MOVE_MAX,
	};
public:
	// ===�v���g�^�C�v�錾===
	CSlime_Boss_2();
	CSlime_Boss_2(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_Boss_2();

	void Update() override;



	void SetNormalSpeed() override;
	void SetMaxHp() override;

private:
	// ===�v���g�^�C�v�錾===
	void MoveSwitch();
	void MoveNormal();
	void MoveJumpCharge();
	void MoveJump();
	void MoveTargetShadow();
	void MoveDrop();
	void MoveDropRigid();

	// ===�����o�ϐ�===
	int m_nMoveCnt[MOVE_MAX];		// �ړ������̃t���[�����Z�l
	bool m_nMoveFlg[MOVE_MAX];		// �ړ������̃t���[�����Z�l
	tagTransform3d m_PlayerParam;


	float m_assaultDistancePlayer;	// �ˌ����̃v���C���[�Ԃ̋�����ۑ�
	TPos3d<float> m_assaultMovePos;	// �ˌ�����MovePos��ۑ�
};


#endif	//!__SLIME_BOSS_2_H__