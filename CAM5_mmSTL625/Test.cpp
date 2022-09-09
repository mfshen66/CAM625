#include "stdafx.h"
#include "CAM.h"
#include "Models.h"
#include "Mills.h"
#include "SelSet.h"
#include "CAMDoc.h"
#include "Model\SND.h"
#include "Dialogs.h"

/*void CCAMDoc::OnTest()
{
	int i, n = GetSelected(60, 2), rt ;
	double gc[3] ;
	if( n == 2 )
	{
		FList fs[2] ;
		double ps[2][3] ;
		for( i = 0 ; i < 2 ; i++ )
		{
			fs[i] = (FList)GetObj(i) ;
			gc[0] = 1./3 ; //GetU(i) ;
			gc[1] = 1./3 ; //GetV(i) ;
			gc[2] = 1.-gc[0]-gc[1] ;
			fs[i]->GetPos(gc, ps[i]) ;
		}

		Pl* polyline = NULL ;
		if( m_pPart->m_pGM == NULL )
			return ;
		rt = m_pPart->m_pGM->CalGeodesicLine(fs[0], ps[0], fs[1], ps[1], 1.e-6, &polyline) ;
		if( polyline )
		{
			m_pPart->m_pGM->polylines[m_pPart->m_pGM->nPolyline] = polyline ;
			(m_pPart->m_pGM->nPolyline)++ ;
		}
	}

	return ;
}*/

/*void CCAMDoc::OnTest()
{
	int i, n = GetSelected(60, 1) ;
	double gc[3], t, d ;
	if( n == 1 )
	{
		FList fs[2] ;
		double ps[2][3] ;
		fs[0] = (FList)GetObj(0) ;
		gc[0] = 1./3 ; //GetU(i) ;
		gc[1] = 1./3 ; //GetV(i) ;
		gc[2] = 1.-gc[0]-gc[1] ;
		fs[0]->GetPos(gc, ps[0]) ;
		
		d = m_pPart->m_pGM->POLHead[1]->Snap(m_pPart->m_pGM, fs, ps, 1.e-6, i, t) ;
		AddPt(ps[0]) ;
		AddPt(ps[1]) ;
		AddPt(&fs[1]->VertexUsed[0]->Coord.x) ;
		AddPt(&fs[1]->VertexUsed[1]->Coord.x) ;
		AddPt(&fs[1]->VertexUsed[2]->Coord.x) ;
	}

	return ;
}*/


/*
void CCAMDoc::OnTest()
{
	int i, k ;
	GridModel* pGM = m_pPart->m_pGM ;
	POList polys[2] ;
	polys[0] = pGM->POLHead[11] ;
	polys[1] = pGM->POLHead[12] ;
	GDINFO* pGDI ;
	pGM->CalGDInfo(polys, 1.e-3, &pGDI) ;
	if( pGDI )
	{
		for( k = 0 ; k < 2 ; k++ )
		{
			for(i = 1 ; i <= pGDI->ns[k] ; i++ )
			{
				if (pGDI->pps[k][i].I > 0 &&
					pGDI->pps[k][i].perp == 1)
				{
					AddLin(pGDI->pps[k][i].ps[0], pGDI->pps[k][i].ps[1]) ;
				}
			}
		}
		delete pGDI ;
		pGDI = NULL ;
	}

	return ;
}

*/


#include <iostream>
using namespace std;

void CCAMDoc::OnTest()
{
	//PNT3D iPntOfSegment1 = { -1, -1, -1 }, iPntOfSegment2 = { 1, 1, 1 },  // 线段的两个端点
	//	iPntOnPlane = { 0, 0, 0 };
	//VEC3D iNormPlane = {0, 0, 1};  // 平面的法矢及平面上一点
	//double iTolLength = TOLLENGTH, iTolAngle = TOLANGLE;  // 长度容差及角度容差
	//PNT3D oPntsOfIntersection[2] = { 1, 1, 1 };
	//int res = mathSegmentIntPln(iPntOfSegment1, iPntOfSegment2, iPntOnPlane, iNormPlane, iTolLength, iTolAngle, oPntsOfIntersection);
	
	//PNT3D iPntOfTri1 = { 1, 1, 1 }, iPntOfTri2 = { 0, 1, 0 }, iPntOfTri3 = { 1, 0, 1 }, // 三角形的三个顶点
	//	iPntOnPlane = { 0, 0, 0 };
	//VEC3D iNormPlane = { 0, 0, 1 };  // 平面的法矢及平面上一点
	//double iTolLength = TOLLENGTH, iTolAngle = TOLANGLE; // 长度容差及角度容差
	//PNT3D oPntsOfIntersection[3] = { 1 };

	//int res = mathPlnIntTri(
	//	iPntOfTri1, iPntOfTri2, iPntOfTri3, // 三角形的三个顶点
	//	iPntOnPlane, iNormPlane,  // 平面的法矢及平面上一点
	//	iTolLength, iTolAngle,  // 长度容差及角度容差
	//	oPntsOfIntersection); // 交点数组的指针

	//STLPNT3D iSTLPntOfTri1 = { 1, 1, 1 }, iSTLPntOfTri2 = { 0, 1, 0 }, iSTLPntOfTri3 = { 1, 0, 1 }, // 三角形的三个顶点
	//	iSTLPntOnPlane = { 0, 0, 0 };
	//STLVECTOR iSTLNormPlane = { 0, 0, 1 };  // 平面的法矢及平面上一点
	//double iTolLength = TOLLENGTH, iTolAngle = TOLANGLE; // 长度容差及角度容差
	//STLPNT3D oSTLPntsOfIntersection[3];
	//int res = mathPlnIntTri(
	//	iSTLPntOfTri1, iSTLPntOfTri2, iSTLPntOfTri3, // 三角形的三个顶点
	//	iSTLPntOnPlane, iSTLNormPlane,  // 平面的法矢及平面上一点
	//	iTolLength, iTolAngle,  // 长度容差及角度容差
	//	oSTLPntsOfIntersection); // 交点数组的指针

	GridModel* pGM = m_pPart->m_pGM;

	POList polist = pGM->POLHead[1], offset = nullptr;
	double chordal_height = 0;
	offset = polist->GeodesicOffsetNonFlexible(5, 1, chordal_height);
	int n = 0;
	for (int i = 1; i <= (offset->DNum); i++)
		n += (offset->ENum[i] - offset->SNum[i] + 1); // 计算需要等距的点数？？？
	for (size_t i = 1; i < n; i++)
	{
		PNT3D p, q;
		memcpy(p, &offset->PTrail[i], sizeof(PNT3D));
		memcpy(q, &offset->PTrail[i + 1], sizeof(PNT3D));
		AddLin(p, q);
	}

	return;
}