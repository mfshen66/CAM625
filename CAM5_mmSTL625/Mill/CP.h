/*	2010/9/25 nt
 *	the head file of CP
 */
#ifndef _CP_h_
#define _Cp_h_

////////////////////////////////////////////////////////////////
// motion type from XRF 2010/9
#define MOTIONTYPE_MAXNUM 20 
enum EMotionType
{
	UF_PATH_MOTION_TYPE_UNDEFINED = 0, /* Motion type undefined. */
	UF_PATH_MOTION_TYPE_RAPID = 1, /* Motion type rapid. */ // �����˶�
	UF_PATH_MOTION_TYPE_ENGAGE = 2, /* Motion type engage. */ // ����
	UF_PATH_MOTION_TYPE_CUT = 3, /* Motion type cut. */ // ����
	UF_PATH_MOTION_TYPE_RETRACT = 4, /* Motion type retract. */ // �˵�
	UF_PATH_MOTION_TYPE_FIRST_CUT = 5, /* Motion type first cut. */ //��һ������
	UF_PATH_MOTION_TYPE_APPROACH = 6, /* Motion type approach. */ // �ӽ�
	UF_PATH_MOTION_TYPE_STEPOVER = 7, /* Motion type stepover. */ // ����
	UF_PATH_MOTION_TYPE_DEPARTURE = 8, /* Motion type departure.  This is
										only valid for a lathe. */ // �뿪
	UF_PATH_MOTION_TYPE_TRAVERSAL = 9, /* Motion type traversal. */ //��Խ
} ;
//--------------------------------------------------------------
// CP : cutting parameter = ��������
typedef struct _cp CP ;
struct _cp
{
	double speeds[MOTIONTYPE_MAXNUM] ; // unit = mm/min
	int spindle ; // r/min
	double depth ; // cutting depth, unit=mm
	//double m_tol ; // �ӹ�����, unit=mm
	//double m_dTol ; // ��ɢ����, unit=mm
	//double m_dAng ; // ��ɢ�ǶȾ��ȣ�����
	//int m_motionDir ; // �ߵ�����,0=˳ϳ,1=��ϳ
	//double m_slotD ; // �������,unit=mm
	//double m_stepOver ; // ���, unit=mm
	//int m_bm ; // ������ʽ
	//double m_bAng ; // �µ��Ƕ�
	//int m_em ; // �˵���ʽ
} ;

/*
 *	CP.cpp
 */
void cpInit(CP* pCP) ;
////////////////////////////////////////////////////////////////

#endif