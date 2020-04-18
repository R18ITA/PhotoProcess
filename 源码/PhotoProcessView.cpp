// PhotoProcessView.cpp : CPhotoProcessView ���ʵ��
//

#include "stdafx.h"
#include "PhotoProcess.h"

#include "PhotoProcessDoc.h"
#include "PhotoProcessView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhotoProcessView

IMPLEMENT_DYNCREATE(CPhotoProcessView, CView)

BEGIN_MESSAGE_MAP(CPhotoProcessView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_COMMAND(ID_OPEN_PHOTO, &CPhotoProcessView::OnOpenPhoto)
    ON_COMMAND(ID_LINEAR_TRANSFORM, &CPhotoProcessView::OnLinearTransform)
    ON_COMMAND(ID_SEG_LINE_TRANSFORM, &CPhotoProcessView::OnSegLineTransform)
    ON_COMMAND(ID_LOG_TRANSFORM, &CPhotoProcessView::OnLogTransform)
    ON_COMMAND(ID_HISTOGRAM_EQUAL, &CPhotoProcessView::OnHistogramEqual)
    ON_COMMAND(ID_HISTOGRAM_MATCH, &CPhotoProcessView::OnHistogramMatch)
    ON_COMMAND(ID_GATE_GRAD, &CPhotoProcessView::OnGateGrad)
    ON_COMMAND(ID_LAPLACIAN, &CPhotoProcessView::OnLaplacian)
    
    ON_COMMAND(ID_AVERAGE_SMOOTH, &CPhotoProcessView::OnAverageSmooth)
    ON_COMMAND(ID_VALUE_AVRG_SMOOTH, &CPhotoProcessView::OnValueAvrgSmooth)
    ON_COMMAND(ID_SELECT_SMOOTH, &CPhotoProcessView::OnSelectSmooth)
    ON_COMMAND(ID_MIDDLE_SMOOTH, &CPhotoProcessView::OnMiddleSmooth)
    ON_COMMAND(ID_PREFECT_LOW_FILTER, &CPhotoProcessView::OnPrefectLowFilter)
    ON_COMMAND(ID_PREFECT_HIGH_FILTER, &CPhotoProcessView::OnPrefectHighFilter)
    ON_COMMAND(ID_PSEUDO_COLOR_ENHANCE, &CPhotoProcessView::OnPseudoColorEnhance)

	ON_COMMAND(ID_DEGENERATION_MOTION, &CPhotoProcessView::OnDegenerationMotion)
	ON_COMMAND(ID_RESTORE_MOTION, &CPhotoProcessView::OnRestoreMotion)
	
    ON_COMMAND(ID_FILTER_EMBOSS, &CPhotoProcessView::OnFilterEmboss)
	ON_COMMAND(ID_FILTER_SKETCH, &CPhotoProcessView::OnFilterSketch)
	ON_COMMAND(ID_FILTER_BW, &CPhotoProcessView::OnFilterBw)
	ON_COMMAND(ID_FILTER_FOG, &CPhotoProcessView::OnFilterFog)
	ON_COMMAND(ID_FILTER_NEGATIVE, &CPhotoProcessView::OnFilterNegative)
	

END_MESSAGE_MAP()

// CPhotoProcessView ����/����

CPhotoProcessView::CPhotoProcessView()
{
	// TODO: �ڴ˴���ӹ������
    flag=FALSE;

}

CPhotoProcessView::~CPhotoProcessView()
{
}

BOOL CPhotoProcessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPhotoProcessView ����

void CPhotoProcessView::OnDraw(CDC* /*pDC*/)
{
	CPhotoProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPhotoProcessView ��ӡ

BOOL CPhotoProcessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPhotoProcessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPhotoProcessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPhotoProcessView ���

#ifdef _DEBUG
void CPhotoProcessView::AssertValid() const
{
	CView::AssertValid();
}

void CPhotoProcessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPhotoProcessDoc* CPhotoProcessView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhotoProcessDoc)));
	return (CPhotoProcessDoc*)m_pDocument;
}
#endif //_DEBUG


// CPhotoProcessView ��Ϣ�������

