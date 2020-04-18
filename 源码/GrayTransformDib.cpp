//======================================================================
// �ļ��� GrayTransformDib.cpp
// ���ݣ� ͼ��Ҷȱ任��ǿ����-Դ�ļ�
// ���ܣ� ��1�����ԻҶ���ǿ��
//        ��2���ֶ����ԻҶ���ǿ��
//        ��3���������������ԻҶ���ǿ��
// 
//======================================================================

#include "StdAfx.h"
#include "GrayTransformDib.h"
#include<math.h>


//=======================================================
// �������ܣ� ���캯������ʼ�����ݳ�Ա
// ��������� λͼָ��
// ����ֵ��   ��
//=======================================================
CGrayTransformDib::CGrayTransformDib(CDib *pDib)
{
	m_pDib = pDib;
}


//=======================================================
// �������ܣ� ��������
// ��������� ��
// ����ֵ��   ��
//=======================================================

CGrayTransformDib::~CGrayTransformDib(void)
{
	
}


//=======================================================
// �������ܣ� ���ԻҶ���ǿ
// ��������� BYTE gMin-�任��Ŀ��ͼ�����С�Ҷ�ֵ
//            BYTE gMax-�任��Ŀ��ͼ������Ҷ�ֵ
// ����ֵ��   �ɹ�����TRUE�����򷵻�FALSE
//=======================================================

BOOL CGrayTransformDib::Linear_Transform( BYTE gMin, BYTE gMax)
{
	LPBYTE	lpSrc;			// ָ��ԭͼ���ָ��	
	LPBYTE	lpDst;			// ָ�򻺴�ͼ���ָ��	
	LPBYTE	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits;	
	long i,j;			//ѭ������
	BYTE pixel;	//����ֵ

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

	//���ɨ��ͼ���е����ص�,���лҶ����Ա任
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

			//���ݹ�ʽ(5-2)���Ŀ��ͼ�����뵱ǰ���Ӧ�����ص�ĻҶ�ֵ

			*lpDst = (BYTE)(((float)(gMax-gMin)/255)*pixel+gMin+0.5);

		}
	}
	
	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
    //�ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	return TRUE;


}



//=======================================================
// �������ܣ� �ֶ����ԻҶ���ǿ
// ��������� BYTE gSrc1, BYTE gSrc2-ԭͼ��Ҷ�����ֶε�
//            BYTE gDst1, BYTE gDst2-�任���Ŀ��ͼ��Ҷ�����ֶε�
// ����ֵ��   �ɹ�����TRUE�����򷵻�FALSE
//=======================================================

BOOL CGrayTransformDib::Seg_Linear_Transform( BYTE gSrc1, BYTE gSrc2,BYTE gDst1, BYTE gDst2)
{
	LPBYTE	lpSrc;			// ָ��ԭͼ���ָ��	
	LPBYTE	lpDst;			// ָ�򻺴�ͼ���ָ��	
	LPBYTE	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits;	
	long i,j;			//ѭ������
	BYTE pixel;	//����ֵ

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

	//���ɨ��ͼ���е����ص�,���лҶȷֶ����Ա任
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

			//���ݹ�ʽ(5-3)�ұ���ʽ���Ŀ��ͼ�����뵱ǰ���Ӧ�����ص�ĻҶ�ֵ
			if(pixel<gSrc1)
			{
				*lpDst = (BYTE)(((float)gDst1/gSrc1)*pixel+0.5);
			}

			//���ݹ�ʽ(5-3)�ұ���ʽ���Ŀ��ͼ�����뵱ǰ���Ӧ�����ص�ĻҶ�ֵ
			if((pixel>=gSrc1)&&(pixel<=gSrc2))
			{
				*lpDst = (BYTE)(((float)(gDst2-gDst1)/(gSrc2-gSrc1))*(pixel-gSrc1)+gDst1+0.5);
			}

			//���ݹ�ʽ(5-3)�ұ���ʽ���Ŀ��ͼ�����뵱ǰ���Ӧ�����ص�ĻҶ�ֵ
			if((pixel>gSrc2)&&(pixel<=255))
			{
				*lpDst = (BYTE)(((float)(255-gDst2)/(255-gSrc2))*(pixel-gSrc2)+gDst2+0.5);
			}

		}
	}
	
	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
    //�ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	return TRUE;

}

//=======================================================
// �������ܣ� �������������ԻҶ���ǿ
// ��������� double a, double b,double c-��������λ�ú���״�Ĳ���
// ����ֵ��   �ɹ�����TRUE�����򷵻�FALSE
//=======================================================
BOOL CGrayTransformDib::Log_Transform( double a, double b, double c)
{
	LPBYTE	lpSrc;			// ָ��ԭͼ���ָ��	
	LPBYTE	lpDst;			// ָ�򻺴�ͼ���ָ��	
	LPBYTE	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits;	
	long i,j;			//ѭ������
	BYTE pixel;	//����ֵ

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

	//���ɨ��ͼ���е����ص�,���ж������������ԻҶȱ任
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

			//���ݹ�ʽ(5-4)���Ŀ��ͼ�����뵱ǰ���Ӧ�����ص�ĻҶ�ֵ
             
			*lpDst = (BYTE)((log((double)(pixel+1)))/(b*log(c))+a+0.5);

		}
	}
	
	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
    //�ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	return TRUE;

}

