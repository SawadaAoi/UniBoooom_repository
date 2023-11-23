/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�t�F�[�h�p�s�N�Z���V�F�[�_�[
	------------------------------------
	PsFade.hlsl
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/18 ���� takagi
	�E2023/11/19 18�̑��� takagi
	�E2023/11/20 ���� takagi

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
	// =============== �� =====================
	return float4(PsIn.fColor.x, PsIn.fColor.y, PsIn.fColor.z, (1.0f - Tex.Sample(Samp, PsIn.fUv).w));	//�e�N�X�`���̓����x�𔽓]�����h�肵������
}