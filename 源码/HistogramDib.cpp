//======================================================================
// �ļ��� HistogramDib.cpp
// ���ݣ� ֱ��ͼ��ǿ����-Դ�ļ�
// ���ܣ� ��1��ֱ��ͼͳ�ƺ�����
//        ��2��ֱ��ͼ���⻯������
//        ��3��ֱ��ͼƥ�䣨�涨����������
// 
//======================================================================

#include "StdAfx.h"
#include "HistogramDib.h"


//=======================================================
// �������ܣ� ���캯������ʼ�����ݳ�Ա
// ��������� λͼָ��
// ����ֵ��   ��
//=======================================================

CHistogramDib::CHistogramDib(CDib *pDib)
{
	m_pDib = pDib;
}


//=======================================================
// �������ܣ� ��������
// ��������� ��
// ����ֵ��   ��
//=======================================================

CHistogramDib::~CHistogramDib(void)
{
	
}


//=======================================================
// �������ܣ� ֱ��ͼͳ�ƺ���
// ��������� float *probability -�Ҷȷֲ������ܶ�
// ����ֵ��   ��
//=======================================================

void CHistogramDib::Histogram_Statistic( float *probability)
{
	LPBYTE	lpSrc;			// ָ��ԭͼ���ָ��	
	long i,j;			//ѭ������	
	int gray[256]; // �Ҷȼ���
	BYTE pixel;	//����ֵ

	LPBYTE lpDIBBits=m_pDib->GetData();//�ҵ�ԭͼ�����ʼλ��
	LONG lWidth=m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG lHeight=m_pDib->GetHeight();  //���ԭͼ��ĸ߶�

	// �Ҷȼ���������ʼ��
	memset(gray,0,sizeof(gray));

	//���ɨ��ͼ���е����ص�,���лҶȼ���ͳ��
	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth; i++)
		{
			// ָ��ԭͼ������j�У���i�����ص�ָ��			
			lpSrc = (LPBYTE)lpDIBBits + lWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��ΪBYTE����
			pixel = (BYTE)*lpSrc;

			// �Ҷ�ͳ�Ƽ���
			gray[pixel]++;

		}
	}
	
	// ����Ҷȸ����ܶ�
	for(i=0;i<256;i++)
    {
		probability[i] = gray[i] / (lHeight * lWidth *1.0f);
    }
	
}

//=======================================================
// �������ܣ� ֱ��ͼ���⻯����
// ��������� ��
// ����ֵ��   �ɹ�����TRUE�����򷵻�FALSE
//=======================================================

BOOL CHistogramDib::Histogram_Equalization( )
{
	LPBYTE	lpSrc;			// ָ��ԭͼ���ָ��	
	LPBYTE	lpDst;			// ָ�򻺴�ͼ���ָ��	
	LPBYTE	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits;	
	long i,j;			//ѭ������
	BYTE pixel;	//����ֵ

	//ԭͼ��Ҷȷֲ������ܶȱ���
	float fPro[256];
	//�м����
	float temp[256];
	int nRst[256];

	LPBYTE lpDIBBits=m_pDib->GetData();//�ҵ�ԭͼ�����ʼλ��
	LONG lWidth=m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG lHeight=m_pDib->GetHeight();  //���ԭͼ��ĸ߶�
	
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
	if (hNewDIBBits == NULL)
	{
		return FALSE;
	}
	
	lpNewDIBBits = (LPBYTE )LocalLock(hNewDIBBits);

	
	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);

	// ��ʼ���м����temp
	memset(temp, 0, sizeof(temp));

	// ��ȡԭͼ��Ҷȷֲ��ĸ����ܶ�
	Histogram_Statistic(fPro);

	//����ֱ��ͼ���⻯����
	for(i = 0; i < 256; i++)
	{
		if(i == 0)
		{
			temp[0] = fPro[0];	 
		}
		else
		{
			temp[i] = temp[i-1] + fPro[i];	 
		}
		nRst[i] = (int)(255.0f * temp[i] + 0.5f);
	}	


	//��ֱ��ͼ���⻯��Ľ��д��Ŀ��ͼ����
	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth; i++)
		{
			// ָ��ԭͼ������j�У���i�����ص�ָ��			
			lpSrc = (LPBYTE)lpDIBBits + lWidth * j + i;
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��ΪBYTE����
			pixel = (BYTE)*lpSrc;

			*lpDst = (BYTE)(nRst[pixel]);

		}
	}
	
	// ���ƾ��⻯������ͼ��ԭͼ����
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
    //�ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	return TRUE;

}

