#include "StdAfx.h"
#include "UIIconButton.h"


namespace DuiLib
{

IMPLEMENT_DUICONTROL(CIconButtonUI)

CIconButtonUI::CIconButtonUI(void) : m_szIcon(16,16)
{
	SetChildVAlign(DT_VCENTER);
	Add(m_pIconUI = new CButtonUI);
	m_pIconUI->SetMouseEnabled(false);
}


CIconButtonUI::~CIconButtonUI(void)
{
}

LPCTSTR CIconButtonUI::GetClass() const
{
	return DUI_CTR_ICONBUTTON;
}

LPVOID CIconButtonUI::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, DUI_CTR_ICONBUTTON) == 0 ) return static_cast<CIconButtonUI*>(this);
	return __super::GetInterface(pstrName);
}

void CIconButtonUI::DoInit()
{
	m_pIconUI->SetFixedWidth(m_szIcon.cx);
	m_pIconUI->SetFixedHeight(m_szIcon.cy);
}

void CIconButtonUI::PaintText(HDC hDC)
{
	if( IsFocused() ) m_uButtonState |= UISTATE_FOCUSED;
	else m_uButtonState &= ~ UISTATE_FOCUSED;
	if( !IsEnabled() ) m_uButtonState |= UISTATE_DISABLED;
	else m_uButtonState &= ~ UISTATE_DISABLED;

	if( m_dwTextColor == 0 ) m_dwTextColor = m_pManager->GetDefaultFontColor();
	if( m_dwDisabledTextColor == 0 ) m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

	CDuiString sText = GetText();
	if( sText.IsEmpty() ) return;

	RECT rcText = m_rcItem;
	rcText.left += m_rcInset.left;
	rcText.right -= m_rcInset.right;
	rcText.top += m_rcInset.top;
	rcText.bottom -= m_rcInset.bottom;

	rcText.left += m_szIcon.cx;

	RECT m_rcTextPadding = CButtonLayoutUI::m_rcTextPadding;
	GetManager()->GetDPIObj()->Scale(&m_rcTextPadding);
	
	rcText.left += m_rcTextPadding.left;
	rcText.right -= m_rcTextPadding.right;
	rcText.top += m_rcTextPadding.top;
	rcText.bottom -= m_rcTextPadding.bottom;

	DWORD clrColor = IsEnabled()?m_dwTextColor:m_dwDisabledTextColor;

	if( ((m_uButtonState & UISTATE_PUSHED) != 0) && (GetPushedTextColor() != 0) )
		clrColor = GetPushedTextColor();
	else if( ((m_uButtonState & UISTATE_HOT) != 0) && (GetHotTextColor() != 0) )
		clrColor = GetHotTextColor();
	else if( ((m_uButtonState & UISTATE_FOCUSED) != 0) && (GetFocusedTextColor() != 0) )
		clrColor = GetFocusedTextColor();

	int iFont = GetFont();
	if( ((m_uButtonState & UISTATE_PUSHED) != 0) && (GetPushedFont() != -1) )
		iFont = GetPushedFont();
	else if( ((m_uButtonState & UISTATE_HOT) != 0) && (GetHotFont() != -1) )
		iFont = GetHotFont();
	else if( ((m_uButtonState & UISTATE_FOCUSED) != 0) && (GetFocusedFont() != -1) )
		iFont = GetFocusedFont();

	int nLinks = 0;
	if( m_bShowHtml )
		CRenderEngine::DrawHtmlText(hDC, m_pManager, rcText, sText, clrColor, \
		NULL, NULL, nLinks, iFont, m_uTextStyle);
	else
		CRenderEngine::DrawText(hDC, m_pManager, rcText, sText, clrColor, \
		iFont, m_uTextStyle);
}

void CIconButtonUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if( _tcsicmp(pstrName, _T("iconsize")) == 0 )
	{
		SIZE cx = { 0 };
		LPTSTR pstr = NULL;
		cx.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
		cx.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
		m_szIcon = cx;
		m_pIconUI->SetFixedWidth(m_szIcon.cx);
		m_pIconUI->SetFixedHeight(m_szIcon.cy);
	}
	else if( _tcsicmp(pstrName, _T("iconnormalimage")) == 0 ) SetIconNormalImage(pstrValue);
	else if( _tcsicmp(pstrName, _T("iconhotimage")) == 0 ) SetIconHotImage(pstrValue);
	else if( _tcsicmp(pstrName, _T("iconpushedimage")) == 0 ) SetIconPushedImage(pstrValue);
	else if( _tcsicmp(pstrName, _T("iconfocusedimage")) == 0 ) SetIconFocusedImage(pstrValue);
	else if( _tcsicmp(pstrName, _T("icondisabledimage")) == 0 ) SetIconDisabledImage(pstrValue);
	else __super::SetAttribute(pstrName, pstrValue);
}

LPCTSTR CIconButtonUI::GetIconNormalImage() const
{
	return m_pIconUI->GetNormalImage();
}

void CIconButtonUI::SetIconNormalImage(LPCTSTR pStrImage)
{
	m_pIconUI->SetNormalImage(pStrImage);
}

LPCTSTR CIconButtonUI::GetIconHotImage() const
{
	return m_pIconUI->GetHotImage();
}

void CIconButtonUI::SetIconHotImage(LPCTSTR pStrImage)
{
	m_pIconUI->SetHotImage(pStrImage);
}

LPCTSTR CIconButtonUI::GetIconPushedImage() const
{
	return m_pIconUI->GetPushedImage();
}

void CIconButtonUI::SetIconPushedImage(LPCTSTR pStrImage)
{
	m_pIconUI->SetPushedImage(pStrImage);
}

LPCTSTR CIconButtonUI::GetIconFocusedImage() const
{
	return m_pIconUI->GetFocusedImage();
}

void CIconButtonUI::SetIconFocusedImage(LPCTSTR pStrImage)
{
	m_pIconUI->SetFocusedImage(pStrImage);
}

LPCTSTR CIconButtonUI::GetIconDisabledImage() const
{
	return m_pIconUI->GetDisabledImage();
}

void CIconButtonUI::SetIconDisabledImage(LPCTSTR pStrImage)
{
	m_pIconUI->SetDisabledImage(pStrImage);
}

}