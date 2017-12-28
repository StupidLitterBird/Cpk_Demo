#ifndef __CCHART_CUSTOM_LABEL_STANDARD_AXIS_H__
#define __CCHART_CUSTOM_LABEL_STANDARD_AXIS_H__

#include "ChartStandardAxisSerie.h"
#include <vector>
#include <sstream>

class CChartCustomLabelStandardAxis
	:public CChartStandardAxisSerie
{
public:
	CChartCustomLabelStandardAxis(int nMaxLabel=100)
		:m_nMaxLabel(nMaxLabel)
	{
		LabelInit(true,m_nMaxLabel);
	}
	~CChartCustomLabelStandardAxis()
	{

	}
	void SetLabel(unsigned int nStartPos,std::vector<TChartString>& vLabel)
	{
		LabelInit(false);
		if (nStartPos<m_vLabel.size()-1)
		{
			int n=0;
			for (unsigned int i=nStartPos;i<nStartPos+vLabel.size();i++)
			{
				if (i<m_vLabel.size())
				{
					m_vLabel[i]=vLabel[n];
					n++;
				}
			}
		}
	}
	void LabelInit(bool bNumber,int n=100)
	{
		m_vLabel.clear();
		for (unsigned int i=0;i<n-m_vLabel.size();i++)
		{
			if (bNumber)
			{
				TChartString t;
				TChartStringStream stream;
				stream<<i;
				t=stream.str();
				m_vLabel.push_back(t);
			}
			else
			{
				TChartString strNull;
				m_vLabel.push_back(strNull);
			}
		}
	}
protected:
	std::vector<TChartString> m_vLabel;
	int m_nMaxLabel;
private:
	TChartString GetTickLabel(double TickValue);
};




#endif