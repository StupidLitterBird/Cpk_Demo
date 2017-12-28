#if !defined(__CPK_HEADER_H__)
#define __CPK_HEADER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <math.h>
#include <map>
#include <vector>
#include <algorithm>		//排序
#include <afxwin.h>

#include "MdbCpkHeader.h"

//SSE2指令集
//#include <emmintrin.h>
//#include "BoostInclude.h"

#include "BoostInclude.h"
/************************************************************************/
/*  结构体                                                              */
/************************************************************************/

struct SCPK
{
public:
	SCPK()
		:dStdDev(0.0),dCp(0.0),dCpkL(0.0),dCpkU(0.0),dCpk(0.0)
		,dMean(0.0),dMax(-9999999999.00),dMin(9999999999.00),nCount(0),dYieldRate(0.0)
	{

	}

public:
	double dStdDev;		//方差			σ
	double dCp;
	double dCpkL;		//LSL
	double dCpkU;		//USL
	double dCpk;		//CPKs

	double dMean;		//平均值
	double dMax;		//最大值
	double dMin;		//最小值
	int nCount;			//统计数量
	double dYieldRate;	//良品率

private:
// 	friend class boost::serialization::access;
// 	template<class Archive>
// 	void serialize(Archive & ar, const unsigned int version)
// 	{
// 		ar & dStdDev;
// 		ar & dCp;
// 		ar & dCpkL;
// 		ar & dCpkU;
// 		ar & dCpk;
// 		ar & dMean;
// 		ar & dMax;
// 		ar & dMin;
// 		ar & nCount;
// 		ar & dYieldRate;
// 	}

};

struct SPoint2D
{
public:
	SPoint2D() :dX(0.0), dY(0.0)
	{}

	SPoint2D& operator=(SPoint2D& copy)
	{
		dX = copy.dX;
		dY = copy.dY;
		return *this;
	}
public:
	double dX;
	double dY;
};


struct SDoubleDataT
{
	SDoubleDataT(double d,CTime t)
		:dD(d)
	{
		T = t.GetTime();
	}
	SDoubleDataT(double d)
		:dD(d)
	{
		T = (CTime::GetCurrentTime()).GetTime();
	}

	SDoubleDataT()
		:dD(0.0)
	{
		T = (CTime::GetCurrentTime()).GetTime();
	}

	SDoubleDataT& operator=(SDoubleDataT& copy)
	{
		dD = copy.dD;
		T = copy.T;
		return *this;
	}
	//获取系统时间
	CTime GetTime()
	{
		CTime t(T);
		return t;
	}
public:
	double dD;
	__int64 T;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & dD;
		ar & T;
	}
};


//Cpk
struct SCPKHistory
{
public:
	SCPKHistory()
		:strName(""), dDim(0.0), dMaxTol(0.0), dMinTol(0.0)
		, dProportion(1.0), dCompensate(0.0)
		, nDataType(0), dIndirectCompensate(1.0)
//		, tStart(CTime::GetCurrentTime())
	{

	}
	//构造 ：标准值，上限(如+0.02)，下限(如+0.02)，数据名称
	SCPKHistory(double dim,double maxtol,double mintol,CStringA name="")
		:dDim(dim),dMaxTol(maxtol),dMinTol(mintol),strName(name)
		, dProportion(1.0), dCompensate(0.0)
		, nDataType(0), dIndirectCompensate(1.0)
//		, tStart(CTime::GetCurrentTime())
	{
		vdData.clear();
	}
	//构造 ：标准值，上限(如+0.02)，下限(如+0.02),数据集合，数据名称
	SCPKHistory(double dim,double maxtol,double mintol,std::vector<SDoubleDataT>& Data,CStringA name="")
		:dDim(dim),dMaxTol(maxtol),dMinTol(mintol),strName(name)
		, dProportion(1.0), dCompensate(0.0)
		, nDataType(0), dIndirectCompensate(1.0)
//		, tStart(CTime::GetCurrentTime())
	{
		vdData.clear();
		vdData=Data;
	}

