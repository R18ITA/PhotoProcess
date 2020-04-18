//======================================================================
// �ļ��� SharpenProcessDib.h
// ���ݣ� ͼ���񻯴�����-ͷ�ļ�
// ���ܣ� ��1�������ݶ��񻯺�����       
//        ��2��������㺯����
//        ��3��������˹��Ĥ�񻯺���        
// 
//======================================================================

#pragma once

#include "Dib.h" 
#include "afx.h"

class CSharpenProcessDib
{
public:
	// ���캯������ʼ�����ݳ�Ա
	CSharpenProcessDib(CDib *pDib);

	// ��������	
	~CSharpenProcessDib(void);

	// �����ݶ��񻯺���
	BOOL GateGrad(BYTE t);
	
	//������㺯��
    BOOL Convolution(int tempH, int tempW, int tempMX, int tempMY, float *fpTempArray, float fCoef); 

	// ������˹��Ĥ�񻯺���
	void Laplacian( ); 

private:
    // ���ݳ�Ա,CDib�����ָ�� 
	CDib *m_pDib; 

};
