
//======================================================================
// �ļ��� ImageFilterDib.h
// ���ݣ� ͼ���˾�������-ͷ�ļ�
// ���ܣ� ��1����ƬЧ��������       
//        ��2�����Ч��������
//        ��3���ڰ�Ч������        
//        ��4����Ч������
//        ��5������Ч������
//======================================================================

#include "StdAfx.h"
#include "ImageFilterDib.h"
#include "Dib.h"
#include <math.h>

//=======================================================
// �������ܣ� ���캯������ʼ�����ݳ�Ա
// ��������� λͼָ��
// ����ֵ��   ��
//=======================================================

CImageFilterDib::CImageFilterDib(CDib *pDib)
{
	m_pDib = pDib;
}


//=======================================================
// �������ܣ� ��������
// ��������� ��
// ����ֵ��   ��
//=======================================================

CImageFilterDib::~CImageFilterDib(void)
{
	
}

//-----------------------------------------
//	����:			ͼ��ɫ����
//-----------------------------------------
void CImageFilterDib::Negative()
{
	//ͼ��߿�
	LONG width=m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG height=m_pDib->GetHeight();  //���ԭͼ��ĸ߶�
	LPBYTE lpDst;
	//���ݷ��ʵ���ʼλ�ã��������ݵı䶯�ȿ�����Ԫ��
	//Ҳ�������ֽڣ������Ʊ�����ʹ��
    lpDst=this->m_pDib->GetData();
	if(this->m_pDib->IsGrade()==1)//�ԻҶ�ͼ��Ĵ���
	{
		for(int i = 0; i <width * height ; i ++) 
			{
				*lpDst=255-*lpDst;
				lpDst++;
			}
	}
	else                       //�Բ�ɫͼ��Ĵ���
	{
		for(int i = 0; i <width * height *3; i += 3) 
		{
			for(int j=0;j<3;j++)
			{
				*lpDst=255-*lpDst;
				lpDst++;
			}
		}
	}
}
//-----------------------------------------
//	����:			ʵ��ͼ��ĸ���Ч��
//-----------------------------------------
void CImageFilterDib::Emboss()
{
	//ͼ��߿�
	LONG width=m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG height=m_pDib->GetHeight();   //���ԭͼ��ĸ߶�
   	LPBYTE  lpDst;
	LPBYTE  lpTemp;
	UINT Lb; 
	WORD BC;
   	BC=this->m_pDib->GetBitCount();
   	lpDst=this->m_pDib->GetData();
	lpTemp=this->m_pDib->GetData();
	Lb=this->m_pDib->GetLineByte();
	lpTemp=lpTemp+Lb;
	for(int j=0;j<height-1;j++)//��������
	{
		lpTemp=lpTemp+BC/8;
		for(int i=0;i<width-1;i++)//��������
		{
			for(int n=0;n<BC/8;n++)
			{
				*lpDst=abs(*lpDst-*lpTemp)+128;
				if(*lpDst>255)               //����ֵ�Ƿ�����
				*lpDst=255;
				lpDst++;
				lpTemp++;
			}
		}
          //�������һ�е�Ԫ�ػص���һ����ʼλ��
		lpDst=lpDst+BC/8;
	}
}
//-----------------------------------------
//	����:			ʵ��ͼ��ĺڰ�Ч��
//-----------------------------------------
void CImageFilterDib::ColorToBW()
{
	//ͼ��߿�
	LONG width=m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG height=m_pDib->GetHeight();  //���ԭͼ��ĸ߶�
	LPBYTE lpDst;
    lpDst=this->m_pDib->GetData();
	WORD BC;
    BC=this->m_pDib->GetBitCount();
	UINT Lb;
	Lb=this->m_pDib->GetLineByte();
	LPBYTE  lpTemp;//ָ����ʱͼ������ָ��
	lpTemp=lpDst;
	for(int y = 0; y < height;y++)
	{
		for(int x=0;x<width;x++)
		{
			for(int i=0;i<3;i++)
			{
	*lpDst=(*(lpTemp+y*Lb+x*BC/8)+*(lpTemp+y*Lb+x*BC/8+1)+*(lpTemp+y*Lb+x*BC/8+2))/3;    //ƽ��ֵ��
			 lpDst++;
			}
		}
	}
}
//-----------------------------------------
//	����:			ʵ�ָ��Ϸ�ʽ����Ч��
//	����:		
//		f			������
//-----------------------------------------
void CImageFilterDib::ComFog()
{
	//ͼ��߿�
	LONG width=m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG height=m_pDib->GetHeight();  //���ԭͼ��ĸ߶�
     WORD BC;
     BC=this->m_pDib->GetBitCount();//��ȡ��������ռ�õ�λ��
	UINT Lb;
	Lb=this->m_pDib->GetLineByte();
   	LPBYTE  lpDst;//ָ��ԭʼͼ������ָ��
	LPBYTE  lpTemp;//ָ����ʱͼ������ָ��
	LPBYTE  lpTemp1;//ָ����ʱͼ������ָ��
	lpDst=this->m_pDib->GetData();
	lpTemp=(LPBYTE)malloc(sizeof(BYTE)*width*height*BC/8);//����ռ�
	lpTemp1=lpTemp;
	//��ͼ�����ݸ���һ��
	int sum = width * height*BC/8;
	memcpy(lpTemp, lpDst, sum);
	int f=5;//����������
	int k;
	int m,n;
	for(int j=0;j<height;j++)//���Ƹ߶�
	{
		for(int i=0;i<width*BC/8;i++)
		{
			k = abs(rand() % f);
			m = i + k* BC/8;
			n = j + k ;
			// �Գ���ͼ������ĵ������Ӧ����
			if (m > (width-1)*BC/8) 
				m = (width-1) *BC/8;
			if (n > height-1) 
				n = height-1;
			lpTemp1=lpTemp1+n*Lb+m;
			//����ͼ������ֵ
			*lpDst=*lpTemp1;
			lpTemp1=lpTemp;
			lpDst++;	
		}	
	}	
}

