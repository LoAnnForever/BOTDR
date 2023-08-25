
// BOTDRDlg.cpp: 实现文件
//


#include "pch.h"
#include "framework.h"
#include "BOTDR.h"
#include "BOTDRDlg.h"
#include "afxdialogex.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSemaphore fitingprocess_Sp(1, 1);

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
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);//IDI_ICON1//IDR_MAINFRAME
}

void CBOTDRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART_LM_SINGLE, m_ChartLmSingle);
	DDX_Control(pDX, IDC_CHART_LM_OVERALL, m_ChartLmOverall);
	DDX_Control(pDX, IDC_CHART_POWER, m_ChartPower);
	DDX_Control(pDX, IDC_CHART_WENDU_VALUE, m_ChartWenduChaValue);
	DDX_Control(pDX, IDC_LM_PROGRESS, m_LmProCtrl);
	DDX_Control(pDX, IDC_MYSQL_PROGRESS, m_MysqlProCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_combox);
	DDX_Control(pDX, IDC_COMBO2, m_powerbox);
}

BEGIN_MESSAGE_MAP(CBOTDRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FILE_CHIOCE, &CBOTDRDlg::OnBnClickedButtonFileChioce)
	ON_BN_CLICKED(IDC_BUTTON_POWER_DRAW, &CBOTDRDlg::OnBnClickedButtonPowerDraw)
	ON_BN_CLICKED(IDC_BUTTON_SETUP, &CBOTDRDlg::OnBnClickedButtonSetup)
	ON_BN_CLICKED(IDC_BUTTON_LM_OVERALL, &CBOTDRDlg::OnBnClickedButtonLookLmResult)
	ON_BN_CLICKED(IDC_BUTTON_LM_SINGLE, &CBOTDRDlg::OnBnClickedButtonLmSingle)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, &CBOTDRDlg::OnSysExit)
	ON_BN_CLICKED(IDC_BUTTON_SAMPLE, &CBOTDRDlg::OnBnClickedButtonSample)
	ON_BN_CLICKED(IDC_BUTTON_OPENCARD, &CBOTDRDlg::OnBnClickedButtonOpencard)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECARD, &CBOTDRDlg::OnBnClickedButtonClosecard)
	ON_BN_CLICKED(IDC_BUTTON_WEIBO, &CBOTDRDlg::OnBnClickedButtonWeibo)
	ON_BN_CLICKED(IDC_BUTTON_BEGIN_SINGLE_MEASURE, &CBOTDRDlg::OnBnClickedButtonBeginSingleMeasure)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_MEASURE, &CBOTDRDlg::OnBnClickedButtonCloseMeasure)
	ON_BN_CLICKED(IDC_BUTTON_MYSQL_CONNECT, &CBOTDRDlg::OnBnClickedButtonMysqlConnect)
	ON_BN_CLICKED(IDC_BUTTON_MYSQL_DATA_INSERT, &CBOTDRDlg::OnBnClickedButtonMysqlDataInsert)
	ON_BN_CLICKED(IDC_BUTTON_MYSQL_CLOSE, &CBOTDRDlg::OnBnClickedButtonMysqlClose)
	ON_BN_CLICKED(IDC_BUTTON_BEGIN_AUTO_MEASURE, &CBOTDRDlg::OnBnClickedButtonBeginAutoMeasure)
	ON_BN_CLICKED(IDC_BUTTON_BEGIN_DATA_BIAODING, &CBOTDRDlg::OnBnClickedButtonBeginDataBiaoding)
END_MESSAGE_MAP()


// CBOTDRDlg 消息处理程序
/******************************==================自定义函数========================**************************************/

/*************************系统初始化*********************************/
void CBOTDRDlg::System_Init()
{
	int powerpoint = -1;
	CString str;
	Data_Init();
	Chart_Init();
	if (!PathIsDirectory(_T("E:\\BOTDRBINDATA"))) //如果文件夹不存在
	{
		_mkdir("E:\\BOTDRBINDATA"); //如果文件夹不存在创建
	}
	m_LmProCtrl.SetRange(0, 100);
	m_MysqlProCtrl.SetRange(0, 100);
	m_combox.ResetContent();
	m_combox.AddString(_T("COM1"));
	m_combox.AddString(_T("COM2"));
	m_combox.AddString(_T("COM3"));
	m_combox.AddString(_T("COM4"));
	m_combox.AddString(_T("COM5"));
	m_combox.AddString(_T("COM6"));
	m_combox.AddString(_T("COM7"));
	m_combox.AddString(_T("COM8"));
	m_combox.AddString(_T("COM9"));
	m_combox.SetCurSel(3);
	m_powerbox.ResetContent();
	for (int i = 1;i <= LmAmount;i++)
	{
		str.Format(_T("%d"), i);
		m_powerbox.AddString(str);
	}
	m_powerbox.SetCurSel(0);
	GetDlgItem(IDC_BUTTON_LM_SINGLE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_POWER_DRAW)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_CLOSE_MEASURE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SAMPLE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_CLOSECARD)->EnableWindow(false);
	//获取保存文件选择框的指针
	CButton* Cwnd_check_banana = (CButton*)GetDlgItem(IDC_CHECK_SAVEFILE);
	CString COM;
	GetDlgItemText(IDC_COMBO1, COM);
	COM = _T("//./") + COM;
	WeiboInit(COM);
	OpenOrCloseWeiBo(0);//关闭微波源输出
	m_weibo_serial.Close();
	//设置默认保存文件
	if (Cwnd_check_banana) Cwnd_check_banana->SetCheck(TRUE);//TRUE为选中，FALSE为未选中
	string StrSetup;
	string LookStr;

	string StrData;
	string LookData;
	istringstream LookStream, SetupStream;
	ifstream LookFile;
	int fblenth, fiamount, lmamount, maichongwd;
	LookFile.open(".\\" + to_string(FiberLength) + "km-标定文件" + to_string(FileAmount) + "-" + to_string(LmAmount) + ".csv");
	if (!LookFile)
	{
		Messageveiw(m_Message, _T("未找到标定文件！"));
		LookFile.close();
		Sandard_flag = 0;
		return;
	}
	getline(LookFile, StrSetup);
	SetupStream.clear();
	SetupStream.str(StrSetup);
	getline(SetupStream, StrData, ',');
	fblenth = atoi(StrData.c_str());
	getline(SetupStream, StrData, ',');
	fiamount = atoi(StrData.c_str());
	getline(SetupStream, StrData, ',');
	lmamount = atoi(StrData.c_str());
	getline(SetupStream, StrData, ',');
	maichongwd = atoi(StrData.c_str());
	if (FiberLength == fblenth && FileAmount == fiamount && LmAmount == lmamount && GetDlgItemInt(IDC_EDIT_MAICHONG_WIDTH) == maichongwd)
	{
		getline(LookFile, LookStr);
		LookStream.clear();
		LookStream.str(LookStr);
		for (int a = 0; a < DataAllAmount; a++)
		{
			getline(LookStream, LookData, ',');
			StandardData[a] = (double)atof(LookData.c_str());
		}
		Messageveiw(m_Message, _T("标定文件导入成功！"));
		//删除标定文件
		if (MysqlYesNo_flag == 1)
		{
			if (MysqlConnect())
			{
				mysql_query(&mysql, "DELETE FROM RATING_DATA;");
				Messageveiw(m_Message, _T("删除服务器标定数据"));
				Messageveiw(m_Message, _T("正在插入当前标定数据......"));
				MysqlSendData(StandardData);
				MysqlClose();
			}
		}
		Sandard_flag = 1;
		return;
	}
	else
	{
		Sandard_flag = 0;
		return;
	}
}

/*************************曲线绘制窗口初始化*********************************/
void CBOTDRDlg::Chart_Init()
{
	/*****************************LM单点拟合窗口初始化***********************************/
	m_ChartLmSingle.SetBackColor(RGB(215, 215, 215));
	m_ChartLmSingle.RefreshCtrl();

	TChartString LSTitle = _T("LM单点拟合");    //图表标题
	CChartTitle* LSpTitle = m_ChartLmSingle.GetTitle();
	LSpTitle->RemoveAll();
	LSpTitle->AddString(LSTitle);
	LSpTitle->SetColor(RGB(0, 0, 0));

	LSpLeftAxis = m_ChartLmSingle.CreateStandardAxis(CChartCtrl::LeftAxis);
	LSpLeftAxis->SetMinMax(-0.1,1.1);
	LSpLeftAxis->SetTextColor(RGB(0, 0, 0));
	LSpLeftAxis->SetAxisColor(RGB(0, 0, 0));
	LSpLeftAxis->GetLabel()->SetText(_T("Power"));  //左轴label
	LSpLeftAxis->GetLabel()->SetColor(RGB(0, 0, 0));


	LSpBottomAxis = m_ChartLmSingle.CreateStandardAxis(CChartCtrl::BottomAxis);
	LSpBottomAxis->SetMinMax((Begin_Fre - 700) / 1000.00, (End_Fre - 700) / 1000.00);
	LSpBottomAxis->SetTextColor(RGB(0, 0, 0));
	LSpBottomAxis->SetAxisColor(RGB(0, 0, 0));
	LSpBottomAxis->GetLabel()->SetText(_T("Frequency")); //右轴label
	LSpBottomAxis->GetLabel()->SetColor(RGB(0, 0, 0));

	/*****************************LM完整拟合窗口初始化***********************************/
	m_ChartLmOverall.SetBackColor(RGB(215, 215, 215));
	m_ChartLmOverall.RefreshCtrl();

	TChartString LOTitle = _T("LM完整拟合");    //图表标题
	CChartTitle* LOpTitle = m_ChartLmOverall.GetTitle();
	LOpTitle->RemoveAll();
	LOpTitle->AddString(LOTitle);
	LOpTitle->SetColor(RGB(0, 0, 0));

	LOpLeftAxis = m_ChartLmOverall.CreateStandardAxis(CChartCtrl::LeftAxis);
	LOpLeftAxis->SetMinMax((Begin_Fre - 700)/1000.00, (End_Fre - 700)/1000.00);
	LOpLeftAxis->SetTextColor(RGB(0, 0, 0));
	LOpLeftAxis->SetAxisColor(RGB(0, 0, 0));
	LOpLeftAxis->GetLabel()->SetText(_T("Frequency"));  //左轴label
	LOpLeftAxis->GetLabel()->SetColor(RGB(0, 0, 0));

	LOpBottomAxis = m_ChartLmOverall.CreateStandardAxis(CChartCtrl::BottomAxis);
	LOpBottomAxis->SetMinMax(0, GetDlgItemInt(IDC_EDIT_FIBER_LENGTH) * 1000);
	LOpBottomAxis->SetTextColor(RGB(0, 0, 0));
	LOpBottomAxis->SetAxisColor(RGB(0, 0, 0));
	LOpBottomAxis->GetLabel()->SetText(_T("Distance")); //右轴label
	LOpBottomAxis->GetLabel()->SetColor(RGB(0, 0, 0));

	/*****************************功率曲线绘制窗口初始化***********************************/
	m_ChartPower.SetBackColor(RGB(215, 215, 215));
	m_ChartPower.RefreshCtrl();

	TChartString PTitle = _T("功率曲线");    //图表标题
	CChartTitle* PpTitle = m_ChartPower.GetTitle();
	PpTitle->RemoveAll();
	PpTitle->AddString(PTitle);
	PpTitle->SetColor(RGB(0, 0, 0));

	PpLeftAxis = m_ChartPower.CreateStandardAxis(CChartCtrl::LeftAxis);
	PpLeftAxis->SetMinMax(-2, 2);
	PpLeftAxis->SetTextColor(RGB(0, 0, 0));
	PpLeftAxis->SetAxisColor(RGB(0, 0, 0));
	PpLeftAxis->GetLabel()->SetText(_T("Power"));  //左轴label
	PpLeftAxis->GetLabel()->SetColor(RGB(0, 0, 0));

	PpBottomAxis = m_ChartPower.CreateStandardAxis(CChartCtrl::BottomAxis);
	PpBottomAxis->SetMinMax(0, GetDlgItemInt(IDC_EDIT_FIBER_LENGTH) * 1000);
	PpBottomAxis->SetTextColor(RGB(0, 0, 0));
	PpBottomAxis->SetAxisColor(RGB(0, 0, 0));
	PpBottomAxis->GetLabel()->SetText(_T("Distance")); //右轴label
	PpBottomAxis->GetLabel()->SetColor(RGB(0, 0, 0));

	/*****************************温度差值窗口初始化***********************************/
	m_ChartWenduChaValue.SetBackColor(RGB(215, 215, 215));
	m_ChartWenduChaValue.RefreshCtrl();

	TChartString WTitle = _T("温差/应变曲线");    //图表标题
	CChartTitle* WvTitle = m_ChartWenduChaValue.GetTitle();
	WvTitle->RemoveAll();
	WvTitle->AddString(WTitle);
	WvTitle->SetColor(RGB(0, 0, 0));

	WvLeftAxis = m_ChartWenduChaValue.CreateStandardAxis(CChartCtrl::LeftAxis);
	WvLeftAxis->SetMinMax(-50, 50);
	WvLeftAxis->SetTextColor(RGB(0, 0, 0));
	WvLeftAxis->SetAxisColor(RGB(0, 0, 0));
	WvLeftAxis->GetLabel()->SetText(_T("温度/应变°C"));  //左轴label
	WvLeftAxis->GetLabel()->SetColor(RGB(0, 0, 0));

	WvBottomAxis = m_ChartWenduChaValue.CreateStandardAxis(CChartCtrl::BottomAxis);
	WvBottomAxis->SetMinMax(0, GetDlgItemInt(IDC_EDIT_FIBER_LENGTH) * 1000);
	WvBottomAxis->SetTextColor(RGB(0, 0, 0));
	WvBottomAxis->SetAxisColor(RGB(0, 0, 0));
	WvBottomAxis->GetLabel()->SetText(_T("Distance")); //右轴label
	WvBottomAxis->GetLabel()->SetColor(RGB(0, 0, 0));

	/*********界面刷新**********/
	m_ChartLmSingle.EnableRefresh(true);
	m_ChartLmOverall.EnableRefresh(true);
	m_ChartPower.EnableRefresh(true);
	m_ChartWenduChaValue.EnableRefresh(true);
}

