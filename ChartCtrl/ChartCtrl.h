/*
 *
 *	ChartCtrl.h
 *
 *	Written by C�dric Moonen (cedric_moonen@hotmail.com)
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
 *
 */


#pragma once

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ChartSerie.h"
#include "ChartAxisSerie.h"
#include "ChartGridSerie.h"
#include "ChartLegend.h"
#include "ChartTitle.h"
#include "ChartGradient.h"
#include "ChartCursor.h"
#include "ChartMouseListener.h"
#include "ChartStandardAxisSerie.h"
#include "ChartLogarithmicAxis.h"
#include "ChartDateTimeAxis.h"

#include "ChartCrossHairCursor.h"
#include "ChartDragLineCursor.h"
//20170109 ChartRectangle
#include "ChartFormSerie.h"
#include "ChartRectangleSubSerie.h"
//Custon Axis
#include "CChartCustomLabelStandardAxis.h"
	
#include <map>


class CChartStandardAxis;
class CChartLogarithmicAxis;
class CChartDateTimeAxis;
class CChartCrossHairCursor;
class CChartDragLineCursor;

class CChartPointsSerie;
class CChartLineSerie;
class CChartFormSerie;
class CChartRectangleSubSerie;
class CChartSurfaceSerie;
class CChartBarSerie;
class CChartCandlestickSerie;
class CChartGanttSerie;

/////////////////////////////////////////////////////////////////////////////
// CChartCtrl window

//! The main chart control class.
/**

**/
class CChartCtrl : public CWnd
{

public:
	//! Retrieves de device context.
	//�����豸�����ġ�
	/**
		This function is used for internal purposes only.
		//�˺����������ڲ�Ŀ��
	**/
	CDC* GetDC();
	//! Retrieves the plotting rectangle.
	//�������ƾ��Ρ�
	CRect GetPlottingRect()  const { return m_PlottingRect; }

	//! Returns a pointer to the legend object.
	//����ָ��ͼ�������ָ�롣
	CChartLegend* GetLegend() const  { return m_pLegend; }
	//! Returns a pointer to the title object.
	//����ָ���������ָ�롣
	CChartTitle*  GetTitle()  const  { return m_pTitles; }

	//! An enumeration of the different axis positions.
	//��ͬ��λ�õ�ö�١�
	enum EAxisPos
	{
		LeftAxis = 0,
		BottomAxis,
		RightAxis,
		TopAxis
	};

	//! Create and attach a standard axis to the control.
	//������׼�Ტ���丽�ӵ��ؼ���
	/**
		@param axisPos
			The position of the axis. 
		@return The created standard axis.
	**/
	CChartStandardAxisSerie* CreateStandardAxis(EAxisPos axisPos);
	//! Create and attach a logarithmic axis to the control.
	//��������һ�����������ӵ��ؼ���
	/**
		@param axisPos
			The position of the axis. 
		@return The created logarithmic axis.
	**/

	//! Create Custom Axis Created by ��ӱ�� mail to:wlyc1@163.com
	/**
		@param axisPos
			The position of the axis.
		@param bCustom
			If custom,Create a CustomAxis.
		@return The created Custom axis.
	**/
	CChartCustomLabelStandardAxis* CreateStandardAxis(EAxisPos axisPos,bool bCustom);
	CChartLogarithmicAxis* CreateLogarithmicAxis(EAxisPos axisPos);
	//! Create and attach a date/time axis to the control.
	//��������������/ʱ���ᵽ�ؼ���
	/**
		@param axisPos
			The position of the axis. 
		@return The created date/time axis.
	**/
	CChartDateTimeAxis* CreateDateTimeAxis(EAxisPos axisPos);
	//! Attach a custom axis to the control.
	//���ḽ�ӵ��ؼ���
	/**
		This function takes ownership of the axis pointer, so you 
		must not destroy it. If the axis is alread attached to a
		chart control (even this one), the function will fail with 
		an assertion. This function should be used only when you want
		to provide a custom axis to the control, otherwise you should
		use the AttachStandardAxis, AttachLogarithmicAxis and 
		AttachDateTimeAxis instead.
		@param pAxis
			The axis to attach to the control.
		@param axisPos
			The position of the axis. This value can be:
			- LeftAxis
			- BottomAxis
			- RightAxis
			- TopAxis
	**/
	void AttachCustomAxis(CChartAxisSerie* pAxis, EAxisPos axisPos);
	
