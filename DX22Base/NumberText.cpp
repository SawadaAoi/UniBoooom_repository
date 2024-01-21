// ������

#include "NumberText.h"

const float DEF_NUM_SPACE = 55.0f;

const TDiType<int> NUM_SPLIT = { 5, 2 };
const TDiType<float> NUM_UVSCALE = { (1.0f / 5) ,(1.0f / 2) };

CNumberText::CNumberText(CCamera* pCamaer, Texture* pTexture, TDiType<float> pos, TDiType<float> size, int nDispNum, int nDigits)
	:m_pTexture(pTexture)
	, m_fRightPos(pos)
	, m_fSize(size)
	, m_nDispNum(nDispNum)
	, m_nDigits(nDigits)
	, m_fSpace(DEF_NUM_SPACE)
{
	NumStorage();

}

CNumberText::~CNumberText()
{
	SAFE_DELETE(m_pCamera);
}

void CNumberText::Update()
{

}

void CNumberText::Draw()
{
	for (int i=0;i< m_p2dPoly.size();i++)
	{
		int width = m_fSpace * i;

		m_p2dPoly[i]->SetCamera(m_pCamera);
		m_p2dPoly[i]->SetTexture(m_pTexture);
		m_p2dPoly[i]->SetSize({ m_fSize.x - width, m_fSize.y, 0.0f });
		m_p2dPoly[i]->SetPos({ m_fRightPos.x, m_fRightPos.y, 0.0f });


		int x = m_DigitArray[i] % NUM_SPLIT.x;	//�������O��W���܂�
		int y = m_DigitArray[i] / NUM_SPLIT.x;	//�z��ɓ����Ă鐔���̏ꏊ���v�Z���Ă܂�

		m_p2dPoly[i]->SetUvOffset((TDiType<float>)( NUM_UVSCALE.x * x, NUM_UVSCALE.y * y, 0.0f));
		m_p2dPoly[i]->SetUvScale((TDiType<float>)(NUM_UVSCALE.x, NUM_UVSCALE.y, 0.0f));
		m_p2dPoly[i]->Draw();
	}

}

void CNumberText::SetSpace(float nSpace)
{
	m_fSpace = nSpace;
}

void CNumberText::NumStorage()
{
	// �������z������Z�b�g
	m_DigitArray.clear();
	m_p2dPoly.clear();

	// �\�����鐔����0�ȏ�̏ꍇ
	if (0 < m_nDispNum)
	{
		// nNumber��S�Ċi�[����܂ŌJ��Ԃ�
		while (0 != m_nDispNum)
		{
			m_DigitArray.push_back(m_nDispNum % 10);	// nNumber�̉�1�����i�[����
			m_nDispNum /= 10;							// nNumber��1���X���C�h������
			m_p2dPoly.push_back(new C2dObject());
		}

	}

	// �w�茅���܂�0���߂���
	while (m_DigitArray.size() < m_nDigits)
	{
		m_DigitArray.push_back(0);
		m_p2dPoly.push_back(new C2dObject());

	}
}
