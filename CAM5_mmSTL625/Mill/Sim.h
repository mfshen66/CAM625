/*	2010/3/31 nt
 *	the head file of CSim
 */
#ifndef _Sim_h_
#define _Sim_h_

////////////////////////////////////////////////////////////////
// CSim : �����˶�����
class CSim
{
private:
	int m_state ; // 0=δ��ʼ, 1=����, 2=���
	CTool* m_pTool ; // ����
	RFRAME m_old ; // m_pTool��ԭʼλ��
	GCODETPATH* m_pGT ; // gcode for 3-axis, ����, ����������������
	int m_n ; // ��λ������
	double m_minsp ; // mm/min
	double m_maxsp ; // mm/min
	int m_pause ; // nt add 2010/7/2, 1=pause

	UINT m_t ; // last update time, unit=second/1000, 0=initial_value
	int m_i ; // �ϴθ��¸��߹���i����λ��, 0=initial_value
	double m_speed ; // mm/min
	RFRAME m_lf1 ; // ��λ��:i
	RFRAME m_lf2 ; // ��λ��:i+1
	double m_d ; // from m_lf1.O to m_lf2.O
	RFRAME m_lf ; // m_pTool�ĵ�ǰλ��,��m_lf1��m_lf2֮��
	int m_bi ; // ��ǰG����Ŀ�������
	char m_cb[256] ; // ��ǰG�����һ�У���һ��block
	int m_rs ; // running state, see GCT_API.h
	
public:
	CSim() ;
	~CSim() ;

	int IsPaused() ; // nt add 2010/7/2
	int Pause() ; // nt add 2010/7/2
	int Continue() ; // nt add 2010/7/2
	int GetState() ;
	int SetGT(GCODETPATH* pGT) ;
	CTool* GetTool() ;
	int SetTool(CTool* pTool) ;
	int SetMinSpeed(double minsp) ;
	int SetMaxSpeed(double maxsp) ;
	int GetBI() ;
	int GetCurBlk(CString& cb) ;
	int GetCurPos(PNT3D cp) ;
	int GetRS() ;
	int UpdateTPN(int i) ; // update tool path node
	int Start(UINT ct) ; // ct=current time
	int Update(UINT ct) ; // ct=current time
	int Draw(void* pVI) ;
} ;
////////////////////////////////////////////////////////////////
#endif