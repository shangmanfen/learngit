
// ����V2Dlg.h : ͷ�ļ�
//

#pragma once
#include "mscomm1.h"


// C����V2Dlg �Ի���
class C����V2Dlg : public CDialogEx
{
// ����
public:
	C����V2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_V2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCom();
	afx_msg void OnBnClickedCancel();
//	CMscomm1 mscomm;
	afx_msg void OnBnClickedReceive();
	afx_msg void OnBnClickedSend();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
};
