#pragma once
#include "resource.h"
#include "ListView.h"
#include "GDIPlusSetup.h"
#include "FileManager.h"
#include <windowsx.h>

#define Create_Font(lf, size, style) CreateFont(size, lf.lfWidth, lf.lfEscapement, lf.lfOrientation, style, lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, lf.lfPitchAndFamily, lf.lfFaceName);
#define MAX_LOADSTRING 100
#define SECTION_CHI_TIEU 20
#define SECTION_THU_NHAP 390

enum ListHandle
{
	NO_LIST,
	CHI_LIST,
	THU_LIST
};

namespace GlobalVar
{
	HINSTANCE hInst;                                // current instance
	WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

	// Stored Chi tiêu list
	PersonalFinance::ListView*			gListView_ChiTieu;
	// Stored Thu nhập list
	PersonalFinance::ListView*			gListView_ThuNhap;

	// Stored HWND main window
	HWND								gHWndMain;
	// Stored HWND Statistic window
	HWND								gHWndStatistic;

	// Check Stat Thu nhập
	BOOL								gFlagStatThu = FALSE;
	// Check Stat Chi tiêu
	BOOL								gFlagStatChi = FALSE;

	// Stored Old Item for Modify
	PersonalFinance::FinanceItem*		gOldItem = NULL;
	// Stored New Item for Modify
	PersonalFinance::FinanceItem*		gNewItem = NULL;

	// HDC Mem for double buffering GDI+ on Statistics window
	HDC									gHdcMem = NULL;

	// Stored item index when right click on item
	int									giItemPopup = -1;
	// Stored list id when right click on item
	ListHandle							gListPopup = NO_LIST;
}
