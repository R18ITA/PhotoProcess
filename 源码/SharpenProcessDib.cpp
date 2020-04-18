//======================================================================
// �ļ��� SharpenProcessDib.cpp
// ���ݣ� ͼ���񻯴�����-Դ�ļ�
// ���ܣ� ��1�������ݶ��񻯺�����
//        ��2���������
//        ��3��������˹��Ĥ�񻯺���       
// 
//======================================================================

#include "StdAfx.h"
#include "SharpenProcessDib.h"
#include<math.h>


//=======================================================
// �������ܣ� ���캯������ʼ�����ݳ�Ա
// ��������� λͼָ��
// ����ֵ��   ��
//=======================================================
CSharpenProcessDib::CSharpenProcessDib(CDib *pDib)
{
	m_pDib = pDib;
}


//=======================================================
// �������ܣ� ��������
// ��������� ��
// ����ֵ��   ��
//=======================================================

CSharpenProcessDib::~CSharpenProcessDib(void)
{
	
}


//=======================================================
// �������ܣ� �����ݶ��񻯴�����
// ��������� BYTE t -����ֵ
// ����ֵ��   �ɹ�����TRUE�����򷵻�FALSE
//=======================================================

BOOL CSharpenProcessDib::GateGrad(BYTE t)
{
	
	LPBYTE	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits;	
	long i,j;			//ѭ������
	
    BYTE temp; //�ݴ�˫��һ��΢�ֽ��

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
	memset(lpNewDIBBits, (BYTE)0, lWidth * lHeight);

	//���ɨ��ͼ���е����ص�,���������ݶ��񻯴���
	
	for(j=1;j<lHeight-1;j++)
    {
		for(i=1;i<lWidth-1;i++)
		{
			//����˫��һ��΢�ֹ�ʽ���㵱ǰ���صĻҶ�ֵ
			temp=(BYTE)sqrt((float)((lpDIBBits[lWidth*j+i]-lpDIBBits[lWidth*j+(i-1)])*(lpDIBBits[lWidth*j+i]-lpDIBBits[lWidth*j+(i-1)])
                +(lpDIBBits[lWidth*j+i]-lpDIBBits[lWidth*(j-1)+i])*(lpDIBBits[lWidth*j+i]-lpDIBBits[lWidth*(j-1)+i])));
			if (temp>=t)
			{   
				if((temp+100)>255)
					lpNewDIBBits[lWidth*j+i]=255;
				else 
					lpNewDIBBits[lWidth*j+i]=temp+100;
			}
			if (temp<t)
				lpNewDIBBits[lWidth*j+i]=lpDIBBits[lWidth*j+i];
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
// �������ܣ� ������㺯��
// ��������� int tempH:ģ��߶�        
//            int tempW:ģ����                                   
//            int tempMX:ģ�������Ԫ��X����               
//            int tempMY:ģ�������Ԫ��Y����             
//            float *fpTempArray:ָ��ģ�������ָ��                      
//            float fCoef��ģ��ϵ��                                 
// ����ֵ��   �ɹ�����TRUE�����򷵻�FALSE
//=======================================================

BOOL CSharpenProcessDib::Convolution(int tempH, int tempW, int tempMX, int tempMY, float *fpTempArray, float fCoef)
{
    	
	LPBYTE	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits;	
	long i,j,k,l;			//ѭ������
	float fResult;    //�ݴ�����м���     

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
	memset(lpNewDIBBits, (BYTE)0, lWidth * lHeight);

	//���ɨ��ͼ���е����ص�,���о������
    
	for(j=tempMY;j<lHeight-tempH+tempMY+1;j++)
    {
		for(i=tempMX;i<lWidth-tempW+tempMX+1;i++)
		{
			//��������ֵ
			fResult=0;
			for(k=0;k<tempH;k++)
				for(l=0;l<tempW;l++)
					fResult=fResult+lpDIBBits[(j-tempMY+k)*lWidth+(i-tempMX+l)]*fpTempArray[k*tempW+l];
			//����ϵ��
			fResult*=fCoef;
			//ȡ����ֵ
			fResult=(float)fabs(fResult);
			//�ж��Ƿ񳬹�255
			if(fResult>255)
				//������255��ֱ�Ӹ�ֵΪ255
                lpNewDIBBits[j*lWidth+i]=255;
			else
				//δ����255����ֵΪ������
				lpNewDIBBits[j*lWidth+i]=(BYTE)(fResult+0.5);
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
// �������ܣ� ������˹�񻯴�����
// ��������� ��
// ����ֵ��   ��
//=======================================================
void CSharpenProcessDib::Laplacian( )
{
	int tempH;  //ģ��߶�
	int tempW;  //ģ����
	float tempC;  //ģ��ϵ��
	int tempMY;   //ģ������Ԫ��Y����
	int tempMX;   //ģ������Ԫ��X����
	float Template[9];   //ģ������	

	//����������˹ģ�����
	tempW=3;
	tempH=3;
	tempC=1.0;
	tempMY=1;
	tempMX=1;
	Template[0]=0.0;
    Template[1]=1.0;
	Template[2]=0.0;
	Template[3]=1.0;
	Template[4]=-4.0;
	Template[5]=1.0;
	Template[6]=0.0;
	Template[7]=1.0;
	Template[8]=0.0;

	//���þ������
	Convolution(tempH,tempW,tempMX,tempMY,Template,tempC); 

}