/***************************************************************/
/*函数名称：CalculateQ(double a1, double a2, double *X, double *Y, int PointsNum)
/*输入参数：a1,a2略；*X，*Y为待拟合点的X和Y坐标；PointsNum为参与拟合的点数
/*返回值：Q值
/***************************************************************/
double CBOTDRDlg::CalculateQ(double a1, double a2, double* X, double* Y, int PointsNum)
{
	double Q = 0, q = 0;
	for (int i = 0; i < PointsNum; i++)
	{
		q = pow(a2, 2) / (pow(a2, 2) + 4 * pow(X[i] - a1, 2)) - Y[i];//根据具体需要拟合的函数书写公式
		Q += pow(q, 2);//平方和
	}
	return Q;
}
/***************************************************************/
/*函数名称：Calculate_hij
/*输入参数：*h用于存放h1和h2的数组首地址；a1,a2略；*X，*Y为待拟合点的X和Y坐标；PointsNum为参与拟合的点数
/*函数作用：根据给定的a1、a2、X[i]、Y[i]值，计算h1和h2，并存放到*h所指数组中。
/*返回值：无
/***************************************************************/
void CBOTDRDlg::Calculate_hij(double* h, double a1, double a2, double* X, double* Y, double d, int PointsNum)
{
	double b11 = 0, b12 = 0, b22 = 0, y1 = 0, y2 = 0, d_a1 = 0, d_a2 = 0;
	for (int i = 0; i < PointsNum; i++)
	{
		d_a1 = 8 * pow(a2, 2) * (X[i] - a1) / pow((pow(a2, 2) + 4 * pow(X[i] - a1, 2)), 2);//此处为dy/da1的公式
		d_a2 = 8 * a2 * pow(X[i] - a1, 2) / pow((pow(a2, 2) + 4 * pow(X[i] - a1, 2)), 2);//此处为dy/da2的公式
		b11 += pow(d_a1, 2);
		b12 += d_a1 * d_a2;
		b22 += d_a2 * d_a2;
		y1 += d_a1 * (Y[i] - pow(a2, 2) / (pow(a2, 2) + 4 * pow(X[i] - a1, 2)));
		y2 += d_a2 * (Y[i] - pow(a2, 2) / (pow(a2, 2) + 4 * pow(X[i] - a1, 2)));
	}
	double h1 = 0, h2 = 0, div = 0;//以下为解方程
	div = (b11 + d) * (b22 + d) - b12 * b22;
	h1 = ((b22 + d) * y1 - b12 * y2) / div;
	h2 = ((b11 + d) * y2 - b22 * y1) / div;
	//将计算出的h1，和h2放到数组中
	h[0] = h1;
	h[1] = h2;
}
/***************************************************************/
/*函数名称：LM_Core（）
/*输入参数：*a1,*a2为给定的初值的指针；*X，*Y为待拟合点的X和Y坐标；PointsNum为参与拟合的点数
/*函数作用：根据给定的a1初值、a2初值、X[i]、Y[i]，d初值值，完成拟合，求出待拟合参数a1，和a2
/*返回值：循环次数。如果返回的循环次数大于或者等于200，说明拟合失败
/***************************************************************/
int CBOTDRDlg::LM_Core(double* a1, double* a2, double* X, double* Y, double d, int PointsNum)//此处a1和a2必须用指针传递
{
	double Q0 = 0, Q0_New = 0;
	double a1_New = 0, a2_New = 0;
	double h[2] = { 0, 0 };
	int i = 0;
	do
	{
		i++;//循环次数指示器
		int j = 0;//
		while (true)
		{
			j++;
			Q0 = CalculateQ(*a1, *a2, X, Y, PointsNum);//首先计算出Q0；
			Calculate_hij(h, *a1, *a2, X, Y, d, PointsNum);//然后计算出h1,h2赋给数组h,h[0]为h1,h[1]为h2
			a1_New = *a1 + h[0];//暂时更新a1和a2的值
			a2_New = *a2 + h[1];
			Q0_New = CalculateQ(a1_New, a2_New, X, Y, PointsNum);//重新计算Q0；
			if (Q0_New < Q0)//如果残差缩小，说明d取值合适，正式更新a1和a2，退出此迭代
			{
				*a1 = a1_New;
				*a2 = a2_New;
				break;
			}
			else if (j > 5)
			{
				break;//如果d太大还没满足要求，则退出while循环。如果没有这个条件限制，则可能进入死循环
			}
			else//如果残差增大，扩大10倍d重新计算
				d = 100 * d;
		}
	} while (((abs(h[0]) > abs(h[1])) ? abs(h[0]) : abs(h[1])) > FitError && i < LoopNumForFit);//当h1和h2的绝对值中的最大值小于定义的误差时停止拟合，注意此处逻辑,千万别把>号写反。
	return i;
}

bool CBOTDRDlg::SaoPinSample()
{
	StartTime = clock();
	CString StrFre, COM;
	//int Ret = -1;
	int f = 0;
	long datalen = 0;
	for (int num = 0; num < LmAmount; num++)
	{
		GetDlgItemText(IDC_COMBO1, COM);
		COM = _T("//./") + COM;
		WeiboInit(COM);
		SetWeiboData(Begin_Fre + num * SaoPinJianGe);
		m_weibo_serial.Close();
		long t1 = GetTickCount();//程序段结束后取得系统运行时间(ms)
		Sample(&(stCardInfo[0]), 0, num, datalen);
		long t2 = GetTickCount();//程序段结束后取得系统运行时间(ms)
		m_LmProCtrl.SetPos((int)(((double)(num + 1) / (double)LmAmount) * 100));
		strprogress.Format(_T("%d%%"), (int)(((double)(num + 1) / (double)LmAmount) * 100));
		SetDlgItemText(IDC_STATIC_PROFRESS, strprogress);
		StrFre.Format(_T("当前频率点:%dMHz\r\n单次扫频时间:%0.3fs"), Begin_Fre + num * SaoPinJianGe - 700, (t2 - t1) / 1000.000);
		Messageveiw(m_Message, StrFre);
		//if (Auto_Sample_flag == 1)
		//{
		//	DrawWaveS(num);
		//}
		//UpdateWindow();
		if (Sample_flag == 1)
		{
			return false;
		}
	}
	m_LmProCtrl.SetPos(100);
	strprogress.Format(_T("%d%%"), 100);
	SetDlgItemText(IDC_STATIC_PROFRESS, strprogress);
	FinishTime = clock();//程序结束时间
	TotalTime = (double)(FinishTime - StartTime) / CLOCKS_PER_SEC;//计算程序运行时间
	m_Message += ("扫频采集完成\r\n耗时：" + to_string(TotalTime) + "秒\r\n").c_str();
	//实时显示在信息窗口上
	SetDlgItemText(IDC_EDIT_MESSAGE_VIEW, m_Message);
	return true;
}

void CBOTDRDlg::LmOverall()
{
	int prcess = 0, model = 0, time = 0;
	double a1, a2;
	double* X = new double[LmAmount];
	double* Y = new double[LmAmount];
	double Fre_init = (Begin_Fre - 700) / 1000.000;
	for (int a = 0;a < LmAmount;a++)
	{
		X[a] = Fre_init + a * 0.005;
	}
	for (int b = 0;b < DataAllAmount;b++)
	{  
		a1 = CenterFre, a2 = ThreedBWidth;
		for (int c = 0;c < LmAmount;c++)
		{
			Y[c] = GyhResult[c][b + 1];
		}
		time = LM_Core(&a1, &a2, X, Y, 0.001, LmAmount);
		if (time < 15)
		{
			LmResultCenterFre[b] = a1;
			LmResultThreeWidth[b] = a2;
		}
		else
		{
			LmResultCenterFre[b] = 10.700;
			LmResultThreeWidth[b] = a2;
		}
		prcess = (int)(((float)b / (float)DataAllAmount) * 100);
		if (model != prcess)
		{
			model = prcess;
			m_LmProCtrl.SetPos(model);
			strprogress.Format(_T("%d%%\t\n"), model);
			SetDlgItemText(IDC_STATIC_PROFRESS, strprogress);
		}
	}
//	ChartLine_Draw(true, m_ChartLmOverall, 0, FiberLength * 1000, (double)(Begin_Fre - 700) / 1000.000, (double)(End_Fre - 700) / 1000.000, LineDistance, LmResultCenterFre, DataAllAmount, RGB(255, 0, 0));
	m_ChartLmOverall.EnableRefresh(false);
	LOpLeftAxis->SetMinMax((Begin_Fre - 700) / 1000.000, (End_Fre - 700) / 1000.000);
	m_ChartLmOverall.RemoveAllSeries();
	pLineSerie = m_ChartLmOverall.CreateLineSerie();
	pLineSerie->SetSeriesOrdering(poNoOrdering);//设置为无序
	pLineSerie->AddPoints(LineDistance, LmResultCenterFre, DataAllAmount);
	//pLineSerie->SetColor(RGB(255, 0, 0));
	m_ChartLmOverall.EnableRefresh(true);
	m_LmProCtrl.SetPos(100);
	strprogress.Format(_T("%d%%"), 100);
	SetDlgItemText(IDC_STATIC_PROFRESS, strprogress);
	delete[]X;
	delete[]Y;
}

void CBOTDRDlg::RoutineLm()
{
	StartTime = clock();
	LmOverall();
	FinishTime = clock();//程序结束时间
	TotalTime = (double)(FinishTime - StartTime) / CLOCKS_PER_SEC;//计算程序运行时间
	m_Message += ("LM处理完成\r\n耗时：" + to_string(TotalTime) + "秒\r\n").c_str();
	//实时显示在信息窗口上
	SetDlgItemText(IDC_EDIT_MESSAGE_VIEW, m_Message);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_MESSAGE_VIEW);
	int nline = pedit->GetLineCount();
	pedit->LineScroll(nline - 1);
	//判断是否需要保存文件
	CButton* pbt = (CButton*)GetDlgItem(IDC_CHECK_SAVEFILE);
	int idsavefile = pbt->GetCheck();
	if (idsavefile == BST_CHECKED)
	{
		Messageveiw(m_Message, _T("正在保存实时数据......"));
		ofstream LMResultFile;
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		LMResultFile.open(m_EndGyhPath + to_string(sys.wYear) +
			"-" + to_string(sys.wMonth) +
			"-" + to_string(sys.wDay) +
			"_" + to_string(sys.wHour) +
			"-" + to_string(sys.wMinute) +
			"-" + to_string(sys.wSecond) + "_" + to_string(FiberLength) + "km-" + to_string(FileAmount) + "-" + to_string(LmAmount) + ".csv", ios::out);
		for (int n = 0; n < DataAllAmount; n++)
			LMResultFile << LineDistance[n] << ",";
		LMResultFile << endl;
		for (int i = 0; i < DataAllAmount; i++)
		{
			LMResultFile << LmResultCenterFre[i] << ",";
		}
		LMResultFile << endl;
		for (int j = 0; j < DataAllAmount; j++)
		{
			LMResultFile << LmResultThreeWidth[j] << ",";
		}
		LMResultFile << endl;
		LMResultFile.close();
		Messageveiw(m_Message, _T("保存完成"));
	}
	/*if (MysqlConnect_flag == 1)
	{
		mysql_query(&mysql, "DELETE FROM REALTING_DATA;");
		Messageveiw(m_Message, _T("删除服务器中的上一组数据"));
		Messageveiw(m_Message, _T("正在插入实时数据......"));
		MysqlSendData(LmResultCenterFre);
	}*/
}

//保存标定文件
void CBOTDRDlg::SandardLm()
{
	StartTime = clock();
	ofstream LMResultFile;
	LMResultFile.open(".\\" + to_string(FiberLength) + "km-标定文件" + to_string(FileAmount) + "-" + to_string(LmAmount) + ".csv", ios::out);
	LmOverall();
	LMResultFile << FiberLength << ",";
	LMResultFile << FileAmount << ",";
	LMResultFile << LmAmount << ",";
	LMResultFile << GetDlgItemInt(IDC_EDIT_MAICHONG_WIDTH) << ",";
	LMResultFile << endl;
	for (int i = 0; i < DataAllAmount; i++)
	{
		StandardData[i] = LmResultCenterFre[i];
		LMResultFile << LmResultCenterFre[i] << ",";
	}
	LMResultFile << endl;
	LMResultFile.close();
	FinishTime = clock();//程序结束时间
	TotalTime = (double)(FinishTime - StartTime) / CLOCKS_PER_SEC;//计算程序运行时间
	m_Message += ("已保存标定文件......\r\nLM处理完成\r\n耗时：" + to_string(TotalTime) + "秒\r\n").c_str();
	//实时显示在信息窗口上
	SetDlgItemText(IDC_EDIT_MESSAGE_VIEW, m_Message);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_MESSAGE_VIEW);
	int nline = pedit->GetLineCount();
	pedit->LineScroll(nline - 1);
	if (MysqlConnect_flag == 1)
	{
		mysql_query(&mysql, "DELETE FROM RATING_DATA;");
		Messageveiw(m_Message, _T("删除服务器标定数据"));
		Messageveiw(m_Message, _T("正在插入当前标定数据......"));
		MysqlSendData(StandardData);
		MysqlClose();
		MysqlConnect_flag = 0;
	}
}

bool CBOTDRDlg::MysqlConnect()
{
	GetDlgItemText(IDC_EDIT_MYSQL_ADDRESS, m_Sql_address);
	GetDlgItemText(IDC_EDIT_MYSQL_USER, m_Sql_user);
	GetDlgItemText(IDC_EDIT_MYSQL_PASSWORD, m_Sql_password);
	m_Sql_databases = _T("botdr");
	m_Sql_server_number = GetDlgItemInt(IDC_EDIT_MYSQL_NUMBER);
	if (Sql_Init(m_Sql_address, m_Sql_user, m_Sql_password, m_Sql_databases, m_Sql_server_number))
	{
		//创建数据表***************************************************************************************
		char sql_create[200];
		sprintf_s(sql_create, "CREATE TABLE IF NOT EXISTS RATING_DATA(id BIGint PRIMARY KEY NOT NULL,space double NOT NULL,centerfre double NOT NULL,creat_time datetime NOT NULL);");
		int result = mysql_query(&mysql, sql_create);
		if (result == 0)
		{
			Messageveiw(m_Message, _T("初始化标定数据表完成"));
		}
		else
		{
			Messageveiw(m_Message, _T("初始化标定数据表失败"));
		}
		sprintf_s(sql_create, "CREATE TABLE IF NOT EXISTS ICE_DATA(id BIGint PRIMARY KEY AUTO_INCREMENT,space double NOT NULL,ice_thickness double NOT NULL,creat_time datetime NOT NULL);");
		result = mysql_query(&mysql, sql_create);
		if (result == 0)
		{
			Messageveiw(m_Message, _T("初始化覆冰数据表完成"));
		}
		else
		{
			Messageveiw(m_Message, _T("初始化覆冰数据表失败"));
		}
		sprintf_s(sql_create, "CREATE TABLE IF NOT EXISTS HISTORICAL_DATA(id BIGint PRIMARY KEY AUTO_INCREMENT,space double NOT NULL,temperature double NOT NULL,creat_time datetime NOT NULL);");
		result = mysql_query(&mysql, sql_create);
		if (result == 0)
		{
			Messageveiw(m_Message, _T("初始化历史数据表完成"));
		}
		else
		{
			Messageveiw(m_Message, _T("初始化历史数据表失败"));
		}
		sprintf_s(sql_create, "CREATE TABLE IF NOT EXISTS TEMPERATURE_DATA(id BIGint PRIMARY KEY NOT NULL,space double NOT NULL,temperature double NOT NULL,creat_time datetime NOT NULL);");
		result = mysql_query(&mysql, sql_create);
		if (result == 0)
		{
			Messageveiw(m_Message, _T("初始化温度数据表完成"));
		}
		else
		{
			Messageveiw(m_Message, _T("初始化温度数据表失败"));
		}
		return true;
	}
	else
	{
		return false;
	}

}