	SCPKHistory(double dim, double maxtol, double mintol, std::vector<double>& Data, CStringA name = "")
		:dDim(dim), dMaxTol(maxtol), dMinTol(mintol), strName(name)
		, dProportion(1.0), dCompensate(0.0)
		, nDataType(0), dIndirectCompensate(1.0)
		//		, tStart(CTime::GetCurrentTime())
	{
		vdData.clear();
		std::vector<SDoubleDataT> vD;
		for (unsigned int i = 0; i < Data.size();i++)
		{
			vD.push_back(SDoubleDataT(Data[i]));
		}
		vdData = vD;
	}
	//构造 ：标准值，上限(如+0.02)，下限(如+0.02),数据<double>iterator，数据名称
	SCPKHistory(double dim,double maxtol,double mintol,std::vector<double>::iterator itStart,std::vector<double>::iterator itEnd,CStringA name="")
		:dDim(dim),dMaxTol(maxtol),dMinTol(mintol),strName(name)
		, dProportion(1.0), dCompensate(0.0)
		, nDataType(0), dIndirectCompensate(1.0)
//		, tStart(CTime::GetCurrentTime())
	{
		vdData.clear();
		while(itStart!=itEnd)
		{
			vdData.push_back(*itStart);
			itStart++;
		}
	}

	//构造 ：标准值，上限(如+0.02)，下限(如+0.02),数据指针double 与长度，数据名称
	SCPKHistory(double dim,double maxtol,double mintol,double *pData,int nDataLen,CStringA name="")
		:dDim(dim),dMaxTol(maxtol),dMinTol(mintol),strName(name)
		, dProportion(1.0), dCompensate(0.0)
		, nDataType(0), dIndirectCompensate(1.0)
//		, tStart(CTime::GetCurrentTime())
	{
		vdData.clear();
		for (int i=0;i<nDataLen;i++)
		{
			vdData.push_back(pData[i]);
		}
	}

	SCPKHistory& operator=(SCPKHistory& copy)
	{
		strName=copy.strName;
		dDim=copy.dDim;
		dMinTol=copy.dMinTol;
		dMaxTol=copy.dMaxTol;
		vdData=copy.vdData;
		dProportion = copy.dProportion;
		dCompensate = copy.dCompensate;
		nDataType = copy.nDataType;
		dIndirectCompensate = copy.dIndirectCompensate;
//		tStart = copy.tStart;
		std::vector<SDoubleDataT>::iterator it=copy.vdData.begin();
		while(it!=copy.vdData.end())
		{
			vdData.push_back(*it);
			it++;
		}
		return *this;
	}

	inline SCPK GetCpk()
	{
		SCPK sRes;
		sRes.nCount=vdData.size();
		if (!sRes.nCount)
		{
			sRes.dMax=0.00;
			sRes.dMin=0.0;
		}
		double dSum(0.0);	//和
		double dAccum(0.0);
		for (unsigned int i=0;i<vdData.size();i++)
		{
			dSum+=vdData[i].dD;
			//最大最小值
			if (sRes.dMax<vdData[i].dD)
			{
				sRes.dMax = vdData[i].dD;
			}
			if (sRes.dMin>vdData[i].dD)
			{
				sRes.dMin = vdData[i].dD;
			}
		}
		//平均值
		sRes.dMean=vdData.size()?dSum/vdData.size():0.0;
		for (unsigned int i=0;i<vdData.size();i++)
		{
			dAccum += pow((vdData[i].dD - sRes.dMean), 2.0);
		}
		sRes.dStdDev=sqrt(dAccum/(vdData.size()-1));
		if (dAccum>-0.000001 && dAccum<0.000001)
		{
			sRes.dStdDev=0.00;
		}
		if (sRes.dStdDev<0.00000001 &&sRes.dStdDev>-0.00000001)
		{
			sRes.dCp=sRes.dCpk=sRes.dCpkL=sRes.dCpkU=0.0;
		}
		else
		{
			//cp
			sRes.dCp=(dMaxTol+dMinTol)/(6*sRes.dStdDev);
			//cpkl
			sRes.dCpkL=(sRes.dMean-dDim+dMinTol)/(3*sRes.dStdDev);
			//cpku
			sRes.dCpkU=(dDim+dMaxTol-sRes.dMean)/(3*sRes.dStdDev);
			//cpk
			sRes.dCpk=sRes.dCpkL>sRes.dCpkU?sRes.dCpkU:sRes.dCpkL;
		}
		//统计良品率
		double dH=dDim+dMaxTol;
		double dL=dDim-dMinTol;
		int nYieldCount(0);
		for (unsigned int i=0;i<vdData.size();i++)
		{
			if (vdData[i].dD >= dL && vdData[i].dD <= dH)
			{
				nYieldCount++;
			}
		}
		sRes.dYieldRate=vdData.size()?(double)nYieldCount/vdData.size():0.0;
		return sRes;
	};
	/****************************************************************************
		取得正态分布曲线
		参数:
			dAxisStart		轴起点
			dAxisStep		轴每pdc点代表间距
			nLen			轴DC点长度
	****************************************************************************/
	inline std::vector<SPoint2D> GetNormalDistribution(double dAxisStart,double dAxisStep,int nLen,double dMax)
	{
		std::vector<SPoint2D> vptRes;
		int nCount=vdData.size();
		double dMean(0.0),dSum(0.0),dSumn(0.0),dMain(0.0);
		for (int iIndex = 0; iIndex < nCount;iIndex++)
		{
			dSum += vdData[iIndex].dD;
		}
		dMean = dSum / nCount;
		for (int iIndex = 0; iIndex < nCount; iIndex++)
		{
			dSumn = dSumn + pow(vdData[iIndex].dD - dMean, 2);
		}
		dSumn = dSumn / (double)nCount;
		dMain = sqrt(dSumn);
		for (int iIndex = 0; iIndex < nLen; iIndex++)
		{
			double dN = dAxisStart + dAxisStep*(double)iIndex;
			double dK1 = -1 * pow(dN - dMean, 2);
			double dK2 = 2 * dSumn;
			double dK3 = sqrt(2 * 3.1414926)*dMain;
			SPoint2D sp;
			sp.dX = dN;
			sp.dY = (exp(dK1 / dK2)) / dK3*dMax;
#if _MSC_VER >= 1700
			if (isnan(sp.dY))
			{
				sp.dY = 0.0;
			}
#else
			if (_isnan(sp.dY))
			{
				sp.dY = 0.0;
			}
#endif // _MSC_VER
		}
		return vptRes;
	};

