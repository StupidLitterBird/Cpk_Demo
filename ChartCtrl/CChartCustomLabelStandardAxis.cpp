#include "stdafx.h"
#include "CChartCustomLabelStandardAxis.h"



TChartString CChartCustomLabelStandardAxis::GetTickLabel(double TickValue)
{
	double dM = TickValue / (double)(int)TickValue;
	if (dM > 0.999999 && dM < 1.01)
	{
		int nValue = (int)TickValue;
		if (nValue >= (int)m_vLabel.size())
		{
			return *(m_vLabel.end());
		}
		return m_vLabel[nValue];
	}
	else
	{
		return TChartString();
	}
}