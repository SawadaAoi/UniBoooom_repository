// –¢Š®¬

#pragma once
#include "2dObject.h"
#include "Texture.h"
#include "DiType.h"	//‚R‚Â‚Ì“¯‚¶Œ^‚ğ‚ÂŒ^


class CNumberText 
{
public:
	CNumberText(CCamera* pCamaer, Texture* pTexture, TDiType<float> pos, TDiType<float> size, int nDispNum, int nDigits);
	~CNumberText();
	void Update();
	void Draw();

	void SetSpace(float nSpace);

private:
	void NumStorage();

	Texture* m_pTexture;
	CCamera* m_pCamera;
	std::vector<C2dObject*> m_p2dPoly;
	std::vector<int> m_DigitArray;
	int m_nDispNum;
	int m_nDigits;
	TDiType<float> m_fRightPos;
	TDiType<float> m_fSize;
	float m_fSpace;
};

