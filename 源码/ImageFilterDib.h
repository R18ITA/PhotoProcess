//======================================================================
// 文件： ImageFilterDib.h
// 内容： 图像滤镜处理函数-头文件
// 功能： （1）底片效果函数；       
//        （2）雕刻效果函数；
//        （3）黑白效果函数        
//        （4）雾化效果函数
//        （5）素描效果函数
//======================================================================

#pragma once

#include "afx.h"

# include "Dib.h"


class CImageFilterDib
{
public:
	// 构造函数，初始化数据成员
	CImageFilterDib(CDib *pDib);

	// 析构函数	
	~CImageFilterDib(void);

	// 图像反色函数
	void Negative();

	//图像的浮雕效果函数
	void Emboss();
	
	//黑白效果函数
    void ColorToBW();

	//复合方式雾化效果函数

    void ComFog(); 

	//素描效果函数
	void LaplacianB();

private:
    // 数据成员,CDib对象的指针 
	CDib *m_pDib; 

};