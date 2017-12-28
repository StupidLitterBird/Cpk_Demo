#include "stdafx.h"
#include "ChartFormSerie.h"
#include "ChartRectangleSubSerie.h"


using namespace std;

class CChartCtrl;


CChartRectangleSubSerie::CChartRectangleSubSerie(CChartCtrl* pParent)
	:CChartFormSerie(pParent), m_dAngel(0.0), m_Mid(EM_MID), m_nWide(0), m_nHeight(0)
	, m_bClick(false), m_nPenStyle(0), m_nLineWide(1)
{
	m_pt.x = 0;
	m_pt.y = 0;
	m_PenColor = RGB(0, 0, 0);
	m_pointStart.x = 1;
	m_pointStart.y = 1;
}


CChartRectangleSubSerie::~CChartRectangleSubSerie()
{
}



void CChartRectangleSubSerie::SetAngel(double dAngel)
{
	m_dAngel = dAngel;
	RefreshCtrl();
}

void CChartRectangleSubSerie::SetAngel(CPoint pt)
{
	CPoint ptM;
	ptM.x = m_pt.x + m_pointStart.x;
	ptM.y = m_pt.y + m_pointStart.y;
	double dAng = LintToAngel(ptM, pt);
	TRACE("%.5f\n", dAng);
	SetAngel(dAng);
}

void CChartRectangleSubSerie::SetRectangleWidth(int nLineWide)
{
	m_nLineWide = nLineWide;
	RefreshCtrl();
}


void CChartRectangleSubSerie::SetPenStyle(int NewStyle)
{
	m_nPenStyle = NewStyle;
	RefreshCtrl();
}

void CChartRectangleSubSerie::SetClick(bool bClick)
{
	m_bClick = bClick;
	RefreshCtrl();
}

void CChartRectangleSubSerie::SetMid(EMind md)
{
	m_Mid = md;
	RefreshCtrl();
}

void CChartRectangleSubSerie::SetWide(int nWide)
{
	m_nWide = nWide;
	RefreshCtrl();
}

void CChartRectangleSubSerie::SetHeight(int nHeight)
{
	m_nHeight = nHeight;
	RefreshCtrl();
}

void CChartRectangleSubSerie::SetPenColor(COLORREF color)
{
	m_PenColor = color;
	RefreshCtrl();
}

bool CChartRectangleSubSerie::PointInRect(CPoint pt)
{
	//还原原本点倍
 	CPoint inPt(pt.x, pt.y);
	CPoint centerPt(m_pt.x + m_pointStart.x, m_pt.y + m_pointStart.y);

	CPoint ptOld= GyratePoint(inPt, centerPt, -m_dAngel);

	CRect rect = GetNoAngelRect(m_Mid);
	if (PtInRect(&rect, ptOld))
	{
		return true;
	}
	else
	{
		return false;
	}
}

