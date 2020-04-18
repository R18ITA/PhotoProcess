// PhotoProcessView.h : CPhotoProcessView ��Ľӿ�
//


#pragma once

#include "Dib.h"
#include "GrayTransformDib.h"
#include "HistogramDib.h"
#include "SmoothProcessDib.h"
#include "SharpenProcessDib.h"
#include "FrequencyFilterDib.h"
#include "ColorEnhanceDib.h"
#include "ImageRestoreDib.h"
#include "ImageFilterDib.h"


class CPhotoProcessView : public CView
{
protected: // �������л�����
	CPhotoProcessView();
	DECLARE_DYNCREATE(CPhotoProcessView)

// ����
public:
	CPhotoProcessDoc* GetDocument() const;

    CDib m_PhotoImage;//��Ƭͼ��
    BOOL flag;//����Ƭͼ���Ǳ���
   

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPhotoProcessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnOpenPhoto();
public:
    afx_msg void OnLinearTransform();
public:
    afx_msg void OnSegLineTransform();
public:
    afx_msg void OnLogTransform();
public:
    afx_msg void OnHistogramEqual();
public:
    afx_msg void OnHistogramMatch();
public:
    afx_msg void OnGateGrad();
public:
    afx_msg void OnLaplacian();



public:
    afx_msg void OnAverageSmooth();
public:
    afx_msg void OnValueAvrgSmooth();
public:
    afx_msg void OnSelectSmooth();
public:
    afx_msg void OnMiddleSmooth();
public:
    afx_msg void OnPrefectLowFilter();
public:
    afx_msg void OnPrefectHighFilter();
public:
    afx_msg void OnPseudoColorEnhance();
public:
	afx_msg void OnDegenerationMotion();
public:
	afx_msg void OnRestoreMotion();
	

public:
	afx_msg void OnFilterEmboss();
public:
	afx_msg void OnFilterSketch();
public:
	afx_msg void OnFilterFog();
public:
	afx_msg void OnFilterBw();
public:
	afx_msg void OnFilterNegative();
};

#ifndef _DEBUG  // PhotoProcessView.cpp �еĵ��԰汾
inline CPhotoProcessDoc* CPhotoProcessView::GetDocument() const
   { return reinterpret_cast<CPhotoProcessDoc*>(m_pDocument); }
#endif