void CPhotoProcessView::OnOpenPhoto()
{
    
	if(flag==TRUE)
		this->Invalidate();
	// �����������Ǵ򿪲���ʾ��Ƭͼ��
    CString  filename;
    CFileDialog dlg(TRUE,_T("BMP"),_T("*.BMP"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("λͼ�ļ�(*.BMP)|*.BMP|"));	
    if(IDOK==dlg.DoModal())	
    filename.Format ("%s",dlg.GetPathName() ); 
   
    m_PhotoImage.LoadFromFile(filename);//����Ƭͼ��
    flag=TRUE;//��Ƭͼ��򿪺󣬽���Ǳ�����Ϊ��

	//��ʾͼ��
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);
	


}

void CPhotoProcessView::OnLinearTransform()
{
    // �˺���ʵ�ֻҶ�������ǿ����
    
    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//���ƴ���ǰ��ͼ��

    CGrayTransformDib GrayTransform(&m_PhotoImage);//����һ��CGrayTransformDib����
    BYTE min,max;  //���ñ任��ĻҶ�����
    min=100;
    max=200;
	 
	GrayTransform.Linear_Transform( min,max);  //���ûҶ����Ա任��ǿ����

	CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point,size);//���ƴ�����ͼ��
}

void CPhotoProcessView::OnSegLineTransform()
{
    // �˺���ʵ�ֶַ�������ǿ����

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//���ƴ���ǰ��ͼ��

    CGrayTransformDib GrayTransform(&m_PhotoImage); //����һ��CGrayTransformDib����
    BYTE gSrc1,gSrc2, gDst1, gDst2;  //���÷ֶε�
    gSrc1=100;
    gSrc2=150;
    gDst1=50;
    gDst2=200;
	GrayTransform.Seg_Linear_Transform( gSrc1,  gSrc2, gDst1, gDst2);//���÷ֶ����Ա任��ǿ����

	CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
}

void CPhotoProcessView::OnLogTransform()
{
    // �˺���ʵ�ֶ������������Ա任��ǿ����

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//���ƴ���ǰ��ͼ��

    CGrayTransformDib GrayTransform(&m_PhotoImage);//����һ��CGrayTransformDib����

    double a,b,c;  //���������任��������
    a=50.0;
    b=0.8;
    c=1.05;       
	GrayTransform.Log_Transform( a, b, c);  //���ö������������Ա任��ǿ����

	CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
}

void CPhotoProcessView::OnHistogramEqual()
{
   
    // �˺���ʵ��ֱ��ͼ���⻯��ǿ����

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//���ƴ���ǰ��ͼ��

    CHistogramDib Histgram(&m_PhotoImage);//����һ��CHistogramDib����
         
    Histgram.Histogram_Equalization( );   //����ֱ��ͼ���⻯������

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
}

void CPhotoProcessView::OnHistogramMatch()
{
    // �˺���ʵ��ֱ��ͼ�涨����ǿ����

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//���ƴ���ǰ��ͼ��

    CHistogramDib Histgram(&m_PhotoImage);//����һ��CHistogramDib����
         
    int nu[64];  //�涨ֱ��ͼӳ���ϵ,����涨ֱ��ͼ�ĻҶȼ�Ϊ64
    float pu[64]; //�涨�Ҷȷֲ�����
    float a=1.0f/(32.0f*63.0f); 
    for(int i=0;i<64;i++)
    {
        nu[i]=i*4;
        pu[i]=a*i;
    }      
     
	Histgram.Histogram_Match( 64,nu,pu); //����ֱ��ͼ�涨������

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ
}


void CPhotoProcessView::OnAverageSmooth()
{
    // �˺���ʵ�������ֵƽ������

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//���ƴ���ǰ��ͼ��

    CSmoothProcessDib Smooth(&m_PhotoImage);//����һ��CSmoothProcessDib����         
    Smooth.Average_Smooth( );  //��������ƽ��ƽ������

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
}

void CPhotoProcessView::OnValueAvrgSmooth()
{
    // �˺���ʵ�������Ȩ��ֵƽ������

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//���ƴ���ǰ��ͼ��

    CSmoothProcessDib Smooth(&m_PhotoImage);//����һ��CSmoothProcessDib����         
    
    int Structure[3][3]={1,2,1,2,4,2,1,2,1};//�����Ȩģ��
     
	Smooth.Value_Average_Smooth(Structure); //���������Ȩƽ��ƽ������

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
}

void CPhotoProcessView::OnSelectSmooth()
{
    // �˺���ʵ��ѡ��ʽ��Ĥƽ������

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//���ƴ���ǰ��ͼ��

    CSmoothProcessDib Smooth(&m_PhotoImage);//����һ��CSmoothProcessDib����         
    Smooth.Select_Smooth( );  //����ѡ��ʽ��Ĥƽ������

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
}