//=======================================================
// �������ܣ� ֱ��ͼ�涨����ƥ�䣩����
// ��������� BYTE bGray -�涨ֱ��ͼ�ĻҶȼ�
//            int *npMap -�涨ֱ��ͼӳ���ϵ
//            float *fpPro -�涨�Ҷȷֲ�����
// ����ֵ��   �ɹ�����TRUE�����򷵻�FALSE
//=======================================================

BOOL CHistogramDib::Histogram_Match( BYTE bGray, int *npMap, float *fpPro)
{
	LPBYTE	lpSrc;			// ָ��ԭͼ���ָ��	
	LPBYTE	lpDst;			// ָ�򻺴�ͼ���ָ��	
	LPBYTE	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits;	
	long i,j;			//ѭ������
	BYTE pixel;	//����ֵ

	//ԭͼ��Ҷȷֲ������ܶȱ���
	float fPro[256];
	//�м����
	float temp[256];
	//�Ҷ�ӳ������
	int nMap[256];

	LPBYTE lpDIBBits=m_pDib->GetData();//�ҵ�ԭͼ�����ʼλ��
	LONG lWidth=m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG lHeight=m_pDib->GetHeight();  //���ԭͼ��ĸ߶�
	
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
	if (hNewDIBBits == NULL)
	{
		return FALSE;
	}
	
	lpNewDIBBits = (LPBYTE )LocalLock(hNewDIBBits);

	
	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ0
	lpDst = (LPBYTE)lpNewDIBBits;
	memset(lpDst, (BYTE)0, lWidth * lHeight);

	// ��ȡԭͼ��Ҷȷֲ��ĸ����ܶ�
	Histogram_Statistic(fPro);

	// ����ԭͼ���ۼ�ֱ��ͼ
	for (i = 0; i < 256; i++)
	{
		if (i == 0)
		{
			temp[0] = fPro[0];			 
		}
		else
		{
			temp[i] = temp[i-1] + fPro[i];			 
		}
			fPro[i] = temp[i];
	}

	// ����涨�任����ۼ�ֱ��ͼ
	for (i = 0; i < bGray; i++)
	{
		if (i == 0)
		{
			temp[0] = fpPro[0];
		}
		else
		{
			temp[i] = temp[i-1] + fpPro[i];
		}
		fpPro[i] = temp[i];
	}

	// ȷ��ӳ���ϵ
	for (i = 0; i < 256; i++)
	{
		// ��ӽ��Ĺ涨ֱ��ͼ�Ҷȼ�
		int m = 0;
		// ��С��ֵ
		float min_value = 1.0f;
		// ö�ٹ涨ֱ��ͼ���Ҷ�
		for (j = 0; j < bGray; j++)
		{
			// ��ǰ��ֵ
			float now_value = 0.0f;
			//  ��ֵ����
			if (fPro[i] - fpPro[j] >= 0.0f)
				now_value = fPro[i] - fpPro[j];
			else
				now_value = fpPro[j] - fPro[i];
			// Ѱ����ӽ��Ĺ涨ֱ��ͼ�Ҷȼ�
			if (now_value < min_value)
			{
				// ��ӽ��ĻҶȼ�
				m = j;
				// ��С��ֵ
				min_value = now_value;
			}
		}

		// �����Ҷ�ӳ���
		nMap[i] = npMap[m];
	}

	// �Ը����ؽ���ֱ��ͼ�涨��ӳ�䴦��
	for (j = 0; j < lHeight; j ++)
	{
		for (i = 0; i < lWidth; i ++)
		{
			// ָ��ԭͼ������j�У���i�����ص�ָ��			
			lpSrc = (LPBYTE)lpDIBBits + lWidth * j + i;
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��ΪBYTE����
			pixel = (BYTE)*lpSrc;
            //��Ŀ��ͼ�����ӳ�䴦��
			*lpDst = (BYTE)(nMap[pixel]);

		}
	}
	
	// ����ֱ��ͼ�涨��������ͼ��ԭͼ����
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
    //�ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	return TRUE;

}