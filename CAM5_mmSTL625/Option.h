#pragma once

////////////////////////////////////////////////////////////////
//	system options
//	nt add 2010/11/28
//1����0.35����
//1Ӣ�磽72��
//С���=9��=3.163����
/*	�ֺ�������Ļ����ϵ  
Ǧ��ӡˢ��ʱ�������С��ʹ���ֺ���Ϊ��λ�ġ�
Ȼ�����˵����Ű���е�ʱ��������Ĵ�С���չ��ʱ�׼��
�á�������Ϊ��λ�ˡ������������ֱ�׼��ͳһ������û
��ֱ�ӻ���Ĺ�ʽ�� 

�������ֺ��������������д����ŵ��ֺű�ʾ��ǰ��
���õ��ֺš���ֵ��Ժ��׵Ļ��������ʹ��
��������2.845=���������Ĺ�ʽ�����л��㣬����72����
����ԼΪ25.3mm���ҡ�ͬ���ģ�Ҳ���Է�����ʹ�ò�����
���ִ�С����2.845����������������߰���1����Լ��
0.35mm���л��㡣 

1Ӣ��=2.54����=25.4���ס� 
���   �ֺ�         ���� 
1     �����غţ�    89 
2     ���غţ�      54  
3      ����         42 
4      С����       36 
5     ����һ�ţ�    31.5       
6      һ��         28    
7     ��Сһ�ţ�    24 
8      ����         21 
9      С����       18 
10     ����         15.75 
11    ��С���ţ�    15 
12     �ĺ�         14    
13     С�ĺ�       12 
14     ���         10.5 
15     С���       9        
16     ����         7.875 
17     С����       6.875 
18     �ߺ�         5.25 
19     �˺�         4.5 
*/
//--------------------------------------------------------------
typedef struct _option OPTION ;
struct _option
{
	CStr fontName ;
	double fontH ;
	int bkColor ;
	int unit ; // 0=mm, 1=m, 2=inch
	double gridSize ; // ����߳�
	double refPlaneHalfSize ;
	UINT simUpdateT ; // ����CSim��ʱ����, unit=0.001second
	UINT simDispT ; // ���»��Ƶ�ʱ����, unit=0.001second
	int colorIndex ; // ��ɫ����
	int materialIndex ; // ��������
	int width ; // �߿�, ��λ��0.01mm
	CStr ltName ; // ��������
	double tol ;
	double ang ;
	double curDTol ; // ������ɢ
	double curDAng ; // ������ɢ
	double curDChd ; // ������ɢ
	double surDTol ; // �����ʷ�
	double surDAng ; // �����ʷ�
	double surDChd ; // �����ʷ�
	double fitTol ; // ����ݲ�, unit=mm
	double extL ; // ���쳤��, unit=mm
	double extR ; // ����뾶, unit=mm
	double extA ; // ����Բ�Ľ�, unit=����
	double attMin ; // ������Сֵ
	double attMax ; // �������ֵ
	int nZPlane ; // ����ƽ��
	double pSize ; // ��Ĵ�С, unit=m
	int pSize2 ; // in pixel
	double r ; // ��Բ
	double r1 ; // ����Բ
	double r2 ; // ����Բ
	double planeW ;
	double cylH ;
	double cylR ;
	double coneH ;
	double coneR ;
	double sphR ;
	double torusR1 ;
	double torusR2 ;
	int dimArrowType ; // �ߴ��ͷ����
	double dimH ;
	int dimColor ;
	CStr dimFontName ;
	int dimLinearPre[2] ; // ���Գߴ�precision, ��ʾС����ǰ�����λ
	int dimAngularPre[2] ; // �Ƕȳߴ�precision, ��ʾС����ǰ�����λ
	CStr hTName ; // ����������
	double hAng ; // �Ƕ�
	double hW1 ; // �����߼��1
	double hW2 ; // �����߼��2
	double hTol ; // ���������
	double symH ; // ���Ÿ߶�
	CStr txtFontName ;
	double txtH ;
	int txtBkColor ;
	int txtColor ;
	// 625��Ŀ������nt add 2021/6/15
	double dTol ; // �Ҹ߲� 0.1mm
	double minEdge ; // ��������̱߳������񶥵���С���룬ȱʡֵ1.0mm
	double maxEdge ; // ����Ƭ���ڱ���󳤶ȣ�ȱʡֵ100.0mm
	double minAngle ; // ��������С�ǣ���λ=��
	double minArea ; // ����Ƭ��С�����ȱʡֵ1.0mm^2
	double bTol ; // ����Ƭ�������жϣ�ȱʡֵ0.001mm���߽��ݲ�
	// �������ѡ�δ��...
} ;

/*
 *	Option.cpp
 */
int optionInit(OPTION* option) ;
int optionSerialize(OPTION* option, CArchive& ar) ;
int optionLoad(OPTION* option, CStr& pathName) ;
int optionSave(OPTION* option, CStr& pathName) ;
////////////////////////////////////////////////////////////////