void CPhotoProcessView::OnMiddleSmooth()
{
     // �˺���ʵ����ֵ�˲�ƽ������

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//���ƴ���ǰ��ͼ��

    CSmoothProcessDib Smooth(&m_PhotoImage);//����һ��CSmoothProcessDib����         
    Smooth.Middle_Smooth( ); //������ֵ�˲�ƽ������

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
}



void CPhotoProcessView::OnGateGrad( )
{
    // �˺���ʵ�������ݶ��񻯴���

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }

	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//���ƴ���ǰ��ͼ��

    CSharpenProcessDib Sharpen(&m_PhotoImage);//����һ��CSharpenProcessDib����
         
    BYTE t=30;
	Sharpen.GateGrad(t);   //���������ݶ��񻯴�����

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��     
}

void CPhotoProcessView::OnLaplacian( )
{
    // �˺���ʵ��������˹�񻯴���

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }

	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //���ƴ���ǰ��ͼ��

    CSharpenProcessDib Sharpen(&m_PhotoImage);//����һ��CSharpenProcessDib����         
    
	Sharpen.Laplacian( );   //����������˹�񻯴�����

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
    
}

void CPhotoProcessView::OnPrefectLowFilter()
{
    // �˺���ʵ�������ͨ�˲�����

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }

	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //���ƴ���ǰ��ͼ��

    CFrequencyFilterDib FrequencyFilter(&m_PhotoImage);// ����һ��CFrequencyFilterDib����
    //���ý�ֹƵ���������
    int u=100;
    int v=100;     
	FrequencyFilter.Perfect_Low_Filter( u,v); //���������ͨ�˲�����

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
}

void CPhotoProcessView::OnPrefectHighFilter()
{
    // �˺���ʵ�������ͨ�˲�����

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }

	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //���ƴ���ǰ��ͼ��

    CFrequencyFilterDib FrequencyFilter(&m_PhotoImage);// ����һ��CFrequencyFilterDib����
    //���ý�ֹƵ���������
    int u=100;
    int v=100;     
	FrequencyFilter.Perfect_High_Filter( u,v); //���������ͨ�˲�����

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
}

