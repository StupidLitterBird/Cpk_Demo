/*
 *
 *	ChartCtrl.h
 *
 *	Written by C閐ric Moonen (cedric_moonen@hotmail.com)
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
	//检索设备上下文。
	/**
		This function is used for internal purposes only.
		//此函数仅用于内部目的
	**/
	CDC* GetDC();
	//! Retrieves the plotting rectangle.
	//检索绘制矩形。
	CRect GetPlottingRect()  const { return m_PlottingRect; }

	//! Returns a pointer to the legend object.
	//返回指向图例对象的指针。
	CChartLegend* GetLegend() const  { return m_pLegend; }
	//! Returns a pointer to the title object.
	//返回指向标题对象的指针。
	CChartTitle*  GetTitle()  const  { return m_pTitles; }

	//! An enumeration of the different axis positions.
	//不同轴位置的枚举。
	enum EAxisPos
	{
		LeftAxis = 0,
		BottomAxis,
		RightAxis,
		TopAxis
	};

	//! Create and attach a standard axis to the control.
	//创建标准轴并将其附加到控件。
	/**
		@param axisPos
			The position of the axis. 
		@return The created standard axis.
	**/
	CChartStandardAxisSerie* CreateStandardAxis(EAxisPos axisPos);
	//! Create and attach a logarithmic axis to the control.
	//创建并将一个对数轴连接到控件。
	/**
		@param axisPos
			The position of the axis. 
		@return The created logarithmic axis.
	**/

	//! Create Custom Axis Created by 梁颖昌 mail to:wlyc1@163.com
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
	//创建并连接日期/时间轴到控件。
	/**
		@param axisPos
			The position of the axis. 
		@return The created date/time axis.
	**/
	CChartDateTimeAxis* CreateDateTimeAxis(EAxisPos axisPos);
	//! Attach a custom axis to the control.
	//将轴附加到控件。
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
	
	//! Attach Custom Axis Created by 梁颖昌 mail to:wlyc1@163.com
	//将自定义轴附加到控件。
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
	//创建点系列并将其附加到控件
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
	//创建线系列并将其附加到控件
	/**
		The function will assert if the associated axes are not attached 
		to the control.
		该功能将确定相关轴是否未连接到控制器。
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
	//创建面板系列并将其附加到控件
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
	//创建并将柱状bar系列附加到控件
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
	//创建蜡烛条系列并将其附加到控件
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
	//创建甘特系列并将其附加到控件
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
	//包含添加到图表中的所有系列的地图。
	TFormSeriesMap m_mapFormSeries;

	//! Attaches a custom series to the chart
	//将自定义系列附加到图表
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
	//从图表中检索特定系列
	/**
		@param uSerieId
			The Id of the series to retrieve
		@return The series or NULL if uSerieId is not attributed.
	**/
	CChartSerie* GetSerie(unsigned uSerieId) const;
	//! Removes a specific series from the chart
	//从图表中删除特定系列
	/**
		@param uSerieId
			The Id of the series to be removed.
	**/
	void RemoveSerie(unsigned uSerieId);
	//! Removes all the series from the chart
	//从图表中删除所有系列
	void RemoveAllSeries();
	//! Returns the number of series in the chart
	//返回图表中的系列数量
	size_t GetSeriesCount() const;

	//! Create and attach a cross-hair cursor to the control
	//创建十字光标并将其附加到控件
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
	//创建拖动线光标并将其附加到控件
	/**
		A drag-line cursor is a simple line (horizontal or vertical) that can be
		dragged with the mouse by clicking on it. It is attached to a specific axis.
		拖动光标是一个简单的线（水平或垂直），可以通过单击鼠标来拖动鼠标。 它连接到特定轴。
		@param relatedAxis
			The axis position to which the cursor is attached to.
		@return The created drag-line cursor.
		@remark The function will assert if the associated axis is not attached 
		to the control.
	**/
	CChartDragLineCursor* CreateDragLineCursor(EAxisPos relatedAxis);
	//! Attach a custom cursor to the control
	//将自定义光标附加到控件
	/**
		You should only use this function if you want to attach a custom cursor
		to the control. Otherwise, you should use the CreateXXXCursor helper functions.
		如果要将自定义光标附加到控件，则只能使用此函数。 否则，应该使用CreateXXXCursor辅助函数。
		@param pCursor
			The custom cursor to be attached to the control.
	**/
	void AttachCustomCursor(CChartCursor* pCursor);
	//! Removes a cursor with a specific Id from the control.
	//从控件中删除具有特定标识的游标。
	/**
		The cursor Id can be retrieved on through the CChartCursor::GetCursorId function.
		可以通过CChartCursor :: GetCursorId函数检索游标Id。
		@param cursorId
			The Id of the cursor to remove from the control.
	**/
	void RemoveCursor(unsigned cursorId);

	//! Shows/hides the mouse cursor when it is over the plotting area.
	//在绘图区域上方显示/隐藏鼠标光标。
	void ShowMouseCursor(bool bShow);

	CChartAxisSerie* GetBottomAxis() const;
	CChartAxisSerie* GetLeftAxis() const;
	CChartAxisSerie* GetTopAxis() const;
	CChartAxisSerie* GetRightAxis() const;
	//! Returns a specific axis attached to the control
	//返回附加到控件的特定轴
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
	//返回用作边框的边的类型。
	UINT GetEdgeType() const        { return EdgeType;    }
	//! Sets the edge type.
	//设置边缘类型
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
	//返回背景颜色
	COLORREF GetBackColor() const			{ return m_BackColor;   }
	//! Sets the background color.
	//设置背景颜色。
	void SetBackColor(COLORREF NewCol)		
	{ 
		m_BackColor = NewCol;  
		m_bBackGradient = false; 
		RefreshCtrl();
	}
	//! Returns the color of the plotting area's border 
	//返回绘制区域边框的颜色
	COLORREF GetBorderColor() const			{ return m_BorderColor;   }
	//! Sets the color of the plotting area's border 
	//设置绘图区域边框的颜色
	void SetBorderColor(COLORREF NewCol)	{ m_BorderColor = NewCol;	RefreshCtrl(); }
	//! Returns the color of the zoom rectangle
	//返回缩放矩形的颜色
	COLORREF GetZoomRectColor() const		{ return m_ZoomRectColor;   }
	//! Sets the color of the zoom rectangle
	//设置缩放矩形的颜色
	void SetZoomRectColor(COLORREF NewCol)	{ m_ZoomRectColor = NewCol; RefreshCtrl(); }
	//! Sets a gradient background
	//设置渐变背景
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
	//启用/禁用平移功能
	void SetPanEnabled(bool bEnabled)  { m_bPanEnabled = bEnabled;  }
	//! Returns true if the pan feature is enabled
	//如果启用平移功能，则返回true
	bool GetPanEnabled() const		   { return m_bPanEnabled;	    }
	//! Enables/disables the zoom feature
	//启用/禁用缩放功能
	void SetZoomEnabled(bool bEnabled) { m_bZoomEnabled = bEnabled; }
	//! Returns true if the zoom feature is enabled
	//如果启用缩放功能，则返回true
	bool GetZoomEnabled() const		   { return m_bZoomEnabled;	    }
	//! Undo all pan and zoom operations that were done on the chart
	//撤消在图表上完成的所有平移和缩放操作
	void UndoPanZoom();

	//! Forces a refresh of the control.
	//强制刷新控件。
	/**
		This function is used for internal purposes.
		此函数用于内部目的。
	**/
	void RefreshCtrl();
	//! Enables/disables the refresh of the control
	//启用/禁用控件的刷新
	/**
		This function is used when several settings have to be changed at the same 
		time on the control. This way we can avoid refreshing the control when it 
		is not needed.
		当需要在控制器上同时更改多个设置时使用此功能。 这样我们可以避免在不需要时刷新控件。
		@param bEnable
			false to disable the refresh and true to re-enable the refresh.
	**/
	void EnableRefresh(bool bEnable);
	//! Creates the control dynamically.
	//动态创建控制(件)。
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
	//帮助函数将日期转换为双精度值
	static double DateToValue(const COleDateTime& Date);
	//! Helper function to convert a double value to a date
	//辅助函数将double值转换为日期
	static COleDateTime ValueToDate(double Value);

	//! Print the chart
	//打印图表
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
	//将图表保存到图像文件
	/**
		This function is not available for VC6 and earlier.
		此功能不适用于VC6和更早版本。
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
	//默认构造函数
    CChartCtrl();	
	//! Default destructor
	//默认释构函数
    virtual ~CChartCtrl();

	//! Register a mouse listener with the control.
	//使用注册控件鼠标监听器。
	/**
		This listener will be notified each time a mouse event occurs on the control.
		每当在控件上发生鼠标事件时，都会通知此侦听器。
		@param pMouseListener
			The mouse listener to register with this control.
	**/
	void RegisterMouseListener(CChartMouseListener* pMouseListener) { m_pMouseListener = pMouseListener;}

	//! Tell the control to set the current series to the first series.
	//告诉控制器将当前系列设置为第一个系列。
	/**
		This function is used with the GetNextSerie to iterate over all 
		series in the control.
	**/
	void GoToFirstSerie();
	//! Returns the next series in the control.
	//返回控件中的下一个系列。
	/**
		This function is used with the GoToFirstSerie to iterate over all 
		series in the control. First call GoToFirstSerie and then call this 
		function until it returns NULL to iterate over all series.
		Warning: calling this function without calling GoToFirstSerie before
		might lead to unpredicted results. The same if you add or remove
		series between the call to GetFirstSerie and the call to GetNextSerie.
		此函数与GoToFirstSerie一起使用以遍历控件中的所有系列。 首先调用GoToFirstSerie，然后调用此函数，直到返回NULL以遍历所有系列。
		警告：调用此函数而不调用GoToFirstSerie可能会导致不可预测的结果。 如果在GetFirstSerie的调用和对GetNextSerie的调用之间添加或删除系列，也是如此。
		@return the next series or NULL if we already are at the last series.
	**/
	CChartSerie* GetNextSerie();

	//! Refreshes all the axes which are automatic for the screen.
	//刷新屏幕自动的所有轴。
	void RefreshScreenAutoAxes();


	void SetShowRecttangle(bool bShow);
	// Generated message map functions
	//生成的消息映射函数
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
	//可以调用此功能在屏幕上绘制图表或进行打印
	virtual void DrawChart(CDC* pDC, CRect ChartRect);
	virtual void DrawBackground(CDC* pDC, CRect ChartRect);

