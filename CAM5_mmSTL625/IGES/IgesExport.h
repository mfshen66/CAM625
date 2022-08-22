#ifndef _IgesExport_h_
#define _IgesExport_h_

////////////////////////////////////////////////////////////////
// ����IGES
// nt 2012/10/13
class CIgesExport
{
private:
	int m_flags ; // ����:&1=point, &2=curve, &4=�ü�����
	IGES* m_iges ; // �洢���������IGES entity
	COA m_fs ;
	double m_tol ;

public:
	CIgesExport(int flags) ;
	~CIgesExport() ;

	void AddFeature(CFeature* pF) ;
	int Export(CString& fileName) ; // return 0=error, 1=ok
private:
	IENTITY* iPoint2Entity(PNT3D p) ;
	IENTITY* iCurve2Entity(CURVE* curve, INTERVAL* interval) ;
	IENTITY* iSurface2Entity(SURFACE* surface, BOXUV* boxuv) ;
	IENTITY* iTFace2Entity(TFACE* pTFace) ;
} ;
////////////////////////////////////////////////////////////////

#endif
