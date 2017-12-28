#include "stdafx.h"
#include "ChartFormSerie.h"
#include "ChartCtrl.h"

unsigned int CChartFormSerie::m_uNextFormId;

CChartFormSerie::CChartFormSerie(CChartCtrl* pParent)
	:m_pParentCtrl(pParent), m_bIsVisible(true), m_bShadow(false), m_iShadowDepth(3), m_bMove(true), m_bResize(false)
	, m_bCanResize(false), m_nRotationLen(20), m_bRotatiAreaMode(false), m_bRotatiRevise(true)
{
	m_nFormId = m_uNextFormId;
	m_uNextFormId++;
	m_ptMouseMovePoint = CPoint(0, 0);
	m_ptMovePoint = CPoint(0, 0);
	m_rectRotateArea = CRect(0, 0, 0, 0);
}


CChartFormSerie::~CChartFormSerie()
{

}


void CChartFormSerie::SetResize(bool bResize)
{
	if (m_bCanResize)
		m_bResize = bResize;
	else
		m_bResize = false;
	RefreshCtrl();
}

void CChartFormSerie::RefreshCtrl()
{
	m_pParentCtrl->RefreshCtrl(); 
}

void CChartFormSerie::SetRotateArea(bool bCan)
{
	m_bRotateArea = bCan;
}


double CChartFormSerie::LintToAngel(CPoint pt1, CPoint pt2)
{
	double x1, x2, y1, y2;
	x1 = (double)pt1.x;
	x2 = (double)pt2.x;
	y1 = (double)pt1.y;
	y2 = (double)pt2.y;

	if (fabs(x1 - x2) < 0.0000001 && fabs(y1 - y2) < 0.0000001)
	{
		//AfxMessageBox("求直线角度时，发现描述直线的两点重复！");
		return 0;
	}
	DOUBLE k(0);
	DOUBLE angular(0.0);
	if (fabs(x1 - x2) > 0.0000001)
	{
		k = (y2 - y1) / (x2 - x1);
		if (k<-0.0000001)
		{
			if (y2>y1)
				angular = -atan(k) + PI;
			else
				angular = -atan(k);
		}
		else if (k > 0.0000001)
		{
			if (y2 > y1)
				angular = 2.0*PI - atan(k);
			else
				angular = PI - atan(k);
		}
		else
		{
			// y1==y2时
			if (x1 > x2)
				angular = PI;
			else
				angular = 0;
		}
	}
	else
	{
		if (y2 > y1)
			angular = PI / 2.0*3.0;
		else
			angular = PI / 2.0;
	}
	angular = angular*180.0 / PI;
	if (angular > 90.0)
	{
		angular = angular - 90.0;
	}
	else
	{
		angular +=270.0;
	}
	//旋转角度归整
	if (m_bRotatiRevise)
	{
		for (int i = 0; i < 360; i += 45)
		{
			if (angular > i)
			{
				if (angular - 3.0 < i)
				{
					angular = (double)i;
					break;
				}
			}
			else
			{
				if (angular + 3.0 > i)
				{
					angular = (double)i;
					break;
				}
			}
		}
	}
	return angular;
}

void CChartFormSerie::SetRotatiAreaMode(bool bEnabled)
{
	m_bRotatiAreaMode = bEnabled;
	RefreshCtrl();
}