void CPhotoProcessView::OnPseudoColorEnhance()
{
    // �˺���ʵ��������˹�񻯴���

    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }

	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //���ƴ���ǰ��ͼ��

    CColorEnhanceDib ColorEnhance(&m_PhotoImage);// ����һ��CColorEnhanceDib����

    BYTE *bpColorsTable;
    // α��ɫ�����
    BYTE ColorsTable[256*4]={      
      0,  0,  0,0  ,     0,  0,  7,0  ,     0,  0, 15,0  ,     0,  0, 23,0  , //4
      0,  0, 31,0  ,     0,  0, 39,0  ,     0,  0, 47,0  ,     0,  0, 55,0  , //8
      0,  0, 63,0  ,     0,  0, 71,0  ,     0,  0, 79,0  ,     0,  0, 87,0  , //12
      0,  0, 85,0  ,     0,  0,103,0  ,     0,  0,111,0  ,     0,  0,119,0  , //16
      0,  0,127,0  ,     0,  0,135,0  ,     0,  0,143,0  ,     0,  0,151,0  , //20
      0,  0,159,0  ,     0,  0,167,0  ,     0,  0,175,0  ,     0,  0,183,0  , //24
      0,  0,191,0  ,     0,  0,199,0  ,     0,  0,207,0  ,     0,  0,215,0  , //28
      0,  0,223,0  ,     0,  0,231,0  ,     0,  0,239,0  ,     0,  0,247,0  , //32
      0,  0,255,0  ,     0,  8,255,0  ,     0, 16,255,0  ,     0, 24,255,0  , //36
      0, 32,255,0  ,     0, 40,255,0  ,     0, 48,255,0  ,     0, 56,255,0  , //40
      0, 64,255,0  ,     0, 72,255,0  ,     0, 80,255,0  ,     0, 88,255,0  , //44
      0, 96,255,0  ,     0,104,255,0  ,     0,112,255,0  ,     0,120,255,0  , //48
      0,128,255,0  ,     0,136,255,0  ,     0,144,255,0  ,     0,152,255,0  , //52
      0,160,255,0  ,     0,168,255,0  ,     0,176,255,0  ,     0,184,255,0  , //56
      0,192,255,0  ,     0,200,255,0  ,     0,208,255,0  ,     0,216,255,0  , //60
      0,224,255,0  ,     6,232,255,0  ,     0,240,255,0  ,     0,248,255,0  , //64
      0,255,255,0  ,     0,255,247,0  ,     0,255,239,0  ,     0,255,231,0  , //68
      0,255,223,0  ,     0,255,215,0  ,     0,255,207,0  ,     0,255,199,0  , //72
      0,255,191,0  ,     0,255,183,0  ,     0,255,175,0  ,     0,255,167,0  , //76
      0,255,159,0  ,     0,255,151,0  ,     0,255,143,0  ,     0,255,135,0  , //80
      0,255,127,0  ,     0,255,119,0  ,     0,255,111,0  ,     0,255,103,0  , //84
      0,255, 95,0  ,     0,255, 87,0  ,     0,255, 79,0  ,     0,255, 71,0  , //88
      0,255, 63,0  ,     0,255, 55,0  ,     0,255, 47,0  ,     0,255, 39,0  , //92
      0,255, 31,0  ,     0,255, 23,0  ,     0,255, 15,0  ,     0,255,  7,0  , //96
      0,255,  0,0  ,     8,255,  0,0  ,    16,255,  0,0  ,    24,255,  0,0  , //100
     32,255,  0,0  ,    40,255,  0,0  ,    48,255,  0,0  ,    56,255,  0,0  , //104
     64,255,  0,0  ,    72,255,  0,0  ,    80,255,  0,0  ,    88,255,  0,0  , //108
     96,255,  0,0  ,   104,255,  0,0  ,   112,255,  0,0  ,   120,255,  0,0  , //112
    128,255,  0,0  ,   136,255,  0,0  ,   144,255,  0,0  ,   152,255,  0,0  , //116
    160,255,  0,0  ,   168,255,  0,0  ,   176,255,  0,0  ,   184,255,  0,0  , //120
    192,255,  0,0  ,   200,255,  0,0  ,   208,255,  0,0  ,   216,255,  0,0  , //124
    224,255,  0,0  ,   232,255,  0,0  ,   240,255,  0,0  ,   248,255,  0,0  , //128
    255,255,  0,0  ,   255,251,  0,0  ,   255,247,  0,0  ,   255,243,  0,0  , //132
    255,239,  0,0  ,   255,235,  0,0  ,   255,231,  0,0  ,   255,227,  0,0  , //136
    255,223,  0,0  ,   255,219,  0,0  ,   255,215,  0,0  ,   255,211,  0,0  , //140
    255,207,  0,0  ,   255,203,  0,0  ,   255,199,  0,0  ,   255,195,  0,0  , //144
    255,191,  0,0  ,   255,187,  0,0  ,   255,183,  0,0  ,   255,179,  0,0  , //148
    255,175,  0,0  ,   255,171,  0,0  ,   255,167,  0,0  ,   255,163,  0,0  , //152
    255,159,  0,0  ,   255,155,  0,0  ,   255,151,  0,0  ,   255,147,  0,0  , //156
    255,143,  0,0  ,   255,139,  0,0  ,   255,135,  0,0  ,   255,131,  0,0  , //160
    255,127,  0,0  ,   255,123,  0,0  ,   255,119,  0,0  ,   255,115,  0,0  , //164
    255,111,  0,0  ,   255,107,  0,0  ,   255,103,  0,0  ,   255, 99,  0,0  , //168
    255, 95,  0,0  ,   255, 91,  0,0  ,   255, 87,  0,0  ,   255, 83,  0,0  , //172
    255, 79,  0,0  ,   255, 75,  0,0  ,   255, 71,  0,0  ,   255, 67,  0,0  , //176
    255, 63,  0,0  ,   255, 59,  0,0  ,   255, 55,  0,0  ,   255, 51,  0,0  , //180
    255, 47,  0,0  ,   255, 43,  0,0  ,   255, 39,  0,0  ,   255, 35,  0,0  , //184
    255, 31,  0,0  ,   255, 27,  0,0  ,   255, 23,  0,0  ,   255, 19,  0,0  , //188
    255, 15,  0,0  ,   255, 11,  0,0  ,   255,  7,  0,0  ,   255,  3,  0,0  , //192
    255,  0,  0,0  ,   255,  4,  4,0  ,   255,  8,  8,0  ,   255, 12, 12,0  , //196
    255, 16, 16,0  ,   255, 20, 20,0  ,   255, 24, 24,0  ,   255, 28, 28,0  , //200
    255, 32, 32,0  ,   255, 36, 36,0  ,   255, 40, 40,0  ,   255, 44, 44,0  , //204
    255, 48, 48,0  ,   255, 52, 52,0  ,   255, 56, 56,0  ,   255, 60, 60,0  , //208
    255, 64, 64,0  ,   255, 68, 68,0  ,   255, 72, 72,0  ,   255, 76, 76,0  , //212
    255, 80, 80,0  ,   255, 84, 84,0  ,   255, 88, 88,0  ,   255, 92, 92,0  , //216
    255, 96, 96,0  ,   255,100,100,0  ,   255,104,104,0  ,   255,108,108,0  , //220
    255,112,112,0  ,   255,116,116,0  ,   255,120,120,0  ,   255,124,124,0  , //224
    255,128,128,0  ,   255,132,132,0  ,   255,136,136,0  ,   255,140,140,0  , //228
    255,144,144,0  ,   255,148,148,0  ,   255,152,152,0  ,   255,156,156,0  , //232
    255,160,160,0  ,   255,164,164,0  ,   255,168,168,0  ,   255,172,172,0  , //236
    255,176,176,0  ,   255,180,180,0  ,   255,184,184,0  ,   255,188,188,0  , //240
    255,192,192,0  ,   255,196,196,0  ,   255,200,200,0  ,   255,204,204,0  , //244
    255,208,208,0  ,   255,212,212,0  ,   255,216,216,0  ,   255,220,220,0  , //248
    255,224,224,0  ,   255,228,228,0  ,   255,232,232,0  ,   255,236,236,0  , //252
    255,240,240,0  ,   255,244,244,0  ,   255,248,248,0  ,   255,252,252,0   //256
    };

    bpColorsTable=ColorsTable ;
	ColorEnhance.Pseudo_Color_Enhance( bpColorsTable );

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
}

