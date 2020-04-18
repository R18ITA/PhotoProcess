//======================================================================
// �ļ��� GrayTransformDib.h
// ���ݣ� ͼ��Ҷȱ任��ǿ����-ͷ�ļ�
// ���ܣ� ��1�����ԻҶ���ǿ��
//        ��2���ֶ����ԻҶ���ǿ��
//        ��3���������������ԻҶ���ǿ��
//        
// 
//======================================================================

#pragma once

#include "Dib.h"

#include "afx.h"

class CGrayTransformDib
{
public:
	// ���캯������ʼ�����ݳ�Ա
	CGrayTransformDib(CDib *pDib);

	// ��������	
	~CGrayTransformDib(void);

	// ���ԻҶ���ǿ
	BOOL Linear_Transform( BYTE gMin, BYTE gMax);

	// �ֶ����ԻҶ���ǿ
	BOOL Seg_Linear_Transform( BYTE gSrc1, BYTE gSrc2,BYTE gDst1, BYTE gDst2);

	// �������������ԻҶ���ǿ
	BOOL Log_Transform( double a, double b, double c);

	

private:
    // ���ݳ�Ա,CDib�����ָ�� 
	CDib *m_pDib; 

};
