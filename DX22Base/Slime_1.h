#pragma once
#include "SlimeBase.h"
class CSlime_1 :
	public CSlimeBase
{
public:
	CSlime_1();

	~CSlime_1();

	void Union() override;
	void Explosion() override;
	void HitBranch() override;



private:

};