void CPhotoProcessView::OnDegenerationMotion()
{
	  //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ���˶�ģ����
	if (m_PhotoImage.GetBitCount() != 8)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ���˶�ģ����", "ϵͳ��ʾ" ,
			MB_ICONINFORMATION | MB_OK);
						
		// ����
		return;
	}
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //���ƴ���ǰ��ͼ��

    CImageRestoreDib ImageRestore(&m_PhotoImage);// ����һ��CImageRestoreDib����
	ImageRestore.DIBMotionDegeneration();

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
	
}

/*************************************************************************
BOOL  WINAPI  DIBMotionRestore(CDib *pDib)
{
	BYTE *	lpSrc;               // ָ��Դͼ���ָ��
	LONG    lWidth, lHeight ;      // ͼ��Ŀ�Ⱥ͸߶�
	LONG	lLineBytes;          // ͼ��ÿ�е��ֽ���
	//�õ�ͼ��Ŀ�Ⱥ͸߶�
	CSize   SizeDim;
	SizeDim = pDib->GetDimensions();
	lWidth  = SizeDim.cx;
	lHeight = SizeDim.cy;	
	//�õ�ʵ�ʵ�Dibͼ��洢��С
	CSize   SizeRealDim;
	SizeRealDim = pDib->GetDibSaveDim();
	lLineBytes = SizeRealDim.cx;              //����ͼ��ÿ�е��ֽ���	
	LPBYTE  lpDIBBits = pDib->m_lpImage;   //ͼ�����ݵ�ָ��
	//ѭ������
	long iColumn;
	long jRow;
	int i,n,m;	
	int temp1,temp2,totalq,q1,q2,z;            //��ʱ����
	double p,q;                            //��ʱ����	
	int A = 80;                            //����A��ֵ	
	int B = 10;                            //����B��ֵ	
	int nTotLen=10;                       //�ܵ��ƶ�����
	// ͼ���Ȱ������ٸ�ntotlen
	int K=lLineBytes/nTotLen;
	int error[10];
	int *nImageDegener;                        //�����洢Դͼ��ʱ������
	nImageDegener = new int [lHeight*lLineBytes];  // Ϊʱ���������ռ�
	// �����ش���������
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
		// ����error[i]
		for(i = 0; i < 10; i++)
		{
			error[i] = 0;
			for(n = 0; n < K; n++)
				for(m = 0; m <= n; m++)
				{
					// �����Ƿ�Ϊһ�еĿ�ʼ��
					if(i == 0 && m == 0)
					{
						temp1=temp2=0;
					}
					// ���в������
					else
					{
						lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + m*10+i;
						temp1=*lpSrc;
						lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + m*10+i-1;
						temp2 = *lpSrc;
					}
					error[i] = error[i] + temp1 - temp2;
				}
				error[i] = B * error[i] / K;
		}
		for(iColumn = 0; iColumn < lLineBytes; iColumn++)
		{			
			// ����m���Լ�z
			m = iColumn / nTotLen;
			z = iColumn - m*nTotLen;
			// ��ʼ��
			totalq = 0;
			q = 0;
			for(n = 0; n <= m; n++)
			{
				q1 = iColumn - nTotLen*n;
				if(q1 == 0)
					q = 0;
				// ���в������
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
			//�õ�f(x,y)��ֵ
			temp1 = totalq + A - p;
			// ʹ�����ص�ȡֵ����ȡֵ��Χ
			if(temp1 < 0)
				temp1 = 0;
			if(temp1 > 255)
				temp1 = 255;
			nImageDegener[lLineBytes*jRow + iColumn] = temp1;
		}
	}
	//ת��Ϊͼ��
	for (jRow = 0;jRow < lHeight ;jRow++)
	{
		for(iColumn = 0;iColumn < lLineBytes ;iColumn++)
		{
			// ָ��Դͼ������jRow�У���iColumn�����ص�ָ��			
 			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * jRow + iColumn;
			*lpSrc = nImageDegener[lLineBytes*jRow + iColumn];   //�洢����ֵ
		}
	}
	delete nImageDegener;   //�ͷŴ洢�ռ�	
	return true;            // ����
}

*************************************************************************/

