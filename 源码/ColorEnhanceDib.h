//======================================================================
// �ļ��� ColorEnhanceDib.h
// ���ݣ� ͼ��Ҷȵ���ɫ��ǿ-ͷ�ļ�
// ���ܣ� ��1��α��ɫ��ǿ
//        
// 
//======================================================================

#pragma once

#include "Dib.h"

#include "afx.h"

class CColorEnhanceDib
{
public:
	// ���캯������ʼ�����ݳ�Ա
	CColorEnhanceDib(CDib *pDib);

	// ��������	
	~CColorEnhanceDib(void);

	// α��ɫ��ǿ
	void Pseudo_Color_Enhance( BYTE * bpColorsTable );

	
private:
    // ���ݳ�Ա,CDib�����ָ�� 
	CDib *m_pDib; 

};
