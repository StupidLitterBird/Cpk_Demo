#pragma once
#include <vector>

//单个数据属性
struct SDBDataPorperty
{
	SDBDataPorperty()
		:m_strName(L""), m_dProportion(0.0), m_dCompensate(0.0), m_nDataType(0), m_dStd(0.0)
		, m_dPlusTolerance(0.0), m_dDnegativeTolerance(0.0), m_dIndirectCompensate(0.0)
	{
		m_nID = -1;
	}
	/*****************************************************************************
	构造
		CString m_strName;				数据名称
		double m_dProportion;			比例
		double m_dCompensate;			补偿
		int m_nDataType;				数据类型 0:真实,1:大于0 ,2:小于0
		double m_dStd;					标准值
		double m_dPlusTolerance;		正公差
		double m_dDnegativeTolerance;	负公差
		double m_dIndirectCompensate;	间接比例
	*******************************************************************************/
	SDBDataPorperty(CString strName, double dProportion, double dCompensate, int nDataType, double dStd, double dPlusTolerance, double dDnegativeTolerance, double dIndirectCompensate)
		:m_strName(strName), m_dProportion(dProportion), m_dCompensate(dCompensate), m_nDataType(nDataType), m_dStd(dStd)
		, m_dPlusTolerance(dPlusTolerance), m_dDnegativeTolerance(dDnegativeTolerance), m_dIndirectCompensate(dIndirectCompensate)
	{
		m_nID = -1;
	}
	long m_nID;						//数据记录ID
	CString m_strName;				//数据名称
	double m_dProportion;			//比例
	double m_dCompensate;			//补偿
	int m_nDataType;				//数据类型 0:真实,1:大于0 ,2:小于0
	double m_dStd;					//标准值
	double m_dPlusTolerance;		//正公差
	double m_dDnegativeTolerance;	//负公差
	double m_dIndirectCompensate;	//间接比例
};

//内联结构体
struct SDBData
{
	enum DataType
	{
		DT_BOOL,		//布尔
		DT_String,		//字符串
		DT_Double,		//双精度浮点
	};
public:
	/**************************************************************************
	手动类型构造 需要补齐
		1.dt的类型和对应类型的数值
		2.对应的bool/double/CString类型的值
	**************************************************************************/
	SDBData(int PorpertyID) :
		dt(DT_BOOL), nPorpertyID(PorpertyID), nID(-1), bData(false), dData(0.0){}
	/**************************************************************************
	手动类型构造 需要补齐
		1.对应的bool/double/CString类型的值
	**************************************************************************/
	SDBData(int PorpertyID, DataType datatpye)
		:dt(datatpye), nPorpertyID(PorpertyID), nID(-1), bData(false), dData(0.0)
	{

	}
	/**************************************************************************
	带类型构造 double
	**************************************************************************/
	SDBData(int PorpertyID, double dataDouble)
		:dt(DT_Double), nPorpertyID(PorpertyID), nID(-1), bData(false), dData(dataDouble)
	{

	}

	/**************************************************************************
	带类型构造 string
	**************************************************************************/
	SDBData(int PorpertyID, CString dataString)
		:dt(DT_String), nPorpertyID(PorpertyID), nID(-1), bData(false), dData(0.0), strData(dataString)
	{

	}

	/**************************************************************************
	带类型构造 bool
	**************************************************************************/
	SDBData(int PorpertyID, bool boolData)
		:dt(DT_BOOL), nPorpertyID(PorpertyID), nID(-1), bData(boolData), dData(0.0)
	{

	}

public:
	long nID;
	long nPorpertyID;
	DataType dt;
	bool bData;
	double dData;
	CString strData;
};



struct SDBDataSheet
{
	SDBDataSheet() 
		:m_TimeStart(0), m_TimeRecord(0)
	{
		m_vDatas.clear();
	}
	CTime m_TimeStart;
	CTime m_TimeRecord;
	std::vector<SDBData> m_vDatas;
};