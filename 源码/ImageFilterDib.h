//======================================================================
// �ļ��� ImageFilterDib.h
// ���ݣ� ͼ���˾�������-ͷ�ļ�
// ���ܣ� ��1����ƬЧ��������       
//        ��2�����Ч��������
//        ��3���ڰ�Ч������        
//        ��4����Ч������
//        ��5������Ч������
//======================================================================

#pragma once

#include "afx.h"

# include "Dib.h"


class CImageFilterDib
{
public:
	// ���캯������ʼ�����ݳ�Ա
	CImageFilterDib(CDib *pDib);

	// ��������	
	~CImageFilterDib(void);

	// ͼ��ɫ����
	void Negative();

	//ͼ��ĸ���Ч������
	void Emboss();
	
	//�ڰ�Ч������
    void ColorToBW();

	//���Ϸ�ʽ��Ч������

    void ComFog(); 

	//����Ч������
	void LaplacianB();

private:
    // ���ݳ�Ա,CDib�����ָ�� 
	CDib *m_pDib; 

};