CRect CChartRectangleSubSerie::GetNoAngelRect(EMind eMid)
{
	CRect rtRes;
	switch (eMid)
	{
	case CChartRectangleSubSerie::EM_MID:
	{//中心点为基准
		rtRes.left = m_pointStart.x + m_pt.x - m_nWide / 2;
		rtRes.top = m_pointStart.y + m_pt.y - m_nHeight / 2;
		rtRes.right = m_pointStart.x + m_pt.x + m_nWide / 2;
		rtRes.bottom = m_pointStart.y + m_pt.y + m_nHeight / 2;
	}
	break;
	case CChartRectangleSubSerie::EM_LT:
	{//标准左上角为起点
		rtRes.left = m_pointStart.x + m_pt.x;
		rtRes.top = m_pointStart.y + m_pt.y;
		rtRes.right = m_pointStart.x + m_pt.x + m_nWide;
		rtRes.bottom = m_pointStart.y + m_pt.y + m_nHeight;
	}
	break;
	case CChartRectangleSubSerie::EM_TM:
	{
		rtRes.left = m_pointStart.x + m_pt.x - m_nWide / 2;
		rtRes.top = m_pointStart.y + m_pt.y;
		rtRes.right = m_pointStart.x + m_pt.x + m_nWide / 2;
		rtRes.bottom = m_pointStart.y + m_pt.y + m_nHeight;

	}
	break;
	case CChartRectangleSubSerie::EM_RT:
	{
		rtRes.left = m_pointStart.x + m_pt.x - m_nWide;
		rtRes.top = m_pointStart.y + m_pt.y;
		rtRes.right = m_pointStart.x + m_pt.x;
		rtRes.bottom = m_pointStart.y + m_pt.y + m_nHeight;
	}
	break;
	case CChartRectangleSubSerie::EM_LM:
	{
		rtRes.left = m_pointStart.x + m_pt.x;
		rtRes.top = m_pointStart.y + m_pt.y - m_nHeight / 2;
		rtRes.right = m_pointStart.x + m_pt.x + m_nWide;
		rtRes.bottom = m_pointStart.y + m_pt.y + m_nHeight / 2;
	}
	break;
	case CChartRectangleSubSerie::EM_LB:
	{
		rtRes.left = m_pointStart.x + m_pt.x;
		rtRes.top = m_pointStart.y + m_pt.y - m_nHeight;
		rtRes.right = m_pointStart.x + m_pt.x + m_nWide;
		rtRes.bottom = m_pointStart.y + m_pt.y;
	}
	break;
	case CChartRectangleSubSerie::EM_BM:
	{
		rtRes.left = m_pointStart.x + m_pt.x - m_nWide / 2;
		rtRes.top = m_pointStart.y + m_pt.y - m_nHeight;
		rtRes.right = m_pointStart.x + m_pt.x + m_nWide / 2;
		rtRes.bottom = m_pointStart.y + m_pt.y;
	}
	break;
	case CChartRectangleSubSerie::EM_RB:
	{
		rtRes.left = m_pointStart.x + m_pt.x - m_nWide;
		rtRes.top = m_pointStart.y + m_pt.y - m_nHeight;
		rtRes.right = m_pointStart.x + m_pt.x;
		rtRes.bottom = m_pointStart.y + m_pt.y;
	}
	break;
	case CChartRectangleSubSerie::EM_RM:
	{
		rtRes.left = m_pointStart.x + m_pt.x - m_nWide;
		rtRes.top = m_pointStart.y + m_pt.y - m_nHeight / 2;
		rtRes.right = m_pointStart.x + m_pt.x;
		rtRes.bottom = m_pointStart.y + m_pt.y + m_nHeight / 2;
	}
	break;
	default:
		break;
	}
	return rtRes;
}

