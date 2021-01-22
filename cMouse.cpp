#include <windowsx.h>
#include "cMouse.h"

cMouse gMouse;

/**********************************************************************************/
cMouse::cMouse()
{
	mouse1pressed = false;
	mouse1released = false;
	mouse2pressed = false;
	mouse2released = false;
	mousescrollpressed = false;
	mousescrollreleased = false;
}

void cMouse::FillRGBA(int x, int y, int w, int h, DWORD dwColor)
{
	g_pSurface->DrawSetColor(RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor));
	g_pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void cMouse::DrawMouse()
{
	if (!ActiveMouse || HideMouse)
		return;

	FillRGBA(MousePos[0] + 1, MousePos[1], 1, 17, OUTLINE);
	for (int i = 0; i < 11; i++)
		FillRGBA(MousePos[0] + 2 + i, MousePos[1] + 1 + i, 1, 1, OUTLINE);
	FillRGBA(MousePos[0] + 8, MousePos[1] + 12, 5, 1, OUTLINE);
	FillRGBA(MousePos[0] + 8, MousePos[1] + 13, 1, 1, OUTLINE);
	FillRGBA(MousePos[0] + 9, MousePos[1] + 14, 1, 2, OUTLINE);
	FillRGBA(MousePos[0] + 10, MousePos[1] + 16, 1, 2, OUTLINE);
	FillRGBA(MousePos[0] + 8, MousePos[1] + 18, 2, 1, OUTLINE);
	FillRGBA(MousePos[0] + 7, MousePos[1] + 16, 1, 2, OUTLINE);
	FillRGBA(MousePos[0] + 6, MousePos[1] + 14, 1, 2, OUTLINE);
	FillRGBA(MousePos[0] + 5, MousePos[1] + 13, 1, 1, OUTLINE);
	FillRGBA(MousePos[0] + 4, MousePos[1] + 14, 1, 1, OUTLINE);
	FillRGBA(MousePos[0] + 3, MousePos[1] + 15, 1, 1, OUTLINE);
	FillRGBA(MousePos[0] + 2, MousePos[1] + 16, 1, 1, OUTLINE);
	for (int i = 0; i < 4; i++)
		FillRGBA(MousePos[0] + 2 + i, MousePos[1] + 2 + i, 1, 14 - (i * 2), COLORCODE(255 - (i * 4), 255 - (i * 4), 255 - (i * 4), 255));
	FillRGBA(MousePos[0] + 6, MousePos[1] + 6, 1, 8, COLORCODE(235, 235, 235, 255));
	FillRGBA(MousePos[0] + 7, MousePos[1] + 7, 1, 9, COLORCODE(231, 231, 231, 255));
	for (int i = 0; i < 4; i++)
		FillRGBA(MousePos[0] + 8 + i, MousePos[1] + 8 + i, 1, 4 - i, COLORCODE(227 - (i * 4), 227 - (i * 4), 227 - (i * 4), 255));
	FillRGBA(MousePos[0] + 8, MousePos[1] + 14, 1, 4, COLORCODE(207, 207, 207, 255));
	FillRGBA(MousePos[0] + 9, MousePos[1] + 16, 1, 2, COLORCODE(203, 203, 203, 255));

}

void cMouse::ClickHandler()
{
	if (this->ActiveMouse)
	{
		//Left button
		if ((GetAsyncKeyState(VK_LBUTTON)))
		{
			this->mouse1pressed = true;
		}
		else if (!(GetAsyncKeyState(VK_LBUTTON)))
		{
			if (this->mouse1pressed)
				this->mouse1released = true;
			else
			{
				this->mouse1released = false;
			}
			this->mouse1pressed = false;
		}
		//Right button
		if ((GetAsyncKeyState(VK_RBUTTON)))
		{
			this->mouse2pressed = true;
		}
		else if (!(GetAsyncKeyState(VK_RBUTTON)))
		{
			if (this->mouse2pressed)
				this->mouse2released = true;
			else
			{
				this->mouse2released = false;
			}
			this->mouse2pressed = false;
		}
		this->mousescrollpressed = false;
	}
}

bool cMouse::MousePeekMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){
	if (!ActiveMouse)
		return false;
	switch (uMsg){
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_MOUSEHWHEEL:
		if (this->mousescrollpressed = false)
			this->mousescrollpressed = true;
	case WM_RBUTTONDOWN:
		return true;
	case WM_MOUSEMOVE:
		MousePos[0] = GET_X_LPARAM(lParam);
		MousePos[1] = GET_Y_LPARAM(lParam);
		return true;
	}
	return false;
}