	//! Attach Custom Axis Created by ��ӱ�� mail to:wlyc1@163.com
	//���Զ����ḽ�ӵ��ؼ���
	/**
		@param pAxis
			The axis to attach to the control.
		@param axisPos
			The position of the axis. This value can be:
			- LeftAxis
			- BottomAxis
			- RightAxis
			- TopAxis
	**/
	void AttachCustomAxis(CChartCustomLabelStandardAxis *pAxis, EAxisPos axisPos);

	//! Create and attach a point series to the control
	//������ϵ�в����丽�ӵ��ؼ�
	/**
		@param bSecondaryHorizAxis
			Specifies if the horizontal axis is the secondary axis or not. 
		@param bSecondaryVertAxis
			Specifies if the vertical axis is the secondary axis or not. 
		@return The created chart point series.
		@remark The function will assert if the associated axes are not attached 
		to the control.
		@see AttachCustomSerie for more info about the parameters of the function.
	**/
	CChartPointsSerie* CreatePointsSerie(bool bSecondaryHorizAxis=false, bool bSecondaryVertAxis=false);
	//! Create and attach a line series to the control
	//������ϵ�в����丽�ӵ��ؼ�
	/**
		The function will assert if the associated axes are not attached 
		to the control.
		�ù��ܽ�ȷ��������Ƿ�δ���ӵ���������
		@param bSecondaryHorizAxis
			Specifies if the horizontal axis is the secondary axis or not. 
		@param bSecondaryVertAxis
			Specifies if the vertical axis is the secondary axis or not. 
		@return The created chart line series.
		@remark The function will assert if the associated axes are not attached 
		to the control.
		@see AttachCustomSerie for more info about the parameters of the function.
	**/
	CChartLineSerie* CreateLineSerie(bool bSecondaryHorizAxis=false, bool bSecondaryVertAxis=false);
	//! Create and attach a surface series to the control
	//�������ϵ�в����丽�ӵ��ؼ�
	/**
		The function will assert if the associated axes are not attached 
		to the control.
		@param bSecondaryHorizAxis
			Specifies if the horizontal axis is the secondary axis or not. 
		@param bSecondaryVertAxis
			Specifies if the vertical axis is the secondary axis or not. 
		@return The created chart surface series.
		@remark The function will assert if the associated axes are not attached 
		to the control.
		@see AttachCustomSerie for more info about the parameters of the function.
	**/
	CChartSurfaceSerie* CreateSurfaceSerie(bool bSecondaryHorizAxis=false, bool bSecondaryVertAxis=false);
	//! Create and attach a bar series to the control
	//����������״barϵ�и��ӵ��ؼ�
	/**
		@param bSecondaryHorizAxis
			Specifies if the horizontal axis is the secondary axis or not. 
		@param bSecondaryVertAxis
			Specifies if the vertical axis is the secondary axis or not. 
		@return The created chart bar series.
		@remark The function will assert if the associated axes are not attached 
		to the control.
		@see AttachCustomSerie for more info about the parameters of the function.
	**/
	CChartBarSerie* CreateBarSerie(bool bSecondaryHorizAxis=false, bool bSecondaryVertAxis=false,bool bZeroOffset=false);
	//! Create and attach a candlestick series to the control
	//����������ϵ�в����丽�ӵ��ؼ�
	/**
		@param bSecondaryHorizAxis
			Specifies if the horizontal axis is the secondary axis or not. 
		@param bSecondaryVertAxis
			Specifies if the vertical axis is the secondary axis or not. 
		@return The created chart candlestick series.
		@remark The function will assert if the associated axes are not attached 
		to the control.
		@see AttachCustomSerie for more info about the parameters of the function.
	**/
	CChartCandlestickSerie* CreateCandlestickSerie(bool bSecondaryHorizAxis=false, bool bSecondaryVertAxis=false);
	//! Create and attach a gantt series to the control
	//��������ϵ�в����丽�ӵ��ؼ�
	/**
		@param bSecondaryHorizAxis
			Specifies if the horizontal axis is the secondary axis or not. 
		@param bSecondaryVertAxis
			Specifies if the vertical axis is the secondary axis or not. 
		@return The created chart gantt series.
		@remark The function will assert if the associated axes are not attached 
		to the control.
		@see AttachCustomSerie for more info about the parameters of the function.
	**/
	CChartGanttSerie* CreateGanttSerie(bool bSecondaryHorizAxis=false, bool bSecondaryVertAxis=false);


