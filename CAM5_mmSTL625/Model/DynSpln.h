/*	1997/4/6 nt
 *	��̬������ͷ�ļ�
 */
#ifndef _DynSpln_h_
#define _DynSpln_h_

///////////////////////////////////////////////////////////////
//	dynamic b-spline curve
class CDynSpln // ��̬������
{
private:
	int			m_maxNum ;// �����ƶ������
    int         m_idDraw ; // 0:��δ������,1:�ѻ�����
	int         m_idSave ;
	int			m_idModify ;// 0:���޸�,1:���޸�,2:���޸�
    int			m_idPeriodic ;
    int			m_colorIndex ;// ��ɫ����
    int         m_idNew ;// 1:��ʼ���µ�����

    int         m_posi ; // ��Ϊm_nCount+1,������һ��ֵ��;
                          // ��С�ڻ����m_nCount,���޸����в�ֵ��
	int			m_nCount ;// ��ֵ������
    PCSPLINE	m_staticSpline ;/ ��̬����

    STR1D		m_p_u ;// [0,m_maxNum-1]
    STR3D       m_tangPoints ;// [0,m_maxNum-1]
	STR3D		m_intpPoints ;// ��ֵ�㴮[0,m_maxNum-1]
	PCSPLINE	m_dynmSpline ;// ��̬����
	
	int			m_nAppxi ; // �ƽ���ĸ���
	STR3D		m_appxis ; // ���ߵ���ɢ�ƽ�
public:
	CDynSpln(int maxNum = 128) ;
	~CDynSpln() ;
	
	void		Init() ;
	int			Start(PNT3D p) ;// ��ʼ��һ����ֵ��
	int			Append(PNT3D p) ; // ����һ����ֵ��
	int			Modify(PNT3D p) ; // �޸�����ֵ��
	int			Update() ;// ������������
	void		Draw() ; // �����߱䶯����
    void        Eraze() ;
	int			Disc(double accumChord) ;
	PCSPLINE	GetSpline() ;
    int         GetIdNew() ;
    int         GetIdDraw() ;
    void        SetIdDraw(int idDraw) ;
    void        DrawIntpPoints() ;
} ;
///////////////////////////////////////////////////////////////
	
#endif