//-----------------------------------------
//ģ��ľ������
//-----------------------------------------
int TempltExcute(LPBYTE lptemp,int* templt, int ttw,UINT lb,WORD bc, int x, int y)
{
	int i,j;
	int m=0,px,py;
	LPBYTE lptemp1=lptemp;

	//�ֱ��ģ����ÿ��λ�ý��м���
	for(i=0; i<ttw; i++)
	{
		for(j=0; j<ttw; j++)
		{
			//����������ԭͼ���ϵ�λ��
			px=x-ttw/2+j;
			py=y-ttw/2+i;
			lptemp=lptemp1+py*lb+px*bc/8;
			//��ÿ�����صĻҶȳ���Ȩֵ�����
			m+=((*lptemp)+(*(lptemp+1))+(*(lptemp+2)))/3*templt[i*ttw+j];
		
		}
	}
	return m;
}
//-----------------------------------------
//����:ʵ��ͼ�������Ч��
//-----------------------------------------
void CImageFilterDib::LaplacianB()
{
	//ͼ��߿�
	LONG width=this->m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG height=this->m_pDib->GetHeight();  //���ԭͼ��ĸ߶�
    	WORD BC;
   	BC=this->m_pDib->GetBitCount();//��ȡ��������ռ�õ�λ��
	UINT Lb;
	Lb=this->m_pDib->GetLineByte();//��ȡͼ��ÿ�е��ֽ���
  	LPBYTE  lpDst;//ָ��ԭʼͼ������ָ��
	LPBYTE  lpTemp;//ָ����ʱͼ������ָ��
	LPBYTE  lpTemp1;//ָ����ʱͼ������ָ��
	lpDst=this->m_pDib->GetData();
	lpTemp=(LPBYTE)malloc(sizeof(BYTE)*width*height*BC/8);//����ռ�
	lpTemp1=(LPBYTE)malloc(sizeof(BYTE)*width*height*BC/8);//����ռ�
	//��ͼ�����ݸ���һ��
	int sum = width * height*BC/8;
	memcpy(lpTemp, lpDst, sum);
	memcpy(lpTemp1, lpDst, sum);
	double scale = 2;
	//������˹����ģ��
	int templt[9]={ 1, 1, 1, 1,-8, 1, 1, 1, 1 };
	//�������ģ��
	int templtTest1[9]={ 1, 1,-1, 1, 0,-1, 1,-1,-1 };
	int templtTest2[9]={ 1, 1, 1,-1, 0, 1,-1,-1,-1 };
	//ģ������ģ��
	int templtAve[9]={ 1, 1, 1, 1, 4, 1, 1, 1, 1};
	int x,y;
	int a,b,b1,b2;
	int tw=3;//����ģ����
	//���ζ�ԭͼ���ÿ�����ؽ��д���
	for(y = 1; y < height - 1; y++)
		for(x = 1; x < width - 1; x++)
		{
			//������˹�������
			a=TempltExcute(lpTemp,templt, tw,Lb,BC,  x,  y);
			//�������
			b1=abs(TempltExcute(lpTemp,templtTest1,  tw,Lb,BC,  x,  y));
			b2=abs(TempltExcute(lpTemp,templtTest2,  tw,Lb,BC, x,  y));
			b=b1>b2?b1:b2;
			if(b<25)
				a=0;
			else
			{
				a = (int)(a * scale);
				//���޴���
				if(a > 255) a = 255;
				else if(a < 32) a=0;
			}
			//��ɫ����
			a=255-a;
			*(lpTemp1+y*Lb+x*BC/8)=a;
			*(lpTemp1+y*Lb+x*BC/8+1)=a;
			*(lpTemp1+y*Lb+x*BC/8+2)=a;
		}

		//ģ������
		for(y = 1; y < height- 1; y++)
		{
			for(x = 1; x < width - 1; x++)
			{
				a=TempltExcute(lpTemp1,templtAve,  tw,Lb,BC,  x,  y) / 12;
				*(lpDst+y*Lb+x*BC/8)=a;
				*(lpDst+y*Lb+x*BC/8+1)=a;
				*(lpDst+y*Lb+x*BC/8+2)=a;
			}
		}	
}
