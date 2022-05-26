
// BOTDRDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "BOTDR.h"
#include "BOTDRDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CBOTDRDlg 对话框



CBOTDRDlg::CBOTDRDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOTDR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBOTDRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_CHART_LM_SINGLE,m_ChartLmSingle);
	DDX_Control(pDX, IDC_CHART_LM_OVERALL, m_ChartLmOverall);
	DDX_Control(pDX, IDC_CHART_POWER, m_ChartPower);
}

BEGIN_MESSAGE_MAP(CBOTDRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FILE_CHIOCE, &CBOTDRDlg::OnBnClickedButtonFileChioce)
	ON_BN_CLICKED(IDC_BUTTON_POWER_DRAW, &CBOTDRDlg::OnBnClickedButtonPowerDraw)
	ON_BN_CLICKED(IDC_BUTTON_SETUP, &CBOTDRDlg::OnBnClickedButtonSetup)
	ON_BN_CLICKED(IDC_BUTTON_ADD_AVERAGE, &CBOTDRDlg::OnBnClickedButtonAddAverage)
	ON_BN_CLICKED(IDC_BUTTON_LM_OVERALL, &CBOTDRDlg::OnBnClickedButtonLmOverall)
	ON_BN_CLICKED(IDC_BUTTON_LM_SINGLE, &CBOTDRDlg::OnBnClickedButtonLmSingle)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, &CBOTDRDlg::OnSysExit)
END_MESSAGE_MAP()


// CBOTDRDlg 消息处理程序

void CBOTDRDlg::System_Init()
{
	Chart_Init();
	Data_Init();
}

void CBOTDRDlg::Chart_Init()
{
	/*****************************LM单点拟合窗口初始化***********************************/
	m_ChartLmSingle.SetBackColor(RGB(0, 0, 0));
	m_ChartLmSingle.RefreshCtrl();

	TChartString LSTitle = _T("LM单点拟合");    //图表标题
	CChartTitle* LSpTitle = m_ChartLmSingle.GetTitle();
	LSpTitle->AddString(LSTitle);
	LSpTitle->SetColor(RGB(255, 255, 255));

	CChartAxis* LSpLeftAxis = m_ChartLmSingle.CreateStandardAxis(CChartCtrl::LeftAxis);
	LSpLeftAxis->SetMinMax(-0.1,1.1);
	LSpLeftAxis->SetTextColor(RGB(255, 255, 255));
	LSpLeftAxis->SetAxisColor(RGB(255, 255, 255));
	LSpLeftAxis->GetLabel()->SetText(_T("Power"));  //左轴label
	LSpLeftAxis->GetLabel()->SetColor(RGB(255, 255, 255));


	CChartAxis* LSpBottomAxis = m_ChartLmSingle.CreateStandardAxis(CChartCtrl::BottomAxis);
	LSpBottomAxis->SetMinMax(11800, 11905);
	LSpBottomAxis->SetTextColor(RGB(255, 255, 255));
	LSpBottomAxis->SetAxisColor(RGB(255, 255, 255));
	LSpBottomAxis->GetLabel()->SetText(_T("Frequency")); //右轴label
	LSpBottomAxis->GetLabel()->SetColor(RGB(255, 255, 255));

	/*****************************LM完整拟合窗口初始化***********************************/
	m_ChartLmOverall.SetBackColor(RGB(0, 0, 0));
	m_ChartLmOverall.RefreshCtrl();

	TChartString LOTitle = _T("LM完整拟合");    //图表标题
	CChartTitle* LOpTitle = m_ChartLmOverall.GetTitle();
	LOpTitle->AddString(LOTitle);
	LOpTitle->SetColor(RGB(255, 255, 255));

	CChartAxis* LOpLeftAxis = m_ChartLmOverall.CreateStandardAxis(CChartCtrl::LeftAxis);
	LOpLeftAxis->SetMinMax(11750, 11950);
	LOpLeftAxis->SetTextColor(RGB(255, 255, 255));
	LOpLeftAxis->SetAxisColor(RGB(255, 255, 255));
	LOpLeftAxis->GetLabel()->SetText(_T("Frequency"));  //左轴label
	LOpLeftAxis->GetLabel()->SetColor(RGB(255, 255, 255));

	CChartAxis* LOpBottomAxis = m_ChartLmOverall.CreateStandardAxis(CChartCtrl::BottomAxis);
	LOpBottomAxis->SetMinMax(0,2000);
	LOpBottomAxis->SetTextColor(RGB(255, 255, 255));
	LOpBottomAxis->SetAxisColor(RGB(255, 255, 255));
	LOpBottomAxis->GetLabel()->SetText(_T("distance")); //右轴label
	LOpBottomAxis->GetLabel()->SetColor(RGB(255, 255, 255));

	/*****************************功率曲线绘制窗口初始化***********************************/
	m_ChartPower.SetBackColor(RGB(0, 0, 0));
	m_ChartPower.RefreshCtrl();

	TChartString PTitle = _T("功率曲线");    //图表标题
	CChartTitle* PpTitle = m_ChartPower.GetTitle();
	PpTitle->AddString(PTitle);
	PpTitle->SetColor(RGB(255, 255, 255));

	CChartAxis* PpLeftAxis = m_ChartPower.CreateStandardAxis(CChartCtrl::LeftAxis);
	PpLeftAxis->SetMinMax(3750, 3950);
	PpLeftAxis->SetTextColor(RGB(255, 255, 255));
	PpLeftAxis->SetAxisColor(RGB(255, 255, 255));
	PpLeftAxis->GetLabel()->SetText(_T("Power"));  //左轴label
	PpLeftAxis->GetLabel()->SetColor(RGB(255, 255, 255));

	CChartAxis* PpBottomAxis = m_ChartPower.CreateStandardAxis(CChartCtrl::BottomAxis);
	PpBottomAxis->SetMinMax(0, 2000);
	PpBottomAxis->SetTextColor(RGB(255, 255, 255));
	PpBottomAxis->SetAxisColor(RGB(255, 255, 255));
	PpBottomAxis->GetLabel()->SetText(_T("distance")); //右轴label
	PpBottomAxis->GetLabel()->SetColor(RGB(255, 255, 255));

	/*********界面刷新**********/
	m_ChartLmSingle.EnableRefresh(true);
	m_ChartLmOverall.EnableRefresh(true);
	m_ChartPower.EnableRefresh(true);
}

