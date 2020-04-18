//======================================================================
// �ļ��� FrequencyFilterDib.h
// ���ݣ� ͼ��Ƶ���˲���ǿ-ͷ�ļ�
// ���ܣ� ��1������Ҷ�任������       
//        ��2�������ͨ�˲�����
//        ��3�������ͨ�˲�����
// 
//======================================================================

#pragma once

#include "Dib.h" 
#include "afx.h"

class CFrequencyFilterDib
{
public:
	// ���캯������ʼ�����ݳ�Ա
	CFrequencyFilterDib(CDib *pDib);

	// ��������	
	~CFrequencyFilterDib(void);


    //����Ҷ�任����
    void fourier(double * data, int height, int width, int isign);

	// �����ͨ�˲�����
	void Perfect_Low_Filter(int u,int v);
	
	// �����ͨ�˲�����
	void Perfect_High_Filter(int u,int v); 

private:
    // ���ݳ�Ա,CDib�����ָ�� 
	CDib *m_pDib; 

};