// PhotoProcessDoc.h : CPhotoProcessDoc ��Ľӿ�
//


#pragma once


class CPhotoProcessDoc : public CDocument
{
protected: // �������л�����
	CPhotoProcessDoc();
	DECLARE_DYNCREATE(CPhotoProcessDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CPhotoProcessDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


