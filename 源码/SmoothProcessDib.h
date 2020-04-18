//======================================================================
// �ļ��� SmoothProcessDib.h
// ���ݣ� ͼ��ƽ��������-ͷ�ļ�
// ���ܣ� ��1������ƽ��ƽ��������
//        ��2����Ȩƽ��ƽ��������
//        ��3��ѡ��ʽ��Ĥƽ��������
//        ��4����ֵ�˲�ƽ������       
// 
//======================================================================

#pragma once

#include "Dib.h"

#include "afx.h"

class CSmoothProcessDib
{
public:
	// ���캯������ʼ�����ݳ�Ա
	CSmoothProcessDib(CDib *pDib);

	// ��������	
	~CSmoothProcessDib(void);

	// ����ƽ��ƽ������
	BOOL Average_Smooth( );

	// ��Ȩƽ��ƽ������
	BOOL Value_Average_Smooth( int Structure[3][3]);

	// ѡ��ʽ��Ĥƽ������
	BOOL Select_Smooth( );

	// ��ֵ�˲�ƽ������
	BOOL Middle_Smooth( );

	

private:
    // ���ݳ�Ա,CDib�����ָ�� 
	CDib *m_pDib; 

};