void CBOTDRDlg::MysqlSendData(double *senddata)
{
	MaiKuanDataAmount = (int)((GetDlgItemInt(IDC_EDIT_MAICHONG_WIDTH) / 10) * 2.5);
	Temperture = new double[MysqlDataAllAmount]();
	//手动输入光纤对应温度
	CString strtemp;
	GetDlgItemText(IDC_EDIT_TEMPERATURE, strtemp);
	double temp = (double)_wtof(strtemp);
	for (int a = 0; a < MysqlDataAllAmount; a++)
	{
		Temperture[a] = temp;
	}

	int julixinxi = GetDlgItemInt(IDC_EDIT_MAICHONG_WIDTH) / 10;
	//导入数据****************************************************************************************************************
	for (int a = 0; a < MysqlDataAllAmount; a++)
	{
		MysqlLineDistance[a] = (a + 1) * julixinxi;
		for (int b = 0; b < MaiKuanDataAmount; b++)
		{
			//MysqlLmResult[a] = MysqlLmResult[a] + LmResultCenterFre[a * MaiKuanDataAmount + b];//横向累加平均
			MysqlLmResult[a] = MysqlLmResult[a] + senddata[a * MaiKuanDataAmount + b];//横向累加平均

		}
		MysqlLmResult[a] = MysqlLmResult[a] / MaiKuanDataAmount;
	}
	char sql_insert[200];
	long t1 = GetTickCount();//程序段结束后取得系统运行时间(ms)
	//获取系统当前时间,插入数据
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	if (senddata == StandardData)
	{
		for (int i = 0; i < MysqlDataAllAmount; i++)
		{
			sprintf_s(sql_insert, "insert into RATING_DATA(id,space,centerfre,creat_time) value('%d','%.3lf','%.3lf','%d-%d-%d %d:%d:%d');",i+1, MysqlLineDistance[i], MysqlLmResult[i], sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			mysql_query(&mysql, sql_insert);
			//sprintf_s(sql_insert, "insert into HISTORICAL_DATA(space,temperature,creat_time) value('%.3lf','%.3lf','%d-%d-%d %d:%d:%d');", MysqlLineDistance[i], Temperture[i], sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			//mysql_query(&mysql, sql_insert);
			int mysqlprogrss = (int)(((float)(i + 1) / (float)MysqlDataAllAmount) * 100);
			m_MysqlProCtrl.SetPos(mysqlprogrss);
			strmysqlprogress.Format(_T("%d%%"), mysqlprogrss);
			SetDlgItemText(IDC_STATIC_MYSQL_PROGRESS, strmysqlprogress);
		}
		//ChartLine_Draw(true, m_ChartLmOverall, 0, FiberLength * 1000, (double)(Begin_Fre - 700) / 1000.000, (double)(End_Fre - 700) / 1000.000, MysqlLineDistance, MysqlLmResult, MysqlDataAllAmount, RGB(255, 0, 0));
		long t2 = GetTickCount();//程序段结束后取得系统运行时间(ms)
		//计算打印上传数据的时间
		CString inserttime;
		inserttime.Format(_T("标定数据插入成功，耗时:%ds"), (t2 - t1)/1000);
		Messageveiw(m_Message, inserttime);
	}
	//if (senddata == LmResultCenterFre)
	//{
	//	for (int i = 0; i < MysqlDataAllAmount; i++)
	//	{
	//		sprintf_s(sql_insert, "insert into REALTING_DATA(id,space,centerfre,creat_time) value('%d','%.3lf','%.3lf','%d-%d-%d %d:%d:%d');",i+1, MysqlLineDistance[i], MysqlLmResult[i], sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
	//		//sprintf_s(sql_insert, "insert into LMALL(space,centerfre) value('%.3lf','%.3lf');", MysqlLineDistance[i], MysqlLmResult[i]);
	//		mysql_query(&mysql, sql_insert);
	//		int mysqlprogrss = (int)(((float)(i + 1) / (float)MysqlDataAllAmount) * 100);
	//		m_MysqlProCtrl.SetPos(mysqlprogrss);
	//		strmysqlprogress.Format(_T("%d%%"), mysqlprogrss);
	//		SetDlgItemText(IDC_STATIC_MYSQL_PROGRESS, strmysqlprogress);
	//	}
	//	//ChartLine_Draw(true, m_ChartLmOverall, 0, FiberLength * 1000, (double)(Begin_Fre - 700) / 1000.000, (double)(End_Fre - 700) / 1000.000, MysqlLineDistance, MysqlLmResult, MysqlDataAllAmount, RGB(255, 0, 0));
	//	long t2 = GetTickCount();//程序段结束后取得系统运行时间(ms)
	//	//计算打印上传数据的时间
	//	CString inserttime;
	//	inserttime.Format(_T("实时数据插入成功，耗时:%ds"), (t2 - t1) / 1000);
	//	Messageveiw(m_Message, inserttime);
	//}
	if (senddata == Tempdiff)
	{
		for (int i = 0; i < MysqlDataAllAmount; i++)
		{
			Temperture[i] = Temperture[i] + MysqlLmResult[i];
			sprintf_s(sql_insert, "insert into TEMPERATURE_DATA(id,space,temperature,creat_time) value('%d','%.3lf','%.3lf','%d-%d-%d %d:%d:%d');", i + 1, MysqlLineDistance[i], Temperture[i], sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			mysql_query(&mysql, sql_insert);
			sprintf_s(sql_insert, "insert into HISTORICAL_DATA(space,temperature,creat_time) value('%.3lf','%.3lf','%d-%d-%d %d:%d:%d');", MysqlLineDistance[i], Temperture[i], sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
			mysql_query(&mysql, sql_insert);
			int mysqlprogrss = (int)(((float)(i + 1) / (float)MysqlDataAllAmount) * 100);
			m_MysqlProCtrl.SetPos(mysqlprogrss);
			strmysqlprogress.Format(_T("%d%%"), mysqlprogrss);
			SetDlgItemText(IDC_STATIC_MYSQL_PROGRESS, strmysqlprogress);
		}
		//ChartLine_Draw(true, m_ChartLmOverall, 0, FiberLength * 1000, (double)(Begin_Fre - 700) / 1000.000, (double)(End_Fre - 700) / 1000.000, MysqlLineDistance, MysqlLmResult, MysqlDataAllAmount, RGB(255, 0, 0));
		long t2 = GetTickCount();//程序段结束后取得系统运行时间(ms)
		//计算打印上传数据的时间
		CString inserttime;
		inserttime.Format(_T("温度数据插入成功，耗时:%ds"), (t2 - t1) / 1000);
		Messageveiw(m_Message, inserttime);
	}
	for (int a = 0; a < MysqlDataAllAmount; a++)
	{
		MysqlLmResult[a] = 0;
	}
	delete[] Temperture;
	//下载并打印表中所有的数据************************************************************************************************
	//mysql_query(&mysql, "SELECT * FROM LMALL");
	//MYSQL_RES* res; //查询结果集 
	//res = mysql_store_result(&mysql);
	//MYSQL_ROW row;
	//CString loaddata;
	//USES_CONVERSION;//unicode下char*转CString
	//while (row = mysql_fetch_row(res))
	//{
	//	loaddata.Format(_T("id: %s   space: %s   centerfre: %s"), A2W(row[0]), A2W(row[1]), A2W(row[2]));
	//	Messageveiw(m_Message, loaddata);
	//}
	////释放结果集
	//mysql_free_result(res);
	//res = NULL;

	// TODO: 在此添加控件通知处理程序代码  
}

void CBOTDRDlg::MysqlClose()
{
	//关闭数据库*************************************************************************************************************
	mysql_close(&mysql);
	Messageveiw(m_Message, _T("关闭数据库"));
}

LPCSTR CBOTDRDlg::CString_to_LPCSTR(CString p_cstr)
{
	CStringA strA(p_cstr);
	LPCSTR m_lpcstr = strA;
	return m_lpcstr;
}


bool CBOTDRDlg::Sql_Init(CString p_sql_address, CString p_sql_user, CString p_sql_password, CString p_sql_databases, int p_sql_server_number)
{
	int sql_server_number = p_sql_server_number;//端口号,一般是3306
	//初始化数据库 
	mysql_init(&mysql);
	//设置字符编码
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//连接数据库 
	USES_CONVERSION;//unicode下CString转char*
	if (mysql_real_connect(&mysql, W2A(p_sql_address), W2A(p_sql_user), W2A(p_sql_password), W2A(p_sql_databases), sql_server_number, NULL, 0) == NULL) {
		Messageveiw(m_Message, _T("链接数据库失败"));
		return false;
	}
	Messageveiw(m_Message, _T("链接数据库成功"));
	return true;
}



/*************************系统数组内存分配与初始化*********************************/
void CBOTDRDlg::Data_Init()
{
	int dain = 0;
	LineDistance = new double[DataAllAmount]();
	while (dain< DataAllAmount)
	{
		LineDistance[dain] = dain * 0.4;
		dain++;
	}
	dain = 0;
	//归一化数据内存分配
	GyhResult = new double * [LmAmount]; 
	PowerData = new double * [LmAmount];
	while (dain < LmAmount)
	{
		GyhResult[dain] = new double[DataAllAmount + 1]();
		PowerData[dain] = new double[DataAllAmount]();
		dain++;
	}
	dain = 0;
	LmResultCenterFre = new double[DataAllAmount]();
	LmResultThreeWidth = new double[DataAllAmount]();
	StandardData = new double[DataAllAmount]();
	MysqlDataAllAmount = (int)(FiberLength * 1000 / (GetDlgItemInt(IDC_EDIT_MAICHONG_WIDTH)/10));
	MysqlLineDistance = new double[MysqlDataAllAmount]();
	MysqlLmResult = new double[MysqlDataAllAmount]();
	Tempdiff = new double[DataAllAmount]();
}


/*************************系统数据内存释放*********************************/
void CBOTDRDlg::Data_Delete()
{
	int dade = 0;

	delete[] LineDistance;
	//归一化数据内存释放
	while (dade < LmAmount)
	{
		delete[] GyhResult[dade];
		delete[] PowerData[dade];
		dade++;
	}
	dade = 0;
	delete[] GyhResult;
	delete[] LmResultCenterFre;
	delete[] LmResultThreeWidth;
	delete[] StandardData;
	delete[] MysqlLineDistance;
	delete[] MysqlLmResult;
	delete[] PowerData;
	delete[] Tempdiff;

	/*LineDistance = NULL;
	GyhResult = NULL;
	LmResultCenterFre = NULL;
	MysqlLineDistance = NULL;
	MysqlLmResult = NULL;
	PowerData = NULL;
	StandardData = NULL;
	LmResultThreeWidth = NULL;
	Tempdiff = NULL;*/
}

/*************************绘制曲线*********************************/
void CBOTDRDlg::ChartLine_Draw(bool FLASH, CChartCtrl& pChart, double xMin, double xMax, double yMin, double yMax,
	double* x, double* y, int pPointNumber, COLORREF LineColor)
{
	pChart.EnableRefresh(false);
	
	if (pChart == m_ChartPower)
	{
		PpLeftAxis->SetMinMax(yMin, yMax);
	}
	else if (pChart == m_ChartLmOverall)
	{
		LOpLeftAxis->SetMinMax(yMin, yMax);
	}
	else if (pChart == m_ChartWenduChaValue)
	{
		WvLeftAxis->SetMinMax(yMin, yMax);
	}
	else
	{
		LSpLeftAxis->SetMinMax(yMin, yMax);
		LSpBottomAxis->SetMinMax(xMin, xMax);
	}
	if (FLASH)
		pChart.RemoveAllSeries();
	pLineSerie = pChart.CreateLineSerie();
	pLineSerie->SetSeriesOrdering(poNoOrdering);//设置为无序
	pLineSerie->AddPoints(x, y, pPointNumber);
	//pLineSerie->SetColor(LineColor);

	pChart.EnableRefresh(true);
}
/*************************绘制点阵*********************************/
void CBOTDRDlg::ChartPoint_Draw(bool FLASH, CChartCtrl& pChart, double xMin, double xMax, double yMin, double yMax,
	TChartString pTitle, const TChartString pYtitle, const TChartString pXtitle, double* x, double* y, int pPointNumber, COLORREF LineColor)
{
	pChart.EnableRefresh(false);
	if (FLASH)
		pChart.RemoveAllSeries();
	TChartString msTitle = pTitle;    //图表标题
	CChartTitle* mpTitle = pChart.GetTitle();
	mpTitle->RemoveAll();
	mpTitle->AddString(msTitle);
	mpTitle->SetColor(RGB(0, 0, 0));
	if (pChart == m_ChartPower)
	{
		PpLeftAxis->SetMinMax(yMin, yMax);
	}
	else if (pChart == m_ChartLmOverall)
	{
		LOpLeftAxis->SetMinMax(yMin, yMax);
	}
	else
	{
		LSpLeftAxis->SetMinMax(yMin, yMax);
		LSpBottomAxis->SetMinMax(xMin, xMax);
	}
	pPointsSerie = pChart.CreatePointsSerie();
	pPointsSerie->SetSeriesOrdering(poNoOrdering);//设置为无序
	pPointsSerie->SetPointSize(8,8);
	pPointsSerie->AddPoints(x, y, pPointNumber);
	pPointsSerie->SetColor(RGB(0,0,255));
	pChart.EnableRefresh(true);
}
/*************************初始化采集卡***************************/
int CBOTDRDlg::StdIni(ST_CARDINFO* pstCardInfo, unsigned int unBoardIndex)
{
	unsigned int Fref = 10000000;//Reference clock frequency. 
	QTFM_COMMON_CLOCK_REFERENCE RefClkMode = QTFM_COMMON_CLOCK_REF_MODE_2;//Change to QTFM_COMMON_CLOCK_REF_MODE_1 if external reference clock is required.
	QTFM_COMMON_ADC_CLOCK ADCClkMode = QTFM_COMMON_ADC_CLOCK_MODE_0;//Change to QTFM_COMMON_ADC_CLOCK_MODE_1 if external sampling clock is required.

	QTFM_INPUT_RANGE   CurrInputRange = QTFM_INPUT_RANGE_1;//+full-scale in mV
	double              OffSet = 0;//[-fullscale,+fullscale] in uV

	int nRet = -1;//Default return value
	//////////////////////////////////////////////////////////////////////////
	//----Open card
	pstCardInfo->dib.EnableReplay = 0;
	pstCardInfo->Storage.EnableStreaming = 0;
	pstCardInfo->vfifo.EnableVfifo = 1;
	CHECK_RETURN_VALUE(QTOpenBoard(pstCardInfo, unBoardIndex));
	CHECK_RETURN_VALUE(QTResetBoard(pstCardInfo));
	//////////////////////////////////////////////////////////////////////////
	//Take max sample rate as default. Users feel free to change it by uncomment this line then assign new value.
	//pstCardInfo->ClockInfo.SRate = 250000000;//Sample rate in Hz
	//////////////////////////////////////////////////////////////////////////
	//----Setup clock
	CHECK_RETURN_VALUE(QTClockSet(pstCardInfo, Fref, 1, (pstCardInfo->ClockInfo.SRate), QTFM_COMMON_CLOCK_VCO_MODE_0, RefClkMode, ADCClkMode, 1));
	//----Setup AFE
	if (pstCardInfo->ProdInfo.product_number != 0x1125)
	{
		CHECK_RETURN_VALUE(QTAdcModeSet(pstCardInfo, 0, (pstCardInfo->stAI.bForceIOdelay) ? 0 : (1 << 8), 0));
	}
	//----Setup Input range and offset
	if (pstCardInfo->ProdInfo.couple_type == 0xDC)
	{
		//----Set analog input range first then offset
		CHECK_RETURN_VALUE(QTChannelRangeSet(pstCardInfo, -1, CurrInputRange));
		//----Set analog offset
		CHECK_RETURN_VALUE(QTChannelOffsetSet(pstCardInfo, -1, OffSet));
	}
	if (pstCardInfo->ProdInfo.product_number == 0x8254)
	{
		Messageveiw(m_Message, _T("找到设备0x8254"));
		return RES_SUCCESS;
	}
}
/*************************绘制数据***************************/
void CBOTDRDlg::DrawWaveS(unsigned int num)
{
	int Fre;
	double pXmin = 0, pXmax = DataAllAmount * 0.4, pYmin = 0, pYmax = 0;
	//储存功率的数组
	Fre = GetDlgItemInt(IDC_EDIT_BEGIN_FREQUENCY) + num * SaoPinJianGe;
	pYmin = PowerData[num][0];
	pYmax = PowerData[num][0];
	for (int i = 1; i < DataAllAmount; i++)
	{
		if (pYmin > PowerData[num][i])
			pYmin = PowerData[num][i];
		if (pYmax < PowerData[num][i])
			pYmax = PowerData[num][i];
	}
//	ChartLine_Draw(true, m_ChartPower, pXmin, pXmax, pYmin - 0.015, pYmax + 0.015, LineDistance, PowerData[num], DataAllAmount, RGB(255, 0, 0));
	m_ChartPower.EnableRefresh(false);
	PpLeftAxis->SetMinMax(pYmin - 0.015, pYmax + 0.015);
	m_ChartPower.RemoveAllSeries();
	pLineSerie = m_ChartPower.CreateLineSerie();
	pLineSerie->SetSeriesOrdering(poNoOrdering);//设置为无序
	pLineSerie->AddPoints(LineDistance, PowerData[num], DataAllAmount);
	//pLineSerie->SetColor(RGB(255, 0, 0));

	m_ChartPower.EnableRefresh(true);
	return;
}
bool CBOTDRDlg::WeiboInit(CString m_szCommName)
{
	if (m_weibo_serial.Open((LPCTSTR)m_szCommName, 0, 0, false) != ERROR_SUCCESS)
	{
		MessageBox(_T("未能打开微波源"), _T("提示！"));
		return false;
	}
	//if (m_weibo_serial.Setup(CSerial::EBaud115200, CSerial::EData8, CSerial::EParNone, CSerial::EStop1) != ERROR_SUCCESS)
	//{
	//	MessageBox(_T("微波源设置失败"), _T("提示！"));
	//	return false;
	//}
	//if (m_weibo_serial.SetupHandshaking(CSerial::EHandshakeHardware) != ERROR_SUCCESS)
	//{
	////	MessageBox(_T("微波源SetupHandshaking失败"), _T("提示！"));
	//	return false;
	//}
	//m_weibo_serial.Open((LPCTSTR)m_szCommName, 0, 0, false);
	m_weibo_serial.Setup(CSerial::EBaud115200, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
	m_weibo_serial.SetupHandshaking(CSerial::EHandshakeHardware);
	return true;
}
bool CBOTDRDlg::GuangyuanInit(CString m_gyCommName)
{
	if (m_guangyuan_serial.Open((LPCTSTR)m_gyCommName, 0, 0, true) != ERROR_SUCCESS)
	{
		MessageBox(_T("未能打开光源"), _T("提示！"));
		return false;
	}
	m_guangyuan_serial.Setup(CSerial::EBaud9600, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
	m_guangyuan_serial.SetupHandshaking(CSerial::EHandshakeHardware);
	return true;
}
void CBOTDRDlg::SetWeiboData(int p_fre)
{
	CString m_fre;
	m_fre.Format(_T("FREQ:CW %dMHZ\n"), p_fre);//CString_to_LPCSTR(m_fre)//OUTP:STAT ON

	m_weibo_serial.Write(CString_to_LPCSTR(m_fre));
	//return true;
	
}
void CBOTDRDlg::OpenOrCloseWeiBo(int flag)
{
	CString m_fre;
	if(flag==1)
		m_fre.Format(_T("OUTP:STAT ON\n"));//CString_to_LPCSTR(m_fre)//OUTP:STAT ON
	else
		m_fre.Format(_T("OUTP:STAT OFF\n"));//CString_to_LPCSTR(m_fre)//OUTP:STAT off
	m_weibo_serial.Write(CString_to_LPCSTR(m_fre));
}
bool CBOTDRDlg::SoaInit(CString m_soaCommName)
{
	
	if (m_soa_serial.Open(m_soaCommName, 0, 0, true) == ERROR_SUCCESS)
	{
		MessageBox(_T("打开soa"), _T("提示！"));
		return false;
	}
	if (m_soa_serial.Setup(CSerial::EBaud9600, CSerial::EData8, CSerial::EParNone, CSerial::EStop1) != ERROR_SUCCESS)
	{
		MessageBox(_T("soa设置失败"), _T("提示！"));
		return false;
	}
	if (m_soa_serial.SetupHandshaking(CSerial::EHandshakeHardware) != ERROR_SUCCESS)
	{
		MessageBox(_T("soaSetupHandshaking失败"), _T("提示！"));
		return false;
	}
	/*m_soa_serial.SetMask(CSerial::EEventBreak |
		CSerial::EEventCTS |
		CSerial::EEventDSR |
		CSerial::EEventError |
		CSerial::EEventRing |
		CSerial::EEventRLSD |
		CSerial::EEventRecv);*/
	//m_soa_serial.Setup(CSerial::EBaud9600, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
	//m_soa_serial.SetupHandshaking(CSerial::EHandshakeHardware);
	return true;
}
void CBOTDRDlg::SetSoaData(char * p_strsoa)
{
	byte istrsoa[] = { 0x8F,0x72,0x00,0x72,0x80,0x00,0x64,0x00,0x00,0x00,0x00,0x64 };
	m_soa_serial.Write((char *)istrsoa);
}
bool CBOTDRDlg::SetGuangyuanData(int wendu)
{
	//char str26[] = {0x54,0x43,0x31,0x3A,0x54,0x43,0x41,0x44,0x4A,0x55,0x53,0x54,0x54,0x45,0x4D,0x50,0x3D,0x32,0x36,0x0D };
	//char str25[] = {0x54,0x43,0x31,0x3A,0x54,0x43,0x41,0x44,0x4A,0x55,0x53,0x54,0x54,0x45,0x4D,0x50,0x3D,0x32,0x35,0x0D };
	char str25[] = { 0xAA,0x55,0xC7,0x02,0x77,0x74,0xFE,0x00 };
	char str26[] = { 0xAA,0x55,0xC7,0x02,0xDB,0x74,0xFE,0x00 };
	if (wendu == 26)
	{
		m_guangyuan_serial.Write(str26);
		return true;
	}
	if (wendu == 25)
	{
		m_guangyuan_serial.Write(str25);
		return true;
	}
	return false;
}

void CBOTDRDlg::Messageveiw(CString &m_Message,CString pMessage)
{
	MessageCount++;
	m_Message = m_Message + pMessage + _T("\r\n");
	GetDlgItem(IDC_EDIT_MESSAGE_VIEW)->SetWindowText(m_Message);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_MESSAGE_VIEW);
	int nline = pedit->GetLineCount();
	pedit->LineScroll(nline - 1);
	if (MessageCount == 1000)
	{
		m_Message = _T("");
		MessageCount = 0;
	}
}
int CBOTDRDlg::Sample(ST_CARDINFO* pstCardInfo, unsigned int unBoardIndex, unsigned int num,long& datalen)
{
	int Ret = -1;
	unsigned int point = 0;
	//point = ceil(((FiberLength * 1000 + 1) / 1024) * 2.5);//	point = ceil((FiberLength * 2.5) / 1024) + 2;
	point = ceil((FiberLength * 1000 * 2.5) / 1024);
	//point = ceil(FiberLength * 2.5);
	unsigned int SegmentLen = point * 1024;// 12 * 30720;//number of samples per segment
	unsigned int DmaGranularityB = point * 1024;//12*30 << 10;//PCIe DMA granularity to get data. It shouldn't be greater than EACH_DMA_MAX_LEN unsigned int DmaGranularityB = 2*10 << 10;//3km
	unsigned int AccCnt = GetDlgItemInt(IDC_EDIT_FILE_AMOUNT);//>=3;
	unsigned int MeanEn = 1;
	unsigned int MeanMode = 0;//0:16bit mode 1:32bit mode
	QTFM_ABA_MODE ABAMode = ABA_NORMAL_MODE;//正常采样模式，禁用ABA采样模式，此时以下两个参数取值无意义
	unsigned int ABADivider = 48;//In step of 16
	unsigned int NoChnInUse = 1;//Number of active channel in use

	unsigned int PreTriggerLen = 0;//pre-trigger length in samples欲触发点数之和为0
	unsigned int SegmentCnt = GetDlgItemInt(IDC_EDIT_FILE_AMOUNT);//触发次数==AccCnt
	QTFM_COMMON_TRIGGER_MODE TrigMode = QTFM_COMMON_TRIGGER_MODE_EDGE;//触发方式：边沿触发
	unsigned int uncompressMode = 0;//bit[0]=1:使能数据压缩模块,0:禁止数据压缩功能	
	unsigned int TimeStampEn = 0;//禁用时间戳功能
	int SaveFile = 1;
	//参数 TimeStampEn 控制时间戳使能和禁止。TimeStampEn=0 时禁止时间戳功能；
	//TimeStampEn = 3 时使能时间戳，用板载采样时钟计时；
	//TimeStampEn = 0x13 时使能时间戳，使用外部输入的定时时钟（比如 GPS 的 1PPS 秒脉冲）计时。其他值非法。

	//时间戳
	unsigned int TimeStampSegmentLen = 0;
	unsigned int TimeStampSel = 0;//时间戳数据选择。0：选择GPS时间戳数据；1：选择用户时间戳数据
	unsigned int GpsScond = 0;
	char DataFormat = 0;//0:offset binary; 1:two's complement

	//初始化分配内存空间
	ULONGLONG ullTotalLen = (ULONGLONG)0;
	unsigned char* pszBuf = NULL;
	FILE* fp = NULL;
	const char* path = ("E:\\BOTDRBINDATA\\sp-" + to_string(num) + ".bin").c_str();
	fp = fopen(path, "wb");
	long long RecvDataLen = 0;
	long long AvailableData = 0;//No. of available sample data bytes in buffer
	int BufOverflow = -1;//buffer overflow flag
	unsigned int NoBytesOverwritten = 0;//No. of overwritten sample data bytes
	
	Ret = QTResetBoard(pstCardInfo);
	if (Ret != RES_SUCCESS)return -1;
	pstCardInfo->DAQParams.AccCnt = AccCnt;
	//if (AccCnt && (!MeanEn || MeanMode))
	//	pstCardInfo->dib.MaxEachDmaLenB = SegmentLen * 4 - (SegmentLen * 4) % 128;//align with 128B
	//else
	//	pstCardInfo->dib.MaxEachDmaLenB = SegmentLen * 2 - (SegmentLen * 2) % 128;//align with 128B
	pstCardInfo->dib.MaxEachDmaLenB = (DmaGranularityB > EACH_DMA_MAX_LEN) ? EACH_DMA_MAX_LEN : DmaGranularityB;
	pstCardInfo->dib.MaxEachDmaLenB = pstCardInfo->dib.MaxEachDmaLenB - pstCardInfo->dib.MaxEachDmaLenB % 128;//Align with 128 bytes
	
	//CH1通道使能
	Ret = QTInputChannelSet(pstCardInfo, CHANNEL_0, 0, 0, 0, 0, 1);//Channel 0
	if (Ret != RES_SUCCESS)return -1;
	//CHECK_RETURN_VALUE(QTInputChannelSet(pstCardInfo, CHANNEL_1, 0, 0, 0, 0, 1));//Channel 1
	//CHECK_RETURN_VALUE(QTInputChannelSet(pstCardInfo, CHANNEL_2, 0, 0, 0, 0, 1));//Channel 0
	//CHECK_RETURN_VALUE(QTInputChannelSet(pstCardInfo, CHANNEL_3, 0, 0, 0, 0, 1));//Channel 1
	//参数 DataFormat 为 0 时，采用二进制偏移码（默认）；当 DataFormat 为 1 时，采用二进制补码。
	Ret = QTDataFormatSet(pstCardInfo, 0);
	if (Ret != RES_SUCCESS)return -1;
	//设置工作模式和时间戳
	Ret = QTABAModeSet(pstCardInfo, ABAMode, ABADivider, NoChnInUse);
	Ret = QTWorkModeSet(pstCardInfo, SegmentLen, PreTriggerLen, SegmentCnt, QTFM_COMMON_BOARD_WORK_MODE_STD_MULTI | TrigMode, uncompressMode, 0);
	Ret = QTTimestampSet(pstCardInfo, TimeStampEn, TimeStampSegmentLen, GpsScond, (pstCardInfo->ClockInfo.SRate), TimeStampSel);
	if (Ret != RES_SUCCESS)return -1;
	//选择触发方式
	//CHECK_RETURN_VALUE(QTChannelTriggerSet(pstCardInfo, CHANNEL_1, QTFM_COMMON_TRIGGER_TYPE_RISING_EDGE, 3350, 3400, 1));//CH2通道上升沿触发
	Ret = QTExtTriggerSet(pstCardInfo, QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_1, QTFM_COMMON_TRIGGER_TYPE_RISING_EDGE, 1);//外部通道1上升沿触发
	if (Ret != RES_SUCCESS)return -1;
	if (pstCardInfo->DAQParams.AccCnt == 0)
		ullTotalLen = (ULONGLONG)pstCardInfo->SegmentCnt * (ULONGLONG)pstCardInfo->SegmentSize;
	else
		ullTotalLen = ((ULONGLONG)pstCardInfo->SegmentCnt * (ULONGLONG)pstCardInfo->SegmentSize) / (pstCardInfo->DAQParams.AccCnt);
	pszBuf = (unsigned char*)malloc(sizeof(char) * ullTotalLen);
	//pszBuf = new unsigned char[sizeof(char) * ullTotalLen]();
	if (!pszBuf)
	{
		//printf_s("Buffer allocate error\n");
		return -1;
	}
	//采集卡等待开始采样
	QTStart(pstCardInfo, QTFM_COMMON_TRANSMIT_DIRECTION_BRD2PC, 1, 0xffffffff, 0);
	//采集数据
	while (RecvDataLen < ullTotalLen)
	{
		QTBufStatusGet(pstCardInfo, &AvailableData, &BufOverflow, &NoBytesOverwritten);
		if (BufOverflow || NoBytesOverwritten) break;
		RecvDataLen += NoBytesOverwritten;
		if (AvailableData < pstCardInfo->dib.MaxEachDmaLenB) continue;
		QTBufSDataGet(pstCardInfo, &pszBuf[RecvDataLen], (unsigned int)pstCardInfo->dib.MaxEachDmaLenB);//Get full size of data once data is ready
		RecvDataLen += pstCardInfo->dib.MaxEachDmaLenB;
	}
	datalen = RecvDataLen / 2;
	//CString strdatalen;
	//strdatalen.Format(_T("%d"),datalen);
	//Messageveiw(m_Message, strdatalen);
	for (int j = 0; j < DataAllAmount; j += 1)
	{
		PowerData[num][j] = (-1)*((256.0 * pszBuf[j * 2 + 1] + pszBuf[j * 2]) - 32768) * (4.0 / 65536) / 0.92531;
	}
	if (BufOverflow)
	{
		Messageveiw(m_Message, _T("采样点数据丢失！请增加缓冲读取速率或降低采样率"));
	}
	if (NoBytesOverwritten)
	{
		Messageveiw(m_Message, _T("采样点数据可能被破坏！请增加缓冲读取速率或降低采样率"));
	}
	fwrite(pszBuf, sizeof(UCHAR), ullTotalLen, fp);
	fclose(fp);
	/*CString filesave;
	filesave.Format(_T("频率点：%d 文件保存成功"), Begin_Fre + SaoPinJianGe * num);*/
	//delete[]pszBuf;
	free(pszBuf);
	pszBuf = NULL;
	//停止采集卡采集(并不是关闭)
	QTStart(pstCardInfo, QTFM_COMMON_TRANSMIT_DIRECTION_BRD2PC, 0, 0xffffffff, 0);
	//Ret = RES_SUCCESS;
	return Ret;
}

int CBOTDRDlg::StdClo(ST_CARDINFO* pstCardInfo)
{
	int Ret = -1;
	//关闭采集卡
	Ret = QTCloseBoard(pstCardInfo);
	return Ret;
}

bool CBOTDRDlg::SetupRefreshYesNo()
{
	CString strctfre, strdbwid, strfibi;
	GetDlgItemText(IDC_EDIT_CENTER_FREQUENCY, strctfre);
	GetDlgItemText(IDC_EDIT_THREEDB_WIDEH, strdbwid);
	GetDlgItemText(IDC_EDIT_FIBER_INDEX, strfibi);
	if ((Begin_Fre == GetDlgItemInt(IDC_EDIT_BEGIN_FREQUENCY))&&
		(End_Fre == GetDlgItemInt(IDC_EDIT_END_FREQUENCY)) &&
		(SaoPinJianGe == GetDlgItemInt(IDC_EDIT_SAOPIN_JIANGE) )&&
		(FileAmount == GetDlgItemInt(IDC_EDIT_FILE_AMOUNT)) &&
		(FiberLength == GetDlgItemInt(IDC_EDIT_FIBER_LENGTH)) &&
		(MaiChongWidth == GetDlgItemInt(IDC_EDIT_MAICHONG_WIDTH)) &&
		(CenterFre == (double)_wtof(strctfre) )&&
		(ThreedBWidth == (double)_wtof(strdbwid) )&&
		(FIberIndex == (double)_wtof(strfibi)))
	{
		return false;
	}
	return true;
}

/*************************归一化***************************/
bool CBOTDRDlg::Gyh()
{
	vector<double> GyhFind(LmAmount, 0);//用于归一化处理中的查找
	/*进行数据导入，循环次数为需要处理的频率点个数*/
	int gyhprogress = 0;
	ofstream SingleKmFile;
	SingleKmFile.open(m_EndGyhPath + "python-已归一化_0.4m-" + to_string(FileAmount) + "-" + to_string(LmAmount) + ".csv", ios::out);
	
	/*ofstream AllKmFile;
	AllKmFile.open(m_EndGyhPath + to_string(FiberLength) + "km-已归一化_0.4m" + to_string(FileAmount) + "-" + to_string(LmAmount) + ".csv", ios::out);
	AllKmFile << "" << ",";
	for (int n = 0; n < DataAllAmount; n++)
		AllKmFile << DataAllAmount * 0.4 << ",";
	AllKmFile << endl;*/
	for (int a = 0; a < LmAmount; a++)
	{
		GyhResult[a][0] = Begin_Fre + SaoPinJianGe * a;
		//AllKmFile << GyhResult[a][0] << ",";
	}
	for (int e = 0; e < LmAmount; e++)
	{
		SingleKmFile << GyhResult[e][0] << ',';
	}
	//AllKmFile << endl;
	
	
	for (int b = 0;b < FiberLength;b++)
	{
		//double Lin = Gyh_Get_Beginvalue(CenterFre, ThreedBWidth, 11.900);
		for (int c = DataKmAmount * b; c < DataKmAmount * b + DataKmAmount; c++)//第3个循环，循环次数为每个文件包含的数据个数，进行数据转换处理
		{
			for (int d = 0; d < LmAmount; d++)
			{
				GyhFind[d] = (PowerData[d][c]) * (-1);//导入数据
			}
			auto max_fre = max_element(GyhFind.begin(), GyhFind.end());
			auto min_fre = min_element(GyhFind.begin(), GyhFind.end());
			double Max = GyhFind[max_fre - GyhFind.begin()];
			double Min = GyhFind[min_fre - GyhFind.begin()];
			for (int d = 0;d < LmAmount;d++)
			{
				//GyhFind[d] = Lin + (((GyhFind[d] - Min) / (Max - Min)) * (1.000000 - Lin));
				GyhFind[d] = (GyhFind[d] - Min) / (Max - Min);
				GyhResult[d][c + 1] = GyhFind[d];
			}
		}
		gyhprogress = (int)(((float)b / (float)FiberLength) * 100);
		m_LmProCtrl.SetPos(gyhprogress);
		strprogress.Format(_T("%d%%"), gyhprogress);
		SetDlgItemText(IDC_STATIC_PROFRESS, strprogress);
	}
	//for (int j = 0; j < LmAmount; j++)
	//{
	//	GyhFileIfs[j].close();
	//}
	//for (int h = 0; h < LmAmount; h++)
	//{
	//	for (int i = 0; i < DataAllAmount; i++)
	//	{
	//		AllKmFile << GyhResult[h][i] << endl;
	//	}
	//	AllKmFile << endl;
	//}
	//AllKmFile.close();
	for (int e = 0; e < LmAmount; e++)
	{
		for (int f = 0; f < DataKmAmount * 2; f++)
		{
			SingleKmFile << GyhResult[e][DataKmAmount* (FiberLength-2)+f+1] << ',';
		}
		SingleKmFile << endl;
	}
	SingleKmFile.close();//关闭文件
	return true;
}
/******************归一化处理*****************************/
void CBOTDRDlg::GuiYiHua()
{
	if (FileFlag == 1)
	{
		if (SetupRefreshYesNo())
		{
			AfxMessageBox(_T("检测到参数改动，请先设置参数！"));
			return;
		}
		CWaitCursor wait;
		StartTime = clock();
		if (Gyh())
		{
			FinishTime = clock();//程序结束时间
			TotalTime = (double)(FinishTime - StartTime) / CLOCKS_PER_SEC;//计算程序运行时间
			m_Message += ("已归一化处理完成\r\n耗时：" + to_string(TotalTime) + "秒\r\n").c_str();
			//实时显示在信息窗口上
			SetDlgItemText(IDC_EDIT_MESSAGE_VIEW, m_Message);
			CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_MESSAGE_VIEW);
			int nline = pedit->GetLineCount();
			pedit->LineScroll(nline - 1);
			m_LmProCtrl.SetPos(100);
			strprogress.Format(_T("%d%%"), 100);
			SetDlgItemText(IDC_STATIC_PROFRESS, strprogress);
		}
		else
		{
			FinishTime = clock();//程序结束时间
			TotalTime = (double)(FinishTime - StartTime) / CLOCKS_PER_SEC;//计算程序运行时间
			m_Message += ("已归一化处理失败，请重试！\r\n耗时：" + to_string(TotalTime) + "秒\r\n").c_str();
			//实时显示在信息窗口上
			SetDlgItemText(IDC_EDIT_MESSAGE_VIEW, m_Message);
			CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_MESSAGE_VIEW);
			int nline = pedit->GetLineCount();
			pedit->LineScroll(nline - 1);
			m_LmProCtrl.SetPos(100);
			strprogress.Format(_T("%d%%"), 100);
			SetDlgItemText(IDC_STATIC_PROFRESS, strprogress);
		}
		wait.~CWaitCursor();
		return;
	}
	AfxMessageBox(_T("请先设置文件路径！"));
	return;
}

void CBOTDRDlg::TemperatureDiff()
{
	for (int a = 0; a < DataAllAmount; a++)
	{
		if (LmResultCenterFre[a] == 10.700)
		{
			Tempdiff[a] = -50;
		}
		else
			Tempdiff[a] = (LmResultCenterFre[a] - StandardData[a]) * 1000;
	}
	//ChartLine_Draw(true, m_ChartWenduChaValue, 0, FiberLength * 1000, pYmin, pYmax, LineDistance, Tempdiff, DataAllAmount, RGB(255, 0, 0));
	m_ChartWenduChaValue.EnableRefresh(false);
//	WvLeftAxis->SetMinMax(pYmin, pYmax);
	m_ChartWenduChaValue.RemoveAllSeries();
	pLineSerie = m_ChartWenduChaValue.CreateLineSerie();
	pLineSerie->SetSeriesOrdering(poNoOrdering);//设置为无序
	pLineSerie->AddPoints(LineDistance, Tempdiff, DataAllAmount);
	//pLineSerie->SetColor(RGB(255, 0, 0));
	m_ChartWenduChaValue.EnableRefresh(true);
	if (MysqlConnect_flag == 1)
	{
		mysql_query(&mysql, "DELETE FROM TEMPERATURE_DATA;");
		Messageveiw(m_Message, _T("删除服务器温度数据"));
		Messageveiw(m_Message, _T("正在插入当前温度数据......"));
		MysqlSendData(Tempdiff);
	}

}

void CBOTDRDlg::IniSave()
{
	CString hadsave, strfibp, strplp, strfip, strbfr, strefr, strfia, strlen, strcfr, strwfr, strspf, strfii, strspjg, strmcwid, strautotime;
	CString strsqladdress, strsqluser, strsqlpassword, strsqlnumber;
	CString strSandardflag;
	CString strlimitday;
	hadsave = _T("1");
	strSandardflag.Format(_T("%d"),Sandard_flag);
	GetDlgItemText(IDC_EDIT_FIBER_PLACE, strfibp);
	GetDlgItemText(IDC_EDIT_PLACE_POINT, strplp);
	GetDlgItemText(IDC_EDIT_FILE_PATH, strfip);
	GetDlgItemText(IDC_EDIT_BEGIN_FREQUENCY, strbfr);
	GetDlgItemText(IDC_EDIT_END_FREQUENCY, strefr);
	GetDlgItemText(IDC_EDIT_FILE_AMOUNT, strfia);
	GetDlgItemText(IDC_EDIT_FIBER_LENGTH, strlen);
	GetDlgItemText(IDC_EDIT_CENTER_FREQUENCY, strcfr);
	GetDlgItemText(IDC_EDIT_THREEDB_WIDEH, strwfr);
	GetDlgItemText(IDC_EDIT_SAMPLE_FRE, strspf);
	GetDlgItemText(IDC_EDIT_MYSQL_ADDRESS, strsqladdress);
	GetDlgItemText(IDC_EDIT_MYSQL_USER, strsqluser);
	GetDlgItemText(IDC_EDIT_MYSQL_PASSWORD, strsqlpassword);
	GetDlgItemText(IDC_EDIT_MYSQL_NUMBER, strsqlnumber);
	GetDlgItemText(IDC_EDIT_FIBER_INDEX, strfii);
	GetDlgItemText(IDC_EDIT_SAOPIN_JIANGE, strspjg);
	GetDlgItemText(IDC_EDIT_MAICHONG_WIDTH, strmcwid);
	GetDlgItemText(IDC_EDIT_AUTO_MEASURE_TIME, strautotime);
	GetDlgItemText(IDC_EDIT_MYSQL_DAYLIMIT, strlimitday);

	WritePrivateProfileString(_T("Flag"), _T("SAVEYESNO"), hadsave, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Flag"), _T("SANDARDYESNO"), strSandardflag, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("FIBER_PLACE"), strfibp, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("PLACE_POint"), strplp, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("FILE_PATH"), strfip, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("BEGIN_FREQUENCY"), strbfr, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("END_FREQUENCY"), strefr, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("FILE_AMOUNT"), strfia, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("FIBER_LENGTH"), strlen, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("CENTER_FREQUENCY"), strcfr, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("THREEDB_WIDEH"), strwfr, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("SAMPLE_FRE"), strspf, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("SQL_ADDRESS"), strsqladdress, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("SQL_USER"), strsqluser, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("SQL_PASSWORD"), strsqlpassword, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("SQL_NUMBER"), strsqlnumber, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("FIRBER_INDEX"), strfii, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("SAOPIN_JIANGE"), strspjg, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("MAICHONG_WIDTH"), strmcwid, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("AUTO_MEASURE_TIME"), strautotime, _T(".\\BOTDR.ini"));
	WritePrivateProfileString(_T("Parameter"), _T("LIMIT_DAY"), strlimitday, _T(".\\BOTDR.ini"));
}

void CBOTDRDlg::IniLoad()
{
	CString hadsave, strSandardflag;
	GetPrivateProfileString(_T("Flag"), _T("SAVEYESNO"),_T("0"), hadsave.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	if (_wtoi(hadsave) != 1)
	{
		return;
	}

	GetPrivateProfileString(_T("Flag"), _T("SANDARDYESNO"), _T("0"), strSandardflag.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	Sandard_flag = _wtoi(strSandardflag);

	CString strfip, strfibp, strplp, strbfr, strefr, strfia, strlen, strcfr, strwfr, strspf, strfii, strspjg, strmcwid, strautotime;
	CString strsqladdress, strsqluser, strsqlpassword, strsqlnumber;
	CString strlimitday;

	GetPrivateProfileString(_T("Parameter"), _T("FIBER_PLACE"), _T("0"), strfibp.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_FIBER_PLACE, strfibp);
	GetPrivateProfileString(_T("Parameter"), _T("PLACE__POint"), _T("0"), strplp.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_PLACE_POINT, strplp);

	string BgPath;
	bool fileisdir;//判断文件夹是否存在
	GetPrivateProfileString(_T("Parameter"), _T("FILE_PATH"), _T("0"), strfip.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_FILE_PATH, strfip);
	fileisdir = PathIsDirectory(strfip);
	BgPath = CT2A(strfip.GetBuffer());
	if (fileisdir)
	{
		SetBasicPath(BgPath);
		SetEndGyhPath("\\");
		FileFlag = 1;
	}
	else
	{
		AfxMessageBox(_T("文件路径不存在，请重新选择文件路径"));
	}
	GetPrivateProfileString(_T("Parameter"), _T("BEGIN_FREQUENCY"), _T("0"), strbfr.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	Begin_Fre = _wtoi(strbfr);
	SetDlgItemInt(IDC_EDIT_BEGIN_FREQUENCY, Begin_Fre);
	GetPrivateProfileString(_T("Parameter"), _T("END_FREQUENCY"), _T("0"), strefr.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	End_Fre = _wtoi(strefr);
	SetDlgItemInt(IDC_EDIT_END_FREQUENCY, End_Fre);
	GetPrivateProfileString(_T("Parameter"), _T("SAOPIN_JIANGE"), _T("0"), strspjg.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_SAOPIN_JIANGE, strspjg);
	SaoPinJianGe = _wtoi(strspjg);

	LmAmount = (End_Fre - Begin_Fre) / SaoPinJianGe + 1;
	SetDlgItemInt(IDC_EDIT_LMPOINT_NUMBER, LmAmount);

	GetPrivateProfileString(_T("Parameter"), _T("FILE_AMOUNT"), _T("0"), strfia.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	FileAmount = _wtoi(strfia);
	SetDlgItemInt(IDC_EDIT_FILE_AMOUNT, FileAmount);
	GetPrivateProfileString(_T("Parameter"), _T("FIBER_LENGTH"), _T("0"), strlen.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	FiberLength = _wtoi(strlen);
	SetDlgItemInt(IDC_EDIT_FIBER_LENGTH, FiberLength);
	DataAllAmount = DataKmAmount * FiberLength;

	GetPrivateProfileString(_T("Parameter"), _T("CENTER_FREQUENCY"), _T("0"), strcfr.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	CenterFre = (double)_wtof(strcfr);
	SetDlgItemText(IDC_EDIT_CENTER_FREQUENCY, strcfr);
	GetPrivateProfileString(_T("Parameter"), _T("THREEDB_WIDEH"), _T("0"), strwfr.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	ThreedBWidth = (double)_wtof(strwfr);
	SetDlgItemText(IDC_EDIT_THREEDB_WIDEH, strwfr);
	GetPrivateProfileString(_T("Parameter"), _T("SAMPLE_FRE"), _T("0"), strspf.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_SAMPLE_FRE, strspf);

	GetPrivateProfileString(_T("Parameter"), _T("SQL_ADDRESS"), _T("0"), strsqladdress.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_MYSQL_ADDRESS, strsqladdress);
	GetPrivateProfileString(_T("Parameter"), _T("SQL_USER"), _T("0"), strsqluser.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_MYSQL_USER, strsqluser);
	GetPrivateProfileString(_T("Parameter"), _T("SQL_PASSWORD"), _T("0"), strsqlpassword.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_MYSQL_PASSWORD, strsqlpassword);
	GetPrivateProfileString(_T("Parameter"), _T("SQL_NUMBER"), _T("0"), strsqlnumber.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_MYSQL_NUMBER, strsqlnumber);
	GetPrivateProfileString(_T("Parameter"), _T("MAICHONG_WIDTH"), _T("0"), strmcwid.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_MAICHONG_WIDTH, strmcwid);
	MaiChongWidth = _wtoi(strmcwid);
	GetPrivateProfileString(_T("Parameter"), _T("AUTO_MEASURE_TIME"), _T("0"), strautotime.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_AUTO_MEASURE_TIME, strautotime);
	AutoMeasureTime = _wtoi(strautotime);
	GetPrivateProfileString(_T("Parameter"), _T("FIRBER_INDEX"), _T("0"), strfii.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_FIBER_INDEX, strfii);
	FIberIndex = (double)_wtof(strfii);
	GetPrivateProfileString(_T("Parameter"), _T("LIMIT_DAY"), _T("0"), strlimitday.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\BOTDR.ini"));
	SetDlgItemText(IDC_EDIT_MYSQL_DAYLIMIT, strlimitday);
	Messageveiw(m_Message, _T("参数导入完成!"));
}

BOOL CBOTDRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(false);
	if (pSysMenu != nullptr)
	{
		bool bNameValid;
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
	SetIcon(m_hIcon, true);			// 设置大图标
	SetIcon(m_hIcon, false);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	IniLoad();
	System_Init();
	MysqlYesNo_flag = 1;
	SetDlgItemText(IDC_EDIT_MESSAGE_VIEW, m_Message);
	//显示最新的一行
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_MESSAGE_VIEW);
	int nline = pedit->GetLineCount();
	pedit->LineScroll(nline - 1);
	return true;  // 除非将焦点设置到控件，否则返回 true
}
//屏蔽回车键和ESC键
BOOL CBOTDRDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
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

/******************************==================控件和窗口消息处理========================**************************************/

/*************************原始数据文件路径选取*********************************/
void CBOTDRDlg::OnBnClickedButtonFileChioce()
{
	char FilePath[1000];     //存放选择的目录路径 
	CString Getpath;
	string BgPath;
	ZeroMemory(FilePath, sizeof(FilePath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = (LPWSTR)FilePath;
	bi.lpszTitle = _T("请选择数据路径");
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
		SetEndGyhPath("\\");
		FileFlag = 1;
		CWaitCursor wait;
		System_Init();
		wait.~CWaitCursor();
	}
	else
	{
		if (FileFlag == 0)
		{
			AfxMessageBox(_T("文件路径不存在，请重新选择文件路径"));
			return;
		}
	}
	// TODO: 在此添加控件通知处理程序代码
}

/*************************功率曲线绘制*********************************/
void CBOTDRDlg::OnBnClickedButtonPowerDraw()
{
	if (FileFlag == 1)
	{
		if (SetupRefreshYesNo())
		{
			AfxMessageBox(_T("检测到参数改动，请先设置参数！"));
			return;
		}
		int Fre;
		double pXmin = 0, pXmax = DataAllAmount * 0.4, pYmin = 0, pYmax = 0;
		unsigned char* SiPowerData = new unsigned char[DataAllAmount * 2]();//用于读取的短整型数组
		double* pPowerData = new double[DataAllAmount]();//储存功率的数组
		Fre = GetDlgItemInt(IDC_COMBO2) * SaoPinJianGe + Begin_Fre;
		SetPowerPath("\\sp-" + to_string((Fre - Begin_Fre) / SaoPinJianGe) + FileType);
		ifstream Frequency_Power_File;
		Frequency_Power_File.open(m_PowerPath, ios::binary);
		if (!Frequency_Power_File)
		{
			AfxMessageBox(_T("无效的目录，无法继续绘制，请保证功率参数和文件路径设置正确！"));
			Frequency_Power_File.close();
			delete[] pPowerData;
			delete[] SiPowerData;
			return;
		}
		Frequency_Power_File.read((char*)SiPowerData, sizeof(unsigned char) * DataAllAmount * 2);
		pPowerData[0] = (-1) * ((256.0 * SiPowerData[0 * 2 + 1] + SiPowerData[0 * 2]) - 32768) * (4.0 / 65536) / 0.92531;//累加计算
		pYmin = pPowerData[0];
		pYmax = pPowerData[0];
		for (int i = 1; i < DataAllAmount; i++)
		{
			pPowerData[i] = (-1) * ((256.0 * SiPowerData[i * 2 + 1] + SiPowerData[i * 2]) - 32768) * (4.0 / 65536) / 0.92531;//累加计算
			if (pYmin > pPowerData[i])
				pYmin = pPowerData[i];
			if (pYmax < pPowerData[i])
				pYmax = pPowerData[i];
		}
		ChartLine_Draw(true, m_ChartPower, pXmin, pXmax, pYmin - 0.015, pYmax + 0.015, LineDistance, pPowerData, DataAllAmount, RGB(255,0,0));
		Frequency_Power_File.clear();
		Frequency_Power_File.close();
		delete[] pPowerData;
		delete[] SiPowerData;
		return;
	}
	AfxMessageBox(_T("未设置文件路径或未进行累加平均处理，请先设置文件路径和参数！"));
	return;
	// TODO: 在此添加控件通知处理程序代码
}

/*************************参数设置*********************************/
void CBOTDRDlg::OnBnClickedButtonSetup()
{
	if (SetupRefreshYesNo())//重新设置参数的话,先释放之前的内存，重置参数设置标志位
	{
		Data_Delete();
	}
	else
	{
		Messageveiw(m_Message, _T("参数未改动"));
		return;
	}
	CWaitCursor wait;
	Begin_Fre = GetDlgItemInt(IDC_EDIT_BEGIN_FREQUENCY);
	End_Fre = GetDlgItemInt(IDC_EDIT_END_FREQUENCY);
	SaoPinJianGe = GetDlgItemInt(IDC_EDIT_SAOPIN_JIANGE);
	LmAmount = (End_Fre - Begin_Fre) / SaoPinJianGe + 1;
	SetDlgItemInt(IDC_EDIT_LMPOINT_NUMBER, LmAmount);
	FileAmount = GetDlgItemInt(IDC_EDIT_FILE_AMOUNT);
	FiberLength = GetDlgItemInt(IDC_EDIT_FIBER_LENGTH);
	DataAllAmount = DataKmAmount * FiberLength;
	CString strctfre, strdbwid, strfibi;
	GetDlgItemText(IDC_EDIT_CENTER_FREQUENCY, strctfre);
	GetDlgItemText(IDC_EDIT_THREEDB_WIDEH, strdbwid);
	GetDlgItemText(IDC_EDIT_FIBER_INDEX, strfibi);
	CenterFre = (double)_wtof(strctfre);
	ThreedBWidth = (double)_wtof(strdbwid);
	FIberIndex = (double)_wtof(strfibi);
	MaiChongWidth = GetDlgItemInt(IDC_EDIT_MAICHONG_WIDTH);
	m_ChartWenduChaValue.RemoveAllSeries();
	m_ChartPower.RemoveAllSeries();
	m_ChartLmOverall.RemoveAllSeries();
	m_ChartLmSingle.RemoveAllSeries();
	System_Init();
	CString str;
	m_powerbox.ResetContent();
	for (int i = 1;i <= LmAmount;i++)
	{
		str.Format(_T("%d"), i);
		m_powerbox.AddString(str);
	}
	m_powerbox.SetCurSel(1);
	GetDlgItem(IDC_BUTTON_LM_SINGLE)->EnableWindow(false);
	Messageveiw(m_Message,_T("参数设置完成\r\n"));
	wait.~CWaitCursor();
	// TODO: 在此添加控件通知处理程序代码
}

void CBOTDRDlg::OnBnClickedButtonLookLmResult()
{
	this->GetDlgItem(IDC_BUTTON_LM_OVERALL)->EnableWindow(false);
	double* LookCenterFre = new double[DataAllAmount]();
	string LookStr;
	string LookData;
	istringstream LookStream;
	ifstream LookFile;
	LookFile.open(".\\" + to_string(FiberLength) + "km-标定文件" + to_string(FileAmount) + "-" + to_string(LmAmount) + ".csv");
	if (!LookFile)
	{
		AfxMessageBox(_T("无效的目录，无法继续绘制，请保证参数和文件路径设置正确！"));
		LookFile.close();
		delete[] LookCenterFre;
		this->GetDlgItem(IDC_BUTTON_LM_OVERALL)->EnableWindow(true);
		return;
	}
	getline(LookFile, LookStr);
	getline(LookFile, LookStr);
	LookStream.clear();
	LookStream.str(LookStr);
	for (int a = 0; a < DataAllAmount; a++)
	{
		getline(LookStream, LookData, ',');
		LookCenterFre[a] = (double)atof(LookData.c_str());
	}
	ChartLine_Draw(true, m_ChartLmOverall, 0, FiberLength * 1000, (Begin_Fre - 700) / 1000.000, (End_Fre - 700) / 1000.000, LineDistance, LookCenterFre, DataAllAmount, RGB(255, 0, 0));
	delete[] LookCenterFre;
	this->GetDlgItem(IDC_BUTTON_LM_OVERALL)->EnableWindow(true);
	//// TODO: 在此添加控件通知处理程序代码
}


void CBOTDRDlg::OnBnClickedButtonLmSingle()
{
	int place = 0;
	place = (GetDlgItemInt(IDC_EDIT_FIBER_PLACE) - 1) * 2500 + GetDlgItemInt(IDC_EDIT_PLACE_POINT);
	double* X = new double[LmAmount];
	double Fre_init = (Begin_Fre - 700) / 1000.000;
	//CString StrFre;
	//StrFre.Format(_T("%f采样成功"), Fre_init)
	//Messageveiw(m_Message, StrFre);
	for (int a = 0;a < LmAmount;a++)
	{
		X[a] = Fre_init + a * 0.005;
	}
	double* Y = new double[LmAmount];
	for (int b = 0;b < LmAmount;b++)
	{
		Y[b] = GyhResult[b][place + 1];
	}
	double a1 = 10.835, a2 = 0.060;
	int LoopNum = 0;
	LoopNum = LM_Core(&a1, &a2, X, Y, 0.001, LmAmount);//d1为0.1，拟合单条需循环100次左右，时间10s；
	//d1为0.01，拟合单挑需循环30次左右，时间4.7s；             //d1为0.001，拟合单挑需循环10次左右，时间1.5s
	//m_Message = "";
	CString strlmsingle;
	strlmsingle.Format(_T("中心频率:%lfGHz\r\n3dB带宽:%lfGHz\r\n拟合次数:%d"), a1, a2, LoopNum);
	//m_Message.Format(_T("%lf,%lf,%d\t\n"), a1, a2, LoopNum);
	Messageveiw(m_Message, strlmsingle);
	double* LMX = new double[LmAmount];
	for (int c = 0;c < LmAmount;c++)
	{
		LMX[c] = Fre_init + c * 0.005;
	}
	double* LMY = new double[LmAmount];
	for (int d = 0;d < LmAmount;d++)
	{
		LMY[d] = Gyh_Get_Beginvalue(a1, a2, LMX[d]);
	}

	TChartString pPTitle = to_wstring((place + 1) * 0.4) + _T("m-LM");    //图表标题
	TChartString pYtitle = _T("Power");    //图表标题
	TChartString pXtitle = _T("Fre");    //图表标题
	//ChartPoint_Draw(true, m_ChartLmSingle, (double)(Begin_Fre - 700) / 1000.000, (double)(End_Fre - 700) / 1000.000, -0.2, 1.2, pPTitle, pYtitle, pXtitle, X, Y, LmAmount,RGB(255,0,0));
	ChartLine_Draw(true, m_ChartLmSingle, (double)(Begin_Fre - 700) / 1000.000, (double)(End_Fre - 700) / 1000.000, -0.2, 1.2, LMX, LMY, LmAmount, RGB(0, 255, 0));
	ChartPoint_Draw(false, m_ChartLmSingle, (double)(Begin_Fre - 700) / 1000.000, (double)(End_Fre - 700) / 1000.000, -0.2, 1.2, pPTitle, pYtitle, pXtitle, X, Y, LmAmount, RGB(0, 255, 0));
	//ChartPoint_Draw(m_ChartLmSingle, 10.800, 10.900, -0.2, 1.2, pPTitle, pYtitle, pXtitle, X, Y, 100);

	// TODO: 在此添加控件通知处理程序代码
	delete[]X;
	delete[]Y;
	delete[]LMX;
	delete[]LMY;
	// TODO: 在此添加控件通知处理程序代码
}


void CBOTDRDlg::OnBnClickedButtonSample()
{
	CWaitCursor wait;
	int Ret = -1;
	CString COM;
	//long datalen = 0;
	int num = ((GetDlgItemInt(IDC_COMBO2) * SaoPinJianGe + Begin_Fre) - Begin_Fre) / SaoPinJianGe;
	GetDlgItemText(IDC_COMBO1, COM);
	COM = _T("//./") + COM;
	WeiboInit(COM);
	OpenOrCloseWeiBo(1);//打开微波源输出
	m_weibo_serial.Close();
	Sleep(2000);
	long datalen;
	Ret = Sample(&stCardInfo[0], 0, num,datalen);//Sample(&stCardInfo[0], 0, i, &datalen);
	if (Ret == RES_SUCCESS)
	{
		Messageveiw(m_Message, _T("采样成功"));
		DrawWaveS(num);
	}
	else
	{
		Messageveiw(m_Message, _T("采样失败"));
	}
	GetDlgItemText(IDC_COMBO1, COM);
	COM = _T("//./") + COM;
	WeiboInit(COM);
	OpenOrCloseWeiBo(0);//关闭微波源输出
	m_weibo_serial.Close();
	wait.~CWaitCursor();
	// TODO: 在此添加控件通知处理程序代码
}
void CBOTDRDlg::OnBnClickedButtonOpencard()
{
	CWaitCursor wait;
	int Ret = -1;
	//CBOTDRDlg *Dlg = (CBOTDRDlg*)this;
	Ret = StdIni(&stCardInfo[0], 0);
	//StdIni(&stCardInfo[0], 0);
	if (Ret == RES_SUCCESS)
	{
		GetDlgItem(IDC_BUTTON_SAMPLE)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_CLOSECARD)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(false);
		Messageveiw(m_Message, _T("成功打开采集卡"));
	}	
	else
	{
		MessageBox(_T("未能打开采集卡"), _T("提示！"));
		Messageveiw(m_Message, _T("打开采集卡失败"));
	}
	wait.~CWaitCursor();
	// TODO: 在此添加控件通知处理程序代码
}
void CBOTDRDlg::OnBnClickedButtonClosecard()
{
	//CWaitCursor wait;
	int Ret = -1;
	Ret = StdClo(&stCardInfo[0]);//关闭采集卡
	if (Ret == RES_SUCCESS)
	{
		GetDlgItem(IDC_BUTTON_SAMPLE)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_CLOSECARD)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(true);
		Messageveiw(m_Message, _T("成功关闭采集卡"));
	}
	else
	{
		Messageveiw(m_Message, _T("关闭采集卡失败"));
	}
	//wait.~CWaitCursor();
	// TODO: 在此添加控件通知处理程序代码
}
    
void CBOTDRDlg::OnBnClickedButtonWeibo()
{
	//串行端口设置为：115200bps，无奇偶校验，8个数据位，1个停止位。命令终止符为换行符（“\n”）。
	// TODO: 在此添加控件通知处理程序代码
	CString COM;
	GetDlgItemText(IDC_COMBO1, COM);
	COM = _T("//./")+ COM;
	WeiboInit(COM);
	SetWeiboData(Begin_Fre + (GetDlgItemInt(IDC_COMBO2)-1) * SaoPinJianGe);
	m_weibo_serial.Close();
	Messageveiw(m_Message, _T("微波源频率设置成功！"));
}
void CBOTDRDlg::OnBnClickedButtonBeginSingleMeasure()
{
	if (Sandard_flag == 0)
	{
		AfxMessageBox(_T("请先标定光纤！"));
		return;
	}
	if (SetupRefreshYesNo())
	{
		AfxMessageBox(_T("检测到参数改动，请先设置参数！"));
		return;
	}
	if (FileFlag == 0)
	{
		AfxMessageBox(_T("文件路径不存在，请重新选择文件路径"));
		return;
	}

	GetDlgItem(IDC_BUTTON_LM_SINGLE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_POWER_DRAW)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_FILE_CHIOCE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_LM_OVERALL)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SETUP)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_CLOSECARD)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SAMPLE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_WEIBO)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_BEGIN_SINGLE_MEASURE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_BEGIN_DATA_BIAODING)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_BEGIN_AUTO_MEASURE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_CLOSE_MEASURE)->EnableWindow(true);
	m_LmProCtrl.SetPos(0);
	strprogress.Format(_T("%d%%"), 0);
	SetDlgItemText(IDC_STATIC_PROFRESS, strprogress);
	m_MysqlProCtrl.SetPos(0);
	strmysqlprogress.Format(_T("%d%%"), 0);
	SetDlgItemText(IDC_STATIC_MYSQL_PROGRESS, strmysqlprogress);
	//UpdateWindow();
	fitingprocess_Sp.Lock();
	Sample_flag = 0;
	int Ret = -1;
	Ret = StdIni(&stCardInfo[0], 0);
	if (Ret == RES_SUCCESS)
		Messageveiw(m_Message, _T("成功打开采集卡"));
	else
	{
		Messageveiw(m_Message, _T("打开采集卡失败"));
		return;
	}
	BOTDR_AddGuangYuanThread = AfxBeginThread(AddGuangYuanThread, this);
	//Sleep(2000);
	BOTDR_AddSampleThread = AfxBeginThread(AddSampleThread, this);
}
void CBOTDRDlg::OnBnClickedButtonCloseMeasure()
{
	Sample_flag = 1;
	GetDlgItem(IDC_BUTTON_CLOSE_MEASURE)->EnableWindow(false);
}
void CBOTDRDlg::OnBnClickedButtonMysqlConnect()
{
	MysqlConnect();//根据界面上的信息连接数据库中的数据表
		// TODO: 在此添加控件通知处理程序代码
}
void CBOTDRDlg::OnBnClickedButtonMysqlDataInsert()
{
	//检查服务器数据是否超出最大数据量限制
	CString deletetime;
	int limitcount = (GetDlgItemInt(IDC_EDIT_MYSQL_DAYLIMIT) + 1) * (24 * 60 / AutoMeasureTime) * (FiberLength * 1000 / (MaiChongWidth / 10));//数据量上限
	int shijilimitcount = (GetDlgItemInt(IDC_EDIT_MYSQL_DAYLIMIT)) * (24 * 60 / AutoMeasureTime) * (FiberLength * 1000 / (MaiChongWidth / 10));//实际数据量上限
	mysql_query(&mysql, "SELECT COUNT(*) FROM historical_data");
	MYSQL_RES* res; //查询结果集 
	res = mysql_store_result(&mysql);
	MYSQL_ROW row;
	row = mysql_fetch_row(res);
	if (atoi(row[0]) >= limitcount)
	{
		//删除多余数据
		Messageveiw(m_Message, _T("历史数据量已达限定值\r\n正在删除多余历史数据量。。。。"));
		char sql_insert[200];
		long t1 = GetTickCount();//程序段结束后取得系统运行时间(ms)
		sprintf_s(sql_insert, "DELETE FROM historical_data WHERE id<%d;", atoi(row[0]) - shijilimitcount + 1);
		mysql_query(&mysql, sql_insert);
		//获取系统当前时间,删除数据
		long t2 = GetTickCount();//程序段结束后取得系统运行时间(ms)
		deletetime.Format(_T("多余历史数据删除成功，耗时:%ds"), (t2 - t1) / 1000);
		Messageveiw(m_Message, deletetime);
		Messageveiw(m_Message, _T("正在重新排序历史数据表。。。。"));
		t1 = GetTickCount();//程序段结束后取得系统运行时间(ms)
		mysql_query(&mysql, "SET @i=0;");
		mysql_query(&mysql, "UPDATE historical_data SET id =(@i := @i + 1);");
		mysql_query(&mysql, "ALTER TABLE historical_data auto_increment = 1;");
		//获取系统当前时间,插入数据
		t2 = GetTickCount();//程序段结束后取得系统运行时间(ms)
		//计算打印上传数据的时间
		deletetime.Format(_T("历史数据表重新排序成功，耗时:%ds"), (t2 - t1) / 1000);
		Messageveiw(m_Message, deletetime);
	}
	mysql_free_result(res);
	res = NULL;
	//MysqlSendData(LmResultCenterFre);*/
}
void CBOTDRDlg::OnBnClickedButtonMysqlClose()
{
	//删除数据表*************************************************************************************************************
	/*mysql_query(&mysql, "DROP TABLE LMALL;");
	Messageveiw(m_Message, _T("删除数据表"));*/
	MysqlClose();
	// TODO: 在此添加控件通知处理程序代码
}

void CBOTDRDlg::OnBnClickedButtonBeginAutoMeasure()
{
	//SoaInit(_T("//./COM1"));
	//////int temp = GetDlgItemInt(IDC_EDIT_MAICHONG_WIDTH) * 0.2;
	//////char bb = temp % 128;
	//////char aa = temp / 128;
	//////char strsoainit[] = {0x8F,0x72,0x00,0x72};
	//char strsoa[] = { 0x8F,0x72,0x00,0x72,0x80,0x00,0x64,0x00,0x00,0x00,0x00,0x64 };
	//////SetSoaData(strsoainit);
	//SetSoaData(strsoa);
	//m_soa_serial.Close();
	////
	AutoMeasureTime = GetDlgItemInt(IDC_EDIT_AUTO_MEASURE_TIME);
	if (Sandard_flag == 0)
	{
		AfxMessageBox(_T("请先标定光纤！"));
		return;
	}
	if (SetupRefreshYesNo())
	{
		AfxMessageBox(_T("检测到参数改动，请先设置参数！"));
		return;
	}
	if (FileFlag == 0)
	{
		AfxMessageBox(_T("文件路径不存在，请重新选择文件路径"));
		return;
	}
	GetDlgItem(IDC_BUTTON_LM_SINGLE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_POWER_DRAW)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_FILE_CHIOCE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_LM_OVERALL)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SETUP)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_CLOSECARD)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SAMPLE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_WEIBO)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_BEGIN_SINGLE_MEASURE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_BEGIN_DATA_BIAODING)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_BEGIN_AUTO_MEASURE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_CLOSE_MEASURE)->EnableWindow(true);
	m_LmProCtrl.SetPos(0);
	strprogress.Format(_T("%d%%"), 0);
	SetDlgItemText(IDC_STATIC_PROFRESS, strprogress);
	//m_guangyuan_serial.Close();
	fitingprocess_Sp.Lock();
	Sample_flag = 0;
	Auto_Sample_flag = 0;
	BOTDR_AddGuangYuanThread = AfxBeginThread(AddGuangYuanThread, this);
	//Sleep(2000);
	BOTDR_AddSampleThread = AfxBeginThread(AddAutoMeasureThread, this);
}
void CBOTDRDlg::OnBnClickedButtonBeginDataBiaoding()
{
	//// TODO: 在此添加控件通知处理程序代码
	if (SetupRefreshYesNo())
	{
		AfxMessageBox(_T("检测到参数改动，请先设置参数！"));
		return;
	}
	if (FileFlag == 0)
	{
		AfxMessageBox(_T("文件路径不存在，请重新选择文件路径"));
		return;
	}
	GetDlgItem(IDC_BUTTON_LM_SINGLE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_POWER_DRAW)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_FILE_CHIOCE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_LM_OVERALL)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SETUP)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_CLOSECARD)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SAMPLE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_WEIBO)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_BEGIN_SINGLE_MEASURE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_BEGIN_DATA_BIAODING)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_BEGIN_AUTO_MEASURE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_CLOSE_MEASURE)->EnableWindow(true);
	m_LmProCtrl.SetPos(0);
	strprogress.Format(_T("%d%%"), 0);
	SetDlgItemText(IDC_STATIC_PROFRESS, strprogress);
	m_MysqlProCtrl.SetPos(0);
	strmysqlprogress.Format(_T("%d%%"), 0);
	SetDlgItemText(IDC_STATIC_MYSQL_PROGRESS, strmysqlprogress);
	fitingprocess_Sp.Lock();
	Sample_flag = 0;
	int Ret = -1;
	Ret = StdIni(&stCardInfo[0], 0);
	if (Ret == RES_SUCCESS)
		Messageveiw(m_Message, _T("成功打开采集卡\r\n开始标定光纤......"));
	else
	{
		Messageveiw(m_Message, _T("打开采集卡失败"));
		return;
	}
	BOTDR_AddGuangYuanThread = AfxBeginThread(AddGuangYuanThread, this);
	//Sleep(2000);
	BOTDR_AddSampleThread = AfxBeginThread(AddSandardSampleThread, this);
}



