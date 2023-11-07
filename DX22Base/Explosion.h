//wb_[p@----------------------------------------------------
/*========================================
HEW/UniBoooom!!
---------------------------------------
­pwb_
---------------------------------------
Expplosion.h

ì¬Ò A F¶

ÏXð
E2023/11/03 wb_[ì¬ / A F¶
E2023/11/05 p[^Ýè /@A F¶
E2023/11/07 Ï^TriType¨CSphereÉ /A F¶
======================================== */

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__
#include "Model.h"
#include "Shader.h"
#include "Sphereinfo.h"


//=============== \¢Ìè` =====================

//=============== NXè` =====================

//=============== ñè` =======================

class CExplosion
{
public:
	CExplosion();
	~CExplosion();
	void Update();
	void Draw();
	void SetSphere(CSphereInfo::Sphere sphere);
	void SetExplode(bool YN);
	bool GetExplode();
	CSphereInfo::Sphere GetSphere();


protected:
	Model* m_pModel;
	VertexShader* m_pVS;
	CSphereInfo::Sphere m_Sphere;
	float m_fSize;
	bool m_bExploded;	//­µ½ÌtO

private:
};

#endif // __EXPLOSION_H__
