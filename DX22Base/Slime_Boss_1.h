/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�X���C��1.h
	------------------------------------
	Slime_Boss_1.h
	------------------------------------
	�쐬��	�鑺����

	�ύX����
	�E2023/11/17 �N���X�쐬 Suzumura
	�E2023/11/23 �ˌ������̒ǉ� Suzumura

========================================== */
#ifndef __SLIME_BOSS_1__H__
#define __SLIME_BOSS_1__H__

// =============== �C���N���[�h ===================
#include "Slime_BossBase.h"
#include "AnimeModel.h"
// =============== �񋓒�` ===================
enum E_BOSS_1_STATE
{
	NORMAL = 0,
	CHARGE,
	ASSAULT
};

// =============== �N���X��` =====================
class CSlime_Boss_1 :
	public CSlime_BossBase
{
public:
	// ===�v���g�^�C�v�錾===
	CSlime_Boss_1();
	CSlime_Boss_1(TPos3d<float> pos, VertexShader* pVS, AnimeModel* pModel);
	~CSlime_Boss_1();

	void Update(tagTransform3d playerTransform) override;
	void Draw() override;

	void NormalMove() override;
	void SetNormalSpeed() override;
	void SetMaxHp() override;

	void Charge(TPos3d<float> playerPos, TPos3d<float> movePos);	// ���ߊ֐�
	void Assault();	// �ˌ��֐�

private:
	void ResetAssault();
	// ===�����o�ϐ�===
	int m_nFrame;		// Update���ň����t���[��


	float m_assaultDistancePlayer;	// �ˌ����̃v���C���[�Ԃ̋�����ۑ�
	TPos3d<float> m_assaultMovePos;	// �ˌ�����MovePos��ۑ�
};


#endif //__SLIME_BOSS_1__H__
