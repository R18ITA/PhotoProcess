// PhotoProcessView.cpp : CPhotoProcessView 类的实现
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
	// 标准打印命令
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

// CPhotoProcessView 构造/析构

CPhotoProcessView::CPhotoProcessView()
{
	// TODO: 在此处添加构造代码
    flag=FALSE;

}

CPhotoProcessView::~CPhotoProcessView()
{
}

BOOL CPhotoProcessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPhotoProcessView 绘制

void CPhotoProcessView::OnDraw(CDC* /*pDC*/)
{
	CPhotoProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPhotoProcessView 打印

BOOL CPhotoProcessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPhotoProcessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPhotoProcessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CPhotoProcessView 诊断

#ifdef _DEBUG
void CPhotoProcessView::AssertValid() const
{
	CView::AssertValid();
}

void CPhotoProcessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPhotoProcessDoc* CPhotoProcessView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhotoProcessDoc)));
	return (CPhotoProcessDoc*)m_pDocument;
}
#endif //_DEBUG


// CPhotoProcessView 消息处理程序

void CPhotoProcessView::OnOpenPhoto()
{
    
	if(flag==TRUE)
		this->Invalidate();
	// 本函数功能是打开并显示照片图像
    CString  filename;
    CFileDialog dlg(TRUE,_T("BMP"),_T("*.BMP"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|"));	
    if(IDOK==dlg.DoModal())	
    filename.Format ("%s",dlg.GetPathName() ); 
   
    m_PhotoImage.LoadFromFile(filename);//打开照片图像
    flag=TRUE;//照片图像打开后，将标记变量置为真

	//显示图像
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);
	


}

void CPhotoProcessView::OnLinearTransform()
{
    // 此函数实现灰度线性增强处理
    
    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//绘制处理前的图像

    CGrayTransformDib GrayTransform(&m_PhotoImage);//创建一个CGrayTransformDib对象
    BYTE min,max;  //设置变换后的灰度区间
    min=100;
    max=200;
	 
	GrayTransform.Linear_Transform( min,max);  //调用灰度线性变换增强函数

	CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point,size);//绘制处理后的图像
}

void CPhotoProcessView::OnSegLineTransform()
{
    // 此函数实现分段线性增强处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//绘制处理前的图像

    CGrayTransformDib GrayTransform(&m_PhotoImage); //创建一个CGrayTransformDib对象
    BYTE gSrc1,gSrc2, gDst1, gDst2;  //设置分段点
    gSrc1=100;
    gSrc2=150;
    gDst1=50;
    gDst2=200;
	GrayTransform.Seg_Linear_Transform( gSrc1,  gSrc2, gDst1, gDst2);//调用分段线性变换增强函数

	CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
}

void CPhotoProcessView::OnLogTransform()
{
    // 此函数实现对数函数非线性变换增强处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//绘制处理前的图像

    CGrayTransformDib GrayTransform(&m_PhotoImage);//创建一个CGrayTransformDib对象

    double a,b,c;  //对数函数变换参数设置
    a=50.0;
    b=0.8;
    c=1.05;       
	GrayTransform.Log_Transform( a, b, c);  //调用对数函数非线性变换增强函数

	CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
}

void CPhotoProcessView::OnHistogramEqual()
{
   
    // 此函数实现直方图均衡化增强处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//绘制处理前的图像

    CHistogramDib Histgram(&m_PhotoImage);//创建一个CHistogramDib对象
         
    Histgram.Histogram_Equalization( );   //调用直方图均衡化处理函数

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
}

void CPhotoProcessView::OnHistogramMatch()
{
    // 此函数实现直方图规定化增强处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//绘制处理前的图像

    CHistogramDib Histgram(&m_PhotoImage);//创建一个CHistogramDib对象
         
    int nu[64];  //规定直方图映射关系,这里规定直方图的灰度级为64
    float pu[64]; //规定灰度分布概率
    float a=1.0f/(32.0f*63.0f); 
    for(int i=0;i<64;i++)
    {
        nu[i]=i*4;
        pu[i]=a*i;
    }      
     
	Histgram.Histogram_Match( 64,nu,pu); //调用直方图规定化函数

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图
}


void CPhotoProcessView::OnAverageSmooth()
{
    // 此函数实现邻域均值平滑处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//绘制处理前的图像

    CSmoothProcessDib Smooth(&m_PhotoImage);//创建一个CSmoothProcessDib对象         
    Smooth.Average_Smooth( );  //调用邻域平均平滑函数

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
}

