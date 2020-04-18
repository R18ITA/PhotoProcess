//======================================================================
// �ļ��� FrequencyFilterDib.cpp
// ���ݣ� ͼ��Ƶ���˲���ǿ-Դ�ļ�
// ���ܣ� ��1������Ҷ�任������       
//        ��2�������ͨ�˲�����
//        ��3�������ͨ�˲�����
// 
//======================================================================

#include "StdAfx.h"
#include "FrequencyFilterDib.h"
#include<math.h>
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 


#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
#define pi 3.14159265359


//=======================================================
// �������ܣ� ���캯������ʼ�����ݳ�Ա
// ��������� λͼָ��
// ����ֵ��   ��
//=======================================================
CFrequencyFilterDib::CFrequencyFilterDib(CDib *pDib)
{
	m_pDib = pDib;
}


//=======================================================
// �������ܣ� ��������
// ��������� ��
// ����ֵ��   ��
//=======================================================

CFrequencyFilterDib::~CFrequencyFilterDib(void)
{
	
}


//=======================================================
// �������ܣ� ����Ҷ�任����
// ��������� double * data-ʱ������ָ��
//            int height-ͼ��ĸ߶�
//            int width-ͼ����
//            int isign-��ʾ�����任
// ����ֵ��   ��
//=======================================================

void CFrequencyFilterDib::fourier(double * data, int height, int width, int isign)
{
	int idim;
	unsigned long i1,i2,i3,i2rev,i3rev,ip1,ip2,ip3,ifp1,ifp2;
	unsigned long ibit,k1,k2,n,nprev,nrem,ntot,nn[3];
	double tempi,tempr;
	double theta,wi,wpi,wpr,wr,wtemp;	
	ntot=height*width; 
	nn[1]=height;
	nn[2]=width;
	nprev=1;
	for (idim=2;idim>=1;idim--) 
	{
		n=nn[idim];
		nrem=ntot/(n*nprev);
		ip1=nprev << 1;
		ip2=ip1*n;
		ip3=ip2*nrem;
		i2rev=1;
		for (i2=1;i2<=ip2;i2+=ip1)
		{
			if (i2 < i2rev) 
			{
				for (i1=i2;i1<=i2+ip1-2;i1+=2) 
				{
					for (i3=i1;i3<=ip3;i3+=ip2)
					{
						i3rev=i2rev+i3-i2;
						SWAP(data[i3],data[i3rev]);
						SWAP(data[i3+1],data[i3rev+1]);
					}
				}
			}
			ibit=ip2 >> 1;
			while (ibit >= ip1 && i2rev > ibit)
			{
				i2rev -= ibit;
				ibit >>= 1;
			}
			i2rev += ibit;
		}
		ifp1=ip1;
		while (ifp1 < ip2) 
		{
			ifp2=ifp1 << 1;
			theta=isign*pi*2/(ifp2/ip1);
			wtemp=sin(0.5*theta);
			wpr = -2.0*wtemp*wtemp;
			wpi=sin(theta);
			wr=1.0;
			wi=0.0;
			for (i3=1;i3<=ifp1;i3+=ip1)
			{
				for (i1=i3;i1<=i3+ip1-2;i1+=2) 
				{
					for (i2=i1;i2<=ip3;i2+=ifp2) 
					{
						k1=i2;
						k2=k1+ifp1;
						tempr=wr*data[k2]-wi*data[k2+1];
						tempi=wr*data[k2+1]+wi*data[k2];
						data[k2]=data[k1]-tempr;
						data[k2+1]=data[k1+1]-tempi;
						data[k1] += tempr;
						data[k1+1] += tempi;
					}
				}
				wr=(wtemp=wr)*wpr-wi*wpi+wr;
				wi=wi*wpr+wtemp*wpi+wi;
			}
			ifp1=ifp2;
		}
		nprev *= n;
	}
}