void CChartRectangleSubSerie::Draw(CDC* pDC)
{
	if (!m_bIsVisible)
		return;
	if (!pDC->GetSafeHdc())
		return;

	//计算框的位置

	CPoint ptCenter(m_pointStart.x + m_pt.x, m_pointStart.y + m_pt.y);				//中心点
	CRect rectNoAngel = GetNoAngelRect(m_Mid);

	CPoint ptLT(rectNoAngel.left, rectNoAngel.top);
	CPoint ptRT(rectNoAngel.right, rectNoAngel.top);
	CPoint ptLB(rectNoAngel.left, rectNoAngel.bottom);
	CPoint ptRB(rectNoAngel.right, rectNoAngel.bottom);

	switch (m_Mid)
	{
	case CChartRectangleSubSerie::EM_MID:
	{//中心点为基准
		m_AngelRect.LT = GyratePoint(ptLT, ptCenter, m_dAngel);
		m_AngelRect.RT = GyratePoint(ptRT, ptCenter, m_dAngel);
		m_AngelRect.LB = GyratePoint(ptLB, ptCenter, m_dAngel);
		m_AngelRect.RB = GyratePoint(ptRB, ptCenter, m_dAngel);
	}
		break;
	case CChartRectangleSubSerie::EM_LT:
	{//标准左上角为起点
		m_AngelRect.LT = ptLT;
		m_AngelRect.RT = GyratePoint(ptRT, ptCenter, m_dAngel);
		m_AngelRect.LB = GyratePoint(ptLB, ptCenter, m_dAngel);
		m_AngelRect.RB = GyratePoint(ptRB, ptCenter, m_dAngel);
	}
		break;
	case CChartRectangleSubSerie::EM_TM:
	{
		m_AngelRect.LT = GyratePoint(ptLT, ptCenter, m_dAngel);
		m_AngelRect.RT = GyratePoint(ptRT, ptCenter, m_dAngel);
		m_AngelRect.LB = GyratePoint(ptLB, ptCenter, m_dAngel);
		m_AngelRect.RB = GyratePoint(ptRB, ptCenter, m_dAngel);
	}
		break;
	case CChartRectangleSubSerie::EM_RT:
	{
		m_AngelRect.LT = GyratePoint(ptLT, ptCenter, m_dAngel);
		m_AngelRect.RT = ptRT;
		m_AngelRect.LB = GyratePoint(ptLB, ptCenter, m_dAngel);
		m_AngelRect.RB = GyratePoint(ptRB, ptCenter, m_dAngel);
	}
		break;
	case CChartRectangleSubSerie::EM_LM:
	{
		m_AngelRect.LT = GyratePoint(ptLT, ptCenter, m_dAngel);
		m_AngelRect.RT = GyratePoint(ptRT, ptCenter, m_dAngel);
		m_AngelRect.LB = GyratePoint(ptLB, ptCenter, m_dAngel);
		m_AngelRect.RB = GyratePoint(ptRB, ptCenter, m_dAngel);
	}
		break;
	case CChartRectangleSubSerie::EM_LB:
	{
		m_AngelRect.LT = GyratePoint(ptLT, ptCenter, m_dAngel);
		m_AngelRect.RT = GyratePoint(ptRT, ptCenter, m_dAngel);
		m_AngelRect.LB = ptLB;
		m_AngelRect.RB = GyratePoint(ptRB, ptCenter, m_dAngel);
	}
		break;
	case CChartRectangleSubSerie::EM_BM:
	{
		m_AngelRect.LT = GyratePoint(ptLT, ptCenter, m_dAngel);
		m_AngelRect.RT = GyratePoint(ptRT, ptCenter, m_dAngel);
		m_AngelRect.LB = GyratePoint(ptLB, ptCenter, m_dAngel);
		m_AngelRect.RB = GyratePoint(ptRB, ptCenter, m_dAngel);
	}
		break;
	case CChartRectangleSubSerie::EM_RB:
	{
		m_AngelRect.LT = GyratePoint(ptLT, ptCenter, m_dAngel);
		m_AngelRect.RT = GyratePoint(ptRT, ptCenter, m_dAngel);
		m_AngelRect.LB = GyratePoint(ptLB, ptCenter, m_dAngel);
		m_AngelRect.RB = ptRB;
	}
		break;
	case CChartRectangleSubSerie::EM_RM:
	{
		m_AngelRect.LT = GyratePoint(ptLT, ptCenter, m_dAngel);
		m_AngelRect.RT = GyratePoint(ptRT, ptCenter, m_dAngel);
		m_AngelRect.LB = GyratePoint(ptLB, ptCenter, m_dAngel);
		m_AngelRect.RB = GyratePoint(ptRB, ptCenter, m_dAngel);
	}
		break;
	default:
		break;
	}
	//绘制选择框架后的状态
	if (m_bClick)
	{
		CPen pen;
		if (GetRotatiAreaMode())
			pen.CreatePen(PS_DOT, m_nLineWide, m_PenColor);
		else
			pen.CreatePen(m_nPenStyle, m_nLineWide, m_PenColor);
		CPen *pOldObject = pDC->SelectObject(&pen);

		pDC->MoveTo(m_AngelRect.LT);
		pDC->LineTo(m_AngelRect.RT);
		pDC->LineTo(m_AngelRect.RB);
		pDC->LineTo(m_AngelRect.LB);
		pDC->LineTo(m_AngelRect.LT);

		pDC->SelectObject(pOldObject);
		pen.DeleteObject();

		//画出中心点与

	}
	else
	{
		//绘制框
		CPen pen;
		pen.CreatePen(m_nPenStyle, m_nLineWide, m_PenColor);
		CPen *pOldObject = pDC->SelectObject(&pen);

		pDC->MoveTo(m_AngelRect.LT);
		pDC->LineTo(m_AngelRect.RT);
		pDC->LineTo(m_AngelRect.RB);
		pDC->LineTo(m_AngelRect.LB);
		pDC->LineTo(m_AngelRect.LT);

		pDC->SelectObject(pOldObject);
		pen.DeleteObject();
	}

	//绘制调整大小的状态
	if (m_bResize)
	{
		//计算4个角点的位置
		AngelRectangle rt[4];
		rt[0] = GetAngelRectangle(m_AngelRect.LT, 0.0);
		rt[1] = GetAngelRectangle(m_AngelRect.RT, 0.0);
		rt[2] = GetAngelRectangle(m_AngelRect.LB, 0.0);
		rt[3] = GetAngelRectangle(m_AngelRect.RB, 0.0);
		CPen pen2;
		pen2.CreatePen(m_nPenStyle, m_nLineWide, m_PenColor);
		
		CPen *pOldObject = pDC->SelectObject(&pen2);
		//画笔取空
		pDC->SelectStockObject(NULL_BRUSH);
		for (unsigned int iIndex = 0; iIndex < 4;iIndex++)
		{
			//填充白色为底
			CBrush br(RGB(255,255,255));
			CRgn rgn;
			CPoint arrpt[4];
			arrpt[0] = rt[iIndex].LT;
			arrpt[1] = rt[iIndex].RT;
			arrpt[2] = rt[iIndex].RB;
			arrpt[3] = rt[iIndex].LB;
			if (rgn.CreatePolygonRgn(arrpt, 4, ALTERNATE))
			{
				pDC->FillRgn(&rgn, &br);
			}
			//绘制区域
			pDC->MoveTo(arrpt[0]);
			pDC->LineTo(arrpt[1]);
			pDC->LineTo(arrpt[2]);
			pDC->LineTo(arrpt[3]);
			pDC->LineTo(arrpt[0]);
		}
		pen2.DeleteObject();
		//更新可供选择的角度
		m_rectTouchHorn[0] = GetRectangle(m_AngelRect.LT);
		m_rectTouchHorn[1] = GetRectangle(m_AngelRect.RT);
		m_rectTouchHorn[2] = GetRectangle(m_AngelRect.RB);
		m_rectTouchHorn[3] = GetRectangle(m_AngelRect.LB);

		//画出是否可以旋转
		if (m_bRotateArea)
		{
			//更新可供旋转的角度位置
			double dDis = Distance(ptCenter, m_AngelRect.LT, m_AngelRect.RT);
			CPoint cpCircle;
			cpCircle.y = ptCenter.y - (long)dDis - m_nRotationLen;
			cpCircle.x = ptCenter.x;
			//角度
			cpCircle = GyratePoint(cpCircle, ptCenter, m_dAngel);
		
			//画线至此点
			CPen penCenter;
			penCenter.CreatePen(PS_DOT, 1, m_PenColor);
			pDC->SelectObject(penCenter);
			pDC->MoveTo(ptCenter);
			pDC->LineTo(cpCircle);

			//实心圆
			CRect rectCir1;							//图形中心点
			rectCir1.left = ptCenter.x - 4;
			rectCir1.right = ptCenter.x + 4;
			rectCir1.top = ptCenter.y - 4;
			rectCir1.bottom = ptCenter.y + 4;
			//旋转区域
			m_rectRotateArea.left = cpCircle.x - 8;
			m_rectRotateArea.right = cpCircle.x + 8;
			m_rectRotateArea.top = cpCircle.y - 8;
			m_rectRotateArea.bottom = cpCircle.y + 8;
			CPen penCenter2;
			penCenter2.CreatePen(m_nPenStyle, 1, m_PenColor);
			pDC->SelectObject(&penCenter2);
			pDC->Ellipse(rectCir1);
			pDC->Ellipse(m_rectRotateArea);
			//画出圆中心
			pDC->SetPixel(cpCircle, m_PenColor);
			pDC->SetPixel(ptCenter, m_PenColor);
			pDC->SelectObject(pOldObject);
			penCenter.DeleteObject();
		}
		
	}
}


