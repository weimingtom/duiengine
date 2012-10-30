//////////////////////////////////////////////////////////////////////////
//   File Name: duiwndpanel.h
// Description: CDuiPanel Definition, Virtual Container of DuiWindows
//     Creator: Zhang Xiaoxuan
//     Version: 2009.04.28 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "duiwnd.h"

namespace DuiEngine{

class DUI_EXP CDuiPanel : public CDuiWindow
{
    DUIOBJ_DECLARE_CLASS_NAME(CDuiPanel, "div")

public:
    CDuiPanel() : m_bOnlyDrawChild(FALSE)
    {
    }

public:
    // Hittest children
    virtual HDUIWND DuiGetHWNDFromPoint(POINT ptHitTest, BOOL bOnlyText);
	
protected:
    DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
        DUIWIN_INT_ATTRIBUTE("onlydrawchild", m_bOnlyDrawChild, FALSE)
    DUIWIN_DECLARE_ATTRIBUTES_END()

	BOOL m_bOnlyDrawChild;	//子窗口只显示，不响应用户操作
};

class DUI_EXP CDuiDialog : public CDuiPanel
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiDialog, "dlg")
};

#define DUISB_NULL	0
#define DUISB_HORZ	1
#define DUISB_VERT	2
#define DUISB_BOTH	(DUISB_HORZ|DUISB_VERT)
#define TIMER_SBWAIT	1		//启动连续滚动的定时器
#define TIMER_SBGO	2		//连续滚动的定时器

class DUI_EXP CDuiPanelEx: public CDuiPanel
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiPanelEx, "divex")

	typedef struct tagSBHITINFO
	{
		DWORD uSbCode:16;
		DWORD nState:8;
		DWORD bVertical:8;
	}SBHITINFO,*PSBHITINFO;

public:
	CDuiPanelEx();

	BOOL ShowScrollBar(int wBar, BOOL bShow);

	BOOL EnableScrollBar(int wBar,BOOL bEnable);

	BOOL IsScrollBarEnable(BOOL bVertical);

	void SetScrollInfo(SCROLLINFO si,BOOL bVertical);
	
	BOOL SetScrollPos(BOOL bVertical, int nNewPos,BOOL bRedraw);

	int GetScrollPos(BOOL bVertical);

	BOOL SetScrollRange(BOOL bVertical,int nMinPos,int nMaxPos,BOOL bRedraw);

	BOOL GetScrollRange(BOOL bVertical,	LPINT lpMinPos,	LPINT lpMaxPos);

	BOOL HasScrollBar(BOOL bVertical);


	SBHITINFO HitTest(CPoint pt);

protected:
	CRect GetSbPartRect(BOOL bVertical,UINT uSBCode);

	CRect GetScrollBarRect(BOOL bVertical);

	int OnCreate(LPVOID);

	void OnNcPaint(CDCHandle dc);

	virtual void GetClient(LPRECT pRect);

	virtual BOOL OnDuiNcHitTest(CPoint pt);

	void OnNcLButtonDown(UINT nFlags, CPoint point);

	void OnNcLButtonUp(UINT nFlags,CPoint pt);

	void OnNcMouseMove(UINT nFlags, CPoint point) ;

	void OnNcMouseLeave();

	//滚动条显示或者隐藏时发送该消息
	LRESULT OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam);

	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	void OnDuiTimer(char cTimerID);
protected:
	virtual int  GetScrollLineSize(BOOL bVertical) {return 10;}
	virtual BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos);

	int GetSbSlideLength(BOOL bVertical);

	CRect GetSbSlideRectByPos(BOOL bVertical,int nPos);

	SCROLLINFO m_siVer,m_siHoz;
	CDuiSkinBase *m_pSkinSb;
	int			m_nSbArrowSize;
	int			m_nSbWid;
	CPoint		m_ptDragSb;
	BOOL		m_bDragSb;
	SBHITINFO		m_HitInfo;
	int			m_nDragPos;

	CRect		m_rcClient;
	int			m_wBarVisible;	//滚动条显示信息
	int			m_wBarEnable;	//滚动条可操作信息

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_SKIN_ATTRIBUTE("sbskin", m_pSkinSb, FALSE)
		DUIWIN_INT_ATTRIBUTE("sbarrowsize", m_nSbArrowSize, FALSE)
		DUIWIN_INT_ATTRIBUTE("sbwid", m_nSbWid, FALSE)
		DUIWIN_INT_ATTRIBUTE("sbenable", m_wBarEnable, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_CREATE(OnCreate)
		MSG_WM_NCPAINT_EX(OnNcPaint)
		MSG_WM_NCCALCSIZE(OnNcCalcSize)
		MSG_WM_NCLBUTTONDOWN(OnNcLButtonDown)
		MSG_WM_NCLBUTTONUP(OnNcLButtonUp)
		MSG_WM_NCMOUSEMOVE(OnNcMouseMove)
		MSG_WM_NCMOUSELEAVE(OnNcMouseLeave)
		MSG_WM_MOUSEWHEEL(OnMouseWheel)
		MSG_WM_DUITIMER(OnDuiTimer)
	DUIWIN_END_MSG_MAP()
};

class DUI_EXP CDuiScrollView : public CDuiPanelEx
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiScrollView, "scrollview")
public:
	CDuiScrollView();

	CSize GetViewSize();

	void SetViewSize(CSize szView);

	CPoint GetViewOrigin();

	void SetViewOrigin(CPoint pt);

protected:
	int OnCreate(LPVOID);

	void OnSize(UINT nType,CSize size);
protected:
	virtual void OnViewOriginChanged(CPoint ptOld,CPoint ptNew){}

	virtual CRect GetViewRect();

	virtual BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos);

protected:
	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_INT_ATTRIBUTE("viewwid", m_szView.cx, FALSE)
		DUIWIN_INT_ATTRIBUTE("viewhei", m_szView.cy, FALSE)
		DUIWIN_INT_ATTRIBUTE("origin-x", m_ptOrgin.x, FALSE)
		DUIWIN_INT_ATTRIBUTE("origin-y", m_ptOrgin.y, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_CREATE(OnCreate)
		MSG_WM_SIZE(OnSize)
	DUIWIN_END_MSG_MAP()
protected:
	CSize m_szView;
	CPoint m_ptOrgin;
};

}//namespace DuiEngine