//系统退出和参数保存
void CBOTDRDlg::OnSysExit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox(_T("确实要退出程序吗？"), _T("提示！"), MB_ICONINFORMATION | MB_YESNO) == IDNO)
	{
		LineDistance = nullptr;
		GyhResult = nullptr;
		LmResultCenterFre = nullptr;
		MysqlLineDistance = nullptr;
		MysqlLmResult = nullptr;
		PowerData = nullptr;
		StandardData = nullptr;
		LmResultThreeWidth = nullptr;
		Tempdiff = nullptr;
		return;
	}
	CDialogEx::OnCancel();
}


void CBOTDRDlg::OnDestroy()
{
	Data_Delete();
	IniSave();
	MysqlClose();
	CDialogEx::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
}

UINT AddSampleThread(LPVOID params)
{
	CBOTDRDlg* Dlg = (CBOTDRDlg*)params;
	CString COM;
	Dlg->GetDlgItemText(IDC_COMBO1, COM);
	COM = _T("//./") + COM;
	Dlg->WeiboInit(COM);
	Dlg->OpenOrCloseWeiBo(1);//打开微波源输出
	Dlg->m_weibo_serial.Close();
	Sleep(2000);
	if (Dlg->MysqlConnect())
	{
		Dlg->MysqlConnect_flag = 1;
	}
	bool Samplebool = Dlg->SaoPinSample();
	if (Samplebool)
	{
		Dlg->StdClo(&(Dlg->stCardInfo[0]));
		Dlg->GuiYiHua();
		Dlg->RoutineLm();
		Dlg->TemperatureDiff();
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_SINGLE_MEASURE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_DATA_BIAODING)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_AUTO_MEASURE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_FILE_CHIOCE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_LM_OVERALL)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_LM_SINGLE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_POWER_DRAW)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_SETUP)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_CLOSECARD)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_SAMPLE)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_WEIBO)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_CLOSE_MEASURE)->EnableWindow(false);
		fitingprocess_Sp.Unlock();
		if (Dlg->MysqlConnect_flag == 1)
		{
			Dlg->MysqlClose();
			Dlg->MysqlConnect_flag = 0;
		}
		Dlg->Sample_flag = 1;
		Dlg->GetDlgItemText(IDC_COMBO1, COM);
		COM = _T("//./") + COM;
		Dlg->WeiboInit(COM);
		Dlg->OpenOrCloseWeiBo(0);//关闭微波源输出
		Dlg->m_weibo_serial.Close();
		return true;
	}
	else
	{
		Dlg->Messageveiw(Dlg->m_Message, _T("已退出采集"));
		Dlg->m_LmProCtrl.SetPos(0);
		Dlg->strprogress.Format(_T("%d%%"), 0);
		Dlg->SetDlgItemText(IDC_STATIC_PROFRESS, Dlg->strprogress);
		Dlg->StdClo(&(Dlg->stCardInfo[0]));
		fitingprocess_Sp.Unlock();
		if (Dlg->MysqlConnect_flag == 1)
		{
			Dlg->MysqlClose();
			Dlg->MysqlConnect_flag = 0;
		}
		Dlg->GetDlgItem(IDC_BUTTON_LM_SINGLE)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_POWER_DRAW)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_SINGLE_MEASURE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_DATA_BIAODING)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_AUTO_MEASURE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_FILE_CHIOCE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_LM_OVERALL)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_SETUP)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_CLOSECARD)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_SAMPLE)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_WEIBO)->EnableWindow(true);
		Dlg->GetDlgItemText(IDC_COMBO1, COM);
		COM = _T("//./") + COM;
		Dlg->WeiboInit(COM);
		Dlg->OpenOrCloseWeiBo(0);//关闭微波源输出
		Dlg->m_weibo_serial.Close();
		return true;
	}
}