void CPhotoProcessView::OnValueAvrgSmooth()
{
    // 此函数实现邻域加权均值平滑处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//绘制处理前的图像

    CSmoothProcessDib Smooth(&m_PhotoImage);//创建一个CSmoothProcessDib对象         
    
    int Structure[3][3]={1,2,1,2,4,2,1,2,1};//定义加权模板
     
	Smooth.Value_Average_Smooth(Structure); //调用邻域加权平均平滑函数

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
}

void CPhotoProcessView::OnSelectSmooth()
{
    // 此函数实现选择式掩膜平滑处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//绘制处理前的图像

    CSmoothProcessDib Smooth(&m_PhotoImage);//创建一个CSmoothProcessDib对象         
    Smooth.Select_Smooth( );  //调用选择式掩膜平滑函数

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
}

void CPhotoProcessView::OnMiddleSmooth()
{
     // 此函数实现中值滤波平滑处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//绘制处理前的图像

    CSmoothProcessDib Smooth(&m_PhotoImage);//创建一个CSmoothProcessDib对象         
    Smooth.Middle_Smooth( ); //调用中值滤波平滑函数

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
}



void CPhotoProcessView::OnGateGrad( )
{
    // 此函数实现门限梯度锐化处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }

	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);//绘制处理前的图像

    CSharpenProcessDib Sharpen(&m_PhotoImage);//创建一个CSharpenProcessDib对象
         
    BYTE t=30;
	Sharpen.GateGrad(t);   //调用门限梯度锐化处理函数

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像     
}

void CPhotoProcessView::OnLaplacian( )
{
    // 此函数实现拉普拉斯锐化处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }

	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //绘制处理前的图像

    CSharpenProcessDib Sharpen(&m_PhotoImage);//创建一个CSharpenProcessDib对象         
    
	Sharpen.Laplacian( );   //调用拉普拉斯锐化处理函数

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
    
}

void CPhotoProcessView::OnPrefectLowFilter()
{
    // 此函数实现理想低通滤波处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }

	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //绘制处理前的图像

    CFrequencyFilterDib FrequencyFilter(&m_PhotoImage);// 创建一个CFrequencyFilterDib对象
    //设置截止频域分量参数
    int u=100;
    int v=100;     
	FrequencyFilter.Perfect_Low_Filter( u,v); //调用理想低通滤波函数

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
}

void CPhotoProcessView::OnPrefectHighFilter()
{
    // 此函数实现理想高通滤波处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }

	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //绘制处理前的图像

    CFrequencyFilterDib FrequencyFilter(&m_PhotoImage);// 创建一个CFrequencyFilterDib对象
    //设置截止频域分量参数
    int u=100;
    int v=100;     
	FrequencyFilter.Perfect_High_Filter( u,v); //调用理想高通滤波函数

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
}

void CPhotoProcessView::OnPseudoColorEnhance()
{
    // 此函数实现拉普拉斯锐化处理

    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }

	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //绘制处理前的图像

    CColorEnhanceDib ColorEnhance(&m_PhotoImage);// 创建一个CColorEnhanceDib对象

    BYTE *bpColorsTable;
    // 伪彩色编码表
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
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
}

void CPhotoProcessView::OnDegenerationMotion()
{
	  //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的运动模糊）
	if (m_PhotoImage.GetBitCount() != 8)
	{
		// 提示用户
		MessageBox("目前只支持256色位图的运动模糊！", "系统提示" ,
			MB_ICONINFORMATION | MB_OK);
						
		// 返回
		return;
	}
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //绘制处理前的图像

    CImageRestoreDib ImageRestore(&m_PhotoImage);// 创建一个CImageRestoreDib对象
	ImageRestore.DIBMotionDegeneration();

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
	
}

/*************************************************************************
BOOL  WINAPI  DIBMotionRestore(CDib *pDib)
{
	BYTE *	lpSrc;               // 指向源图像的指针
	LONG    lWidth, lHeight ;      // 图像的宽度和高度
	LONG	lLineBytes;          // 图像每行的字节数
	//得到图像的宽度和高度
	CSize   SizeDim;
	SizeDim = pDib->GetDimensions();
	lWidth  = SizeDim.cx;
	lHeight = SizeDim.cy;	
	//得到实际的Dib图像存储大小
	CSize   SizeRealDim;
	SizeRealDim = pDib->GetDibSaveDim();
	lLineBytes = SizeRealDim.cx;              //计算图像每行的字节数	
	LPBYTE  lpDIBBits = pDib->m_lpImage;   //图像数据的指针
	//循环变量
	long iColumn;
	long jRow;
	int i,n,m;	
	int temp1,temp2,totalq,q1,q2,z;            //临时变量
	double p,q;                            //临时变量	
	int A = 80;                            //常量A赋值	
	int B = 10;                            //常量B赋值	
	int nTotLen=10;                       //总的移动距离
	// 图像宽度包含多少个ntotlen
	int K=lLineBytes/nTotLen;
	int error[10];
	int *nImageDegener;                        //用来存储源图像时域数据
	nImageDegener = new int [lHeight*lLineBytes];  // 为时域数组分配空间
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
				error[i] = B * error[i] / K;
		}
		for(iColumn = 0; iColumn < lLineBytes; iColumn++)
		{			
			// 计算m，以及z
			m = iColumn / nTotLen;
			z = iColumn - m*nTotLen;
			// 初始化
			totalq = 0;
			q = 0;
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
			//得到f(x,y)的值
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
			*lpSrc = nImageDegener[lLineBytes*jRow + iColumn];   //存储象素值
		}
	}
	delete nImageDegener;   //释放存储空间	
	return true;            // 返回
}

*************************************************************************/