void CBOTDRDlg::Data_Init()
{
	int dain = 0;
	AdAvThread = new thread[FIR_CL];
	ThreadResult = new double* [FIR_CL];
	ThreadFileIfs = new ifstream* [FIR_CL];
	while (dain< FIR_CL)
	{
		ThreadResult[dain] = new double[underline];
		ThreadFileIfs[dain] = new ifstream[underline];
		dain++;
	}
	dain = 0;
	ThreadStrData = new string[FIR_CL];
	ThreadUselessData = new string[FIR_CL];
	ThreadFileNumber = new int[FIR_CL];
}

void CBOTDRDlg::Data_Delete()
{
	int dade = 0;
	delete[] AdAvThread;
	while (dade < FIR_CL)
	{
		delete[] ThreadResult[dade];
		delete[] ThreadFileIfs[dade];
		dade++;
	}
	delete[] ThreadResult;
	delete[] ThreadFileIfs;
	delete[] ThreadStrData;
	delete[] ThreadUselessData;
	delete[] ThreadFileNumber;
}

void CBOTDRDlg::Chart_Draw(CChartCtrl pChart, double* x, double* y, TChartString pTitle, int pPointNumber)
{
	TChartString msTitle = pTitle;    //图表标题
	CChartTitle* mpTitle = m_ChartLmSingle.GetTitle();
	mpTitle->AddString(msTitle);
	mpTitle->SetColor(RGB(255, 255, 255));

	CChartLineSerie* pLineSerie1 = nullptr;
	pChart.RemoveAllSeries();
	pLineSerie1 = pChart.CreateLineSerie();
	pLineSerie1->SetSeriesOrdering(poNoOrdering);//设置为无序
	pLineSerie1->AddPoints(x, y, pPointNumber);

	pChart.EnableRefresh(true);
}

