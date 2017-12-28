/*
 *
 *	ChartStandardAxis.h
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

#ifndef _CHARTSTANDARDAXIS_H_
#define _CHARTSTANDARDAXIS_H_

#include "ChartAxisSerie.h"

//! Specialization of a CChartAxis class to display standard values.
class CChartStandardAxisSerie : public CChartAxisSerie
{
friend CChartCtrl;
public:
	//! Default constructor
	CChartStandardAxisSerie();
	//! Default destructor
	~CChartStandardAxisSerie();

	//! Sets the tick increment.
	//设置单位增量。
	/**
		The tick increment is the value between two adjacents
		ticks on the axis.
		刻度增量是轴上两个相邻刻度之间的值。
		@param bAuto
			Specifies if the tick increment is automatically calculated.
		@param newIncrement
			The tick increment to use in manual mode.
	**/
	void SetTickIncrement(bool bAuto, double newIncrement);
	//! Gets the tick increment.
	//获取每刻度增量
	/**
		The tick increment is the value between two adjacents
		ticks on the axis.
	**/
	double GetTickIncrement() const					{ return m_dTickIncrement; }

private:
	double GetFirstTickValue() const;
	bool GetNextTickValue(double dCurrentTick, double& dNextTick) const;
	virtual TChartString GetTickLabel(double TickValue);
	long ValueToScreenDiscrete(double Value) const;
	long GetTickPos(double TickVal) const;
	
	void RefreshTickIncrement();
	void RefreshFirstTick();

	//! Sets the number of decimals points.
	//设置小数点的数量。
	void SetDecimals(unsigned uDecimals)  { m_uDecCount = uDecimals; }

	//! Caches the value of the first tick.
	//缓存第一个tick的值。
	double m_dFirstTickValue;
	//! Indicates the space between ticks (in axis value).
	//表示刻度之间的间隔（轴值）。
	double m_dTickIncrement;		
	//! Number of decimals to display for tick labels.
	//刻度标签显示的小数位数。
	unsigned int m_uDecCount;	
};

#endif  // _CHARTSTANDARDAXIS_H_