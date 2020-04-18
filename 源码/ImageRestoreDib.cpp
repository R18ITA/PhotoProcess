
//======================================================================
// 文件： ImageRestoreDib.h
// 内容： 图像运动复原函数-头文件
// 功能： （1）运动模糊；
//        （2）运动模糊复原；
//        
//======================================================================

#pragma once
#include "stdafx.h"
#include "Dib.h"
#include <math.h>
#include "ImageRestoreDib.h"

//=======================================================
// 函数功能： 构造函数，初始化数据成员
// 输入参数： 位图指针
// 返回值：   无
//=======================================================

CImageRestoreDib::CImageRestoreDib(CDib *pDib)
{
	m_pDib = pDib;
}


//=======================================================
// 函数功能： 析构函数
// 输入参数： 无
// 返回值：   无
//=======================================================

CImageRestoreDib::~CImageRestoreDib(void)
{
	
}

//-----------------------------------------
//	作用:	 对DIB图像模拟由匀速直线运动造成的模糊
//	参数:		
//		CDib  *pDib      指向CDib类的指针
//返回值:
//		BOOL             成功返回TRUE，否则返回FALSE	
//-----------------------------------------
BOOL CImageRestoreDib::DIBMotionDegeneration()
{
	// 指向源图像的指针
	BYTE *	lpSrc;

	LPBYTE lpDIBBits=m_pDib->GetData();//找到原图像的起始位置
	LONG lWidth=m_pDib->GetWidth();    //获得原图像的宽度
	LONG lHeight=m_pDib->GetHeight();  //获得原图像的高度

	// 图像每行的字节数
	LONG	lLineBytes;
    lLineBytes =m_pDib->GetLineByte();
	
	//循环变量
	long iColumn;
	long jRow;

	//临时变量
	int temp,m;

	// 临时变量
	double p,q;
	
	int nTotTime, nTotLen, nTime;

	//总的运动时间10s
	nTotTime = 10;

	// 总的运动距离10个象素点
	nTotLen = 10;
	
	// 摄像机的暴光系数
	double B;

	B = 0.1;

	//用来存储源图象和变换核的时域数据
	int *nImageDegener;

	// 为时域和频域的数组分配空间
	nImageDegener = new int [lHeight*lLineBytes];
	
	// 将数据存入时域数组
	for (jRow = 0; jRow < lHeight; jRow++)
	{
		for(iColumn = 0; iColumn < lLineBytes; iColumn++)
		{
			temp=0;
			
			// 指向源图像倒数第jRow行，第iColumn个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + iColumn;

			// 象素点的象素值积累
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

					// 累加
					lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + m;
					temp = temp + *lpSrc;
				}	
			}
			
			// 乘以摄像机的暴光系数
			temp = B * temp;

			temp=(int)ceil((double)temp);
			
			// 使得temp的取值符合取值范围
			if(temp<0)
				temp=0;

			if(temp>255)
				temp=255;

			nImageDegener[lLineBytes*jRow + iColumn] = temp;
		}
	}	
	
	//转换为图像
	for (jRow = 0;jRow < lHeight ;jRow++)
	{
		for(iColumn = 0;iColumn < lLineBytes ;iColumn++)
		{
			// 指向源图像倒数第jRow行，第iColumn个象素的指针			
 			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + iColumn;
	
			*lpSrc = nImageDegener[lLineBytes*jRow + iColumn];
		}
	}
	
	//释放存储空间
	delete nImageDegener;
	return true;
}

//-----------------------------------------
//	作用:			对由匀速直线运动造成的模糊图象进行复原
//	参数:		
//		 CDib  *pDib       指向CDib类的指针
//返回值:
//		BOOL             成功返回TRUE，否则返回FALSE。
//-----------------------------------------
BOOL  CImageRestoreDib::DIBMotionRestore()
{
	// 指向源图像的指针
	BYTE *	lpSrc;
	
    LPBYTE lpDIBBits=m_pDib->GetData();//找到原图像的起始位置
	LONG lWidth=m_pDib->GetWidth();    //获得原图像的宽度
	LONG lHeight=m_pDib->GetHeight();  //获得原图像的高度

	// 计算图像每行的字节数
	LONG	lLineBytes;
    lLineBytes = m_pDib->GetLineByte();
	
	//循环变量
	long iColumn;
	long jRow;

	int i,n,m;

	//临时变量
	int temp1,temp2,
		totalq,q1,q2,z;

	double p,q;

	// 常量A赋值
	int A = 80;
	
	//常量B赋值
	int B = 10;
	
	//总的移动距离
	int nTotLen=10;

	// 图象宽度包含多少个ntotlen
	int K=lLineBytes/nTotLen;
	
	int error[10];

	//用来存储源图象时域数据
	int *nImageDegener;

	// 为时域数组分配空间
	nImageDegener = new int [lHeight*lLineBytes];

	// 将象素存入数组中
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
		// 计算error[i]
		for(i = 0; i < 10; i++)
		{			
			error[i] = 0;			
			for(n = 0; n < K; n++)
			{
				for(m = 0; m <= n; m++)
				{
					// 象素是否为一行的开始处
					if(i == 0 && m == 0)
					{
						temp1=temp2=0;
					}					
					// 进行差分运算
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
			// 计算m，以及z
			m = iColumn / nTotLen;
			z = iColumn - m*nTotLen;				
			// 初始化
			totalq = 0;	q = 0;			
			for(n = 0; n <= m; n++)
			{
				q1 = iColumn - nTotLen*n;				
				if(q1 == 0)
					q = 0;				
				// 进行差分运算
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
			// 得到f(x,y)的值
			temp1 = totalq + A - p;			
			// 使得象素的取值符合取值范围
			if(temp1 < 0)
				temp1 = 0;			
			if(temp1 > 255)
				temp1 = 255;						
			nImageDegener[lLineBytes*jRow + iColumn] = temp1;
		}
	}
	//转换为图像
	for (jRow = 0;jRow < lHeight ;jRow++)
	{
		for(iColumn = 0;iColumn < lLineBytes ;iColumn++)
		{
			// 指向源图像倒数第jRow行，第iColumn个象素的指针			
 			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + iColumn;
	
			// 存储象素值
			*lpSrc = nImageDegener[lLineBytes*jRow + iColumn];
		}
	}	
	
	//释放存储空间
	delete nImageDegener;
	return true;
}
