/*
*
*	CChartFormSerie.h
*
*	Written by 梁颖昌 (wlyc1@163.com)
*
*
*
*	This code may be used for any non-commercial and commercial purposes in a compiled form.
*	The code may be redistributed as long as it remains unmodified and providing that the
*	author name and this disclaimer remain intact. The sources can be modified WITH the author
*	consent only.
*
*	This code is provided without any garanties. I cannot be held responsible for the damage or
*	the loss of time it causes. Use it at your own risks
*
*	An e-mail to notify me that you are using this code is appreciated also.
*

*	此代码可能以编译的形式用于任何非商业和商业目的。
*	代码可以重新分发，只要它保持未修改并且保持作者姓名和此免责声明完整。
*	只能使用作者同意来修改源。
*	此代码没有任何保证。 我不能对因此造成的损失或损失负责。 使用它
*	你自己的风险一封电子邮件通知我，你正在使用这段代码也赞赏。
*
*/


#define PI 3.1415926535898

#pragma once
//#include "ChartRectangleSerie.h"
class CChartRectangleSubSerie;
class CChartCtrl;

class CChartFormSerie
{
	friend CChartRectangleSubSerie;
	friend CChartCtrl;
public:
	CChartFormSerie(CChartCtrl* pParent);
	virtual ~CChartFormSerie();

	enum enAdjustTheArea
	{
		ADJUST_NONE = 0,
		ADJUST_LT,
		ADJUST_RT,
		ADJUST_RB,
		ADJUST_LB,
	};


	//设置图形为可移动
	void SetMove(bool bMove){ m_bMove = bMove; }
	//取得图形是否可移动
	bool GetMove(){ return m_bMove; }
	//移动图形
	virtual void MoveTo(CPoint ptMove) = 0;
	//设置是否可以改变大小
	void Resize(bool bCanResize){ m_bCanResize = bCanResize; }
	bool CanResize(){ return m_bCanResize; }

	//设置是否可以旋转
	void SetRotateArea(bool bCan);

private:
	//刷新控件
	void RefreshCtrl();
	//绘图
	virtual void Draw(CDC* pDC) = 0;
	//取得图形系列ID
	int GetSerieId(){ return m_nFormId; }
	//指定点坐标是否在图形区域内
	virtual bool PointInRect(CPoint pt) = 0;
	//指点点坐标是否在调整大小区域
	virtual enAdjustTheArea PointInAdjustTheArea(CPoint pt) = 0;
	//设置图形为点击状态
	virtual void SetClick(bool bClick) = 0;
	//取得图形点击状态
	virtual bool GetClicked() = 0;
	//取得图形的中心点
	virtual CPoint GetMoveMidPoint() = 0;
	//设置移动前，图形中心的 鼠标点击位置。
	void SetMouseOrgin(CPoint pt){ m_ptMouseMovePoint = pt; }
	//记录点击鼠标时的图形中心点
	void RecordLocMidPt()
	{
		m_ptMovePoint = GetMoveMidPoint();
	};
	//取得移动前鼠标点击的位置
	CPoint GetMouseOrgin(){ return m_ptMouseMovePoint; }
	CPoint GetMoveOrgin(){ return m_ptMovePoint; }
	//设置是否显示改变大小的状态
	void SetResize(bool bResize);
	//取得是图形是否可以旋转
	bool GetRotateArea(){ return m_bRotateArea; }
	//设置旋转角度
	virtual void SetAngel(double dAngel)=0;
	//根据点位旋转角度
	virtual void SetAngel(CPoint pt)=0;
	//设置旋转模式
	void SetRotatiAreaMode(bool bEnabled = true);
	//查询是否旋转
	bool GetRotatiAreaMode(){ return m_bRotatiAreaMode; }
	//设置旋转修正
	void SetRotatiRevise(bool bEnabled){ m_bRotatiRevise = bEnabled; }
private:
	//tools
	double LintToAngel(CPoint pt1, CPoint pt2);
private:
	//一个固定分配的ID
	static unsigned	m_uNextFormId;
	//形状ID
	unsigned int	m_nFormId;
	//是否可见
	bool			m_bIsVisible;
	//是否启用阴影
	bool			m_bShadow;
	//阴影大小
	int				m_iShadowDepth;
	//阴影颜色
	COLORREF		m_ShadowColor;
	//是否可以移动
	bool			m_bMove;
	//是否可以旋转
	bool			m_bRotateArea;
	//是否调整大小状态
	bool			m_bResize;
	//能否调整大小
	bool			m_bCanResize;
	//记录移动的中心点
	CPoint			m_ptMouseMovePoint;
	//移动前记录的实际位置（不包括偏移量）
	CPoint			m_ptMovePoint;

	//控件操作
	CChartCtrl* m_pParentCtrl;

	//可供鼠标旋转的区域
	CRect			m_rectRotateArea;
	//旋转位置长度
	int m_nRotationLen;
	//旋转状态
	bool m_bRotatiAreaMode;
	//旋转角度修正
	bool m_bRotatiRevise;
};

