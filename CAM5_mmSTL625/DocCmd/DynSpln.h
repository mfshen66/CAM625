/*	2000/8/19 nt
 *	header file of class CDynSpln
 */
#ifndef _DynSPln_h_
#define _DynSpln_h_

class CCAMDoc ;
class CCAMView ;

///////////////////////////////////////////////////////////////
//	dynamic b-spline curve
// nt rewrite 2010/9/7
class CDynSpln : public CCommand // ��̬������
{
private:
	double m_r ; // �жϵ��غϵİ뾶
	RFRAME m_lf ; // nt add 2010/9/7
	double m_dTol ; // b-spline discrete tol
	int	m_moved ; // 0,1:not moved, moved
	int m_posi ; // m_posi >= 0 ��ʾ��ǰ�϶��������;-1��ʾ���϶�״̬
	int	m_max ; // max number of interpolating point
	int	m_np ; // number of interpolating points
    	STR3D m_ps ; // ԭʼ��ֵ�㴮[0,m_max-1]
	STR3D m_temp ; // nt add 2010/9/7, ���ڲ�ֵʱ��
	BSCUR* m_nurbs ; // ��̬����
	int m_na ; // m_na <= m_max
	STR3D m_as ; // [0, m_max-1]
	
public:
	CDynSpln(CCAMDoc* pDoc, CCAMView* pView) ;
	~CDynSpln() ;

	int	Create(double r, double dTol, int max) ;
	int	GetID() ;
	int	OnLButtonDown(UINT nFlags, double p[3], double v[3]) ;
	int	OnLButtonUp(UINT nFlags, double p[3], double v[3]) ;
	int	OnMouseMove(UINT nFlags, double p[3], double v[3]) ;
	int	OnRButtonDown(UINT nFlags, double p[3], double v[3]) ;
	int OnReturn() ; // nt add 2009/10/21
	int	Cancel() ;

	int	Start() ; // 0,1:error,success
	int	End() ; // 0,1:error,success
private:
	void Draw(int mode) ; // 0,1:eraze,draw, note that: mode must be 0 or 1
	int	Append(int posi) ; // ����һ����ֵ��,tail==0,at head;tail==1, at tail
	int	RemoveDoublePt() ;
	int	Modify(PNT3D p) ; // �޸Ĳ�ֵ��

	int	Near(PNT3D p) ; // return an index of point in m_intpPs which is near to p under the tol of m_r
	int	Disc() ; // 0,1:error,success. use tol
	int	IsPeriodic() ; // 0,1:no,yes
	int	IntpPsTs() ; // 0,1:error,success. b-spline interpolate
} ;
///////////////////////////////////////////////////////////////
#endif

