
// Cpk_DemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Cpk_Demo.h"
#include "Cpk_DemoDlg.h"
#include "afxdialogex.h"
#include "ChartCtrl/ChartBarSerie.h"
#include "ChartCtrl/ChartPointsSerie.h"
#include <stack>
#include "ChartCtrl/ChartLineSerie.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCpk_DemoDlg 对话框



CCpk_DemoDlg::CCpk_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCpk_DemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCpk_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCpk_DemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCpk_DemoDlg 消息处理程序

BOOL CCpk_DemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// TODO:  在此添加额外的初始化代码

	m_pCtrl = new CChartCtrl();
	RECT re = { 0, 0, 20, 40 };
	m_pCtrl->Create(this, re, 201, 0x52010000);
	m_pCtrl->SetBackColor(RGB(255, 255, 255));
	m_pCtrl->CreateStandardAxis(CChartCtrl::LeftAxis);
	m_pCtrl->CreateStandardAxis(CChartCtrl::BottomAxis);
	m_pCtrl->CreateStandardAxis(CChartCtrl::RightAxis);
	m_pCtrl->GetRightAxis()->SetAutomatic(true);
	m_pCtrl->GetLeftAxis()->SetAutomatic(true);
	m_pCtrl->GetBottomAxis()->SetAutomatic(false);
	m_pCtrl->SetEdgeType(EDGE_BUMP);
	m_pCtrl->SetZoomEnabled(false);
	m_pCtrl->GetLeftAxis()->GetGrid()->SetVisible(false);
	m_pCtrl->GetBottomAxis()->GetGrid()->SetVisible(false);
	m_pCtrl->SetWindowPos(NULL, 0, 0, 300, 300, SWP_NOZORDER | SWP_NOMOVE);

	m_pNameStatic = new CStatic();
	RECT staticRe = { 0, 0, 0, 0 };
	m_pNameStatic->Create(L"CPK", WS_CHILD | WS_VISIBLE | SS_CENTER, staticRe, this, 301);
	m_pNameStatic->SetWindowPos(NULL, 0, 0, 300, 300, SWP_NOZORDER | SWP_NOMOVE);
	//m_pNameStatic->SetFont(&m_SetFont);

	SCPKHistory cpk = SCPKHistory(12.0, 0.03, 0.03, Random(12.0, 0.02, 0.03, 5000), "efg");
	SetCpkData(cpk);

	return TRUE; 
}

std::vector<double> CCpk_DemoDlg::Random(double dDim, double dMaxTol, double dMinTol, int nLen)
{
	srand((int)time(0) + rand() % 10);
	std::vector<double>dD;
	for (int i = 0; i < nLen; i++)
	{
		dD.push_back(dDim + (rand() % 10)*(rand() % 5) / 1000.0);
		dD.push_back(dDim - (rand() % 10)*(rand() % 5) / 1000.0);
		if (rand() % 8 == 0)
		{
			dD.push_back(dDim + (dMaxTol + rand() % 10 / 1000.0));
		}
		if (rand() % 8 == 1 && rand() % 3 == 1)
		{
			dD.push_back(dDim - (dMinTol + rand() % 10 / 1000.0));
		}
	}
	return dD;
}


