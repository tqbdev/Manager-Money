#pragma once

#include "resource.h"
#include "ListView.h"
#include "GDIPlusSetup.h"
#include "FileManager.h"
#include "GlobalVar.h"
#include "Support.h"
#include <windowsx.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// WinProc for Modify Dialog Box
INT_PTR CALLBACK    WinProcModify(HWND, UINT, WPARAM, LPARAM);

// WinProc for Statistics Summary Dialog Box
INT_PTR CALLBACK    WinProcSummary(HWND, UINT, WPARAM, LPARAM);

// For Statistics Window
ATOM                MyRegisterClass_Stat(HINSTANCE hInstance);
LRESULT CALLBACK    WndProcStatistic(HWND, UINT, WPARAM, LPARAM);

// Handle Message declarations of functions for Main Windows
void				OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void				OnPaint(HWND hwnd);
void				OnDestroy(HWND hwnd);
void				OnClose(HWND hwnd);
BOOL				OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void				OnMove(HWND hwnd, int x, int y);
LRESULT				OnNotify(HWND hwnd, int idFrom, NMHDR *pnm);