void CPhotoProcessView::OnRestoreMotion()
{
	// ͼ��ԭ
	//���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ���˶�ģ����
	if (m_PhotoImage.GetBitCount() != 8)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ���˶�ģ����", "ϵͳ��ʾ" ,
			MB_ICONINFORMATION | MB_OK);
						
		// ����
		return;
	}
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG lHeight=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //���ƴ���ǰ��ͼ��

    CImageRestoreDib ImageRestore(&m_PhotoImage);// ����һ��CImageRestoreDib����
	ImageRestore.DIBMotionRestore();

    CPoint point1;
	point1.x=lWidth+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��

}

/**************************************************************************************
//��ƬЧ��
void Negative(BYTE* pixel, BYTE* tempPixel, int width, int height)
{
	int sum = width * height * 4;  //������������ĳ���
	memcpy(pixel, tempPixel, sum);
	for(int i = 0; i < sum; i += 4)  // ������ֵȡ��
	{
		tempPixel[i]	= 255 - tempPixel[i];	//blue
		tempPixel[i+1]	= 255 - tempPixel[i+1];	//green
		tempPixel[i+2]	= 255 - tempPixel[i+2];	//red
	}
}


//���Ч��
void Emboss(BYTE* pixel, BYTE* tempPixel, int width, int height)
{
	int sum = width * height *4;  //������������ĳ���
	memcpy(tempPixel, pixel, sum);
	int r = 0, g = 0, b = 0;
	for(int i = 0; i < height-1; i++) 
	{
		for (int j = 0; j < (width-1)*4; j+=4) 
		{
			//��������ֵ
			b = abs(tempPixel[i*width*4+j]-tempPixel[(i+1)*width*4+j+4]+128);
			g = abs(tempPixel[i*width*4+j+1]-tempPixel[(i+1)*width*4+j+5]+128);
			r = abs(tempPixel[i*width*4+j+2]-tempPixel[(i+1)*width*4+j+6]+128);
			if (r>255)  //����Խ�������ֵ���д���
				r=255;
			if (g>255)
				g=255;
			if (b>255)
				b=255;
			tempPixel[i*width*4 + j]		= b;//blue
			tempPixel[i*width*4 + j + 1]	= g;//green
			tempPixel[i*width*4 + j + 2]	= r;//red
		}
	}
	for (int k = width * 4 * (height-1); k < width*4*height; k += 4) 
	{
		tempPixel[k]=128;
		tempPixel[k+1]=128;
		tempPixel[k+2]=128;
	}
	for (int l = (width-1) * 4; l < width*4*height; l += width*4) 
	{
		tempPixel[l]=128;
		tempPixel[l+1]=128;
		tempPixel[l+2]=128;
	}
}


//�ڰ�Ч��
void ColorToBW(BYTE* pixel, BYTE* tempPixel, int width, int height)
{
	int sum = width * height * 4;  //������������ĳ���
	memcpy(tempPixel, pixel, sum);

	for(int i = 0; i < sum; i += 4)
	{
		//ƽ��ֵ��
		tempPixel[i]    = (tempPixel[i] + tempPixel[i+1] + tempPixel[i+2]) / 3; //blue
		tempPixel[i + 1] = tempPixel[i];	 //green
		tempPixel[i + 2] = tempPixel[i];										        //red
	}
}


//ˮƽ��
void HorFog(BYTE* pixel, BYTE* tempPixel, int width, int height, int f)
{
	int k;
	int n;
	for(int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width*4; j += 4) 
		{
			k = abs(rand() % f);
			n = j + k*4;
			if (n>(width-1) * 4)
				n = (width-1)*4;
			tempPixel[i*width*4 + j] = pixel[i*width*4 + n];
			tempPixel[i*width*4 + j + 1] = pixel[i*width*4 + n + 1];
			tempPixel[i*width*4 + j + 2] = pixel[i*width*4 + n + 2];
			tempPixel[i*width*4 + j + 3] = pixel[i*width*4 + n + 3];
		}
	}
}


//��ֱ��
void VerFog(BYTE* pixel, BYTE* tempPixel, int width, int height, int f)
{
	int k;
	int m;
	for(int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width*4; j += 4) 
		{
			k = abs(rand() % f);
			m = i + k;
			if (m>height-1)
				m = height-1;
			tempPixel[i*width*4 + j]     = pixel[m*width*4 + j];
			tempPixel[i*width*4 + j + 1] = pixel[m*width*4 + j + 1];
			tempPixel[i*width*4 + j + 2] = pixel[m*width*4 + j + 2];
			tempPixel[i*width*4 + j + 3] = pixel[m*width*4 + j + 3];
		}
	}
}


//������
void ComFog(BYTE* pixel, BYTE* tempPixel, int width, int height, int f)
{
	int k;
	int m, n;
	for(int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width*4; j += 4) 
		{
			k = abs(rand() % f);
			m = i + k;
			n = j + k * 4;
			if (m > height-1)  // �Գ���ͼ������ĵ������Ӧ����
				m = height-1;
			if (n > (width-1) * 4) 
				n = (width-1) * 4;
			tempPixel[i*width*4 + j]     = pixel[m*width*4 + n];  // ������������
			tempPixel[i*width*4 + j + 1] = pixel[m*width*4 + n + 1];
			tempPixel[i*width*4 + j + 2] = pixel[m*width*4 + n + 2];
			tempPixel[i*width*4 + j + 3] = pixel[m*width*4 + n + 3];
		}
	}
}


//����ģ��
int TempltExcuteCl(BYTE** imageBuf0, int w, int h, int* templt, int tw, int x, int y, int cn)
{
	int i,j;                        //ѭ������
	int m=0;                      //������ż�Ȩ��
	int px,py;   
	for(i=0; i<tw; i++)  //���ζ�������ÿ�����ؽ�������
	{
		for(j=0; j<tw; j++)
		{
			py=y-tw/2+i;   //�����Ӧģ����λ�õ�������ԭͼ���е�λ��
			px=x-tw/2+j;
			m+=imageBuf0[py][px*4+cn] * templt[i*tw+j];   //��Ȩ���
		}
	}
	return m;  //���ؽ��
}


//����Ч��
void LaplacianB(BYTE* pixel, BYTE* tempPixel, int w, int h)
{
	BYTE* tempImage;  //������ʱͼ��洢�ռ�
	tempImage = (BYTE*)malloc(sizeof(BYTE)*w*h*4);
	BYTE** imageBuf0 = CreatImage(pixel, w, h);  //��ͼ��ת��Ϊ������ʽ
	BYTE** imageBuf1 = CreatImage(tempPixel, w, h);
	BYTE** tempImageBuf = CreatImage(tempImage, w, h);
	double scale = 2;
	int templt[9]={ 1, 1, 1, 1,-8, 1, 1, 1, 1 };       //������˹����ģ��
	int templtTest1[9]={ 1, 1,-1, 1, 0,-1, 1,-1,-1 };  //�������ģ��
	int templtTest2[9]={ 1, 1, 1,-1, 0, 1,-1,-1,-1 };
	int templtAve[9]={ 1, 1, 1, 1, 4, 1, 1, 1, 1};    //ģ������ģ��
	int x,y;
	int a,b,b1,b2;
	for(y = 1; y < h - 1; y++)  //���ζ�ԭͼ���ÿ�����ؽ��д���
		for(x = 1; x < w - 1; x++)
		{
			a=TempltExcute(imageBuf0, w, h, templt, 3, x, y);   //������˹�������
			b1=abs(TempltExcute(imageBuf0, w, h, templtTest1, 3, x, y));   //�������
			b2=abs(TempltExcute(imageBuf0, w, h, templtTest2, 3, x, y));
			b=b1>b2?b1:b2;
			if(b<25) a=0;
			else
			{
				a = (int)(a * scale);
				if(a > 255) a = 255;  //���޴���
				else if(a < 32) a=0;
			}
			a=255-a;   //��ɫ����
			SetPixel2(tempImageBuf, x, y, a);
		}
		for(y = 1; y < h - 1; y++)  //ģ������
			for(x = 1; x < w - 1; x++)
			{
				a=TempltExcute(tempImageBuf, w, h, templtAve, 3, x, y) / 12;
				SetPixel2(imageBuf1, x, y, a);
			}
	free(tempImage);
	free(imageBuf0);
	free(imageBuf1);
	free(tempImageBuf);
}
*************************************************************************************/


