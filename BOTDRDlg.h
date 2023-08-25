
// BOTDRDlg.h: 头文件
//

#pragma once
#include "framework.h"
#include "ChartCtrl/ChartCtrl.h"
#include "ChartCtrl/ChartAxisLabel.h"
#include "ChartCtrl/ChartLineSerie.h"
#include "ChartCtrl/ChartPointsSerie.h"
#include "QTApi.h"
#include "QTDevice.h"
#include "QTfmCommon.h"
#include "QT_IMPORT.h"
#include "Serial.h"
#include <mysql.h>
#include  <Windows.h>
#include  <atlstr.h>

using namespace std;


#define LoopNumForFit 200
#define FitError 1E-5

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

public:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CChartCtrl m_ChartLmSingle;
	CChartCtrl m_ChartLmOverall;
	CChartCtrl m_ChartPower;
	CChartCtrl m_ChartWenduChaValue;
	CProgressCtrl m_LmProCtrl;
	CProgressCtrl m_MysqlProCtrl;

//窗口坐标轴初始化
	//LM单点拟合
	CChartAxis* LSpLeftAxis;
	CChartAxis* LSpBottomAxis;

	//LM完整拟合
	CChartAxis* LOpLeftAxis;
	CChartAxis* LOpBottomAxis;
	
	//功率曲线
	CChartAxis* PpLeftAxis;
	CChartAxis* PpBottomAxis;

	//温度差值曲线
	CChartAxis* WvLeftAxis;
	CChartAxis* WvBottomAxis;

	//line&&point
	CChartLineSerie* pLineSerie;
	CChartPointsSerie* pPointsSerie;
	/*参数设置*/

	int FileAmount = 0;        //每次需要处理的文件总数
	const int DataKmAmount = 2500;		//0.4m对应1个采样点，1km有2500个数据采样点
	int FiberLength = 0;		//光纤长度
	int DataAllAmount = 0;		//数据总点数，0.4m对应1个采样点，1km有2500个点，总点数==光纤长度（km）*2500
	int LmAmount = 0;		//拟合点数
	int Begin_Fre = 0;//起始采样频率
	int End_Fre = 0;//结束采样频率
	//int CyAmount = 0;//采样点数
	double CenterFre = 0;	//预估计的光纤布里渊中心频率
	double ThreedBWidth = 0;		//预估计的光纤布里渊3db带宽
	double FIberIndex = 0;		//光纤折射率
	int SaoPinJianGe = 0;		//扫频间隔
	int MaiChongWidth = 1000;   //脉冲宽度/ns
	int AutoMeasureTime = 3;   //自动测量时间间隔/分钟
	//CString S_COM;
	CWinThread* BOTDR_AddSampleThread = nullptr;//采样进程
	CWinThread* BOTDR_AddGuangYuanThread = nullptr;//控制光源进程
	
	CString m_Message = _T("说明：\r\n  先设置文件路径，随后设置相关参数，才能进行归一化处理！\r\n");
	CString strprogress = _T("");
	CString strmysqlprogress = _T("");
	int PocessFlag = 0;
	int FileFlag = 0;
	/*文件路径*/
	string m_BasicPath = "";//原始数据路径
	string m_PowerPath = "";//功率曲线绘制数据原始路径
	string m_BeginGyhPath = "";//归一化数据原始路径
	string m_EndGyhPath = "";//归一化结果路径

	//原始数据的文件序号及文件类型

	string FileType = ".bin";

	//其余各类数据
	string StrFrequency = "";//字符类型的频率点
	int Frenum = 0;//int类型的频率点
	

	//数据处理数组
	clock_t StartTime = 0, FinishTime = 0;//用于计算程序运行起始时间
	double TotalTime = 0;//程序运行总时间
	double* LineDistance = nullptr;//存放距离信息
	double** GyhResult = nullptr;//归一化结果
	double* LmResultCenterFre = nullptr;
	double* LmResultThreeWidth = nullptr;
	double** PowerData = nullptr;
	double* StandardData = nullptr;
	double* Tempdiff = nullptr;
	double* Temperture = nullptr;

	//上传数组初始化
	double* MysqlLineDistance = nullptr;//需要上传的距离信息
	double* MysqlLmResult = nullptr;//需要上传的结果信息
	int MysqlDataAllAmount = 0;//100米一个点
	//SOA
	int MaiKuanDataAmount = 0;//根据脉宽计算的数据点数
	//double** DataArray = NULL;//存放原始功率曲线,每一行某个频率点下功率随距离分布
	//double** DataArray = NULL;//存放原始功率曲线,每一行某个频率点下功率随距离分布

public://采集卡
	ST_CARDINFO stCardInfo[_QTFIRMWARE_NUM_OF_CARD];
	//CString m_Message = _T("");
	int StdIni(ST_CARDINFO* pstCardInfo, unsigned int unBoardIndex);//采集卡初始化
	int Sample(ST_CARDINFO* pstCardInfo, unsigned int unBoardIndex, unsigned int num,long& datalen);//采集数据
	int StdClo(ST_CARDINFO* pstCardInfo);//关闭采集卡
	void DrawWaveS(unsigned int num);
	int Sample_flag = 0;
	int Sandard_flag = 0;
	int Auto_Sample_flag = 1;
	int MysqlYesNo_flag = 0;
	int MysqlConnect_flag = 0;
	int MessageCount = 0;