private:
	//! Register the window class used for this control
	//注册用于此控件的窗口类
	bool RegisterWindowClass();

	//! Notifies the mouse listeners about a mouse event on the control.
	//通知鼠标监听器有关控件上的鼠标事件。
	/**
		The function detects on which part of the control the event happened.
		该函数检测事件发生在控件的哪个部分。
		@param mouseEvent
			The type of the mouse event
			鼠标事件的类型
		@param screenPoint
			The screen point on which the event occured.
			事件发生的屏幕点。
	**/
	void SendMouseEvent(CChartMouseListener::MouseEvent mouseEvent, const CPoint& screenPoint) const;

	//! Specifies if the refresh is currently enabled or not.
	//指定当前是否启用刷新
	int m_iEnableRefresh ;
	//! Specifies if there is a pending refresh. 
	//指定是否存在挂起刷新
	//如果是true，一旦执行EnableRefresh（true）,则完成一次刷新
	/**
		If true, once EnableRefresh(true) is called, a refresh of the control
		will be	done.
		如果是true，一旦执行EnableRefresh（true）,则完成一次刷新
	**/
	bool m_bPendingRefresh;
	//! Memory bitmap on which the chart background is drawn (axis, grid, title, ...)
	//绘制图表背景的内存位图（轴、网格、标题、…）
	CDC m_BackgroundDC;	
	//! Specifies if the memory bitmap has already been created.
	//指定内存位图是否已创建。
	bool m_bMemDCCreated;

	//! Specifies if the background is gradient or solid
	//指定背景是渐变还是实心
	bool m_bBackGradient;	
	//! First gradient color for the background
	//第一梯度颜色的背景
	COLORREF m_BackGradientCol1;
	//! Second gradient color for the background
	//第二梯度颜色的背景
	COLORREF m_BackGradientCol2;
	//! The gradient type used for the background
	//用于背景的渐变类型
	EGradientType m_BackGradientType;
	//! The background color (if no gradient used)
	//背景颜色（如果没有梯度使用）
	COLORREF m_BackColor;	
	//! The border color
	//边框颜色
	COLORREF m_BorderColor;
	//! The type of edge
	//边缘类型
	UINT EdgeType;		

	//! Zone in wich the series will be plotted
	//绘制系列(线条,形状)的区域
	CRect m_PlottingRect;	

	typedef std::map<unsigned, CChartSerie*> TSeriesMap;
	//! Map containing all the series added to the chart.
	//包含添加到图表中的所有系列的地图。
	TSeriesMap m_mapSeries;	
	//! The four axis of the control.
	//控制的四个轴
	CChartAxisSerie* m_pAxes[4];
	//自定义的4个轴
	CChartCustomLabelStandardAxis * m_pCAxes[4];

	//! The chart legend
	//图表图例
	CChartLegend* m_pLegend;	
	//! The chart titles
	//图表标题
	CChartTitle*  m_pTitles;	

	//! Specifies if the mouse panning is enabled
	//指定是否启用鼠标平移
	bool m_bPanEnabled;
	//! Specifies if the right mouse button is currently pressed
	//指定是否当前按下鼠标右键
	bool m_bRMouseDown;		
	//! The point on which the panning started
	//平移开始的点
	CPoint m_PanAnchor;

	//! Specifies if the zoom is enabled
	//指定是否启用缩放
	bool  m_bZoomEnabled;
	//! Specifies if the left mouse button is currently pressed
	//指定是否当前按下鼠标左键
	bool  m_bLMouseDown;
	//! The rectangle of the zoom area
	//缩放区域
	CRect m_rectZoomArea;
	//! The color of the zoom rectangle
	//缩放区域的颜色
	COLORREF m_ZoomRectColor;

	//! Specifies if the toolbars have already been created
	//指定是否已创建工具栏
	bool m_bToolBarCreated;

	//! The font used for printing
	//用于打印的字体
    CFont  m_PrinterFont;  
	//! Page size in chartctrl units.
	//以chartctrl为单位的页面大小
    CSize m_LogicalPageSize;     
	//! Page size in device units.
	//页面大小（以设备为单位）
    CSize m_PaperSize;    

	typedef std::map<unsigned, CChartCursor*> TCursorMap;
	//! The map containing all the cursors
	//包含所有游标的地图
	TCursorMap m_mapCursors;

	//! The mouse listener registered with this control
	//鼠标监听器注册了此控件
	CChartMouseListener* m_pMouseListener;

	//! Specifies if the mouse is visible when over the plotting area.
	//指定在绘图区域上方鼠标是否可见。
	bool m_bMouseVisible;

	typedef TSeriesMap::const_iterator TSeriesMapIter;
	//! The iterator of the current series
	//当前系列的迭代器
	TSeriesMapIter m_currentSeries;

	//20170109是否画出绘图区域线
	bool m_bShowRecttangle;

public:
	afx_msg void OnDestroy();
	afx_msg void OnNcDestroy();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