	CChartRectangleSubSerie* CreateRectangleSerie();

	void AttachCustomAxis(CChartFormSerie* pForm);


	typedef std::map<unsigned, CChartFormSerie*> TFormSeriesMap;
	//! Map containing all the series added to the chart.
	//������ӵ�ͼ���е�����ϵ�еĵ�ͼ��
	TFormSeriesMap m_mapFormSeries;

	//! Attaches a custom series to the chart
	//���Զ���ϵ�и��ӵ�ͼ��
	/**
		You should only use this function if you want to attach a custom series
		to the control. Otherwise, you should use the CreateXXXSerie helper functions.
		The function will assert if the associated axes are not attached 
		to the control.
		@param pNewSeries
			The new series to be added. The control will take ownership of 
			the pointer, so dont't delete it yourself.
		@param bSecondaryHorizAxis
			Specifies if the associated horizontal axis is secondary or not. 
			If this value is false, the associated horizontal axis is the 
			bottom axis, otherwise it is the top axis.
		@param bSecondaryVertAxis
			Specifies if the associated vertical axis is secondary or not. 
			If this value is false, the associated vertical axis is the 
			left axis, otherwise it is the right axis.
	**/
	
	void AttachCustomSerie(CChartSerie* pNewSeries, bool bSecondaryHorizAxis=false, bool bSecondaryVertAxis=false);
	//! Retrieves a specific series from the chart
	//��ͼ���м����ض�ϵ��
	/**
		@param uSerieId
			The Id of the series to retrieve
		@return The series or NULL if uSerieId is not attributed.
	**/
	CChartSerie* GetSerie(unsigned uSerieId) const;
	//! Removes a specific series from the chart
	//��ͼ����ɾ���ض�ϵ��
	/**
		@param uSerieId
			The Id of the series to be removed.
	**/
	void RemoveSerie(unsigned uSerieId);
	//! Removes all the series from the chart
	//��ͼ����ɾ������ϵ��
	void RemoveAllSeries();
	//! Returns the number of series in the chart
	//����ͼ���е�ϵ������
	size_t GetSeriesCount() const;

