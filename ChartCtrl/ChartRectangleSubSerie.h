/*
*
*	ChartRectangleSerie.h
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

#pragma once

#include "ChartFormSerie.h"
#include <list>

typedef struct _tagAngelRectangle
{
	CPoint LT;
	CPoint RT;
	CPoint LB;
	CPoint RB;

public:
	_tagAngelRectangle()
	{
		LT = CPoint(0, 0);
		RT = CPoint(0, 0);
		LB = CPoint(0, 0);
		RB = CPoint(0, 0);
	}
}AngelRectangle;

class CChartRectangleSubSerie
	:public CChartFormSerie
{
public:
	CChartRectangleSubSerie(CChartCtrl* pParent);
	virtual ~CChartRectangleSubSerie();

	//线条形状
	enum ERectangleStyle
	{
		NONE=0,
	};
	enum EMind
	{
		EM_MID=0,
		EM_LT,		//LeftTop
		EM_TM,		//TopMid
		EM_RT,		//RightTop
		EM_LM,		//LeftMid
		EM_LB,		//LeftBottom
		EM_BM,		//BottonMid
		EM_RB,		//RightBottom
		EM_RM,		//RightMid
	};
	//设置旋转角度
	virtual void SetAngel(double dAngel);
	//根据点位旋转角度(中心点与附加点)
	virtual void SetAngel(CPoint pt);
	//获得角度
	double GetAngel(){ return m_dAngel; }
	//设置矩形线宽
	void SetRectangleWidth(int nLineWide);
	//取得矩形线宽
	int GetRectangleWidth(){ return m_nLineWide; }
	//取得线样色
	int  GetPenStyle() const { return m_nPenStyle; }
	//设置线条样式
	void SetPenStyle(int NewStyle);
	//设置是否选中
	virtual void SetClick(bool bClick);
	//取得是否被选中
	virtual bool GetClicked(){ return m_bClick; }
	//设置中心点
	void SetMid(EMind md);
	//设置长与宽
	void SetWide(int nWide);
	void SetHeight(int nHeight);

	//设置笔头色
	void SetPenColor(COLORREF color);

	//移动到位置(自动计算偏移量)
	virtual void MoveTo(CPoint ptMove);
	//判断点是否在矩形范围内
	virtual bool PointInRect(CPoint pt);
	virtual CChartFormSerie::enAdjustTheArea PointInAdjustTheArea(CPoint pt);
private:
	typedef std::list<CChartRectangleSubSerie*> TRectangleSeriesList;
	void Draw(CDC* pDC);
	//void DrawLegend(CDC* pDC, const CRect& rectBitmap) const;
// private:
// 	static int m_iInterSpace;
// 	static TRectangleSeriesList m_lstRectangleSeries;
// 	mutable TRectangleSeriesList m_lstStackedSeries;
// 	bool m_bStacked;
	virtual CPoint GetMoveMidPoint()
	{
		CPoint ptRec;
		ptRec.x =m_pt.x+ m_pointStart.x;
		ptRec.y = m_pt.y + m_pointStart.y;
		return ptRec;
	}
private:
	//矩形宽
	int m_nWide;
	//矩形高
	int m_nHeight;
	//图形意义上的中心点
	CPoint m_pt;
	//画笔颜色
	COLORREF m_PenColor;
	//带角度的画线区域
	AngelRectangle m_AngelRect;
	CRect m_rectTouchHorn[4];		//移动的定位角(共4个)

protected:
	//旋转角度
	double m_dAngel;
	//线宽
	int m_nLineWide;
	//中心点位置
	EMind m_Mid;
	//PenStyle
	int m_nPenStyle;
	//是否被选中
	bool m_bClick;
	//起始坐标点
	CPoint m_pointStart;
protected:
	//旋转点算法
	CPoint GyratePoint(const CPoint pt, const CPoint ptCenter, const double dAngel);
	//取得带旋转的矩形区域
	AngelRectangle GetAngelRectangle(const CPoint ptCenter, const double dAngel, const int nLen = 6);
	//取得矩形区域，长度为nLen
	CRect GetRectangle(const CPoint ptCenter, const int nLen = 6);
	//点到直线的距离
	double Distance(CPoint pt, CPoint PtL1, CPoint PtL2);
	//获取未带角度的区域点
	CRect GetNoAngelRect(EMind eMid);
};