	inline unsigned int size()
	{
		return vdData.size();
	}

	void AddData(double dData, CTime t1)
	{
		vdData.push_back(SDoubleDataT(dData, t1));
	}
	void AddData(double dData)
	{
		vdData.push_back(SDoubleDataT(dData));
	}

public:
	std::string strName;			//数据名称
	double dDim;					//标准值
	double dMaxTol;					//上公差		
	double dMinTol;					//下公差	
	double dProportion;				//比例
	double dCompensate;				//补偿
	int nDataType;					//数据类型 0:真实,1:大于0 ,2:小于0
	double dIndirectCompensate;		//间接比例
//	CTime tStart;					//开始时间

	std::vector<SDoubleDataT> vdData;		//储存结果数据

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & strName;
		ar & dDim;
		ar & dMaxTol;
		ar & dMinTol;
		ar & dProportion;
		ar & dCompensate;
		ar & nDataType;
		ar & dIndirectCompensate;
		ar & vdData;
	}
};




// class CVectorSCPKHistoryStream
// {
// private:
// 	friend class boost::serialization::access;
// 
// 	template<class Archive>
// 	void serialize(Archive& ar, const unsigned int version)
// 	{
// 		ar & m_vHistory;
// 	}
// public:
// 	std::vector<SCPKHistory> m_vHistory;
// };