	//! Create and attach a cross-hair cursor to the control
	//����ʮ�ֹ�겢���丽�ӵ��ؼ�
	/**
		A cross-hair cursor display a cross on the control and move accordingly
		to the mouse. It is attached to an horizontal and a vertical axis.
		@param bSecondaryHorizAxis
			Specifies if the horizontal axis is the secondary axis or not. 
		@param bSecondaryVertAxis
			Specifies if the vertical axis is the secondary axis or not. 
		@return The created cross-hair cursor.
		@remark The function will assert if the associated axes are not attached 
		to the control.
	**/
	CChartCrossHairCursor* CreateCrossHairCursor(bool bSecondaryHorizAxis=false, bool bSecondaryVertAxis=false);
	//! Create and attach a drag-line cursor to the control
	//�����϶��߹�겢���丽�ӵ��ؼ�
	/**
		A drag-line cursor is a simple line (horizontal or vertical) that can be
		dragged with the mouse by clicking on it. It is attached to a specific axis.
		�϶������һ���򵥵��ߣ�ˮƽ��ֱ��������ͨ������������϶���ꡣ �����ӵ��ض��ᡣ
		@param relatedAxis
			The axis position to which the cursor is attached to.
		@return The created drag-line cursor.
		@remark The function will assert if the associated axis is not attached 
		to the control.
	**/
	CChartDragLineCursor* CreateDragLineCursor(EAxisPos relatedAxis);
	//! Attach a custom cursor to the control
	//���Զ����긽�ӵ��ؼ�
	/**
		You should only use this function if you want to attach a custom cursor
		to the control. Otherwise, you should use the CreateXXXCursor helper functions.
		���Ҫ���Զ����긽�ӵ��ؼ�����ֻ��ʹ�ô˺����� ����Ӧ��ʹ��CreateXXXCursor����������
		@param pCursor
			The custom cursor to be attached to the control.
	**/
	void AttachCustomCursor(CChartCursor* pCursor);
	//! Removes a cursor with a specific Id from the control.
	//�ӿؼ���ɾ�������ض���ʶ���αꡣ
	/**
		The cursor Id can be retrieved on through the CChartCursor::GetCursorId function.
		����ͨ��CChartCursor :: GetCursorId���������α�Id��
		@param cursorId
			The Id of the cursor to remove from the control.
	**/
	void RemoveCursor(unsigned cursorId);

	//! Shows/hides the mouse cursor when it is over the plotting area.
	//�ڻ�ͼ�����Ϸ���ʾ/��������ꡣ
	void ShowMouseCursor(bool bShow);

	CChartAxisSerie* GetBottomAxis() const;
	CChartAxisSerie* GetLeftAxis() const;
	CChartAxisSerie* GetTopAxis() const;
	CChartAxisSerie* GetRightAxis() const;
	//! Returns a specific axis attached to the control
	//���ظ��ӵ��ؼ����ض���
	/**
		If the specified axis does not exist, NULL is returned.
		@param axisPos
			The axis position (left, bottom, right or top).
	**/
	CChartAxisSerie* GetAxis(EAxisPos axisPos) const
	{
		return m_pAxes[axisPos];
	}

	//! Returns the type of the edge used as border.
	//���������߿�ıߵ����͡�
	UINT GetEdgeType() const        { return EdgeType;    }
	//! Sets the edge type.
	//���ñ�Ե����
	/**
		@param NewEdge 
			The type of the edge. See the DrawEdge function in MSDN for 
			a list of the different types.
	**/
	void SetEdgeType(UINT NewEdge)  
	{ 
		EdgeType = NewEdge; 
		RefreshCtrl();
	}

	//! Returns the background color
	//���ر�����ɫ
	COLORREF GetBackColor() const			{ return m_BackColor;   }
	//! Sets the background color.
	//���ñ�����ɫ��
	void SetBackColor(COLORREF NewCol)		
	{ 
		m_BackColor = NewCol;  
		m_bBackGradient = false; 
		RefreshCtrl();
	}
	//! Returns the color of the plotting area's border 
	//���ػ�������߿����ɫ
	COLORREF GetBorderColor() const			{ return m_BorderColor;   }
	//! Sets the color of the plotting area's border 
	//���û�ͼ����߿����ɫ
	void SetBorderColor(COLORREF NewCol)	{ m_BorderColor = NewCol;	RefreshCtrl(); }
	//! Returns the color of the zoom rectangle
	//�������ž��ε���ɫ
	COLORREF GetZoomRectColor() const		{ return m_ZoomRectColor;   }
	//! Sets the color of the zoom rectangle
	//�������ž��ε���ɫ
	void SetZoomRectColor(COLORREF NewCol)	{ m_ZoomRectColor = NewCol; RefreshCtrl(); }
	//! Sets a gradient background
	//���ý��䱳��
	/**
		@param Col1
			The first gradient color
		@param Col2
			The second gradient color
		@param GradientType
			The type of gradient used from Col1 to Col2. It can take the following values:
				- gtHorizontal: a simple left-to-right gradient, from Col1 to Col2.
				- gtVertical: a simple top-to-bottom gradient, from Col1 to Col2. 
				- gtHorizontalDouble: a left-to-middle-to-right gradient, with Col2 in the middle. 
				- gtVerticalDouble: a top-to-middle-to-bottom gradient, with Col2 in the middle. 
	**/
	void SetBackGradient(COLORREF Col1, COLORREF Col2, EGradientType GradientType);

