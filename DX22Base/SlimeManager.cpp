/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムマネージャー クラス実装
   ---------------------------------------
   SlimeManager.cpp

   作成者：鈴村 朋也

   変更履歴
   ・2023/11/05 スライムマネージャークラス作成 /鈴村 朋也

   ======================================== */
#include "SlimeManager.h"
#include "Slime_1.h"

#include <stdlib.h>


// =============== コンストラクタ =============
CSlimeManager::CSlimeManager()
	:m_nRandNum(0)
{
	//"スライム1"生成
	for (int i = 0; i < MAX_SLIME_1; i++)
	{
		m_pSlime[i] = new CSlime_1;
	}
	/*
	//"スライム2"生成
	for (int i = 0; i < MAX_SLIME_2; i++)
	{
		m_pSlime[i] = new CSlime_2;
	}
	//"スライム3"生成
	for (int i = 0; i < MAX_SLIME_2; i++)
	{
		m_pSlime[i] = new CSlime_3;
	}
	//"スライム4"生成
	for (int i = 0; i < MAX_SLIME_2; i++)
	{
		m_pSlime[i] = new CSlime_4;
	}
	*/
}

// =============== デストラクタ =============
CSlimeManager::~CSlimeManager()
{
	//"スライム1"削除
	for (int i = 0; i < MAX_SLIME_1; i++)
	{
		if (m_pSlime[i] != nullptr)
		{
			delete m_pSlime[i];
			m_pSlime[i] = nullptr;
		}
	}
}

/*
 ========================================
   関数 Update()
 ----------------------------------------
   内容：更新処理
 ======================================== */
void CSlimeManager::Update()
{

	//"スライム1"更新
	for (int i = 0; i < MAX_SLIME_1; i++)
	{
		float m_posX, m_posZ;
		int _RandNum = 0;
		// 疑似乱数
		m_nRandNum = rand();	//疑似乱数取得
		_RandNum = m_nRandNum;	//退避

		//ランダムX決定
		m_nRandNum %= 10;	//(0~10)
		if (m_nRandNum < 5)  m_posX = (float)-m_nRandNum;
		else m_posX = (float)m_nRandNum - 5.0f;

		//ランダムZ決定
		_RandNum -= 999;
		_RandNum %= 10;	//(0~10)
		if (_RandNum < 5)  m_posZ = (float)-_RandNum;
		else m_posZ = (float)_RandNum - 5.0f;

		// 敵 生成
		Generate(TTriType<float>(m_posX, 0.0f, m_posZ));
		m_pSlime[i]->Update();
	}
}
/*
 ========================================
   関数 Draw()
 ----------------------------------------
   内容：描画処理
 ======================================== */
void CSlimeManager::Draw()
{
	//"スライム1"描画
	for (int i = 0; i < MAX_SLIME_1; i++)
	{
		m_pSlime[i]->Draw();
	}
}

void CSlimeManager::Generate(TTriType<float> pos)
{
	CSphereInfo::Sphere sphere;
	sphere.radius = 0.0f;
	sphere.pos = pos;

	for (int i = 0; i < MAX_SLIME_1; i++)
	{
		// スライムのuseを検索
		if (m_pSlime[i]->GetUse() == false)
		{
			m_pSlime[i]->SetUse(true);	//useをtrueに
			m_pSlime[i]->SetPos(sphere);	//posを設定
			break;						//見つけたらbreak
		}
	}
	
}
