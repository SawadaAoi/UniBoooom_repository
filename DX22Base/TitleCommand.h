/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�R�}���h��`
	---------------------------------------
	TitleCommand.h

	�쐬��	takagi

	�ύX����
	�E2023/12/16 ���� takagi
	�E2024/02/05 ���t�@�N�^�����O takagi
	�E2024/02/15 �g�k�ω����ԕύX takagi

========================================== */

#ifndef __TITLE_COMMAND_H__	//TitleCommand.h�C���N���[�h�K�[�h
#define __TITLE_COMMAND_H__

// =============== �C���N���[�h =====================
#include "TitleObj.h"	//�e�̃w�b�_
#include <memory.h>		//ptr�Ǘ�
#include "FrameCnt.h"	//�J�E���^
#include <map>			//�A�z�R���e�i

// =============== �N���X��` =====================
class CTitleCommand :public CTitleObj	//�J�n���Y�[���A�E�g����^�C�g���p���ʃI�u�W�F
{
public:
	// ===�񋓒�`==========
	enum E_STATE
	{
		E_STATE_UNSELECTED,			//��I�����
		E_STATE_SELECTED,			//�I�����
		E_STATE_DECIDE,				//������
		E_STATE_MAX,				//�v�f��
	};	//���(�e�N�X�`���ɉe��)
private:
	// ===�萔��`==========
	const std::map<E_STATE, unsigned int> MAP_MAX_ANIMATION_NUM =
	{
		{E_STATE_UNSELECTED, 1},	//��I�����̃A�j���[�V�����R�}��
		{E_STATE_SELECTED, 1},		//�I�����̃A�j���[�V�����R�}��
		{E_STATE_DECIDE, 1},		//���莞�̃A�j���[�V�����R�}��
	};	//�A�j���[�V�����ԍ��̍ő�l
	const std::map<E_STATE, unsigned int> MAP_ANIMATION_INTERVAL =
	{
		{E_STATE_UNSELECTED, 1},	//��I�����̃A�j���[�V�����Ԋu
		{E_STATE_SELECTED, 1},		//�I�����̃A�j���[�V�����Ԋu
		{E_STATE_DECIDE, 1},		//���莞�̃A�j���[�V�����Ԋu
	};	//�A�j���[�V�����Ԋu
	const std::map<E_STATE, unsigned  int> MAP_ANIMATION_FRAME =
	{
		{E_STATE_UNSELECTED, 30},	//��I�����̃A�j���[�V��������
		{E_STATE_SELECTED, 30},	//�I�����̃A�j���[�V��������
		{E_STATE_DECIDE, 30},		//���莞�̃A�j���[�V��������
	};	//�A�j���[�V��������
protected:
	// ===�萔��`==========
	const std::map<E_STATE, const TTriType<float>> MAP_SCALE =
	{
		{E_STATE_UNSELECTED, {120.0f * 3.5f, 26.0f * 3.5f, 0.0f}},				//��I�����̊g�k��
		{E_STATE_SELECTED, {120.0f * 3.5f * 1.1f, 26.0f * 3.5f * 1.1f, 0.0f}},	//�I�����̊g�k��
		{E_STATE_DECIDE, {120.0f * 3.5f * 1.2f, 26.0f * 3.5f * 1.2f, 0.0f}},	//���莞�̊g�嗦
	};	//��Ԃɂ��g�k��
public:
	// ===�v���g�^�C�v�錾===
	virtual ~CTitleCommand();								//�f�X�g���N�^
	virtual void Update() override;							//�X�V
	virtual void ChangeState(const E_STATE& eState) final;	//��ԕύX
	virtual bool DesideAnimeFin() final;					//����A�j���Đ�����
protected:
	// ===�v���g�^�C�v�錾===
	CTitleCommand(const E_STATE& eInitState);	//�R���X�g���N�^
private:
	// ===�ϐ��錾===
	E_STATE m_eTexNo;											//��ԗ�(�e�N�X�`����)
	unsigned int m_unAnimeNo;									//�A�j���[�V�����R�}�ԍ�(�e�N�X�`���c)
	TTriType<float> m_fScale;									//�傫���Ǘ�
	std::shared_ptr<TTriType<float>> m_pfReScalingStartSize;	//�g�k�ω��J�n���̑傫��
	std::shared_ptr<CFrameCnt> m_pFrameCnt;						//�g�k�ω��p�J�E���^
	std::shared_ptr<CFrameCnt> m_pAnimeInterval;				//�A�j���[�V�����Ԋu
	static bool m_bCntUpDwn;									//�J�E���g�A�b�v�E�_�E���؊��t���O
	static std::shared_ptr<CFrameCnt> m_pAlphaCnt;				//�����x�ω��p�J�E���^
};	//�^�C�g���p�R�}���h

#endif	//!__TITLE_COMMAND_H__