UINT AddSandardSampleThread(LPVOID params)
{
	CBOTDRDlg* Dlg = (CBOTDRDlg*)params;
	CString COM;
	Dlg->GetDlgItemText(IDC_COMBO1, COM);
	COM = _T("//./") + COM;
	Dlg->WeiboInit(COM);
	Dlg->OpenOrCloseWeiBo(1);//打开微波源输出
	Dlg->m_weibo_serial.Close();
	Sleep(2000);
	bool Samplebool = Dlg->SaoPinSample();
	if (Dlg->MysqlConnect())
	{
		Dlg->MysqlConnect_flag = 1;
	}
	if (Samplebool)
	{
		Dlg->StdClo(&(Dlg->stCardInfo[0]));//关闭采集卡
		Dlg->GuiYiHua();
		Dlg->SandardLm();
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_DATA_BIAODING)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_SINGLE_MEASURE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_AUTO_MEASURE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_FILE_CHIOCE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_LM_OVERALL)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_LM_SINGLE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_POWER_DRAW)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_SETUP)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_CLOSECARD)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_SAMPLE)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_WEIBO)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_CLOSE_MEASURE)->EnableWindow(false);
		Dlg->Sandard_flag = 1;
		Dlg->Sample_flag = 1;
		fitingprocess_Sp.Unlock();
		Dlg->GetDlgItemText(IDC_COMBO1, COM);
		COM = _T("//./") + COM;
		Dlg->WeiboInit(COM);
		Dlg->OpenOrCloseWeiBo(0);//关闭微波源输出
		Dlg->m_weibo_serial.Close();
		return true;
	}
	else
	{
		Dlg->Messageveiw(Dlg->m_Message, _T("已退出采集"));
		Dlg->m_LmProCtrl.SetPos(0);
		Dlg->strprogress.Format(_T("%d%%"), 0);
		Dlg->SetDlgItemText(IDC_STATIC_PROFRESS, Dlg->strprogress);
		Dlg->StdClo(&(Dlg->stCardInfo[0]));//关闭采集卡
		fitingprocess_Sp.Unlock();
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_DATA_BIAODING)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_LM_SINGLE)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_POWER_DRAW)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_SINGLE_MEASURE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_BEGIN_AUTO_MEASURE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_FILE_CHIOCE)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_LM_OVERALL)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_SETUP)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_CLOSECARD)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(true);
		Dlg->GetDlgItem(IDC_BUTTON_SAMPLE)->EnableWindow(false);
		Dlg->GetDlgItem(IDC_BUTTON_WEIBO)->EnableWindow(true);
		Dlg->GetDlgItemText(IDC_COMBO1, COM);
		COM = _T("//./") + COM;
		Dlg->WeiboInit(COM);
		Dlg->OpenOrCloseWeiBo(0);//关闭微波源输出
		Dlg->m_weibo_serial.Close();
		return true;
	}
}
UINT AddAutoMeasureThread(LPVOID params)
{
	CBOTDRDlg* Dlg = (CBOTDRDlg*)params;
	int Ret = -1;
	int Auto = 0;
	CString StrAuto,COM;
	bool Samplebool;
	CString deletetime;
	int limitcount = (Dlg->GetDlgItemInt(IDC_EDIT_MYSQL_DAYLIMIT) + 1) * (24 * 60 / Dlg->AutoMeasureTime) * (Dlg->FiberLength * 1000 / (Dlg->MaiChongWidth / 10));//数据量上限
	int shijilimitcount = (Dlg->GetDlgItemInt(IDC_EDIT_MYSQL_DAYLIMIT)) * (24 * 60 / Dlg->AutoMeasureTime) * (Dlg->FiberLength * 1000 / (Dlg->MaiChongWidth / 10));//数据量上限
	if (Dlg->MysqlConnect())
	{
		Dlg->MysqlConnect_flag = 1;
	}
	
	while (Dlg->Auto_Sample_flag == 0)
	{
		//打开微波源输出
		Dlg->GetDlgItemText(IDC_COMBO1, COM);
		COM = _T("//./") + COM;
		Dlg->WeiboInit(COM);
		Dlg->OpenOrCloseWeiBo(1);
		Dlg->m_weibo_serial.Close();
		Sleep(2000);
		if (Dlg->MysqlConnect_flag == 1)
		{
			//检查服务器数据是否超出最大数据量限制
			mysql_query(&(Dlg->mysql), "SELECT COUNT(*) FROM historical_data");
			MYSQL_RES* res; //查询结果集 
			res = mysql_store_result(&(Dlg->mysql));
			MYSQL_ROW row;
			row = mysql_fetch_row(res);
			if (atoi(row[0]) >= limitcount)
			{
				//删除多余数据
				Dlg->Messageveiw(Dlg->m_Message, _T("历史数据量已达限定\r\n正在删除多余历史数据量。。。。"));
				char sql_insert[200];
				long t1 = GetTickCount();//程序段结束后取得系统运行时间(ms)
				sprintf_s(sql_insert, "DELETE FROM historical_data WHERE id<%d;", atoi(row[0]) - shijilimitcount + 1);
				mysql_query(&(Dlg->mysql), sql_insert);
				//获取系统当前时间,删除数据
				long t2 = GetTickCount();//程序段结束后取得系统运行时间(ms)
				deletetime.Format(_T("多余历史数据删除成功，耗时:%ds"), (t2 - t1) / 1000);
				Dlg->Messageveiw(Dlg->m_Message, deletetime);
				Dlg->Messageveiw(Dlg->m_Message, _T("正在重新排序历史数据表。。。。"));
				t1 = GetTickCount();//程序段结束后取得系统运行时间(ms)
				mysql_query(&(Dlg->mysql), "SET @i=0;");
				mysql_query(&(Dlg->mysql), "UPDATE historical_data SET id =(@i := @i + 1);");
				mysql_query(&(Dlg->mysql), "ALTER TABLE historical_data auto_increment = 1;");
				//获取系统当前时间,插入数据
				t2 = GetTickCount();//程序段结束后取得系统运行时间(ms)
				//计算打印上传数据的时间
				deletetime.Format(_T("历史数据表重新排序成功，耗时:%ds"), (t2 - t1) / 1000);
				Dlg->Messageveiw(Dlg->m_Message, deletetime);
			}
			mysql_free_result(res);
			res = NULL;
		}
		//开始自动测量
		Dlg->Messageveiw(Dlg->m_Message, _T("开始自动测量。。。。"));
		Auto++;
		Dlg->m_LmProCtrl.SetPos(0);
		Dlg->strprogress.Format(_T("%d%%"), 0);
		Dlg->SetDlgItemText(IDC_STATIC_PROFRESS, Dlg->strprogress);
		Dlg->m_MysqlProCtrl.SetPos(0);
		Dlg->strmysqlprogress.Format(_T("%d%%"),0);
		Dlg->SetDlgItemText(IDC_STATIC_MYSQL_PROGRESS, Dlg->strmysqlprogress);
		Dlg->StdIni(&Dlg->stCardInfo[0], 0);
		Samplebool = Dlg->SaoPinSample();
		if (Samplebool)
		{
			Dlg->StdClo(&(Dlg->stCardInfo[0]));
			Dlg->GuiYiHua();
			Dlg->RoutineLm();
			Dlg->TemperatureDiff();
		}
		else
		{
			Dlg->Messageveiw(Dlg->m_Message, _T("测量已退出"));
			Dlg->m_LmProCtrl.SetPos(0);
			Dlg->strprogress.Format(_T("%d%%"), 0);
			Dlg->SetDlgItemText(IDC_STATIC_PROFRESS, Dlg->strprogress);
			Dlg->StdClo(&(Dlg->stCardInfo[0]));
			Dlg->Auto_Sample_flag = 1;
		}
		if (Dlg->Auto_Sample_flag == 0)
		{
			StrAuto.Format(_T("第%d次测量已结束"), Auto);
			Dlg->Messageveiw(Dlg->m_Message, StrAuto);
			Dlg->Messageveiw(Dlg->m_Message, _T("正在等待下次测量......"));
			Dlg->GetDlgItemText(IDC_COMBO1, COM);
			COM = _T("//./") + COM;
			Dlg->WeiboInit(COM);
			Dlg->OpenOrCloseWeiBo(0);//关闭微波源输出
			Dlg->m_weibo_serial.Close();
			for (int a = 0; a < Dlg->AutoMeasureTime * 30; a++)
			{
				Sleep(2000);
				if (Dlg->Sample_flag == 1)
				{
					Dlg->Messageveiw(Dlg->m_Message, _T("测量已退出"));
					break;
				}
			}
			if (Dlg->Sample_flag == 1)
			{
				break;
			}
		}	
	}
	if (Dlg->MysqlConnect_flag == 1)
	{
		Dlg->MysqlClose();
		Dlg->MysqlConnect_flag = 0;
	}
	Dlg->GetDlgItem(IDC_BUTTON_BEGIN_SINGLE_MEASURE)->EnableWindow(true);
	Dlg->GetDlgItem(IDC_BUTTON_BEGIN_DATA_BIAODING)->EnableWindow(true);
	Dlg->GetDlgItem(IDC_BUTTON_BEGIN_AUTO_MEASURE)->EnableWindow(true);
	Dlg->GetDlgItem(IDC_BUTTON_FILE_CHIOCE)->EnableWindow(true);
	Dlg->GetDlgItem(IDC_BUTTON_LM_OVERALL)->EnableWindow(true);
	Dlg->GetDlgItem(IDC_BUTTON_LM_SINGLE)->EnableWindow(true);
	Dlg->GetDlgItem(IDC_BUTTON_POWER_DRAW)->EnableWindow(true);
	Dlg->GetDlgItem(IDC_BUTTON_SETUP)->EnableWindow(true);
	Dlg->GetDlgItem(IDC_BUTTON_CLOSECARD)->EnableWindow(false);
	Dlg->GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(true);
	Dlg->GetDlgItem(IDC_BUTTON_SAMPLE)->EnableWindow(false);
	Dlg->GetDlgItem(IDC_BUTTON_WEIBO)->EnableWindow(true);
	Dlg->GetDlgItem(IDC_BUTTON_CLOSE_MEASURE)->EnableWindow(false);
	Dlg->Auto_Sample_flag = 1;
	Dlg->Sample_flag = 1;
	fitingprocess_Sp.Unlock();
	Dlg->GetDlgItemText(IDC_COMBO1, COM);
	COM = _T("//./") + COM;
	Dlg->WeiboInit(COM);
	Dlg->OpenOrCloseWeiBo(0);//关闭微波源输出
	Dlg->m_weibo_serial.Close();
	return true;
}


UINT AddGuangYuanThread(LPVOID params)
{
	CBOTDRDlg* Dlg = (CBOTDRDlg*)params;
	while (Dlg->Sample_flag == 0)
	{
		Dlg->GuangyuanInit(_T("//./COM5"));
		Dlg->SetGuangyuanData(26);
		Dlg->m_guangyuan_serial.Close();
		Sleep(2000);
		Dlg->GuangyuanInit(_T("//./COM5"));
		Dlg->SetGuangyuanData(25);
		Dlg->m_guangyuan_serial.Close();
		Sleep(2000);
	}
	return 0;
}


