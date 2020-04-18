//======================================================================
// �ļ��� SmoothProcessDib.cpp
// ���ݣ� ͼ��ƽ��������-Դ�ļ�
// ���ܣ� ��1������ƽ��ƽ��������
//        ��2����Ȩƽ��ƽ��������
//        ��3��ѡ��ʽ��Ĥƽ��������
//        ��4����ֵ�˲�ƽ������       
// 
//======================================================================
#include "StdAfx.h"
#include "SmoothProcessDib.h"



//=======================================================
// �������ܣ� ���캯������ʼ�����ݳ�Ա
// ��������� λͼָ��
// ����ֵ��   ��
//=======================================================
CSmoothProcessDib::CSmoothProcessDib(CDib *pDib)
{
	m_pDib = pDib;
}


//=======================================================
// �������ܣ� ��������
// ��������� ��
// ����ֵ��   ��
//=======================================================

CSmoothProcessDib::~CSmoothProcessDib(void)
{
	
}

//=======================================================
// �������ܣ� ����ƽ��ƽ������
// ��������� ��
// ����ֵ��   �ɹ�����TRUE�����򷵻�FALSE
//=======================================================
BOOL CSmoothProcessDib::Average_Smooth( )
{
		
	LPBYTE	lpDst;			// ָ�򻺴�ͼ���ָ��	
	LPBYTE	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits;	
	long i,j;			//ѭ������
	BYTE average;	//�����ֵ����

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

	//���ɨ��ͼ���е����ص�,���������ֵ
	for(j = 1; j <lHeight-1; j++)
	{
		for(i = 1;i <lWidth-1; i++)
		{
			// ָ��Ŀ��ͼ���j�У���i�����ص�ָ��			
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;

            //��ǰ�㼰����Χ8����ľ�ֵ
			average=(BYTE)((float)(lpDIBBits[(j-1)*lWidth+(i-1)]+lpDIBBits[(j-1)*lWidth+i]+lpDIBBits[(j-1)*lWidth+(i+1)]
					+lpDIBBits[j*lWidth+(i-1)]+lpDIBBits[j*lWidth+i]+lpDIBBits[j*lWidth+i+1]
					+lpDIBBits[(j+1)*lWidth+(i-1)]+lpDIBBits[(j+1)*lWidth+i]+lpDIBBits[(j+1)*lWidth+i+1])/9+0.5);
					
				
				
			//����õľ�ֵ��ֵ��Ŀ��ͼ�����뵱ǰ���Ӧ�����ص�

			*lpDst = average;

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
// �������ܣ� ��Ȩƽ��ƽ������
// ��������� int Structure[3][3]-�����Ȩģ��
// ����ֵ��   �ɹ�����TRUE�����򷵻�FALSE
//=======================================================
BOOL CSmoothProcessDib::Value_Average_Smooth(int Structure[3][3])
{
	LPBYTE	lpDst;			// ָ�򻺴�ͼ���ָ��	
	LPBYTE	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits;	
	long i,j,m,n;			//ѭ������
	int sum=0; //ģ���и���Ԫ���ܺ�
	BYTE value_average;	//�����Ȩ��ֵ����

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

	//��ģ���и�Ԫ��Ȩֵ�ܺ�
	for (m = 0;m < 3;m++ )
	{
		for (n = 0;n < 3;n++)
		{
			sum+=Structure[m][n];		
		}
	}			

	//���ɨ��ͼ���е����ص�,���������Ȩ��ֵ
	for(j = 1; j <lHeight-1; j++)
	{
		for(i = 1;i <lWidth-1; i++)
		{
			// ָ��Ŀ��ͼ���j�У���i�����ص�ָ��			
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;

            //���Ȩ��ֵ
			value_average=(BYTE)((float)(lpDIBBits[(j+1)*lWidth+(i-1)]*Structure[0][0]+lpDIBBits[(j+1)*lWidth+i]*Structure[0][1]
			                     +lpDIBBits[(j+1)*lWidth+i+1]*Structure[0][2]+lpDIBBits[j*lWidth+(i-1)]*Structure[1][0]
								 +lpDIBBits[j*lWidth+i]*Structure[1][1]+lpDIBBits[j*lWidth+i+1]*Structure[1][2]
					             +lpDIBBits[(j-1)*lWidth+(i-1)]*Structure[2][0]+lpDIBBits[(j-1)*lWidth+i]*Structure[2][1]
								 +lpDIBBits[(j-1)*lWidth+(i+1)]*Structure[2][2])/sum+0.5); 				
				
			//����õļ�Ȩ��ֵ��ֵ��Ŀ��ͼ�����뵱ǰ���Ӧ�����ص�
			*lpDst = value_average;

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
// �������ܣ� ѡ��ʽ��Ĥƽ������
// ��������� ��
// ����ֵ��   �ɹ�����TRUE�����򷵻�FALSE
//=======================================================
BOOL CSmoothProcessDib::Select_Smooth( )
{
    LPBYTE	lpDst;			// ָ�򻺴�ͼ���ָ��	
	LPBYTE	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits;	
	int i,j,n;			//ѭ������
   
	BYTE pixel[9];	//������������ֵ
    float mean[9],var[9],varMin; //�����ֵ�����򷽲������Сֵ
    int nMin; //������Сʱ�������     

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

    //��9������ľ�ֵ�뷽��
    for(j=2;j<=lHeight-3;j++)
    {
	    for(i=2;i<=lWidth-3;i++)
		{
		    //��1����
			pixel[0]=lpDIBBits[(j-1)*lWidth+(i-1)];
			pixel[1]=lpDIBBits[(j-1)*lWidth+i];
			pixel[2]=lpDIBBits[(j-1)*lWidth+(i+1)];
			pixel[3]=lpDIBBits[j*lWidth+(i-1)];
			pixel[4]=lpDIBBits[j*lWidth+i];
			pixel[5]=lpDIBBits[j*lWidth+(i+1)];
			pixel[6]=lpDIBBits[(j+1)*lWidth+(i-1)];
			pixel[7]=lpDIBBits[(j+1)*lWidth+i];
			pixel[8]=lpDIBBits[(j+1)*lWidth+(i+1)];
			mean[0]=(float)(pixel[0]+pixel[1]+pixel[2]+pixel[3]+pixel[4]+pixel[5]+pixel[6]+pixel[7]+pixel[8])/9;
			var[0]=0;
			for(n=0;n<=8;n++)
				var[0]+=pixel[n]*pixel[n]-mean[0]*mean[0];
			//��2����
			pixel[0]=lpDIBBits[(j-2)*lWidth+(i-1)];
			pixel[1]=lpDIBBits[(j-2)*lWidth+i];
			pixel[2]=lpDIBBits[(j-2)*lWidth+(i+1)];
			pixel[3]=lpDIBBits[(j-1)*lWidth+(i-1)];
			pixel[4]=lpDIBBits[(j-1)*lWidth+i];
			pixel[5]=lpDIBBits[(j-1)*lWidth+(i+1)];
			pixel[6]=lpDIBBits[j*lWidth+i];
			mean[1]=(float)(pixel[0]+pixel[1]+pixel[2]+pixel[3]+pixel[4]+pixel[5]+pixel[6])/7;
			var[1]=0;
			for(n=0;n<=6;n++)
				var[1]+=pixel[n]*pixel[n]-mean[1]*mean[1];
			//��3����
			pixel[0]=lpDIBBits[(j-1)*lWidth+(i-2)];
			pixel[1]=lpDIBBits[(j-1)*lWidth+(i-1)];
			pixel[2]=lpDIBBits[j*lWidth+(i-2)];
			pixel[3]=lpDIBBits[j*lWidth+(i-1)];
			pixel[4]=lpDIBBits[j*lWidth+i];
			pixel[5]=lpDIBBits[(j+1)*lWidth+(i-2)];
			pixel[6]=lpDIBBits[(j+1)*lWidth+(i-1)];
			mean[2]=(float)(pixel[0]+pixel[1]+pixel[2]+pixel[3]+pixel[4]+pixel[5]+pixel[6])/7;
			var[2]=0;
			for(n=0;n<=6;n++)
				var[2]+=pixel[n]*pixel[n]-mean[2]*mean[2];
			//��4����
			pixel[0]=lpDIBBits[j*lWidth+i];
			pixel[1]=lpDIBBits[(j+1)*lWidth+(i-1)];
			pixel[2]=lpDIBBits[(j+1)*lWidth+i];
			pixel[3]=lpDIBBits[(j+1)*lWidth+(i+1)];
			pixel[4]=lpDIBBits[(j+2)*lWidth+(i-1)];
			pixel[5]=lpDIBBits[(j+2)*lWidth+i];
			pixel[6]=lpDIBBits[(j+2)*lWidth+(i+1)];
			mean[3]=(float)(pixel[0]+pixel[1]+pixel[2]+pixel[3]+pixel[4]+pixel[5]+pixel[6])/7;
	  		var[3]=0;
			for(n=0;n<=6;n++)
				var[3]+=pixel[n]*pixel[n]-mean[3]*mean[3];
			//��5����
			pixel[0]=lpDIBBits[(j-1)*lWidth+(i+1)];
			pixel[1]=lpDIBBits[(j-1)*lWidth+(i+2)];
			pixel[2]=lpDIBBits[j*lWidth+i];
			pixel[3]=lpDIBBits[j*lWidth+(i+1)];
			pixel[4]=lpDIBBits[j*lWidth+(i+2)];
			pixel[5]=lpDIBBits[(j+1)*lWidth+(i+1)];
			pixel[6]=lpDIBBits[(j+1)*lWidth+(i+2)]; 
			mean[4]=(float)(pixel[0]+pixel[1]+pixel[2]+pixel[3]+pixel[4]+pixel[5]+pixel[6])/7;
			var[4]=0;
			for(n=0;n<=6;n++)
				var[4]+=pixel[n]*pixel[n]-mean[4]*mean[4];	
			//��6����
			pixel[0]=lpDIBBits[(j-2)*lWidth+(i+1)];
			pixel[1]=lpDIBBits[(j-2)*lWidth+(i+2)];
			pixel[2]=lpDIBBits[(j-1)*lWidth+i];
			pixel[3]=lpDIBBits[(j-1)*lWidth+(i+1)];
			pixel[4]=lpDIBBits[(j-1)*lWidth+(i+2)];
			pixel[5]=lpDIBBits[j*lWidth+i];
			pixel[6]=lpDIBBits[j*lWidth+(i+1)]; 
			mean[5]=(float)(pixel[0]+pixel[1]+pixel[2]+pixel[3]+pixel[4]+pixel[5]+pixel[6])/7;
	  		var[5]=0;
			for(n=0;n<=6;n++)
				var[5]+=pixel[n]*pixel[n]-mean[5]*mean[5];
			//��7����
			pixel[0]=lpDIBBits[(j-2)*lWidth+(i-2)];
			pixel[1]=lpDIBBits[(j-2)*lWidth+(i-1)];
			pixel[2]=lpDIBBits[(j-1)*lWidth+(i-2)];
			pixel[3]=lpDIBBits[(j-1)*lWidth+(i-1)];
			pixel[4]=lpDIBBits[(j-1)*lWidth+i];
			pixel[5]=lpDIBBits[j*lWidth+(i-1)];
			pixel[6]=lpDIBBits[j*lWidth+i];
			mean[6]=(float)(pixel[0]+pixel[1]+pixel[2]+pixel[3]+pixel[4]+pixel[5]+pixel[6])/7;
	 		var[6]=0;
			for(n=0;n<=6;n++)
				var[6]+=pixel[n]*pixel[n]-mean[6]*mean[6];
			//��8����
			pixel[0]=lpDIBBits[j*lWidth+(i-1)];
			pixel[1]=lpDIBBits[j*lWidth+i];
			pixel[2]=lpDIBBits[(j+1)*lWidth+(i-2)];
			pixel[3]=lpDIBBits[(j+1)*lWidth+(i-1)];
			pixel[4]=lpDIBBits[(j+1)*lWidth+i];
			pixel[5]=lpDIBBits[(j+2)*lWidth+(i-2)];
			pixel[6]=lpDIBBits[(j+2)*lWidth+(i-1)];
			mean[7]=(float)(pixel[0]+pixel[1]+pixel[2]+pixel[3]+pixel[4]+pixel[5]+pixel[6])/7;
	  		var[7]=0;
			for(n=0;n<=6;n++)
				var[7]+=pixel[n]*pixel[n]-mean[7]*mean[7];
			//��9����
			pixel[0]=lpDIBBits[j*lWidth+i];
			pixel[1]=lpDIBBits[j*lWidth+(i+1)];
			pixel[2]=lpDIBBits[(j+1)*lWidth+i];
			pixel[3]=lpDIBBits[(j+1)*lWidth+(i+1)];
			pixel[4]=lpDIBBits[(j+1)*lWidth+(i+2)];
			pixel[5]=lpDIBBits[(j+2)*lWidth+(i+1)];
			pixel[6]=lpDIBBits[(j+2)*lWidth+(i+2)];
			mean[8]=(float)(pixel[0]+pixel[1]+pixel[2]+pixel[3]+pixel[4]+pixel[5]+pixel[6])/7;
	  		var[8]=0;
			for(n=0;n<=6;n++)
				var[8]+=pixel[n]*pixel[n]-mean[8]*mean[8];

			//�󷽲���С������nMin
			varMin=var[0];
			nMin=0;
			for(n=0;n<=8;n++)
			{
				if(varMin>var[n])
				{
					varMin=var[n];
					nMin=n;
				}
				
			}

            // ָ��Ŀ��ͼ���j�У���i�����ص�ָ��			
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
            //��������С�������ֵ��ֵ��Ŀ�����ص�
            *lpDst = (BYTE)(mean[nMin]+0.5);  

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
// �������ܣ� ��ֵ�˲�ƽ������
// ��������� ��
// ����ֵ��   �ɹ�����TRUE�����򷵻�FALSE
//=======================================================
BOOL CSmoothProcessDib::Middle_Smooth( )
{
	LPBYTE	lpDst;			// ָ�򻺴�ͼ���ָ��	
	LPBYTE	lpNewDIBBits;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits;	
	int i,j,x,y,m;			//ѭ������
	int flag=1;  //ѭ����־����
	BYTE pixel[9],mid; //��������ֵ����ֵ
	BYTE temp;//�м����
	
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

	//��ֵ�˲�
	for(j=1;j<lHeight-1;j++)
	{
		for(i=1;i<lWidth-1;i++)
		{
			//��3*3���δ��ڵ���������ֵ����pixel[m]
			m=0;
			for(y=j-1;y<=j+1;y++)
				for(x=i-1;x<=i+1;x++)
				{
					pixel[m]=lpDIBBits[y*lWidth+x];
					m++;
				}
			//��pixel[m]�е�ֵ����������
			do{
				flag=0;
				for(m=0;m<9;m++)
				{
					if(pixel[m]<pixel[m+1])
					{
						temp=pixel[m];
						pixel[m]=pixel[m+1];
						pixel[m+1]=temp;
						flag=1;
					}
				}

			}while(flag==1);

			//����ֵmid				
			mid=pixel[4];

			// ָ��Ŀ��ͼ���j�У���i�����ص�ָ��			
			lpDst = (LPBYTE)lpNewDIBBits + lWidth * j + i;
            //����ֵ����Ŀ��ͼ��ĵ�ǰ��
            *lpDst = mid;

		}
	}

	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
     //�ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

    return TRUE;
}