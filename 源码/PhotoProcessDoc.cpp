// PhotoProcessDoc.cpp : CPhotoProcessDoc ���ʵ��
//

#include "stdafx.h"
#include "PhotoProcess.h"

#include "PhotoProcessDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhotoProcessDoc

IMPLEMENT_DYNCREATE(CPhotoProcessDoc, CDocument)

BEGIN_MESSAGE_MAP(CPhotoProcessDoc, CDocument)
END_MESSAGE_MAP()


// CPhotoProcessDoc ����/����

CPhotoProcessDoc::CPhotoProcessDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CPhotoProcessDoc::~CPhotoProcessDoc()
{
}

BOOL CPhotoProcessDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPhotoProcessDoc ���л�

void CPhotoProcessDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CPhotoProcessDoc ���

#ifdef _DEBUG
void CPhotoProcessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPhotoProcessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPhotoProcessDoc ����
