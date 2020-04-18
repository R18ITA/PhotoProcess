
//======================================================================
// �ļ��� ImageRestoreDib.h
// ���ݣ� ͼ���˶���ԭ����-ͷ�ļ�
// ���ܣ� ��1���˶�ģ����
//        ��2���˶�ģ����ԭ��
//        
//======================================================================

#pragma once
#include "stdafx.h"
#include "Dib.h"
#include <math.h>
#include "ImageRestoreDib.h"

//=======================================================
// �������ܣ� ���캯������ʼ�����ݳ�Ա
// ��������� λͼָ��
// ����ֵ��   ��
//=======================================================

CImageRestoreDib::CImageRestoreDib(CDib *pDib)
{
	m_pDib = pDib;
}


//=======================================================
// �������ܣ� ��������
// ��������� ��
// ����ֵ��   ��
//=======================================================

CImageRestoreDib::~CImageRestoreDib(void)
{
	
}

//-----------------------------------------
//	����:	 ��DIBͼ��ģ��������ֱ���˶���ɵ�ģ��
//	����:		
//		CDib  *pDib      ָ��CDib���ָ��
//����ֵ:
//		BOOL             �ɹ�����TRUE�����򷵻�FALSE	
//-----------------------------------------
BOOL CImageRestoreDib::DIBMotionDegeneration()
{
	// ָ��Դͼ���ָ��
	BYTE *	lpSrc;

	LPBYTE lpDIBBits=m_pDib->GetData();//�ҵ�ԭͼ�����ʼλ��
	LONG lWidth=m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG lHeight=m_pDib->GetHeight();  //���ԭͼ��ĸ߶�

	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
    lLineBytes =m_pDib->GetLineByte();
	
	//ѭ������
	long iColumn;
	long jRow;

	//��ʱ����
	int temp,m;

	// ��ʱ����
	double p,q;
	
	int nTotTime, nTotLen, nTime;

	//�ܵ��˶�ʱ��10s
	nTotTime = 10;

	// �ܵ��˶�����10�����ص�
	nTotLen = 10;
	
	// ������ı���ϵ��
	double B;

	B = 0.1;

	//�����洢Դͼ��ͱ任�˵�ʱ������
	int *nImageDegener;

	// Ϊʱ���Ƶ����������ռ�
	nImageDegener = new int [lHeight*lLineBytes];
	
	// �����ݴ���ʱ������
	for (jRow = 0; jRow < lHeight; jRow++)
	{
		for(iColumn = 0; iColumn < lLineBytes; iColumn++)
		{
			temp=0;
			
			// ָ��Դͼ������jRow�У���iColumn�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + iColumn;

			// ���ص������ֵ����
			for ( nTime = 0; nTime < nTotTime; nTime++ )
			{
				p = (float)iColumn - (float)(nTotLen)*nTime/nTotTime;
				
				if (p > 0)
				{
					q = p - floor((double)p);
					
					if(q >= 0.5)
						m = (int)ceil((double)p);
					else
						m = (int)floor((double)p);

					// �ۼ�
					lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + m;
					temp = temp + *lpSrc;
				}	
			}
			
			// ����������ı���ϵ��
			temp = B * temp;

			temp=(int)ceil((double)temp);
			
			// ʹ��temp��ȡֵ����ȡֵ��Χ
			if(temp<0)
				temp=0;

			if(temp>255)
				temp=255;

			nImageDegener[lLineBytes*jRow + iColumn] = temp;
		}
	}	
	
	//ת��Ϊͼ��
	for (jRow = 0;jRow < lHeight ;jRow++)
	{
		for(iColumn = 0;iColumn < lLineBytes ;iColumn++)
		{
			// ָ��Դͼ������jRow�У���iColumn�����ص�ָ��			
 			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + iColumn;
	
			*lpSrc = nImageDegener[lLineBytes*jRow + iColumn];
		}
	}
	
	//�ͷŴ洢�ռ�
	delete nImageDegener;
	return true;
}

