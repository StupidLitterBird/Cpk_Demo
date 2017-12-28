#pragma once
#include <vector>

//������������
struct SDBDataPorperty
{
	SDBDataPorperty()
		:m_strName(L""), m_dProportion(0.0), m_dCompensate(0.0), m_nDataType(0), m_dStd(0.0)
		, m_dPlusTolerance(0.0), m_dDnegativeTolerance(0.0), m_dIndirectCompensate(0.0)
	{
		m_nID = -1;
	}
	/*****************************************************************************
	����
		CString m_strName;				��������
		double m_dProportion;			����
		double m_dCompensate;			����
		int m_nDataType;				�������� 0:��ʵ,1:����0 ,2:С��0
		double m_dStd;					��׼ֵ
		double m_dPlusTolerance;		������
		double m_dDnegativeTolerance;	������
		double m_dIndirectCompensate;	��ӱ���
	*******************************************************************************/
	SDBDataPorperty(CString strName, double dProportion, double dCompensate, int nDataType, double dStd, double dPlusTolerance, double dDnegativeTolerance, double dIndirectCompensate)
		:m_strName(strName), m_dProportion(dProportion), m_dCompensate(dCompensate), m_nDataType(nDataType), m_dStd(dStd)
		, m_dPlusTolerance(dPlusTolerance), m_dDnegativeTolerance(dDnegativeTolerance), m_dIndirectCompensate(dIndirectCompensate)
	{
		m_nID = -1;
	}
	long m_nID;						//���ݼ�¼ID
	CString m_strName;				//��������
	double m_dProportion;			//����
	double m_dCompensate;			//����
	int m_nDataType;				//�������� 0:��ʵ,1:����0 ,2:С��0
	double m_dStd;					//��׼ֵ
	double m_dPlusTolerance;		//������
	double m_dDnegativeTolerance;	//������
	double m_dIndirectCompensate;	//��ӱ���
};

//�����ṹ��
struct SDBData
{
	enum DataType
	{
		DT_BOOL,		//����
		DT_String,		//�ַ���
		DT_Double,		//˫���ȸ���
	};
public:
	/**************************************************************************
	�ֶ����͹��� ��Ҫ����
		1.dt�����ͺͶ�Ӧ���͵���ֵ
		2.��Ӧ��bool/double/CString���͵�ֵ
	**************************************************************************/
	SDBData(int PorpertyID) :
		dt(DT_BOOL), nPorpertyID(PorpertyID), nID(-1), bData(false), dData(0.0){}
	/**************************************************************************
	�ֶ����͹��� ��Ҫ����
		1.��Ӧ��bool/double/CString���͵�ֵ
	**************************************************************************/
	SDBData(int PorpertyID, DataType datatpye)
		:dt(datatpye), nPorpertyID(PorpertyID), nID(-1), bData(false), dData(0.0)
	{

	}
	/**************************************************************************
	�����͹��� double
	**************************************************************************/
	SDBData(int PorpertyID, double dataDouble)
		:dt(DT_Double), nPorpertyID(PorpertyID), nID(-1), bData(false), dData(dataDouble)
	{

	}

	/**************************************************************************
	�����͹��� string
	**************************************************************************/
	SDBData(int PorpertyID, CString dataString)
		:dt(DT_String), nPorpertyID(PorpertyID), nID(-1), bData(false), dData(0.0), strData(dataString)
	{

	}

	/**************************************************************************
	�����͹��� bool
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