	//! Enables/disables the pan feature
	//����/����ƽ�ƹ���
	void SetPanEnabled(bool bEnabled)  { m_bPanEnabled = bEnabled;  }
	//! Returns true if the pan feature is enabled
	//�������ƽ�ƹ��ܣ��򷵻�true
	bool GetPanEnabled() const		   { return m_bPanEnabled;	    }
	//! Enables/disables the zoom feature
	//����/�������Ź���
	void SetZoomEnabled(bool bEnabled) { m_bZoomEnabled = bEnabled; }
	//! Returns true if the zoom feature is enabled
	//����������Ź��ܣ��򷵻�true
	bool GetZoomEnabled() const		   { return m_bZoomEnabled;	    }
	//! Undo all pan and zoom operations that were done on the chart
	//������ͼ������ɵ�����ƽ�ƺ����Ų���
	void UndoPanZoom();

	//! Forces a refresh of the control.
	//ǿ��ˢ�¿ؼ���
	/**
		This function is used for internal purposes.
		�˺��������ڲ�Ŀ�ġ�
	**/
	void RefreshCtrl();
	//! Enables/disables the refresh of the control
	//����/���ÿؼ���ˢ��
	/**
		This function is used when several settings have to be changed at the same 
		time on the control. This way we can avoid refreshing the control when it 
		is not needed.
		����Ҫ�ڿ�������ͬʱ���Ķ������ʱʹ�ô˹��ܡ� �������ǿ��Ա����ڲ���Ҫʱˢ�¿ؼ���
		@param bEnable
			false to disable the refresh and true to re-enable the refresh.
	**/
	void EnableRefresh(bool bEnable);
	//! Creates the control dynamically.
	//��̬��������(��)��
	/**
		@param pParentWnd 
			Parent window of the control
		@param rect 
			Position of the control
		@param nID
			ID of the control
		@param dwStyle
			Style of the control
	**/
	int Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle=WS_VISIBLE);
	
	//! Helper function to convert a date to a double value
	//��������������ת��Ϊ˫����ֵ
	static double DateToValue(const COleDateTime& Date);
	//! Helper function to convert a double value to a date
	//����������doubleֵת��Ϊ����
	static COleDateTime ValueToDate(double Value);

	//! Print the chart
	//��ӡͼ��
	/**
		@param strTitle
			The title of the print document.
		@param pPrntDialog
			A pointer to a CPrintDialog. 
			If NULL is passed, the default print dialog will be displayed.
	**/
    virtual void Print(const TChartString& strTitle, CPrintDialog* pPrntDialog = NULL);


#if _MFC_VER > 0x0600
	//! Saves the chart to an image file
	//��ͼ���浽ͼ���ļ�
	/**
		This function is not available for VC6 and earlier.
		�˹��ܲ�������VC6�͸���汾��
		@param strFilename
			The name of the file in which to save the image.
		@param rect
			The size of the image. If an empty rectangle is provided, the
			size of the chart on screen will be used (this results in an identical
			image as what is seen on the screen).
		@param nBPP
			The numbers of bits per pixel in the bitmap. Usually 4, 8, 16, 24, or 32. 
		@param guidFileType
			The file type to save the image as. See the CImage::Save in MSDN
			for more information.
	**/
	void SaveAsImage(const TChartString& strFilename, const CRect& rect, 
			int nBPP, REFGUID guidFileType= GUID_NULL);
