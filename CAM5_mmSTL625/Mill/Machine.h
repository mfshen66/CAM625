#ifndef _Machine_h_
#define _Machine_h_

////////////////////////////////////////////////////////////////
// CMachine : ����
/*  �������� from XRF 2010/9
 *  a���������
 *  b����������������������ͣ����ݻ�ת��ɷ�ΪΪA��B��A����B��
 *  c) �������������12�����ͣ�
 *  ����˫�ڶ���A-B��B-A��C-A��C-B��
 *  ����̨˫ת����A��-B����A��-C����B��-A����B��-C����
 *	�����빤��̨�ֱ��ת��A��-B��B��-A��C��-A��C��-B��
*/
// ���������������һ��װ��ģ�ͣ���������Լ��ľֲ�����ϵ,
class CMachine : public CObj
{
private:
	CString m_type ; // for example : "AB", "BA", or "A'B"...
	CString m_name ; // ���Ƽ��ͺ�
	int m_nAxis ; // 3, 4, 5
	RFRAME m_lf ; // ��CMill��CPart����һ����������ϵ 
	// ������������ģ��...
	// ����������˶���ϵ...
	BOX3D m_box ;
public:
	CMachine(int nAxis) ;
	~CMachine() ;

	//int GetBox(BOX3D* box) ;
	//int Draw(void* pVI, int drawMode) ;
	//int Pick(PINFO* pinfo) ;
	int Serialize(CArchive& ar) ;
} ;
////////////////////////////////////////////////////////////////

#endif