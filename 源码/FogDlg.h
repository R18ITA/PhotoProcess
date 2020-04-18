#pragma once


// CFogDlg �Ի���

class CFogDlg : public CDialog
{
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CFogDlg)

public:
	int m_nPos;		// �����������
	int m_nValue;	// ������
	int m_nType;	// ������

	CFogDlg(CWnd* pParent = NULL); 
	virtual ~CFogDlg();

	void Refresh();
	virtual BOOL OnInitDialog();

	// ��Ϣ��Ӧ����
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPrev();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

private:
	bool	m_bModify;	// ͼ���Ƿ��޸�

	// �Ի�������
	enum { IDD = IDD_FOG };
};