void CCpk_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCpk_DemoDlg::OnPaint()
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
HCURSOR CCpk_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCpk_DemoDlg::SetCpkData(SCPKHistory& cpkHis)
{
	//计算CPK数据
	SCPK s = cpkHis.GetCpk();

	m_pCtrl->EnableRefresh(false);
	CChartStandardAxisSerie* pLeftAxis = nullptr;
	CChartStandardAxisSerie* pBottomAxis = nullptr;
	pLeftAxis = (CChartStandardAxisSerie*)m_pCtrl->GetLeftAxis();
	pBottomAxis = (CChartStandardAxisSerie*)m_pCtrl->GetBottomAxis();

	//上下限
	double dMinTol = cpkHis.dDim - cpkHis.dMinTol;
	double dMaxTol = cpkHis.dDim + cpkHis.dMaxTol;

	m_pCtrl->RemoveAllSeries();//清空所有控件
	//OK
	CChartBarSerie* pOkBar = m_pCtrl->CreateBarSerie(false, false, true);
	//NG
	CChartBarSerie* pNGBar = m_pCtrl->CreateBarSerie(false, false, true);
	//临界
	CChartBarSerie* pCrisisBar = m_pCtrl->CreateBarSerie(false, false, true);
	m_pCtrl->RefreshCtrl();
	if (!pOkBar || !pNGBar || !pCrisisBar)
	{//建立Bar失败
		return;
	}
	//计算公差与所有数据最大间隔
	double dMaxInterval = max(-(cpkHis.dDim + cpkHis.dMaxTol - s.dMax), cpkHis.dDim - cpkHis.dMinTol - s.dMin);
	if (dMaxInterval < 0.0)
	{
		dMaxInterval = (cpkHis.dMinTol + cpkHis.dMaxTol) / 2.0;
	}
	else
	{
		dMaxInterval += (cpkHis.dMinTol + cpkHis.dMaxTol) / 2.0;
	}
	double dAxisMin = cpkHis.dDim - max(cpkHis.dMinTol, cpkHis.dMaxTol) - dMaxInterval;		//fabs(cpkHis.dDim-max(cpkHis.dMinTol, cpkHis.dMaxTol) - dMaxInterval);		//fabs(dMinTol - dMaxInterval);
	double dAxisMax = cpkHis.dDim + max(cpkHis.dMinTol, cpkHis.dMaxTol) + dMaxInterval;
	m_pCtrl->GetBottomAxis()->SetMinMax(dAxisMin, dAxisMax);


	//设置刻度间隔
	double dScreenD1 = m_pCtrl->GetBottomAxis()->ScreenToValue(1);
	double dScreenD2 = m_pCtrl->GetBottomAxis()->ScreenToValue(41);
	double dScreenTick = dScreenD2 - dScreenD1;
	pBottomAxis->SetTickIncrement(false, dScreenTick);
	//计算分布间隔为20个DC点距离
	double dScreenD3 = m_pCtrl->GetBottomAxis()->ScreenToValue(11);
	double dInterval = dScreenD3 - dScreenD1;

	//!设定Bar系列参数
	//宽度
	int nL1 = m_pCtrl->GetBottomAxis()->ValueToScreen(0.0);
	int nL2 = m_pCtrl->GetBottomAxis()->ValueToScreen(dInterval);
	int nLen = max(nL2, nL1) - min(nL2, nL1);
	pOkBar->SetBarWidth(nLen);
	pNGBar->SetBarWidth(nLen);
	pCrisisBar->SetBarWidth(nLen);
	//颜色
	pOkBar->ShowGradient(false);
	pOkBar->SetColor(RGB(0, 128, 255));
	pOkBar->SetBorderColor(RGB(255, 255, 255));
	pNGBar->ShowGradient(false);
	pNGBar->SetColor(RGB(255, 0, 0));
	pNGBar->SetBorderColor(RGB(255, 255, 255));
	pCrisisBar->ShowGradient(false);
	pCrisisBar->SetColor(RGB(0, 255, 0));
	pCrisisBar->SetBorderColor(RGB(255, 255, 255));
	//计算标准数据区域(中间区域)
	double dMidStar = cpkHis.dDim - dInterval / 2.0;
	double dMidEnd = cpkHis.dDim + dInterval / 2.0;

	//		ASSERT(dMidStar < 12.0);
	int nMax = 0;			//统计最大数量
	//统计区域值
	std::vector<double> vdXPoints;
	std::vector<double> vdYPoints;
	std::stack<double> vdStackX;
	std::stack<double> vdStackY;

	//陈斌斌11-13 修改AddPoint(dMidStar, nCountMid)为
	//AddPoint(dMidStar, nCountMid)
	int nCountMid = CountDataInterval(dMidStar, dMidEnd, cpkHis);
	if (nCountMid)
	{
		nMax = nCountMid;
		pOkBar->AddPoint(dMidStar, nCountMid);
	}

	//计算标准数据偏小区域
	std::vector<double>vTickLeft;
	vTickLeft.push_back(dMidStar);
	for (;;)
	{//扫描中部往左区域
		double dTickRight = *(vTickLeft.end() - 1);
		double dTickLeft = dTickRight - dInterval;
		if (dTickLeft < dAxisMin)		//退出条件
			break;
		vTickLeft.push_back(dTickLeft);
		//计算区域内的数量
		int nN = CountDataInterval(dTickLeft, dTickRight, cpkHis);
		if (!nN) continue;
		if (nN > nMax)
			nMax = nN;		//统计Y轴最大
		if (dTickLeft > dMinTol)
		{//结果为OK
			pOkBar->AddPoint(dTickLeft, (double)nN);
		}
		else if (dTickLeft < dMinTol
			&& dTickRight >dMinTol)
		{//比较是否在下限区间内 显示绿色
			pCrisisBar->AddPoint(dTickLeft, (double)nN);
		}
		else
		{//NG
			pNGBar->AddPoint(dTickLeft, (double)nN);
		}
		vdStackX.push(dTickLeft + dInterval / 2.0);
		vdStackY.push((double)nN);
	}
	vdXPoints.push_back(dAxisMin);
	vdYPoints.push_back(0.0);
	//从左边反转
	while (!vdStackX.empty())
	{
		vdXPoints.push_back(vdStackX.top());
		vdStackX.pop();
	}
	while (!vdStackY.empty())
	{
		vdYPoints.push_back(vdStackY.top());
		vdStackY.pop();
	}

	if (nCountMid)
	{
		vdXPoints.push_back(dMidStar + dInterval / 2.0);
		vdYPoints.push_back((double)nCountMid);
	}

	std::vector<double>vTickRight;
	vTickRight.push_back(dMidEnd);
	for (;;)
	{//扫描中部往右区域
		double dTickLeft = *(vTickRight.end() - 1);
		double dTickRight = dTickLeft + dInterval;
		if (dTickRight > dAxisMax)		//退出条件
			break;
		vTickRight.push_back(dTickRight);
		//计算区域内的数量
		int nN = CountDataInterval(dTickLeft, dTickRight, cpkHis);
		if (!nN) continue;
		if (nN > nMax)
			nMax = nN;		//统计Y轴最大
		if (dTickRight < dMaxTol)
		{//结果为OK
			pOkBar->AddPoint(dTickLeft, (double)nN);
		}
		else if (dTickLeft < dMaxTol
			&& dTickRight > dMaxTol)
		{//比较是否在下限区间内 显示绿色
			pCrisisBar->AddPoint(dTickLeft, (double)nN);
		}
		else
		{//NG
			pNGBar->AddPoint(dTickLeft, (double)nN);
		}
		vdXPoints.push_back(dTickLeft + dInterval / 2.0);
		vdYPoints.push_back((double)nN);
	}
	vdXPoints.push_back(dAxisMax);
	vdYPoints.push_back(0.0);

	//设置左Y轴最大数值
	m_pCtrl->GetLeftAxis()->SetMinMax(0.0, nMax + 1);

	//USL,LSL
	CChartPointsSerie* pLUSL = m_pCtrl->CreatePointsSerie();
	pLUSL->SetColor(RGB(255, 0, 0));
	//设置直线显示
	pLUSL->SetPointType(CChartPointsSerie::ptVerticalLine);
	pLUSL->SetBorderColor(RGB(255, 0, 0));
	pLUSL->AddPoint(dMinTol, 0.0);
	pLUSL->AddPoint(dMaxTol, 0.0);

	//标准值
	CChartPointsSerie* pDim = m_pCtrl->CreatePointsSerie();
	pDim->SetPointType(CChartPointsSerie::ptVerticalLine);
	pDim->SetBorderColor(RGB(0, 255, 255));
	pDim->AddPoint(cpkHis.dDim, 0.0);
	//曲线
	
	m_pCtrl->EnableRefresh(true);

}

int CCpk_DemoDlg::CountDataInterval(double dStart, double dEnd, SCPKHistory& cpkHis)
{
	double dMax = max(dStart, dEnd);
	double dMin = min(dStart, dEnd);
	int nResCount = 0;
	for (unsigned int nIndex = 0; nIndex < cpkHis.vdData.size(); nIndex++)
	{
		if (cpkHis.vdData[nIndex].dD<dMax && cpkHis.vdData[nIndex].dD>dMin)
		{
			nResCount++;
		}
	}
	return nResCount;
}

void CCpk_DemoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	m_pCtrl->DestroyWindow();
	delete m_pCtrl;


	m_pNameStatic->DestroyWindow();
	delete m_pNameStatic;
}
