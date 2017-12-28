#if !defined(__CPKMOUSELISTENER_H__)
#define __CPKMOUSELISTENER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChartXYSerie.h"
#include "ChartPointsSerie.h"
#include "ChartSeriesMouseListener.h"

#define CCHART_MSG_MOUSE_CLICK	(WM_USER+1017)

class CCustomMouseListener : public CChartMouseListener
{
public:
	CCustomMouseListener(CWnd *hWnd)
	{
		m_Wnd=hWnd;
	}
	void OnMouseEventAxis(MouseEvent mouseEvent, CPoint point,
		CChartAxis* pAxisClicked)
	{
		if (mouseEvent == CChartMouseListener::LButtonDoubleClick)
		{

		}
	}

	void OnMouseEventLegend(MouseEvent mouseEvent, CPoint point)
	{
		if (mouseEvent == CChartMouseListener::LButtonDoubleClick)
		{

		}
	}

	void OnMouseEventPlotArea(MouseEvent mouseEvent, CPoint point)
	{
		if (mouseEvent == CChartMouseListener::LButtonDown)
		{
//			::SendMessageA(m_Wnd->GetSafeHwnd(),CCHART_MSG_MOUSE_CLICK,(WPARAM)point.x,(LPARAM)point.y);
			TRACE("%d,%d", point.x, point.y);
		}
	}
private:
	CWnd* m_Wnd;
};


#endif