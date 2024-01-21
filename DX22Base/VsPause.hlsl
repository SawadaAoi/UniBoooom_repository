/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�|�[�Y�p���_�V�F�[�_�[
	------------------------------------
	VsPause.hlsl
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/18 ���� takagi
	�E2023/11/19 18�̑��� takagi
	�E2023/11/20 ���� takagi
	�E2023/12/01 2dObject�ɓK����`�ɕύX takagi
	�E2023/12/06 pose��pause�C���A�|�[�Y�����\�� takagi

========================================== */

// =============== �\���̒�` =====================
struct VS_IN
{
	float3 fPos : POSITION0;	//�ʒu���
	float2 fUv : TEXCOORD0;		//�e�N�X�`�����
};	//�󂯎����
struct VS_OUT
{
	float4 fPos : SV_POSITION;	//�ʒu���
	float2 fUv : TEXCOORD0;		//�e�N�X�`�����
	float4 fColor : COLOR0;		//�F���
};	//�n�����


// =============== �萔�o�b�t�@ =====================
cbuffer Matrix : register(b0)
{
	float4x4 fWorld;	//���[���h�s��
	float4x4 fView;		//�r���[�s��
	float4x4 fProj;		//�v���W�F�N�V�����s��
};	//�s��
cbuffer Uv : register(b1)
{
	float2 fUvScale;	//UV�g�k
	float2 fUvOffset;	//UV�ړ�
	float4 fColor;		//�F
};	//UV����

/* ========================================
	���C���֐�
	-------------------------------------
	���e�F���_���Ƃɏ���ݒ肷��
	-------------------------------------
	����1�FVS_IN VsIn�FDirectX����󂯎����
	-------------------------------------
	�ߒl�F���̃s�N�Z���ɕ\������F���(rgba)
=========================================== */
VS_OUT main(VS_IN VsIn)
{
	// =============== �ϐ��錾 =====================
	VS_OUT VsOut;	//�o�͗p

	// =============== �X�V =====================
	VsOut.fPos = float4(VsIn.fPos, 1.0f);	//�ʒu���i�[
	VsOut.fPos = mul(VsOut.fPos, fWorld);	//���[���h�s��K�p
	VsOut.fPos = mul(VsOut.fPos, fView);	//�r���[�s��K�p
	VsOut.fPos = mul(VsOut.fPos, fProj);	//�v���W�F�N�V�����s��K�p
	VsOut.fUv = VsIn.fUv;					//�e�N�X�`�����i�[
	VsOut.fUv + 0.5f;						//UV���W�n�̌��_�𒆉��Ɉړ�
	VsOut.fColor = fColor;					//�F�ݒ�

	// =============== �� =====================
	return VsOut;	//�o��
}