void CChartRectangleSubSerie::MoveTo(CPoint ptMove)
{
	m_pt.x = ptMove.x - m_pointStart.x;
	m_pt.y = ptMove.y - m_pointStart.y;
	RefreshCtrl();
}


// void CChartRectangleSubSerie::DrawLegend(CDC *pDC, const CRect& rectBitmap) const
// {
// 	if (m_strSerieName == _T(""))
// 		return;
// 
// 	//Draw line:
// 	LOGBRUSH lb;
// 	lb.lbStyle = BS_SOLID;
// 	lb.lbColor = m_SerieColor;
// 	CPen NewPen(PS_GEOMETRIC | m_nPenStyle, m_nLineWide, &lb);
// 	CPen* pOldPen = pDC->SelectObject(&NewPen);
// 	pDC->MoveTo(rectBitmap.left, rectBitmap.CenterPoint().y);
// 	pDC->LineTo(rectBitmap.right, rectBitmap.CenterPoint().y);
// 	pDC->SelectObject(pOldPen);
// 	DeleteObject(NewPen);
// }

CPoint CChartRectangleSubSerie::GyratePoint(const CPoint pt,const CPoint ptCenter,const double dAngel)
{
	DOUBLE dH = dAngel*PI / 180.0;
	DOUBLE dCos = cos(dH);
	DOUBLE dSin = sin(dH);

	CPoint ptRes;

	int i(pt.x), j(pt.y);
	DOUBLE OldX, OldY, NewX, NewY;
	OldX = ptCenter.x;
	OldY = ptCenter.y;
	NewX = OldX*dCos + OldY*dSin;
	NewY = OldY*dCos - OldX*dSin;

	ptRes.x = (int)(i*dCos + j*dSin + OldX - NewX);
	ptRes.y = (int)(j*dCos - i*dSin + OldY - NewY);
	return ptRes;
}

