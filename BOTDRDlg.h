
// BOTDRDlg.h: 头文件
//

#pragma once
#include "framework.h"
#include "ChartCtrl/ChartCtrl.h"
#include "ChartCtrl/ChartAxisLabel.h"
#include "ChartCtrl/ChartLineSerie.h"
using namespace std;

#define underline 100        //允许创建的文件句柄总数 = underline * 线程数
#define DATA_WJZS 3000       //总共需要处理的文件个数
#define FIR_CL 5             //多线程处理完生成的数据组数（也是总线程数）每个线程生成一组数据
#define DATA_GS 5000         //每个文件包含的数据个数（50km的数据对应125000个）（2500/km）
#define FIR_WJGS 600         //每个线程需要处理的原始数据文件个数= DATA_WJZS(文件总数) / FIR_CL

// CBOTDRDlg 对话框
class CBOTDRDlg : public CDialogEx
{
// 构造
public:
	CBOTDRDlg(CWnd* pParent = nullptr);	// 标准构造函数

	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOTDR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CChartCtrl m_ChartLmSingle;
	CChartCtrl m_ChartLmOverall;
	CChartCtrl m_ChartPower;
	CString m_Message = _T("");

	/*初始数据文件名*/
	string m_BasicPath = "";
	string m_BeginAddAvgPath = "";
	string m_EndAddAvgPath = "";
	string m_PowerPath = "";
	string source0 = "00";
	string source1 = "000";
	string source2 = "0000";
	string source3 = "0";
	string FileType = ".csv";
	string StrFrequency = "";
	int Frenum = 0;
	int Begin_Fre = 0;
	int End_Fre = 0;
	int Fres_Number = 0;

	//数据处理参数
	clock_t StartTime = 0, FinishTime = 0;
	double TotalTime = 0;
	double AddAverageResult = 0;//累加平均最终结果
	thread* AdAvThread = nullptr;//线程
	double** ThreadResult = nullptr;//线程的累加结果
	ifstream** ThreadFileIfs = nullptr;//线程的文件流句柄，最多允许创建500个！
	string* ThreadStrData = nullptr;//线程中读取到的字符串数据
	string* ThreadUselessData = nullptr;//线程中跳过的前三行无用数据
	int* ThreadFileNumber = nullptr;//线程中用于标记文件序号
	double* LineDistance = nullptr;//存放距离信息

public:
	void SetBasicPath(string pBasicPath)
	{
		m_BasicPath = pBasicPath;
	}
	void SetBeginAddAvgPath(string pBeginAddAvgPath)
	{
		m_BeginAddAvgPath = m_BasicPath + pBeginAddAvgPath;
	}
	void SetEndAddAvgPath(string pEndAddAvgPath)
	{
		m_EndAddAvgPath = m_BasicPath + pEndAddAvgPath;
	}
	void SetPowerPath(string pPowerPath)
	{
		m_PowerPath = m_BasicPath + pPowerPath;
	}
	void System_Init();
	void Chart_Init();
	void Data_Init();
	void Data_Delete();
	void Chart_Draw(CChartCtrl &pChart, double* x, double* y, double xMin, double xMax, double yMin, double yMax, 
					TChartString pTitle, int pPointNumber, const TChartString pYtitle,const TChartString pXtitle);
	void Thread_Func(int XC);
	void Add_Average();
	void Gyh();
	void Gyh_Get_Beginvalue();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFileChioce();
	afx_msg void OnBnClickedButtonPowerDraw();
	afx_msg void OnBnClickedButtonSetup();
	afx_msg void OnBnClickedButtonAddAverage();
	afx_msg void OnBnClickedButtonLmOverall();
	afx_msg void OnBnClickedButtonLmSingle();
	afx_msg void OnDestroy();
	afx_msg void OnSysExit();

};