//=======================================================
// �������ܣ� �����ͨ�˲�����
// ��������� int u,int v-��ֹƵ�ʵķ���ֵ
// ����ֵ��   ��
//=======================================================
void CFrequencyFilterDib::Perfect_Low_Filter(int u,int v)
{
    LPBYTE	lpSrc;			// ָ��ԭͼ��ǰ���ָ��
    long i,j;			//ѭ������
	double d0;  //��ֹƵ�����
    double max=0.0; //��һ������

	double *t;  //��������ָ��
    double *H;  //���ݺ���ָ��

	LPBYTE lpDIBBits=m_pDib->GetData();//�ҵ�ԭͼ�����ʼλ��
	LONG lWidth=m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG lHeight=m_pDib->GetHeight();  //���ԭͼ��ĸ߶� 	
	
    long lLineBytes=WIDTHBYTES(lWidth*8);//����ͼ��ÿ�е��ֽ���
	t=new double [lHeight*lLineBytes*2+1]; //�������ռ�
	H=new double [lHeight*lLineBytes*2+1]; //���䴫�ݺ����ռ�
	d0=sqrt((float)(u*u+v*v)) ;  //�����ֹƵ��d0

    //������ֵ�������㴫�ݺ���
	for(j=0;j<lHeight;j++)
	{
		for(i=0;i<lLineBytes;i++)
		{
			lpSrc=lpDIBBits+lLineBytes*j+i;//ָ���i�е�j������
			//������ֵ
            t[(2*lLineBytes)*j+2*i+1]=*lpSrc;
			t[(2*lLineBytes)*j+2*i+2]=0.0;

            //���㴫�ݺ���
			if((sqrt((float)(i*i+j*j)))<=d0)
				H[2*i+(2*lLineBytes)*j+1]=1.0;
			else
				H[2*i+(2*lLineBytes)*j+1]=0.0;
			H[2*i+(2*lLineBytes)*j+2]=0.0;
		}
	}
    //���и���Ҷ�任
    fourier(t,lHeight,lLineBytes,1);

    //����Ҷ�任����봫�ݺ������о������
	for(j=1;j<lHeight*lLineBytes*2;j+=2)
	{
		t[j]=t[j]*H[j]-t[j+1]*H[j+1];
		t[j+1]=t[j]*H[j+1]+t[j+1]*H[j];
	}
    //���и���Ҷ��任
	fourier(t,lHeight,lLineBytes,-1);
    
    //�����һ������
	for(j=0;j<lHeight;j++)
	{
		for(i=0;i<lLineBytes;i++)
		{
			t[(2*lLineBytes)*j+2*i+1]=sqrt(t[(2*lLineBytes)*j+2*i+1]*t[(2*lLineBytes)*j+2*i+1]+t[(2*lLineBytes)*j+2*i+2]*t[(2*lLineBytes)*j+2*i+2]);
			if(max<t[(2*lLineBytes)*j+2*i+1])
				max=t[(2*lLineBytes)*j+2*i+1];
		}
	}

    //������ͼ��,�����浽ԭͼ��������
	for(j=0;j<lHeight;j++)
	{
		for(i=0;i<lLineBytes;i++)
		{
			lpSrc=lpDIBBits+lLineBytes*j+i;
			*lpSrc=(BYTE)(t[(2*lLineBytes)*j+2*i+1]*255.0/max);
		}
	}
    //�ͷ��ڴ�ռ�
	delete t;
	delete H;
}

//=======================================================
// �������ܣ� �����ͨ�˲�����
// ��������� int u,int v-��ֹƵ�ʵķ���ֵ
// ����ֵ��   ��
//=======================================================
void CFrequencyFilterDib::Perfect_High_Filter(int u,int v)
{
    LPBYTE	lpSrc;			// ָ��ԭͼ��ǰ���ָ��
    long i,j;			//ѭ������
	double d0;  //��ֹƵ�����
    double max=0.0; //��һ������

	double *t;  //��������ָ��
    double *H;  //���ݺ���ָ��

	LPBYTE lpDIBBits=m_pDib->GetData();//�ҵ�ԭͼ�����ʼλ��
	LONG lWidth=m_pDib->GetWidth();    //���ԭͼ��Ŀ��
	LONG lHeight=m_pDib->GetHeight();  //���ԭͼ��ĸ߶� 	
	
    long lLineBytes=WIDTHBYTES(lWidth*8);//����ͼ��ÿ�е��ֽ���
	t=new double [lHeight*lLineBytes*2+1]; //�������ռ�
	H=new double [lHeight*lLineBytes*2+1]; //���䴫�ݺ����ռ�
	d0=sqrt((float)(u*u+v*v)) ;  //�����ֹƵ��d0

    //������ֵ�������㴫�ݺ���
	for(j=0;j<lHeight;j++)
	{
		for(i=0;i<lLineBytes;i++)
		{
			lpSrc=lpDIBBits+lLineBytes*j+i;//ָ���i�е�j������
			//������ֵ
            t[(2*lLineBytes)*j+2*i+1]=*lpSrc;
			t[(2*lLineBytes)*j+2*i+2]=0.0;

            //���㴫�ݺ���
			if((sqrt((float)(i*i+j*j)))<=d0)
				H[2*i+(2*lLineBytes)*j+1]=0.0;
			else
				H[2*i+(2*lLineBytes)*j+1]=1.0;
			H[2*i+(2*lLineBytes)*j+2]=0.0;
		}
	}
    //���и���Ҷ�任
    fourier(t,lHeight,lLineBytes,1);

    //����Ҷ�任����봫�ݺ������о������
	for(j=1;j<lHeight*lLineBytes*2;j+=2)
	{
		t[j]=t[j]*H[j]-t[j+1]*H[j+1];
		t[j+1]=t[j]*H[j+1]+t[j+1]*H[j];
	}
    //���и���Ҷ��任
	fourier(t,lHeight,lLineBytes,-1);
    
    //�����һ������
	for(j=0;j<lHeight;j++)
	{
		for(i=0;i<lLineBytes;i++)
		{
			t[(2*lLineBytes)*j+2*i+1]=sqrt(t[(2*lLineBytes)*j+2*i+1]*t[(2*lLineBytes)*j+2*i+1]+t[(2*lLineBytes)*j+2*i+2]*t[(2*lLineBytes)*j+2*i+2]);
			if(max<t[(2*lLineBytes)*j+2*i+1])
				max=t[(2*lLineBytes)*j+2*i+1];
		}
	}

    //������ͼ��
	for(j=0;j<lHeight;j++)
	{
		for(i=0;i<lLineBytes;i++)
		{
			lpSrc=lpDIBBits+lLineBytes*j+i;
			*lpSrc=(BYTE)(t[(2*lLineBytes)*j+2*i+1]*255.0/max);
		}
	}
    //�ͷ��ڴ�ռ�
	delete t;
	delete H;
}