void CBOTDRDlg::Thread_Func(int XC)
{
	for (int u = 0;u < (int)(FIR_WJGS / underline);u++)
	{
		for (int b = 0; b < underline; b++)//第2个循环，循环次数为每次需要处理的原始数据文件个数
		{
			ThreadFileNumber[XC] = XC * FIR_WJGS + u * underline + b;//文件名称初始化
			/*确定需要处理的文件并将其导入文件数据流*/
			if ((ThreadFileNumber[XC]) < 10)
				ThreadFileIfs[XC][b].open(m_BeginAddAvgPath + source2 + (to_string(ThreadFileNumber[XC])) + (FileType), ios::in);
			else if (((ThreadFileNumber[XC]) >= 10) && ((ThreadFileNumber[XC]) <= 99))
				ThreadFileIfs[XC][b].open(m_BeginAddAvgPath + source1 + (to_string(ThreadFileNumber[XC])) + (FileType), ios::in);
			else if (((ThreadFileNumber[XC]) > 99) && ((ThreadFileNumber[XC]) <= 999))
				ThreadFileIfs[XC][b].open(m_BeginAddAvgPath + source0 + (to_string(ThreadFileNumber[XC])) + (FileType), ios::in);
			else
				ThreadFileIfs[XC][b].open(m_BeginAddAvgPath + source3 + (to_string(ThreadFileNumber[XC])) + (FileType), ios::in);
		}
		/*跳过前三行无效数据*/
		for (int b = 0; b < underline; b++)
		{
			for (int k = 0;k < 3;k++)
				getline(ThreadFileIfs[XC][b], ThreadUselessData[XC]);
		}
		for (int c = 0; c < DATA_GS; c++)//第3个循环，循环次数为每个文件包含的数据个数，进行累加处理
		{
			for (int d = 0; d < underline; d++)
			{
				getline(ThreadFileIfs[XC][d], ThreadStrData[XC]);

				//ThreadStrData[XC].erase(0, ThreadStrData[XC].find(",",0)+1);

				ThreadResult[XC][c] += stod(ThreadStrData[XC]);//累加计算
			}
		}
		for (int d = 0; d < underline; d++)
			ThreadFileIfs[XC][d].close();
	}
}

void CBOTDRDlg::Add_Average(int add)
{
	
	Frenum = 500 + add * 5;//计算当前频率点
	StrFrequency = to_string(Frenum);//将频率点转化为字符串

	SetBeginAddAvgPath(("\\11") + StrFrequency + ("\\C411") + StrFrequency);
	SetEndAddAvgPath("\\result\\11");
	//打开文件写入数据
	ofstream outFile;
	outFile.open(m_EndAddAvgPath + StrFrequency + FileType, ios::out);

	/*设置8个线程，将第一次累加处理函数作为线程入口*/
	for (int xcs = 0;xcs < FIR_CL;xcs++)
	{
		AdAvThread[xcs] = thread(&CBOTDRDlg::Thread_Func,this,xcs);
	}
	for (int xcs = 0;xcs < FIR_CL;xcs++)
	{
		AdAvThread[xcs].join();
	}

	for (int j = 0; j < DATA_GS; j++)//循环次数为每个文件包含的数据个数，进行累加处理
	{
		for (int k = 0; k < FIR_CL; k++)
		{
			AddAverageResult += ThreadResult[k][j];
			ThreadResult[k][j] = 0;
		}
		AddAverageResult /= DATA_WJZS;
		outFile << AddAverageResult << endl;
		AddAverageResult = 0;
	}
	outFile.close();//关闭文件
}

BOOL CBOTDRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码
	System_Init();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBOTDRDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBOTDRDlg::OnPaint()
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
HCURSOR CBOTDRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBOTDRDlg::OnBnClickedButtonFileChioce()
{
	// TODO: 在此添加控件通知处理程序代码
	char FilePath[1000];     //存放选择的目录路径 
	CString Getpath;
	string BgPath;
	ZeroMemory(FilePath, sizeof(FilePath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = (LPWSTR)FilePath;
	bi.lpszTitle = _T("请选择处理结果存储路径");
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if (lp && SHGetPathFromIDList(lp, (LPWSTR)FilePath))
	{
		Getpath.Format(_T("%s"), (LPWSTR)FilePath);
		SetDlgItemText(IDC_EDIT_FILE_PATH, Getpath);
		BgPath = CT2A(Getpath.GetBuffer());
		SetBasicPath(BgPath);
	}
	else
		AfxMessageBox(_T("无效的目录，请重新选择"));
	// TODO: 在此添加控件通知处理程序代码
}


void CBOTDRDlg::OnBnClickedButtonPowerDraw()
{
	//Chart_Draw();
	// TODO: 在此添加控件通知处理程序代码
}


void CBOTDRDlg::OnBnClickedButtonSetup()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CBOTDRDlg::OnBnClickedButtonAddAverage()
{
	string SJ;
	for (int add = 0; add < 22; add++)
	{
		Add_Average(add);
	}
	// TODO: 在此添加控件通知处理程序代码
}

void CBOTDRDlg::OnBnClickedButtonLmOverall()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CBOTDRDlg::OnBnClickedButtonLmSingle()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CBOTDRDlg::OnSysExit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox(_T("确实要退出程序吗？"), _T("提示！"), MB_OKCANCEL | MB_ICONWARNING) == IDNO)
		return;
	CDialogEx::OnCancel();
}


void CBOTDRDlg::OnDestroy()
{
	Data_Delete();
	CDialogEx::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
}




