//======================================================================
// �ļ��� HistogramDib.h
// ���ݣ� ֱ��ͼ��ǿ����-ͷ�ļ�
// ���ܣ� ��1��ֱ��ͼͳ�ƺ�����
//        ��2��ֱ��ͼ���⻯������
//        ��3��ֱ��ͼƥ�䣨�涨����������
// 
//======================================================================

#pragma once

#include "Dib.h"

#include "afx.h"

class CHistogramDib
{
public:
	// ���캯������ʼ�����ݳ�Ա
	CHistogramDib(CDib *pDib);

	// ��������	
	~CHistogramDib(void);

	// ֱ��ͼͳ�ƺ���
	void Histogram_Statistic( float *probability);

	// ֱ��ͼ���⻯����
	BOOL Histogram_Equalization( );

	// ֱ��ͼ�涨����ƥ�䣩����
	BOOL Histogram_Match( BYTE bGray, int *npMap, float *fpPro);

private:
    // ���ݳ�Ա,CDib�����ָ�� 
	CDib *m_pDib; 

};
