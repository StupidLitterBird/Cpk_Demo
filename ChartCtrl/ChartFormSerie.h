/*
*
*	CChartFormSerie.h
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


#define PI 3.1415926535898

#pragma once
//#include "ChartRectangleSerie.h"
class CChartRectangleSubSerie;
class CChartCtrl;

class CChartFormSerie
{
	friend CChartRectangleSubSerie;
	friend CChartCtrl;
public:
	CChartFormSerie(CChartCtrl* pParent);
	virtual ~CChartFormSerie();

	enum enAdjustTheArea
	{
		ADJUST_NONE = 0,
		ADJUST_LT,
		ADJUST_RT,
		ADJUST_RB,
		ADJUST_LB,
	};


	//����ͼ��Ϊ���ƶ�
	void SetMove(bool bMove){ m_bMove = bMove; }
	//ȡ��ͼ���Ƿ���ƶ�
	bool GetMove(){ return m_bMove; }
	//�ƶ�ͼ��
	virtual void MoveTo(CPoint ptMove) = 0;
	//�����Ƿ���Ըı��С
	void Resize(bool bCanResize){ m_bCanResize = bCanResize; }
	bool CanResize(){ return m_bCanResize; }

	//�����Ƿ������ת
	void SetRotateArea(bool bCan);

private:
	//ˢ�¿ؼ�
	void RefreshCtrl();
	//��ͼ
	virtual void Draw(CDC* pDC) = 0;
	//ȡ��ͼ��ϵ��ID
	int GetSerieId(){ return m_nFormId; }
	//ָ���������Ƿ���ͼ��������
	virtual bool PointInRect(CPoint pt) = 0;
	//ָ��������Ƿ��ڵ�����С����
	virtual enAdjustTheArea PointInAdjustTheArea(CPoint pt) = 0;
	//����ͼ��Ϊ���״̬
	virtual void SetClick(bool bClick) = 0;
	//ȡ��ͼ�ε��״̬
	virtual bool GetClicked() = 0;
	//ȡ��ͼ�ε����ĵ�
	virtual CPoint GetMoveMidPoint() = 0;
	//�����ƶ�ǰ��ͼ�����ĵ� �����λ�á�
	void SetMouseOrgin(CPoint pt){ m_ptMouseMovePoint = pt; }
	//��¼������ʱ��ͼ�����ĵ�
	void RecordLocMidPt()
	{
		m_ptMovePoint = GetMoveMidPoint();
	};
	//ȡ���ƶ�ǰ�������λ��
	CPoint GetMouseOrgin(){ return m_ptMouseMovePoint; }
	CPoint GetMoveOrgin(){ return m_ptMovePoint; }
	//�����Ƿ���ʾ�ı��С��״̬
	void SetResize(bool bResize);
	//ȡ����ͼ���Ƿ������ת
	bool GetRotateArea(){ return m_bRotateArea; }
	//������ת�Ƕ�
	virtual void SetAngel(double dAngel)=0;
	//���ݵ�λ��ת�Ƕ�
	virtual void SetAngel(CPoint pt)=0;
	//������תģʽ
	void SetRotatiAreaMode(bool bEnabled = true);
	//��ѯ�Ƿ���ת
	bool GetRotatiAreaMode(){ return m_bRotatiAreaMode; }
	//������ת����
	void SetRotatiRevise(bool bEnabled){ m_bRotatiRevise = bEnabled; }
private:
	//tools
	double LintToAngel(CPoint pt1, CPoint pt2);
private:
	//һ���̶������ID
	static unsigned	m_uNextFormId;
	//��״ID
	unsigned int	m_nFormId;
	//�Ƿ�ɼ�
	bool			m_bIsVisible;
	//�Ƿ�������Ӱ
	bool			m_bShadow;
	//��Ӱ��С
	int				m_iShadowDepth;
	//��Ӱ��ɫ
	COLORREF		m_ShadowColor;
	//�Ƿ�����ƶ�
	bool			m_bMove;
	//�Ƿ������ת
	bool			m_bRotateArea;
	//�Ƿ������С״̬
	bool			m_bResize;
	//�ܷ������С
	bool			m_bCanResize;
	//��¼�ƶ������ĵ�
	CPoint			m_ptMouseMovePoint;
	//�ƶ�ǰ��¼��ʵ��λ�ã�������ƫ������
	CPoint			m_ptMovePoint;

	//�ؼ�����
	CChartCtrl* m_pParentCtrl;

	//�ɹ������ת������
	CRect			m_rectRotateArea;
	//��תλ�ó���
	int m_nRotationLen;
	//��ת״̬
	bool m_bRotatiAreaMode;
	//��ת�Ƕ�����
	bool m_bRotatiRevise;
};

