//======================================================================
// 文件： ImageRestoreDib.h
// 内容： 图像运动复原函数-头文件
// 功能： （1）运动模糊；
//        （2）运动模糊复原；
//        
//======================================================================

#pragma once

#include "Dib.h"

#include "afx.h"

class CImageRestoreDib
{
public:
	// 构造函数，初始化数据成员
	CImageRestoreDib(CDib *pDib);

	// 析构函数	
	~CImageRestoreDib(void);

    //对DIB图像模拟由匀速直线运动造成的模糊
    BOOL  DIBMotionDegeneration();
 
    //对由匀速直线运动造成的模糊图象进行复原
	BOOL  DIBMotionRestore();

private:
    // 数据成员,CDib对象的指针 
	CDib *m_pDib; 

};