/************************************************************************************************************
流程:
	1.检索vDataSheet最小数据列
	2.根据最小数据列,检索出具有double类型的数据列的所有PorpertyID,并加入到map
	3.根据PorpertyID数量建立对应的vResHis记录
	4.遍历vDataSheet,把对应PorpertyID的数据加入到对应的vResHis记录,多余的不要

参数:
	std::vector<SDBDataSheet>& vDataSheet
	std::vector<SDBDataPorperty>& vDataPorperty
返回:
	成功: std::vector<SCPKHistory>::size()!=0
	失败: 
*************************************************************************************************************/
//指定数据库记录转换成CPK记录
inline std::vector<SCPKHistory> DataSheetToCpkHistory(std::vector<SDBDataSheet>& vDataSheet, std::vector<SDBDataPorperty>& vDataPorperty)
{
	std::vector<SCPKHistory> vResHis;
	//遍历最小结果与位置
	int nMinSizePos=0;
	int nMinSize = 99999;
	for (unsigned int i = 0; i < vDataSheet.size(); i++)
	{
		if ((int)vDataSheet[i].m_vDatas.size()<nMinSize)
		{
			nMinSize= vDataSheet[i].m_vDatas.size();
			nMinSizePos = i;
		}
	}
	if (nMinSizePos)
	{//存在数据记录

		std::map<unsigned int, SDBDataPorperty> mDataLinePorperty;
		std::map<unsigned int, unsigned int> m_LinePorpertyPos;
		{//加入map记录,方便查找
			std::map<unsigned int, SDBDataPorperty> mDataPorperty;
			for (unsigned int i = 0; i < vDataPorperty.size(); i++)
			{
				mDataPorperty[vDataPorperty[i].m_nID] = vDataPorperty[i];
			}
			//遍历具有Double型数据的Porperty
			for (int i = 0; i < nMinSize; i++)
			{
				if (vDataSheet[nMinSizePos].m_vDatas[i].dt == SDBData::DT_Double && vDataSheet[nMinSizePos].m_vDatas[i].nPorpertyID>0)
				{
					mDataLinePorperty[vDataSheet[nMinSizePos].m_vDatas[i].nPorpertyID] = mDataPorperty[vDataSheet[nMinSizePos].m_vDatas[i].nPorpertyID];
				}
			}
		}
		if (mDataLinePorperty.size())
		{
			std::map<unsigned int, SDBDataPorperty>::iterator it = mDataLinePorperty.begin();
			unsigned int nCLinePos=0;
			for (; it != mDataLinePorperty.end();it++)
			{
				SCPKHistory history;
				history.strName = (std::string)((CStringA)it->second.m_strName);
				history.dDim = it->second.m_dStd;
				history.dMaxTol = it->second.m_dPlusTolerance;
				history.dMinTol = it->second.m_dDnegativeTolerance;
				vResHis.push_back(history);
				//记录对应位置关系
				m_LinePorpertyPos[it->first] = nCLinePos;
				nCLinePos++;
			}
			for (unsigned int i = 0; i < vDataSheet.size(); i++)
			{
				if (i = 0)
				{//取得首个数据参数作为该列数据标准
					for (unsigned int j = 0; j < vDataSheet[i].m_vDatas.size(); j++)
					{
						int nPorpertyID = vDataSheet[i].m_vDatas[j].nPorpertyID;
						if (mDataLinePorperty.find(nPorpertyID) != mDataLinePorperty.end())
						{
							if (vDataSheet[i].m_vDatas[j].dt == SDBData::DT_Double)
							{
								vResHis[m_LinePorpertyPos[nPorpertyID]].vdData.push_back(vDataSheet[i].m_vDatas[j].dData);
							}
						}
					}
				}
				//加入数据记录
			}
		}
	}
	return vResHis;
}


/************************************************************************************************************
CPK数据转换成数据库存储结构
参数:
	std::vector<SCPKHistory>& vHis					输入:CPK数据
	CTime timeRecordStart							输入:CPK数据开始时间
	std::vector<SDBDataSheet>& vDataSheet			输出:数据列表
	std::vector<SDBDataPorperty>& vDataPorperty		输出:数据属性(公差,标准值,不包括比例,补偿等其它数据)
返回:
	成功: 返回true 且输出数据至vDataSheet 和 vDataPorperty
	失败: 返回false
*************************************************************************************************************/
inline bool	CpkHistoryToDataSheet(std::vector<SCPKHistory>& vHis, CTime timeRecordStart, std::vector<SDBDataSheet>& vDataSheet, std::vector<SDBDataPorperty>& vDataPorperty)
{
	bool bOk = false;
	std::vector<SDBDataPorperty> vDP;
	std::vector<SDBDataSheet> vDS;
	for (unsigned int i = 0; i < vHis.size();i++)
	{
		SDBDataPorperty dp;
		dp.m_dStd = vHis[i].dDim;
		dp.m_dPlusTolerance = vHis[i].dMaxTol;
		dp.m_dDnegativeTolerance = vHis[i].dMinTol;
		vDP.push_back(dp);
		SDBDataSheet ds;
		ds.m_TimeStart = timeRecordStart;
		ds.m_TimeRecord = timeRecordStart;
		//遍历数据并加入
		for (unsigned int j = 0; j < vHis[i].vdData.size();j++)
		{
			SDBData D(-1, vHis[i].vdData[j].dD);
			ds.m_vDatas.push_back(D);
		}
		vDS.push_back(ds);
	}
	if (vDP.size())
	{
		vDataPorperty = vDP;
		bOk = true;
	}
	if (vDS.size())
	{
		vDataSheet = vDS;
		bOk = true;
	}
	return bOk;
}




#endif