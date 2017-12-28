
// Cpk_DemoDlg.h : ͷ�ļ�
//

#pragma once
#include "ChartCtrl/ChartCtrl.h"
#include "CPKHeader.h"

// CCpk_DemoDlg �Ի���
class CCpk_DemoDlg : public CDialogEx
{
// ����
public:
	CCpk_DemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CPK_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	void SetCpkData(SCPKHistory& cpkHis);
	int CountDataInterval(double dStart, double dEnd, SCPKHistory& cpkHis);
	std::vector<double> Random(double dDim, double dMaxTol, double dMinTol, int nLen);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
