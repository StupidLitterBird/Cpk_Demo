/*
*
*	ChartRectangleSerie.h
*
*	Written by ��ӱ�� (wlyc1@163.com)
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

*	�˴�������Ա������ʽ�����κη���ҵ����ҵĿ�ġ�
*	����������·ַ���ֻҪ������δ�޸Ĳ��ұ������������ʹ���������������
*	ֻ��ʹ������ͬ�����޸�Դ��
*	�˴���û���κα�֤�� �Ҳ��ܶ������ɵ���ʧ����ʧ���� ʹ����
*	���Լ��ķ���һ������ʼ�֪ͨ�ң�������ʹ����δ���Ҳ���͡�
*
*/

#pragma once

#include "ChartFormSerie.h"
#include <list>

typedef struct _tagAngelRectangle
{
	CPoint LT;
	CPoint RT;
	CPoint LB;
	CPoint RB;

public:
	_tagAngelRectangle()
	{
		LT = CPoint(0, 0);
		RT = CPoint(0, 0);
		LB = CPoint(0, 0);
		RB = CPoint(0, 0);
	}
}AngelRectangle;

class CChartRectangleSubSerie
	:public CChartFormSerie
{
public:
	CChartRectangleSubSerie(CChartCtrl* pParent);
	virtual ~CChartRectangleSubSerie();

	//������״
	enum ERectangleStyle
	{
		NONE=0,
	};
	enum EMind
	{
		EM_MID=0,
		EM_LT,		//LeftTop
		EM_TM,		//TopMid
		EM_RT,		//RightTop
		EM_LM,		//LeftMid
		EM_LB,		//LeftBottom
		EM_BM,		//BottonMid
		EM_RB,		//RightBottom
		EM_RM,		//RightMid
	};
	//������ת�Ƕ�
	virtual void SetAngel(double dAngel);
	//���ݵ�λ��ת�Ƕ�(���ĵ��븽�ӵ�)
	virtual void SetAngel(CPoint pt);
	//��ýǶ�
	double GetAngel(){ return m_dAngel; }
	//���þ����߿�
	void SetRectangleWidth(int nLineWide);
	//ȡ�þ����߿�
	int GetRectangleWidth(){ return m_nLineWide; }
	//ȡ������ɫ
	int  GetPenStyle() const { return m_nPenStyle; }
	//����������ʽ
	void SetPenStyle(int NewStyle);
	//�����Ƿ�ѡ��
	virtual void SetClick(bool bClick);
	//ȡ���Ƿ�ѡ��
	virtual bool GetClicked(){ return m_bClick; }
	//�������ĵ�
	void SetMid(EMind md);
	//���ó����
	void SetWide(int nWide);
	void SetHeight(int nHeight);

	//���ñ�ͷɫ
	void SetPenColor(COLORREF color);

	//�ƶ���λ��(�Զ�����ƫ����)
	virtual void MoveTo(CPoint ptMove);
	//�жϵ��Ƿ��ھ��η�Χ��
	virtual bool PointInRect(CPoint pt);
	virtual CChartFormSerie::enAdjustTheArea PointInAdjustTheArea(CPoint pt);
private:
	typedef std::list<CChartRectangleSubSerie*> TRectangleSeriesList;
	void Draw(CDC* pDC);
	//void DrawLegend(CDC* pDC, const CRect& rectBitmap) const;
// private:
// 	static int m_iInterSpace;
// 	static TRectangleSeriesList m_lstRectangleSeries;
// 	mutable TRectangleSeriesList m_lstStackedSeries;
// 	bool m_bStacked;
	virtual CPoint GetMoveMidPoint()
	{
		CPoint ptRec;
		ptRec.x =m_pt.x+ m_pointStart.x;
		ptRec.y = m_pt.y + m_pointStart.y;
		return ptRec;
	}
private:
	//���ο�
	int m_nWide;
	//���θ�
	int m_nHeight;
	//ͼ�������ϵ����ĵ�
	CPoint m_pt;
	//������ɫ
	COLORREF m_PenColor;
	//���ǶȵĻ�������
	AngelRectangle m_AngelRect;
	CRect m_rectTouchHorn[4];		//�ƶ��Ķ�λ��(��4��)

protected:
	//��ת�Ƕ�
	double m_dAngel;
	//�߿�
	int m_nLineWide;
	//���ĵ�λ��
	EMind m_Mid;
	//PenStyle
	int m_nPenStyle;
	//�Ƿ�ѡ��
	bool m_bClick;
	//��ʼ�����
	CPoint m_pointStart;
protected:
	//��ת���㷨
	CPoint GyratePoint(const CPoint pt, const CPoint ptCenter, const double dAngel);
	//ȡ�ô���ת�ľ�������
	AngelRectangle GetAngelRectangle(const CPoint ptCenter, const double dAngel, const int nLen = 6);
	//ȡ�þ������򣬳���ΪnLen
	CRect GetRectangle(const CPoint ptCenter, const int nLen = 6);
	//�㵽ֱ�ߵľ���
	double Distance(CPoint pt, CPoint PtL1, CPoint PtL2);
	//��ȡδ���Ƕȵ������
	CRect GetNoAngelRect(EMind eMid);
};