void CPhotoProcessView::OnRestoreMotion()
{
	// 图像复原
	//如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的运动模糊）
	if (m_PhotoImage.GetBitCount() != 8)
	{
		// 提示用户
		MessageBox("目前只支持256色位图的运动模糊！", "系统提示" ,
			MB_ICONINFORMATION | MB_OK);
						
		// 返回
		return;
	}
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
	LONG lWidth=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG lHeight=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx= lWidth	;
	size.cy= lHeight;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //绘制处理前的图像

    CImageRestoreDib ImageRestore(&m_PhotoImage);// 创建一个CImageRestoreDib对象
	ImageRestore.DIBMotionRestore();

    CPoint point1;
	point1.x=lWidth+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像

}

/**************************************************************************************
//底片效果
void Negative(BYTE* pixel, BYTE* tempPixel, int width, int height)
{
	int sum = width * height * 4;  //计算像素数组的长度
	memcpy(pixel, tempPixel, sum);
	for(int i = 0; i < sum; i += 4)  // 对像素值取反
	{
		tempPixel[i]	= 255 - tempPixel[i];	//blue
		tempPixel[i+1]	= 255 - tempPixel[i+1];	//green
		tempPixel[i+2]	= 255 - tempPixel[i+2];	//red
	}
}


//雕刻效果
void Emboss(BYTE* pixel, BYTE* tempPixel, int width, int height)
{
	int sum = width * height *4;  //计算像素数组的长度
	memcpy(tempPixel, pixel, sum);
	int r = 0, g = 0, b = 0;
	for(int i = 0; i < height-1; i++) 
	{
		for (int j = 0; j < (width-1)*4; j+=4) 
		{
			//处理像素值
			b = abs(tempPixel[i*width*4+j]-tempPixel[(i+1)*width*4+j+4]+128);
			g = abs(tempPixel[i*width*4+j+1]-tempPixel[(i+1)*width*4+j+5]+128);
			r = abs(tempPixel[i*width*4+j+2]-tempPixel[(i+1)*width*4+j+6]+128);
			if (r>255)  //对于越界的像素值进行处理
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


//黑白效果
void ColorToBW(BYTE* pixel, BYTE* tempPixel, int width, int height)
{
	int sum = width * height * 4;  //计算像素数组的长度
	memcpy(tempPixel, pixel, sum);

	for(int i = 0; i < sum; i += 4)
	{
		//平均值法
		tempPixel[i]    = (tempPixel[i] + tempPixel[i+1] + tempPixel[i+2]) / 3; //blue
		tempPixel[i + 1] = tempPixel[i];	 //green
		tempPixel[i + 2] = tempPixel[i];										        //red
	}
}


//水平雾化
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


//垂直雾化
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


//复合雾化
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
			if (m > height-1)  // 对超出图像区域的点进行相应处理
				m = height-1;
			if (n > (width-1) * 4) 
				n = (width-1) * 4;
			tempPixel[i*width*4 + j]     = pixel[m*width*4 + n];  // 更新像素数组
			tempPixel[i*width*4 + j + 1] = pixel[m*width*4 + n + 1];
			tempPixel[i*width*4 + j + 2] = pixel[m*width*4 + n + 2];
			tempPixel[i*width*4 + j + 3] = pixel[m*width*4 + n + 3];
		}
	}
}


//素描模板
int TempltExcuteCl(BYTE** imageBuf0, int w, int h, int* templt, int tw, int x, int y, int cn)
{
	int i,j;                        //循环变量
	int m=0;                      //用来存放加权和
	int px,py;   
	for(i=0; i<tw; i++)  //依次对邻域中每个像素进行运算
	{
		for(j=0; j<tw; j++)
		{
			py=y-tw/2+i;   //计算对应模板上位置的像素在原图像中的位置
			px=x-tw/2+j;
			m+=imageBuf0[py][px*4+cn] * templt[i*tw+j];   //加权求和
		}
	}
	return m;  //返回结果
}


//素描效果
void LaplacianB(BYTE* pixel, BYTE* tempPixel, int w, int h)
{
	BYTE* tempImage;  //定义临时图像存储空间
	tempImage = (BYTE*)malloc(sizeof(BYTE)*w*h*4);
	BYTE** imageBuf0 = CreatImage(pixel, w, h);  //将图像转化为矩阵形式
	BYTE** imageBuf1 = CreatImage(tempPixel, w, h);
	BYTE** tempImageBuf = CreatImage(tempImage, w, h);
	double scale = 2;
	int templt[9]={ 1, 1, 1, 1,-8, 1, 1, 1, 1 };       //拉普拉斯正相模板
	int templtTest1[9]={ 1, 1,-1, 1, 0,-1, 1,-1,-1 };  //噪声检测模板
	int templtTest2[9]={ 1, 1, 1,-1, 0, 1,-1,-1,-1 };
	int templtAve[9]={ 1, 1, 1, 1, 4, 1, 1, 1, 1};    //模糊处理模板
	int x,y;
	int a,b,b1,b2;
	for(y = 1; y < h - 1; y++)  //依次对原图像的每个像素进行处理
		for(x = 1; x < w - 1; x++)
		{
			a=TempltExcute(imageBuf0, w, h, templt, 3, x, y);   //拉普拉斯卷积运算
			b1=abs(TempltExcute(imageBuf0, w, h, templtTest1, 3, x, y));   //噪声检测
			b2=abs(TempltExcute(imageBuf0, w, h, templtTest2, 3, x, y));
			b=b1>b2?b1:b2;
			if(b<25) a=0;
			else
			{
				a = (int)(a * scale);
				if(a > 255) a = 255;  //过限处理
				else if(a < 32) a=0;
			}
			a=255-a;   //反色处理
			SetPixel2(tempImageBuf, x, y, a);
		}
		for(y = 1; y < h - 1; y++)  //模糊处理
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
	//底片效果，求RGB反色
    //如果之前没加载图像，将在这里提示
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
    LONG width=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG  height=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx=width	;
	size.cy= height;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //绘制处理前的图像

    CImageFilterDib ImageFilter(&m_PhotoImage); // 创建一个CImageFilterDib对象
	ImageFilter.Negative();

    CPoint point1;
	point1.x=width+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像

}


void CPhotoProcessView::OnFilterEmboss()
{
	//雕刻效果，浮雕
    if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
    LONG width=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG  height=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx=width	;
	size.cy= height;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //绘制处理前的图像

    CImageFilterDib ImageFilter(&m_PhotoImage); // 创建一个CImageFilterDib对象
	ImageFilter.Emboss();

    CPoint point1;
	point1.x=width+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像

}

void CPhotoProcessView::OnFilterBw()
{
	//黑白效果
 if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
	if (m_PhotoImage.IsGrade() == 1)
	{
		// 提示用户
		MessageBox("目前只支持彩色图像！", "系统提示" ,
			MB_ICONINFORMATION | MB_OK);
		return;
	}
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
    LONG width=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG  height=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx=width	;
	size.cy= height;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //绘制处理前的图像

    CImageFilterDib ImageFilter(&m_PhotoImage); // 创建一个CImageFilterDib对象
	ImageFilter.ColorToBW();

    CPoint point1;
	point1.x=width+40;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像

}


void CPhotoProcessView::OnFilterFog()
{
	//雾化效果
	
if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
    LONG width=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG  height=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx=width	;
	size.cy= height;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //绘制处理前的图像

    CImageFilterDib ImageFilter(&m_PhotoImage); // 创建一个CImageFilterDib对象
	ImageFilter.ComFog();

    CPoint point1;
	point1.x=width+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像

}

void CPhotoProcessView::OnFilterSketch()
{
	//素描效果
if(flag==FALSE)
    {
        AfxMessageBox("请先加载要处理的照片图像！");
        return;
    }
    
	CPoint point;
	CSize size;
	point.x=0;
	point.y=0;
    LONG width=m_PhotoImage.GetWidth();    //获得灰度图像的宽度
	LONG  height=m_PhotoImage.GetHeight();  //获得灰度图像的高度
	size.cx=width	;
	size.cy= height;
	CDC *pDC=GetDC();
	m_PhotoImage.Draw(pDC,point,size);    //绘制处理前的图像

    CImageFilterDib ImageFilter(&m_PhotoImage); // 创建一个CImageFilterDib对象
	ImageFilter.LaplacianB();

    CPoint point1;
	point1.x=width+20;  //+20是为了让两个图像显示时有个间隙
	point1.y=0;
	m_PhotoImage.Draw(pDC,point1,size);//绘制处理后的图像
}