public:	//微波源
	int Weibo_flag = 0;
	CSerial m_weibo_serial;
	bool WeiboInit(CString m_szCommName);
	void SetWeiboData(int p_fre);
	void OpenOrCloseWeiBo(int flag=1);
public://SOA
	CSerial m_soa_serial;
	bool SoaInit(CString m_soaCommName);
	void SetSoaData(char* p_strsoa);

public: //光源
	CSerial m_guangyuan_serial;
	bool GuangyuanInit(CString m_gyCommName);
	bool SetGuangyuanData(int wendu);
public: //系统
	void SetBasicPath(string pBasicPath)
	{//设置原始数据路径
		m_BasicPath = pBasicPath;
	}
	void SetPowerPath(string pPowerPath)
	{//设置功率曲线绘制数据原始路径
		m_PowerPath = "E:\\BOTDRBINDATA" + pPowerPath;
	}
	void SetBeginGyhPath(string pBeginGyhPath)
	{//设置归一化数据原始路径
		m_BeginGyhPath = m_BasicPath + pBeginGyhPath;
	}
	void SetEndGyhPath(string pEndGyhPath)
	{//设置归一化结果路径
		m_EndGyhPath = m_BasicPath + pEndGyhPath;
	}
	
	double Gyh_Get_Beginvalue(double centerfre, double wighfre, double iput)
	{//布里渊曲线函数计算
		return 1.000000 / (1.000000+ ((iput - centerfre) * (iput - centerfre)) / ((wighfre / 2.000000) * (wighfre / 2.000000)));
	}
	void System_Init();
	void Chart_Init();
	void Data_Init();
	void Data_Delete();
	void ChartLine_Draw(bool FLASH, CChartCtrl &pChart, double xMin, double xMax, double yMin, double yMax,
					double* x, double* y, int pPointNumber, COLORREF LineColor);
	void ChartPoint_Draw(bool FLASH, CChartCtrl& pChart, double xMin, double xMax, double yMin, double yMax,
					TChartString pTitle, const TChartString pYtitle, const TChartString pXtitle, double* x, double* y, int pPointNumber, COLORREF LineColor);

	void Messageveiw(CString& m_Message, CString pMessage);

	bool SetupRefreshYesNo();//判断参数是否有变动
	bool Gyh();
	void GuiYiHua();
	void TemperatureDiff();//温度差值计算函数
	void IniSave();
	void IniLoad();
	double CalculateQ(double a1, double a2, double* X, double* Y, int PointsNum);//计算残差平方
	void Calculate_hij(double* h, double a1, double a2, double* X, double* Y, double d, int PointsNum);
	int LM_Core(double* a1, double* a2, double* X, double* Y, double d, int PointsNum);
	bool SaoPinSample();
	void LmOverall();//具体拟合函数
	void RoutineLm();//常规的拟合步骤
	void SandardLm();//标定时的拟合步骤

	//mysql
	bool MysqlConnect();//数据库连接
	void MysqlSendData(double* senddata);//发送数据
	void MysqlClose();//关闭删除数据
	LPCSTR CString_to_LPCSTR(CString p_cstr);

	// 查找计算机可用串口并将串口号设置到Combo Box控件上
	CComboBox m_combox;
	CComboBox m_powerbox;

public:
	//MYSQL
	MYSQL mysql;//数据库句柄
	CString m_Sql_address;
	CString m_Sql_user;
	CString m_Sql_password;
	CString m_Sql_databases;
	int m_Sql_server_number;
//数据库初始化与连接
	bool Sql_Init(CString p_sql_address, CString p_sql_user, CString p_sql_password, CString p_sql_databases, int p_sql_server_number);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFileChioce();
	afx_msg void OnBnClickedButtonPowerDraw();
	afx_msg void OnBnClickedButtonSetup();
	afx_msg void OnBnClickedButtonLookLmResult();
	afx_msg void OnBnClickedButtonLmSingle();
	afx_msg void OnDestroy();
	afx_msg void OnSysExit();
	afx_msg void OnBnClickedButtonSample();//开始采集
	afx_msg void OnBnClickedButtonOpencard();//打开采集卡
	afx_msg void OnBnClickedButtonClosecard();//关闭采集卡
	afx_msg void OnBnClickedButtonWeibo();
	afx_msg void OnBnClickedButtonBeginSingleMeasure();
	afx_msg void OnBnClickedButtonCloseMeasure();
	afx_msg void OnBnClickedButtonMysqlConnect();
	afx_msg void OnBnClickedButtonMysqlDataInsert();
	afx_msg void OnBnClickedButtonMysqlClose();
	afx_msg void OnBnClickedButtonBeginAutoMeasure();
	afx_msg void OnBnClickedButtonBeginDataBiaoding();
};
UINT AddSampleThread(LPVOID params);//常规采集进程
UINT AddSandardSampleThread(LPVOID params);//标定采集进程
UINT AddGuangYuanThread(LPVOID params);//光源控制进程
UINT AddAutoMeasureThread(LPVOID params);//自动循环采集进程