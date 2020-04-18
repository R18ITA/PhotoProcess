
//======================================================================
// 文件： ImageFilterDib.h
// 内容： 图像滤镜处理函数-头文件
// 功能： （1）底片效果函数；       
//        （2）雕刻效果函数；
//        （3）黑白效果函数        
//        （4）雾化效果函数
//        （5）素描效果函数
//======================================================================

#include "StdAfx.h"
#include "ImageFilterDib.h"
#include "Dib.h"
#include <math.h>

//=======================================================
// 函数功能： 构造函数，初始化数据成员
// 输入参数： 位图指针
// 返回值：   无
//=======================================================

CImageFilterDib::CImageFilterDib(CDib *pDib)
{
	m_pDib = pDib;
}


//=======================================================
// 函数功能： 析构函数
// 输入参数： 无
// 返回值：   无
//=======================================================

CImageFilterDib::~CImageFilterDib(void)
{
	
}

//-----------------------------------------
//	作用:			图像反色函数
//-----------------------------------------
void CImageFilterDib::Negative()
{
	//图像高宽
	LONG width=m_pDib->GetWidth();    //获得原图像的宽度
	LONG height=m_pDib->GetHeight();  //获得原图像的高度
	LPBYTE lpDst;
	//数据访问的起始位置，后面数据的变动既可以是元素
	//也可以是字节，看控制变量的使用
    lpDst=this->m_pDib->GetData();
	if(this->m_pDib->IsGrade()==1)//对灰度图像的处理
	{
		for(int i = 0; i <width * height ; i ++) 
			{
				*lpDst=255-*lpDst;
				lpDst++;
			}
	}
	else                       //对彩色图像的处理
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
//	作用:			实现图像的浮雕效果
//-----------------------------------------
void CImageFilterDib::Emboss()
{
	//图像高宽
	LONG width=m_pDib->GetWidth();    //获得原图像的宽度
	LONG height=m_pDib->GetHeight();   //获得原图像的高度
   	LPBYTE  lpDst;
	LPBYTE  lpTemp;
	UINT Lb; 
	WORD BC;
   	BC=this->m_pDib->GetBitCount();
   	lpDst=this->m_pDib->GetData();
	lpTemp=this->m_pDib->GetData();
	Lb=this->m_pDib->GetLineByte();
	lpTemp=lpTemp+Lb;
	for(int j=0;j<height-1;j++)//控制列数
	{
		lpTemp=lpTemp+BC/8;
		for(int i=0;i<width-1;i++)//控制行数
		{
			for(int n=0;n<BC/8;n++)
			{
				*lpDst=abs(*lpDst-*lpTemp)+128;
				if(*lpDst>255)               //数据值是否会溢出
				*lpDst=255;
				lpDst++;
				lpTemp++;
			}
		}
          //跳过最后一列的元素回到下一行起始位置
		lpDst=lpDst+BC/8;
	}
}
//-----------------------------------------
//	作用:			实现图像的黑白效果
//-----------------------------------------
void CImageFilterDib::ColorToBW()
{
	//图像高宽
	LONG width=m_pDib->GetWidth();    //获得原图像的宽度
	LONG height=m_pDib->GetHeight();  //获得原图像的高度
	LPBYTE lpDst;
    lpDst=this->m_pDib->GetData();
	WORD BC;
    BC=this->m_pDib->GetBitCount();
	UINT Lb;
	Lb=this->m_pDib->GetLineByte();
	LPBYTE  lpTemp;//指向临时图像数据指针
	lpTemp=lpDst;
	for(int y = 0; y < height;y++)
	{
		for(int x=0;x<width;x++)
		{
			for(int i=0;i<3;i++)
			{
	*lpDst=(*(lpTemp+y*Lb+x*BC/8)+*(lpTemp+y*Lb+x*BC/8+1)+*(lpTemp+y*Lb+x*BC/8+2))/3;    //平均值法
			 lpDst++;
			}
		}
	}
}
//-----------------------------------------
//	作用:			实现复合方式的雾化效果
//	参数:		
//		f			雾化参数
//-----------------------------------------
void CImageFilterDib::ComFog()
{
	//图像高宽
	LONG width=m_pDib->GetWidth();    //获得原图像的宽度
	LONG height=m_pDib->GetHeight();  //获得原图像的高度
     WORD BC;
     BC=this->m_pDib->GetBitCount();//获取当个像素占用的位数
	UINT Lb;
	Lb=this->m_pDib->GetLineByte();
   	LPBYTE  lpDst;//指向原始图像数据指针
	LPBYTE  lpTemp;//指向临时图像数据指针
	LPBYTE  lpTemp1;//指向临时图像数据指针
	lpDst=this->m_pDib->GetData();
	lpTemp=(LPBYTE)malloc(sizeof(BYTE)*width*height*BC/8);//分配空间
	lpTemp1=lpTemp;
	//将图像数据复制一份
	int sum = width * height*BC/8;
	memcpy(lpTemp, lpDst, sum);
	int f=5;//雾化参数控制
	int k;
	int m,n;
	for(int j=0;j<height;j++)//控制高度
	{
		for(int i=0;i<width*BC/8;i++)
		{
			k = abs(rand() % f);
			m = i + k* BC/8;
			n = j + k ;
			// 对超出图像区域的点进行相应处理
			if (m > (width-1)*BC/8) 
				m = (width-1) *BC/8;
			if (n > height-1) 
				n = height-1;
			lpTemp1=lpTemp1+n*Lb+m;
			//更新图像像素值
			*lpDst=*lpTemp1;
			lpTemp1=lpTemp;
			lpDst++;	
		}	
	}	
}

//-----------------------------------------
//模板的卷积运算
//-----------------------------------------
int TempltExcute(LPBYTE lptemp,int* templt, int ttw,UINT lb,WORD bc, int x, int y)
{
	int i,j;
	int m=0,px,py;
	LPBYTE lptemp1=lptemp;

	//分别对模板上每个位置进行计算
	for(i=0; i<ttw; i++)
	{
		for(j=0; j<ttw; j++)
		{
			//计算像素在原图像上的位置
			px=x-ttw/2+j;
			py=y-ttw/2+i;
			lptemp=lptemp1+py*lb+px*bc/8;
			//将每个像素的灰度乘以权值再相加
			m+=((*lptemp)+(*(lptemp+1))+(*(lptemp+2)))/3*templt[i*ttw+j];
		
		}
	}
	return m;
}
//-----------------------------------------
//作用:实现图像的素描效果
//-----------------------------------------
void CImageFilterDib::LaplacianB()
{
	//图像高宽
	LONG width=this->m_pDib->GetWidth();    //获得原图像的宽度
	LONG height=this->m_pDib->GetHeight();  //获得原图像的高度
    	WORD BC;
   	BC=this->m_pDib->GetBitCount();//获取当个像素占用的位数
	UINT Lb;
	Lb=this->m_pDib->GetLineByte();//获取图像每行的字节数
  	LPBYTE  lpDst;//指向原始图像数据指针
	LPBYTE  lpTemp;//指向临时图像数据指针
	LPBYTE  lpTemp1;//指向临时图像数据指针
	lpDst=this->m_pDib->GetData();
	lpTemp=(LPBYTE)malloc(sizeof(BYTE)*width*height*BC/8);//分配空间
	lpTemp1=(LPBYTE)malloc(sizeof(BYTE)*width*height*BC/8);//分配空间
	//将图像数据复制一份
	int sum = width * height*BC/8;
	memcpy(lpTemp, lpDst, sum);
	memcpy(lpTemp1, lpDst, sum);
	double scale = 2;
	//拉普拉斯正相模板
	int templt[9]={ 1, 1, 1, 1,-8, 1, 1, 1, 1 };
	//噪声检测模板
	int templtTest1[9]={ 1, 1,-1, 1, 0,-1, 1,-1,-1 };
	int templtTest2[9]={ 1, 1, 1,-1, 0, 1,-1,-1,-1 };
	//模糊处理模板
	int templtAve[9]={ 1, 1, 1, 1, 4, 1, 1, 1, 1};
	int x,y;
	int a,b,b1,b2;
	int tw=3;//设置模板宽度
	//依次对原图像的每个像素进行处理
	for(y = 1; y < height - 1; y++)
		for(x = 1; x < width - 1; x++)
		{
			//拉普拉斯卷积运算
			a=TempltExcute(lpTemp,templt, tw,Lb,BC,  x,  y);
			//噪声检测
			b1=abs(TempltExcute(lpTemp,templtTest1,  tw,Lb,BC,  x,  y));
			b2=abs(TempltExcute(lpTemp,templtTest2,  tw,Lb,BC, x,  y));
			b=b1>b2?b1:b2;
			if(b<25)
				a=0;
			else
			{
				a = (int)(a * scale);
				//过限处理
				if(a > 255) a = 255;
				else if(a < 32) a=0;
			}
			//反色处理
			a=255-a;
			*(lpTemp1+y*Lb+x*BC/8)=a;
			*(lpTemp1+y*Lb+x*BC/8+1)=a;
			*(lpTemp1+y*Lb+x*BC/8+2)=a;
		}

		//模糊处理
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
