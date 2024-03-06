/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�|�[�Y�p�s�N�Z���V�F�[�_�[
	------------------------------------
	PsPause.hlsl
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/18 ���� takagi
	�E2023/11/19 18�̑��� takagi
	�E2023/11/20 ���� takagi
	�E2023/12/01 2dPolygon�ɓK����`�ɕύX takagi
	�E2023/12/06 pose��pause�C���A�|�[�Y�����\�� takagi
	�E2024/01/11 �u�����h�X�e�[�g�C���ɔ��������x���� takagi

========================================== */

// =============== �\���̒�` =====================
struct PS_IN
{
	float4 fPos : SV_POSITION;	//�ʒu���
	float2 fUv : TEXCOORD0;		//�e�N�X�`�����
	float4 fColor : COLOR0;		//�F���
};	//�󂯎����

// =============== �o�b�t�@ =====================
Texture2D Tex : register(t0);		//�e�N�X�`��
SamplerState Samp : register(s2);	//�t�F�[�h�p�T���v���[�X�e�[�g

/* ========================================
	���C���֐�
	-------------------------------------
	���e�F�s�N�Z�����ɕ`���F�̏���ݒ肷��
	-------------------------------------
	����1�FPS_IN PsIn�F���_�V�F�[�_�[����󂯎����
	-------------------------------------
	�ߒl�F���̃s�N�Z���ɕ\������F���(rgba)
=========================================== */
float4 main(PS_IN PsIn) : SV_TARGET
{
	// =============== �X�V =====================
	float2 fUv = (PsIn.fUv - 0.5f) * 2.0f;												//UV���W�X�V
	float2 fCentPos = float2(0.0f, 0.0f);												//���S�ʒu
	float4 fColor = Tex.Sample(Samp, PsIn.fUv);											//�e�N�X�`���\��t��
	float fMinAlpha = 0.4f;															//�����x�ŏ��l
	float fMaxAlpha = 1.0f;																//�����x�ő�l
	float fReviseAlpha = -0.24f;														//�����x�␳�l
	fColor.w = min(max(distance(fUv, fCentPos) + fReviseAlpha, fMinAlpha), fMaxAlpha);	//�����x�ύX�F�O���f�[�V�����̂��������A�ڂ₯���l��

	// =============== �� =====================
	return fColor;	//�m�肵���F
}