AngelRectangle CChartRectangleSubSerie::GetAngelRectangle(const CPoint ptCenter, const double dAngel, const int nLen)
{
	int nL = (nLen + 1) / 2 * 2;
	CPoint center = ptCenter;
	AngelRectangle rt;
	CPoint ptLT(center.x - nL / 2, center.y - nL / 2);
	CPoint ptRT(center.x + nL / 2, center.y - nL / 2);
	CPoint ptLB(center.x - nL / 2, center.y + nL / 2);
	CPoint ptRB(center.x + nL / 2, center.y + nL / 2);

	rt.LT = GyratePoint(ptLT, center, dAngel);
	rt.RT = GyratePoint(ptRT, center, dAngel);
	rt.LB = GyratePoint(ptLB, center, dAngel);
	rt.RB = GyratePoint(ptRB, center, dAngel);

	return rt;
}


CRect CChartRectangleSubSerie::GetRectangle(const CPoint ptCenter, const int nLen)
{
	CRect rectGet;
	rectGet.left = ptCenter.x - nLen / 2;
	rectGet.right = rectGet.left + nLen;
	rectGet.top = ptCenter.y - nLen / 2;
	rectGet.bottom = ptCenter.y + nLen;
	return rectGet;
}

CChartFormSerie::enAdjustTheArea CChartRectangleSubSerie::PointInAdjustTheArea(CPoint pt)
{
	CChartFormSerie::enAdjustTheArea aaRes = ADJUST_NONE;
	for (unsigned int iIndex = 0; iIndex < 4;iIndex++)
	{
		if (PtInRect(m_rectTouchHorn[iIndex], pt))
		{
			aaRes = (CChartFormSerie::enAdjustTheArea)(iIndex + 1);
			break;
		}
	}
	return aaRes;
}

double CChartRectangleSubSerie::Distance(CPoint pt, CPoint PtL1, CPoint PtL2)
{
	DOUBLE X = pt.x;
	DOUBLE Y = pt.y;
	DOUBLE A = PtL1.y - PtL2.y;
	DOUBLE B = PtL2.x - PtL1.x;
	DOUBLE C = PtL1.x * PtL2.y - PtL1.y * PtL2.x;
	return fabs(A*X + B*Y + C) / sqrt(A*A + B*B);
}