/**********************************************************************************/
bool cMouse::Leftclick(int x, int y, int w, int h)
{
	if (mouse1pressed &&
		MousePos[0] > x  &&
		w + x > MousePos[0] &&
		MousePos[1] > y  &&
		h + y > MousePos[1])
		return true;
	else
		return false;
}
/**********************************************************************************/
bool cMouse::OneLeftclick(int x, int y, int w, int h)
{
	if (mouse1released &&
		MousePos[0] > x  &&
		w + x > MousePos[0] &&
		MousePos[1] > y  &&
		h + y > MousePos[1])
		return true;
	else
		return false;
}
/**********************************************************************************/
bool cMouse::Rightclick(int x, int y, int w, int h)
{
	if (mouse2pressed &&
		MousePos[0] > x  &&
		w + x > MousePos[0] &&
		MousePos[1] > y  &&
		h + y > MousePos[1])
		return true;
	else
		return false;
}
/**********************************************************************************/
bool cMouse::OneRightclick(int x, int y, int w, int h)
{
	if (mouse2released &&
		MousePos[0] > x  &&
		w + x > MousePos[0] &&
		MousePos[1] > y  &&
		h + y > MousePos[1])
		return true;
	else
		return false;
}
/**********************************************************************************/
bool cMouse::IsOver(int x, int y, int w, int h)
{
	if (MousePos[0] > x		&&
		MousePos[0] < x + w	&&
		MousePos[1] > y		&&
		MousePos[1] < y + h)
		return true;
	else
		return false;
}

void cMouse::Buttons(){
	Mouse1Press = GetAsyncKeyState(VK_LBUTTON) & 1;
	Mouse1Hold = GetAsyncKeyState(VK_LBUTTON);
	Mouse2Press = GetAsyncKeyState(VK_RBUTTON) & 1;
	Mouse2Hold = GetAsyncKeyState(VK_RBUTTON);
	//if(mouse1Press)
	//	gMenu.select();
	//if(mouse2Press)
	//	gMenu.back();
}

void cMouse::DrawString(int x, int y, int r, int g, int b, bool bCenter, const char *pszText, ...)
{
	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t wbuf[1024] = { '\0' };
	va_start(va_alist, pszText);
	vsprintf(szBuffer, pszText, va_alist);
	va_end(va_alist);
	wsprintfW(wbuf, L"%S", szBuffer);
	int iWidth, iHeight;
	g_pSurface->GetTextSize(font, wbuf, iWidth, iHeight);
	g_pSurface->DrawSetTextFont(font);
	g_pSurface->DrawSetTextColor(r, g, b, 255);
	g_pSurface->DrawSetTextPos(x - (bCenter ? iWidth / 2 : 0), y);
	g_pSurface->DrawPrintText(wbuf, wcslen(wbuf));
}
void cMouse::DrawFeatureString(int x, int y, int r, int g, int b, bool bCenter, const char *pszText, ...)
{
	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t wbuf[1024] = { '\0' };
	va_start(va_alist, pszText);
	vsprintf(szBuffer, pszText, va_alist);
	va_end(va_alist);
	wsprintfW(wbuf, L"%S", szBuffer);
	int iWidth, iHeight;
	g_pSurface->GetTextSize(font, wbuf, iWidth, iHeight);
	g_pSurface->DrawSetTextFont(font);
	g_pSurface->DrawSetTextColor(r, g, b, 255);
	g_pSurface->DrawSetTextPos(x - (bCenter ? iWidth / 2 : 0), y);
	g_pSurface->DrawPrintText(wbuf, wcslen(wbuf));
}
void cMouse::DrawString2(int x, int y, int r, int g, int b, bool bCenter, const char *pszText, ...)
{
	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t wbuf[1024] = { '\0' };
	va_start(va_alist, pszText);
	vsprintf(szBuffer, pszText, va_alist);
	va_end(va_alist);
	wsprintfW(wbuf, L"%S", szBuffer);
	int iWidth, iHeight;
	g_pSurface->GetTextSize(font, wbuf, iWidth, iHeight);
	g_pSurface->DrawSetTextFont(font);
	g_pSurface->DrawSetTextColor(r, g, b, 255);
	g_pSurface->DrawSetTextPos(x - (bCenter ? iWidth / 2 : 0), y);
	g_pSurface->DrawPrintText(wbuf, wcslen(wbuf));
}
void cMouse::DrawTabName(int x, int y, int r, int g, int b, bool bCenter, const char *pszText, ...)
{
	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t wbuf[1024] = { '\0' };
	va_start(va_alist, pszText);
	vsprintf(szBuffer, pszText, va_alist);
	va_end(va_alist);
	wsprintfW(wbuf, L"%S", szBuffer);
	int iWidth, iHeight;
	g_pSurface->GetTextSize(font, wbuf, iWidth, iHeight);
	g_pSurface->DrawSetTextFont(font);
	g_pSurface->DrawSetTextColor(r, g, b, 255);
	g_pSurface->DrawSetTextPos(x - (bCenter ? iWidth / 2 : 0), y);
	g_pSurface->DrawPrintText(wbuf, wcslen(wbuf));
}

bool cMouse::CheckMouse(bool key, int x, int y, int w, int h){
	return(key && MousePos[0] > x && w + x > MousePos[0] && MousePos[1] > y && h + y > MousePos[1]);
}

bool cMouse::CheckMouse(int x, int y, int w, int h){
	return(MousePos[0] > x && w + x > MousePos[0] && MousePos[1] > y && h + y > MousePos[1]);
}