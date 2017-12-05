#pragma once
#include "ListView.h"
#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <gdiplus.h>
#pragma comment(lib, "comctl32.lib")

class Support
{
public:
	static void NextTo(HWND main, HWND nextTo);
	static HDC	GetHDCParent(HWND hwnd, SIZE size);
	static void	DrawPieChartSummary(Gdiplus::Graphics *graphics, 
									PersonalFinance::ListView* listChiTieu, 
									PersonalFinance::ListView* listThuNhap);
};