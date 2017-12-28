/*
 *
 *	ChartStandardAxis.h
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
	//���õ�λ������
	/**
		The tick increment is the value between two adjacents
		ticks on the axis.
		�̶������������������ڿ̶�֮���ֵ��
		@param bAuto
			Specifies if the tick increment is automatically calculated.
		@param newIncrement
			The tick increment to use in manual mode.
	**/
	void SetTickIncrement(bool bAuto, double newIncrement);
	//! Gets the tick increment.
	//��ȡÿ�̶�����
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
	//����С�����������
	void SetDecimals(unsigned uDecimals)  { m_uDecCount = uDecimals; }

	//! Caches the value of the first tick.
	//�����һ��tick��ֵ��
	double m_dFirstTickValue;
	//! Indicates the space between ticks (in axis value).
	//��ʾ�̶�֮��ļ������ֵ����
	double m_dTickIncrement;		
	//! Number of decimals to display for tick labels.
	//�̶ȱ�ǩ��ʾ��С��λ����
	unsigned int m_uDecCount;	
};

#endif  // _CHARTSTANDARDAXIS_H_