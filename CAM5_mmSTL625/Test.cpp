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
				if( pGDI->pps[k][i].I > 0 &&
					pGDI->pps[k][i].perp == 1 )
					AddLin(pGDI->pps[k][i].ps[0], pGDI->pps[k][i].ps[1]) ;
			}
		}
		delete pGDI ;
		pGDI = NULL ;
	}

	return ;
}