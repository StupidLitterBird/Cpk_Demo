
// Cpk_DemoDlg.h : 头文件
//

#pragma once
#include "ChartCtrl/ChartCtrl.h"
#include "CPKHeader.h"

// CCpk_DemoDlg 对话框
class CCpk_DemoDlg : public CDialogEx
{
// 构造
public:
	CCpk_DemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CPK_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	void SetCpkData(SCPKHistory& cpkHis);
	int CountDataInterval(double dStart, double dEnd, SCPKHistory& cpkHis);
	std::vector<double> Random(double dDim, double dMaxTol, double dMinTol, int nLen);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CChartCtrl *m_pCtrl;
	CStatic *m_pNameStatic;
	CStatic *m_pResStatic;

public:
	afx_msg void OnDestroy();
};
