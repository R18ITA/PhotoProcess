//======================================================================
// �ļ��� ImageRestoreDib.h
// ���ݣ� ͼ���˶���ԭ����-ͷ�ļ�
// ���ܣ� ��1���˶�ģ����
//        ��2���˶�ģ����ԭ��
//        
//======================================================================

#pragma once

#include "Dib.h"

#include "afx.h"

class CImageRestoreDib
{
public:
	// ���캯������ʼ�����ݳ�Ա
	CImageRestoreDib(CDib *pDib);

	// ��������	
	~CImageRestoreDib(void);

    //��DIBͼ��ģ��������ֱ���˶���ɵ�ģ��
    BOOL  DIBMotionDegeneration();
 
    //��������ֱ���˶���ɵ�ģ��ͼ����и�ԭ
	BOOL  DIBMotionRestore();

private:
    // ���ݳ�Ա,CDib�����ָ�� 
	CDib *m_pDib; 

};