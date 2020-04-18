// FogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MagicHouse.h"
#include "FogDlg.h"
#include "PreviewDlg.h"
#include "Filter.h"
#include "Mainfrm.h"
#include "MagicHouseDoc.h"
#include "MagicHouseView.h"


// CFogDlg �Ի���

IMPLEMENT_DYNAMIC(CFogDlg, CDialog)

CFogDlg::CFogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFogDlg::IDD, pParent)
	, m_nType(0)
	, m_nValue(1)
	, m_nPos(0)
{
	m_bModify = false;
}

CFogDlg::~CFogDlg()
{
}

void CFogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_HFOG, m_nType);
	DDX_Text(pDX, IDC_VALUE, m_nValue);
	DDX_Slider(pDX, IDC_SLIDER, m_nPos);
}


BEGIN_MESSAGE_MAP(CFogDlg, CDialog)
	ON_BN_CLICKED(IDC_PREV, &CFogDlg::OnBnClickedPrev)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_SAVE, &CFogDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDOK, &CFogDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/******************************************************************************
*	����:		��ʼ���Ի���
******************************************************************************/
BOOL CFogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���û���ķ�Χ
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetRange(1, 50);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/******************************************************************************
*	����:		�������Ӧ����
******************************************************************************/
void CFogDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateData(TRUE);
	m_nValue = m_nPos;
	UpdateData(FALSE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

/******************************************************************************
*	����:		���½���ͼ���������
******************************************************************************/
void CFogDlg::Refresh()
{
	UpdateData(TRUE);

	// ����Ԥ���Ի���
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CMagicHouseView* pView = (CMagicHouseView*)pMain->GetActiveView();

	if (m_nType == 0)
		HorFog(pView->m_pImageBuffer, pView->m_pImageTempBuffer, 
		pView->m_nPicWidth, pView->m_nPicHeight, m_nValue);
	else if (m_nType == 1)
		VerFog(pView->m_pImageBuffer, pView->m_pImageTempBuffer, 
		pView->m_nPicWidth, pView->m_nPicHeight, m_nValue);
	else
		ComFog(pView->m_pImageBuffer, pView->m_pImageTempBuffer, 
		pView->m_nPicWidth, pView->m_nPicHeight, m_nValue);
	
	m_bModify = true;
}

/******************************************************************************
*	����:		��Ԥ������ť����Ӧ����
******************************************************************************/
void CFogDlg::OnBnClickedPrev()
{
	Refresh();

	CPreviewDlg dlg;
	dlg.m_nType = 1;
	dlg.DoModal();
}

/******************************************************************************
*	����:		�����桱��ť����Ӧ����
******************************************************************************/
void CFogDlg::OnBnClickedSave()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CMagicHouseView* pView = (CMagicHouseView*)pMain->GetActiveView();

	Refresh();
	pView->OnFileSave();
	m_bModify = false;
}

/******************************************************************************
*	����:		��ȷ������ť����Ӧ����
******************************************************************************/
void CFogDlg::OnBnClickedOk()
{
	if (m_bModify)
	{
		if (IDYES == MessageBox(L"ͼ���Ѿ����ģ��Ƿ񱣴棿", L"Magic House", MB_YESNO))
			OnBnClickedSave();
	}
	OnOK();
}