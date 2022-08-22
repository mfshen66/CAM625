/*	2000/8/19 nt
 *	header file of class doc command CDrawCir
 */
#ifndef _DrawCir_h_
#define _DrawCir_h_

///////////////////////////////////////////////////////////////
//	dynamic draw circle
class CDrawCir : public CCommand // ��̬��Բ
{
private:
	int m_stage ; // nt add 2009/9/5
	PNT3D m_p1 ;
	PNT3D m_p2 ;
	int m_cor ; // nt add 2009/11/25, 1=������У��

public:
	CDrawCir(CCAMDoc* pDoc, CCAMView* pView) ;
	~CDrawCir() ;

	int	GetID() ;
	int SetCor(int cor) ; // nt add 2009/11/25
	int	OnLButtonDown(UINT nFlags, double p[3], double v[3]) ;
	int	OnLButtonUp(UINT nFlags, double p[3], double v[3]) ;
	int	OnMouseMove(UINT nFlags, double p[3], double v[3]) ;
	int	OnRButtonDown(UINT nFlags, double p[3], double v[3]) ;
	int OnReturn() ; // nt add 2009/10/21
	int	Cancel() ;
private:
	void Draw() ;
} ;
///////////////////////////////////////////////////////////////

#endif