#endif

	//! Default constructor
	//Ĭ�Ϲ��캯��
    CChartCtrl();	
	//! Default destructor
	//Ĭ���͹�����
    virtual ~CChartCtrl();

	//! Register a mouse listener with the control.
	//ʹ��ע��ؼ�����������
	/**
		This listener will be notified each time a mouse event occurs on the control.
		ÿ���ڿؼ��Ϸ�������¼�ʱ������֪ͨ����������
		@param pMouseListener
			The mouse listener to register with this control.
	**/
	void RegisterMouseListener(CChartMouseListener* pMouseListener) { m_pMouseListener = pMouseListener;}

	//! Tell the control to set the current series to the first series.
	//���߿���������ǰϵ������Ϊ��һ��ϵ�С�
	/**
		This function is used with the GetNextSerie to iterate over all 
		series in the control.
	**/
	void GoToFirstSerie();
	//! Returns the next series in the control.
	//���ؿؼ��е���һ��ϵ�С�
	/**
		This function is used with the GoToFirstSerie to iterate over all 
		series in the control. First call GoToFirstSerie and then call this 
		function until it returns NULL to iterate over all series.
		Warning: calling this function without calling GoToFirstSerie before
		might lead to unpredicted results. The same if you add or remove
		series between the call to GetFirstSerie and the call to GetNextSerie.
		�˺�����GoToFirstSerieһ��ʹ���Ա����ؼ��е�����ϵ�С� ���ȵ���GoToFirstSerie��Ȼ����ô˺�����ֱ������NULL�Ա�������ϵ�С�
		���棺���ô˺�����������GoToFirstSerie���ܻᵼ�²���Ԥ��Ľ���� �����GetFirstSerie�ĵ��úͶ�GetNextSerie�ĵ���֮����ӻ�ɾ��ϵ�У�Ҳ����ˡ�
		@return the next series or NULL if we already are at the last series.
	**/
	CChartSerie* GetNextSerie();

	//! Refreshes all the axes which are automatic for the screen.
	//ˢ����Ļ�Զ��������ᡣ
	void RefreshScreenAutoAxes();


	void SetShowRecttangle(bool bShow);
	// Generated message map functions
	//���ɵ���Ϣӳ�亯��
protected:
	//{{AFX_MSG(CChartCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
protected:
    virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnPrint(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);

	// This function can be called to draw the chart on the screen or for printing.
	//���Ե��ô˹�������Ļ�ϻ���ͼ�����д�ӡ
	virtual void DrawChart(CDC* pDC, CRect ChartRect);
	virtual void DrawBackground(CDC* pDC, CRect ChartRect);