//-----------------------------------------
//	����:			��������ֱ���˶���ɵ�ģ��ͼ����и�ԭ
//	����:		
//		 CDib  *pDib       ָ��CDib���ָ��
//����ֵ:
//		BOOL             �ɹ�����TRUE�����򷵻�FALSE��
//-----------------------------------------
BOOL  CImageRestoreDib::DIBMotionRestore()
{
	// ָ��Դͼ���ָ��
	BYTE *	lpSrc;
	
    LPBYTE lpDIBBits=m_pDib->GetData();//�ҵ�ԭͼ�����ʼλ��
	LONG lWidth=m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG lHeight=m_pDib->GetHeight();  //���ԭͼ��ĸ߶�

	// ����ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
    lLineBytes = m_pDib->GetLineByte();
	
	//ѭ������
	long iColumn;
	long jRow;

	int i,n,m;

	//��ʱ����
	int temp1,temp2,
		totalq,q1,q2,z;

	double p,q;

	// ����A��ֵ
	int A = 80;
	
	//����B��ֵ
	int B = 10;
	
	//�ܵ��ƶ�����
	int nTotLen=10;

	// ͼ���Ȱ������ٸ�ntotlen
	int K=lLineBytes/nTotLen;
	
	int error[10];

	//�����洢Դͼ��ʱ������
	int *nImageDegener;

	// Ϊʱ���������ռ�
	nImageDegener = new int [lHeight*lLineBytes];

	// �����ش���������
	for (jRow = 0; jRow < lHeight; jRow++)
	{
		for(iColumn = 0; iColumn < lLineBytes; iColumn++)
		{
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + iColumn;	
			nImageDegener[lLineBytes*jRow + iColumn] = (*lpSrc);
		}
	}	
	
	for (jRow = 0; jRow < lHeight; jRow++)
	{		
		// ����error[i]
		for(i = 0; i < 10; i++)
		{			
			error[i] = 0;			
			for(n = 0; n < K; n++)
			{
				for(m = 0; m <= n; m++)
				{
					// �����Ƿ�Ϊһ�еĿ�ʼ��
					if(i == 0 && m == 0)
					{
						temp1=temp2=0;
					}					
					// ���в������
					else
					{
						lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + m*10+i;
						temp1=*lpSrc;						
						lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + m*10+i-1;
						temp2 = *lpSrc;
					}					
					error[i] = error[i] + temp1 - temp2;					
				}
			}
			error[i] = B * error[i] / K;
		}		
		for(iColumn = 0; iColumn < lLineBytes; iColumn++)
		{			
			// ����m���Լ�z
			m = iColumn / nTotLen;
			z = iColumn - m*nTotLen;				
			// ��ʼ��
			totalq = 0;	q = 0;			
			for(n = 0; n <= m; n++)
			{
				q1 = iColumn - nTotLen*n;				
				if(q1 == 0)
					q = 0;				
				// ���в������
				else
				{
					q2 = q1 - 1;					
					lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + q1;
					temp1 = *lpSrc;					
					lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + q2;
					temp2 = *lpSrc;					
					q = (temp1 - temp2) * B;			
				}				
				totalq = totalq + q;
			}			
			p = error[z];
			// �õ�f(x,y)��ֵ
			temp1 = totalq + A - p;			
			// ʹ�����ص�ȡֵ����ȡֵ��Χ
			if(temp1 < 0)
				temp1 = 0;			
			if(temp1 > 255)
				temp1 = 255;						
			nImageDegener[lLineBytes*jRow + iColumn] = temp1;
		}
	}
	//ת��Ϊͼ��
	for (jRow = 0;jRow < lHeight ;jRow++)
	{
		for(iColumn = 0;iColumn < lLineBytes ;iColumn++)
		{
			// ָ��Դͼ������jRow�У���iColumn�����ص�ָ��			
 			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + iColumn;
	
			// �洢����ֵ
			*lpSrc = nImageDegener[lLineBytes*jRow + iColumn];
		}
	}	
	
	//�ͷŴ洢�ռ�
	delete nImageDegener;
	return true;
}