void CPhotoProcessView::OnFilterNegative()
{
	//��ƬЧ������RGB��ɫ
    //���֮ǰû����ͼ�񣬽���������ʾ
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
    LONG width=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG  height=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx=width	;
	size.cy= height;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //���ƴ���ǰ��ͼ��

    CImageFilterDib ImageFilter(&m_PhotoImage); // ����һ��CImageFilterDib����
	ImageFilter.Negative();

    CPoint point1;
	point1.x=width+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��

}


void CPhotoProcessView::OnFilterEmboss()
{
	//���Ч��������
    if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
    LONG width=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG  height=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx=width	;
	size.cy= height;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //���ƴ���ǰ��ͼ��

    CImageFilterDib ImageFilter(&m_PhotoImage); // ����һ��CImageFilterDib����
	ImageFilter.Emboss();

    CPoint point1;
	point1.x=width+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��

}

void CPhotoProcessView::OnFilterBw()
{
	//�ڰ�Ч��
 if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
	if (m_PhotoImage.IsGrade() == 1)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧�ֲ�ɫͼ��", "ϵͳ��ʾ" ,
			MB_ICONINFORMATION | MB_OK);
		return;
	}
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
    LONG width=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG  height=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx=width	;
	size.cy= height;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //���ƴ���ǰ��ͼ��

    CImageFilterDib ImageFilter(&m_PhotoImage); // ����һ��CImageFilterDib����
	ImageFilter.ColorToBW();

    CPoint point1;
	point1.x=width+40;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��

}


void CPhotoProcessView::OnFilterFog()
{
	//��Ч��
	
if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
    LONG width=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG  height=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx=width	;
	size.cy= height;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //���ƴ���ǰ��ͼ��

    CImageFilterDib ImageFilter(&m_PhotoImage); // ����һ��CImageFilterDib����
	ImageFilter.ComFog();

    CPoint point1;
	point1.x=width+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��

}

void CPhotoProcessView::OnFilterSketch()
{
	//����Ч��
if(flag==FALSE)
    {
        AfxMessageBox("���ȼ���Ҫ�������Ƭͼ��");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
    LONG width=m_PhotoImage.GetWidth();    //��ûҶ�ͼ��Ŀ��
	LONG  height=m_PhotoImage.GetHeight();  //��ûҶ�ͼ��ĸ߶�
	size.cx=width	;
	size.cy= height;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //���ƴ���ǰ��ͼ��

    CImageFilterDib ImageFilter(&m_PhotoImage); // ����һ��CImageFilterDib����
	ImageFilter.LaplacianB();

    CPoint point1;
	point1.x=width+20;  //+20��Ϊ��������ͼ����ʾʱ�и���϶
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//���ƴ�����ͼ��
}



