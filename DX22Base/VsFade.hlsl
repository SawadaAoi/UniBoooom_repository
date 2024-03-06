/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�t�F�[�h�p���_�V�F�[�_�[
	------------------------------------
	VsFade.hlsl
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/18 ���� takagi
	�E2023/11/19 18�̑��� takagi
	�E2023/11/20 ���� takagi
	�E2023/11/24 �e�N�X�`���������Ȃ��Ƃ������邽�ߒ萔�o�b�t�@��UvOffset�ǉ� takagi

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

	VsOut.fPos = float4(VsIn.fPos, 1.0f);										//�ʒu���i�[
	VsOut.fPos = mul(VsOut.fPos, fWorld);										//���[���h�s��K�p
	VsOut.fPos = mul(VsOut.fPos, fView);										//�r���[�s��K�p
	VsOut.fPos = mul(VsOut.fPos, fProj);										//�v���W�F�N�V�����s��K�p
	VsOut.fUv = VsIn.fUv;														//�e�N�X�`�����i�[
	VsOut.fUv + 0.5f;															//UV���W�n�̌��_�𒆉��Ɉړ�
	VsOut.fUv *= fUvScale;														//�w�肳�ꂽ�{���Ŋg�k����
	VsOut.fUv += float2(0.5f - fUvScale.x / 2.0f, 0.5f - fUvScale.y / 2.0f);	//�g�k�ŉE�ɉ��т����A�ʒu��␳����
	VsOut.fUv += fUvOffset;														//�ړ��l������ꍇ�͂��̕�UV���W�����炷
	VsOut.fColor = float4(0.0f, 0.0f, 0.0f, 1.0f);								//�F�ݒ�

	// =============== �� =====================
	return VsOut;	//�o��
}