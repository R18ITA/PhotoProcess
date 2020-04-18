//======================================================================
// �ļ��� ColorEnhanceDib.cpp
// ���ݣ� ͼ��Ҷȵ���ɫ��ǿ-Դ�ļ�
// ���ܣ� ��1��α��ɫ��ǿ
//        
// 
//======================================================================
#include "StdAfx.h"
#include "ColorEnhanceDib.h"

//=======================================================
// �������ܣ� ���캯������ʼ�����ݳ�Ա
// ��������� λͼָ��
// ����ֵ��   ��
//=======================================================
CColorEnhanceDib::CColorEnhanceDib(CDib *pDib)
{
	m_pDib = pDib;
}


//=======================================================
// �������ܣ� ��������
// ��������� ��
// ����ֵ��   ��
//=======================================================

CColorEnhanceDib::~CColorEnhanceDib(void)
{
	
}


//=======================================================
// �������ܣ� α��ɫ��ǿ
// ��������� BYTE * bpColorsTable-ָ��Ҫ�滻��α��ɫ�����
// ����ֵ��   ��
//=======================================================

void CColorEnhanceDib::Pseudo_Color_Enhance( BYTE * bpColorsTable )
{
    int i;					// ѭ������	
	DWORD wNumColors;		// ��ɫ���е���ɫ��Ŀ
    LPRGBQUAD m_lpRgbQuad;

    wNumColors = m_pDib->GetNumOfColor();	// ��ȡԭͼ����ɫ���е���ɫ��Ŀ
    m_lpRgbQuad= m_pDib->GetRgbQuad();      //��ȡԪͼ����ɫ��ָ��
		
	if (wNumColors == 256)				// �ж���ɫ��Ŀ�Ƿ���256ɫ
	{		
				
		// ��ȡα��ɫ���룬���µ�ɫ��
		for (i = 0; i < (int)wNumColors; i++)
		{    
            // ���µ�ɫ���ɫ��ɫ��ɫ����
		    (m_lpRgbQuad+i)->rgbBlue = bpColorsTable[i * 4];
			(m_lpRgbQuad+i)->rgbGreen = bpColorsTable[i * 4 + 1];
			(m_lpRgbQuad+i)->rgbRed = bpColorsTable[i * 4 + 2];				
			// ���µ�ɫ�屣��λ
			(m_lpRgbQuad+i)->rgbReserved = 0; 			
		}
	}
	
}