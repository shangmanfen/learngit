
// 串口V2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "串口V2.h"
#include "串口V2Dlg.h"
#include "afxdialogex.h"
#include "mscomm1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma region MyRegion
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C串口V2Dlg 对话框



C串口V2Dlg::C串口V2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_V2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C串口V2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_MSCOMM1, mscomm);
}

BEGIN_MESSAGE_MAP(C串口V2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(OPEN_COM, &C串口V2Dlg::OnBnClickedCom)
	ON_BN_CLICKED(IDCANCEL, &C串口V2Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(RECEIVE, &C串口V2Dlg::OnBnClickedReceive)
	ON_BN_CLICKED(SEND, &C串口V2Dlg::OnBnClickedSend)
END_MESSAGE_MAP()
void C串口V2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C串口V2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C串口V2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
#pragma endregion

// C串口V2Dlg 消息处理程序
CComboBox *comb1;
CComboBox *comb2;
CButton *OPENCOM;
CMscomm1 *mscomm;
CEdit *editReceive;
CButton *sendtype;
BOOL C串口V2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
#pragma region MyRegion

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
#pragma endregion
	// TODO: 在此添加额外的初始化代码
	comb1 = (CComboBox*)GetDlgItem(IDC_COMBO1);
	comb2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	OPENCOM = (CButton*)GetDlgItem(OPEN_COM);
	mscomm = (CMscomm1*)GetDlgItem(IDC_MSCOMM1);
	editReceive = (CEdit*)GetDlgItem(IDC_EDIT2);
	sendtype = (CButton*)GetDlgItem(IDC_CHECK_MAX);
	CString str;
	int i;
	HANDLE m_hComm;
	DWORD dwCreateProperty;
	//Handle to the comms port
	int nPort = 0x00;
	DWORD dwError = 0x00;
	//Call CreateFile to open up the comms port
	CString sPort;
	dwCreateProperty = FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED;
	for (i = 0; i<50; i++) {
		sPort.Format(_T("COM%d"), nPort);
		m_hComm = CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, dwCreateProperty, NULL);
		if (m_hComm == INVALID_HANDLE_VALUE) {
			dwError = ::GetLastError();
			if (dwError == 2) {
				//机器上没有这个串口
			}
			else if (dwError == 5) {
				TRACE("nPort1 = %d.\n", nPort);
				//有这个串口,但是已经被打开
			}
		}
		else {
			//能够正常打开
			TRACE("m_hComm = 0x%x.\n", m_hComm);
			TRACE("nPort2 = %d.\n", nPort);
			str.Format(_T("m_hComm = 0x%x.\n"), m_hComm);
			comb1->AddString(str);
			BOOL bSuccess = CloseHandle(m_hComm);
			m_hComm = INVALID_HANDLE_VALUE;
			if (!bSuccess) {
				TRACE(_T("Failed to close up the comms port, GetLastError:%d\n"), GetLastError());
			}
		}
		nPort++;
	}

	/*int i;
	for (i = 0; i<15; i++)
	{
		//hCom = CreateFile(str, 0, 0, 0,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		str.Format(_T("com %d"), i + 1);
		comb1->AddString(str);
	}*/
	comb1->SetCurSel(0);//预置COM口
	comb2->AddString(_T("9600"));
	comb2->AddString(_T("38400"));
	comb2->AddString(_T("115200"));
	comb2->SetCurSel(2);//预置波特率
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}



//打开/关闭串口
void C串口V2Dlg::OnBnClickedCom()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str, BaudRate;
	GetDlgItemText(OPEN_COM, str);//把IDOK的名称赋值给str
	if (str == "打开串口") {
		if (!mscomm->get_PortOpen()) {
			comb2->GetLBText(comb2->GetCurSel(), BaudRate);//取得所选的字符串，存放到str1
			BaudRate = BaudRate + ',' + 'n' + ',' + '8' + ',' + '1';//关键！
			mscomm->put_CommPort((comb1->GetCurSel() + 1));
			mscomm->put_InputMode(1);//1表示输入方式设置成二进制方式
			mscomm->put_Settings(BaudRate);//比特率为（），无校验，8个数据位，1个停止位
			mscomm->put_InputLen(1024);//设置当前接收区数据长度为1024
			mscomm->put_RThreshold(1);//缓冲区>=一个字符引发事件
			mscomm->put_RTSEnable(1);//设置RT允许

			mscomm->put_PortOpen(true);//打开串口

			if (mscomm->get_PortOpen()) {
				OPENCOM->SetWindowTextW(_T("关闭串口"));
			}
		}
	}
	else if (str == "关闭串口") {
		mscomm->put_PortOpen(false);
		OPENCOM->SetWindowTextW(_T("打开串口"));
	}
}

//退出
void C串口V2Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mscomm->get_PortOpen())
		mscomm->put_PortOpen(false);
	CDialogEx::OnCancel();
}

//清空数据
void C串口V2Dlg::OnBnClickedReceive()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT2, _T(""));
}
//发送数据
void C串口V2Dlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString send;
	GetDlgItemText(IDC_EDIT3, send);
	if (sendtype->GetCheck())//以16进制发送
	{
		TCHAR *string;
		int a = _tcstol(send.GetBuffer(), &string, 16);
		//str2.Format(_T("%x"), a);

		CByteArray senddata;
		senddata.Add(a);
		mscomm->put_Output(COleVariant(senddata));
	}
	else//以字符串类型发送
		mscomm->put_Output(COleVariant(send));//把发送编辑框的数据发送出去
}
BEGIN_EVENTSINK_MAP(C串口V2Dlg, CDialogEx)
	ON_EVENT(C串口V2Dlg, IDC_MSCOMM1, 1, C串口V2Dlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()
//接收数据
CString EditRecieve1;
void C串口V2Dlg::OnCommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	if (mscomm->get_CommEvent() == 2)
	{
		char str[1024] = { 0 };
		long k;
		VARIANT InputData = mscomm->get_Input();	//读缓冲区
		COleSafeArray fs; TCHAR *string;
		fs = InputData;	//VARIANT型变À量转换为COleSafeArray型变量
		for (k = 0; k<fs.GetOneDimSize(); k++)
			fs.GetElement(&k, str + k);	//转换为BYTE型数组

		if (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck()) {
			CString str2 = _T("");
			str2 += str;
			int a = _tcstol(str2.GetBuffer(), &string, 10);
			str2.Format(_T("0x%x"), a);
			EditRecieve1 += str2;
		}
		else {
			EditRecieve1 += str;      //	接收到编辑框里面//SetTimer(1,10,NULL);		//延时10ms
		}
		UpdateData(false);
		editReceive->SetSel(-1, -1);
		SetDlgItemText(IDC_EDIT2, EditRecieve1);//将m_EditReceive内容显示到ID为IDC_EDIT1的编辑框的最后位置
		editReceive->LineScroll(editReceive->GetLineCount() - 1, 0);//将垂直滚动条滚动到最后一行
	}
}