private:
	//! Register the window class used for this control
	//ע�����ڴ˿ؼ��Ĵ�����
	bool RegisterWindowClass();

	//! Notifies the mouse listeners about a mouse event on the control.
	//֪ͨ���������йؿؼ��ϵ�����¼���
	/**
		The function detects on which part of the control the event happened.
		�ú�������¼������ڿؼ����ĸ����֡�
		@param mouseEvent
			The type of the mouse event
			����¼�������
		@param screenPoint
			The screen point on which the event occured.
			�¼���������Ļ�㡣
	**/
	void SendMouseEvent(CChartMouseListener::MouseEvent mouseEvent, const CPoint& screenPoint) const;

	//! Specifies if the refresh is currently enabled or not.
	//ָ����ǰ�Ƿ�����ˢ��
	int m_iEnableRefresh ;
	//! Specifies if there is a pending refresh. 
	//ָ���Ƿ���ڹ���ˢ��
	//�����true��һ��ִ��EnableRefresh��true��,�����һ��ˢ��
	/**
		If true, once EnableRefresh(true) is called, a refresh of the control
		will be	done.
		�����true��һ��ִ��EnableRefresh��true��,�����һ��ˢ��
	**/
	bool m_bPendingRefresh;
	//! Memory bitmap on which the chart background is drawn (axis, grid, title, ...)
	//����ͼ�������ڴ�λͼ���ᡢ���񡢱��⡢����
	CDC m_BackgroundDC;	
	//! Specifies if the memory bitmap has already been created.
	//ָ���ڴ�λͼ�Ƿ��Ѵ�����
	bool m_bMemDCCreated;

	//! Specifies if the background is gradient or solid
	//ָ�������ǽ��仹��ʵ��
	bool m_bBackGradient;	
	//! First gradient color for the background
	//��һ�ݶ���ɫ�ı���
	COLORREF m_BackGradientCol1;
	//! Second gradient color for the background
	//�ڶ��ݶ���ɫ�ı���
	COLORREF m_BackGradientCol2;
	//! The gradient type used for the background
	//���ڱ����Ľ�������
	EGradientType m_BackGradientType;
	//! The background color (if no gradient used)
	//������ɫ�����û���ݶ�ʹ�ã�
	COLORREF m_BackColor;	
	//! The border color
	//�߿���ɫ
	COLORREF m_BorderColor;
	//! The type of edge
	//��Ե����
	UINT EdgeType;		

	//! Zone in wich the series will be plotted
	//����ϵ��(����,��״)������
	CRect m_PlottingRect;	

	typedef std::map<unsigned, CChartSerie*> TSeriesMap;
	//! Map containing all the series added to the chart.
	//������ӵ�ͼ���е�����ϵ�еĵ�ͼ��
	TSeriesMap m_mapSeries;	
	//! The four axis of the control.
	//���Ƶ��ĸ���
	CChartAxisSerie* m_pAxes[4];
	//�Զ����4����
	CChartCustomLabelStandardAxis * m_pCAxes[4];

	//! The chart legend
	//ͼ��ͼ��
	CChartLegend* m_pLegend;	
	//! The chart titles
	//ͼ�����
	CChartTitle*  m_pTitles;	

	//! Specifies if the mouse panning is enabled
	//ָ���Ƿ��������ƽ��
	bool m_bPanEnabled;
	//! Specifies if the right mouse button is currently pressed
	//ָ���Ƿ�ǰ��������Ҽ�
	bool m_bRMouseDown;		
	//! The point on which the panning started
	//ƽ�ƿ�ʼ�ĵ�
	CPoint m_PanAnchor;

	//! Specifies if the zoom is enabled
	//ָ���Ƿ���������
	bool  m_bZoomEnabled;
	//! Specifies if the left mouse button is currently pressed
	//ָ���Ƿ�ǰ����������
	bool  m_bLMouseDown;
	//! The rectangle of the zoom area
	//��������
	CRect m_rectZoomArea;
	//! The color of the zoom rectangle
	//�����������ɫ
	COLORREF m_ZoomRectColor;

	//! Specifies if the toolbars have already been created
	//ָ���Ƿ��Ѵ���������
	bool m_bToolBarCreated;

	//! The font used for printing
	//���ڴ�ӡ������
    CFont  m_PrinterFont;  
	//! Page size in chartctrl units.
	//��chartctrlΪ��λ��ҳ���С
    CSize m_LogicalPageSize;     
	//! Page size in device units.
	//ҳ���С�����豸Ϊ��λ��
    CSize m_PaperSize;    

	typedef std::map<unsigned, CChartCursor*> TCursorMap;
	//! The map containing all the cursors
	//���������α�ĵ�ͼ
	TCursorMap m_mapCursors;

	//! The mouse listener registered with this control
	//��������ע���˴˿ؼ�
	CChartMouseListener* m_pMouseListener;

	//! Specifies if the mouse is visible when over the plotting area.
	//ָ���ڻ�ͼ�����Ϸ�����Ƿ�ɼ���
	bool m_bMouseVisible;

	typedef TSeriesMap::const_iterator TSeriesMapIter;
	//! The iterator of the current series
	//��ǰϵ�еĵ�����
	TSeriesMapIter m_currentSeries;

	//20170109�Ƿ񻭳���ͼ������
	bool m_bShowRecttangle;

public:
	afx_msg void OnDestroy();
	afx_msg void OnNcDestroy();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

