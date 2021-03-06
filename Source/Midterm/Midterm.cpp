// Midterm.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Midterm.h"

using namespace GlobalVar;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MIDTERM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	MyRegisterClass_Stat(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MIDTERM));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(gHWndMain, hAccelTable, &msg) && !IsDialogMessage(gHWndMain, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MIDTERM));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MIDTERM);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MIDTERM));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in gCombobox global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN,
		CW_USEDEFAULT, 0, 670, 800, nullptr, nullptr, hInstance, nullptr);

	gHWndMain = hWnd;

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post gCombobox quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_NOTIFY, OnNotify);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_MOVE, OnMove);

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	// Get system font
	LOGFONT lf; // system font
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFontTitle = Create_Font(lf, 20, 400);
	HFONT hFontStat = Create_Font(lf, 20, 600);

	HWND temp;

#pragma region CHI_TIEU

	temp = CreateWindow(L"STATIC", L"Loại chi tiêu",
		WS_CHILD | WS_VISIBLE,
		10, SECTION_CHI_TIEU, 100, 25,
		hwnd, NULL, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);
	temp = CreateWindow(L"COMBOBOX", L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_SIMPLE | CBS_DROPDOWN | CBS_SORT | CBS_HASSTRINGS | WS_TABSTOP,
		10, SECTION_CHI_TIEU + 30, 100, 25,
		hwnd, (HMENU)IDC_TYPE_CHI, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);

	temp = CreateWindow(L"STATIC", L"Tên chi tiêu",
		WS_CHILD | WS_VISIBLE,
		120, SECTION_CHI_TIEU, 100, 25,
		hwnd, NULL, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);
	temp = CreateWindow(L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
		120, SECTION_CHI_TIEU + 30, 300, 25,
		hwnd, (HMENU)IDC_NAME_CHI, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);

	temp = CreateWindow(L"STATIC", L"Số tiền (VND)",
		WS_CHILD | WS_VISIBLE,
		430, SECTION_CHI_TIEU, 100, 25,
		hwnd, NULL, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);
	temp = CreateWindow(L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
		430, SECTION_CHI_TIEU + 30, 100, 25,
		hwnd, (HMENU)IDC_PRICE_CHI, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);

	temp = CreateWindow(L"BUTTON", L"Thêm",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		540, SECTION_CHI_TIEU + 30, 100, 25, hwnd,
		(HMENU)IDC_ADD_CHI, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);

	HWND cboxChi = GetDlgItem(hwnd, IDC_TYPE_CHI);
	SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Ăn uống");
	SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Di chuyển");
	SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Nhà cửa");
	SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Xe cộ");
	SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Nhu yếu");
	SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Dịch vụ");

	SendMessage(cboxChi, CB_SETCURSEL, (WPARAM)0, NULL);

	gListView_ChiTieu = new PersonalFinance::ListView();
	gListView_ChiTieu->Create(hwnd, IDC_LIST_CHI, hInst, 630, 200, 10, SECTION_CHI_TIEU + 70);

	ListView_SetHeaderSortImage(gListView_ChiTieu->GetThisHandle(), 0, SHOW_UP_ARROW);
	SendMessage(gListView_ChiTieu->GetThisHandle(), WM_SETFONT, WPARAM(hFontTitle), TRUE);

	temp = CreateWindow(L"BUTTON", L"Thống kê >",
		WS_CHILD | WS_VISIBLE,
		500, SECTION_CHI_TIEU + 300, 120, 30, hwnd,
		(HMENU)IDC_STATISTIC_CHI, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontStat), TRUE);

#pragma endregion

#pragma region THU_NHAP

	temp = CreateWindow(L"STATIC", L"Loại thu nhập",
		WS_CHILD | WS_VISIBLE,
		10, SECTION_THU_NHAP, 100, 25,
		hwnd, NULL, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);
	temp = CreateWindow(L"COMBOBOX", L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_SIMPLE | CBS_DROPDOWN | CBS_SORT | CBS_HASSTRINGS | WS_TABSTOP,
		10, SECTION_THU_NHAP + 30, 100, 25,
		hwnd, (HMENU)IDC_TYPE_THU, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);

	temp = CreateWindow(L"STATIC", L"Tên thu nhập",
		WS_CHILD | WS_VISIBLE,
		120, SECTION_THU_NHAP, 100, 25,
		hwnd, NULL, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);
	temp = CreateWindow(L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
		120, SECTION_THU_NHAP + 30, 300, 25,
		hwnd, (HMENU)IDC_NAME_THU, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);

	temp = CreateWindow(L"STATIC", L"Số tiền (VND)",
		WS_CHILD | WS_VISIBLE,
		430, SECTION_THU_NHAP, 100, 25,
		hwnd, NULL, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);
	temp = CreateWindow(L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
		430, SECTION_THU_NHAP + 30, 100, 25,
		hwnd, (HMENU)IDC_PRICE_THU, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);

	temp = CreateWindow(L"BUTTON", L"Thêm",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		540, SECTION_THU_NHAP + 30, 100, 25, hwnd,
		(HMENU)IDC_ADD_THU, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);

	HWND cboxThu = GetDlgItem(hwnd, IDC_TYPE_THU);
	SendMessage(cboxThu, CB_ADDSTRING, NULL, (LPARAM)L"Part-time");
	SendMessage(cboxThu, CB_ADDSTRING, NULL, (LPARAM)L"Full-time");
	SendMessage(cboxThu, CB_ADDSTRING, NULL, (LPARAM)L"Over-time");

	SendMessage(cboxThu, CB_SETCURSEL, (WPARAM)0, NULL);

	gListView_ThuNhap = new PersonalFinance::ListView();
	gListView_ThuNhap->Create(hwnd, IDC_LIST_THU, hInst, 630, 200, 10, SECTION_THU_NHAP + 70);

	ListView_SetHeaderSortImage(gListView_ThuNhap->GetThisHandle(), 0, SHOW_UP_ARROW);
	SendMessage(gListView_ThuNhap->GetThisHandle(), WM_SETFONT, WPARAM(hFontTitle), TRUE);

	temp = CreateWindow(L"BUTTON", L"Thống kê >",
		WS_CHILD | WS_VISIBLE,
		500, SECTION_THU_NHAP + 300, 120, 30, hwnd,
		(HMENU)IDC_STATISTIC_THU, hInst, NULL);
	SendMessage(temp, WM_SETFONT, WPARAM(hFontStat), TRUE);

#pragma endregion

	// Khoi tao GDI+
	Midterm::GDIPlusSetup::GDIPlusInit();

	return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case  IDC_ADD_CHI:
	{
		int length = -1;

		// Get type
		length = ComboBox_GetTextLength(GetDlgItem(hwnd, IDC_TYPE_CHI));
		TCHAR *type = new TCHAR[length + 1];
		Edit_GetText(GetDlgItem(hwnd, IDC_TYPE_CHI), type, length + 1);

		// Get name
		length = Edit_GetTextLength(GetDlgItem(hwnd, IDC_NAME_CHI));

		if (length == 0)
		{
			MessageBox(hwnd, L"Phải có trường tên!\r\nVui lòng nhập tên!", L"Notification", MB_OK | MB_ICONWARNING);
			delete[] type;
			break;
		}

		TCHAR *name = new TCHAR[length + 1];
		Edit_GetText(GetDlgItem(hwnd, IDC_NAME_CHI), name, length + 1);

		// Get price
		length = Edit_GetTextLength(GetDlgItem(hwnd, IDC_PRICE_CHI));

		if (length == 0)
		{
			MessageBox(hwnd, L"Phải có trường số tiền!\r\nVui lòng nhập số tiền!", L"Notification", MB_OK | MB_ICONWARNING);
			delete[] type;
			delete[] name;
			break;
		}

		TCHAR *price = new TCHAR[length + 1];
		Edit_GetText(GetDlgItem(hwnd, IDC_PRICE_CHI), price, length + 1);

		try
		{
			gListView_ChiTieu->AddItem(type, name, price);
		}
		catch (LPWSTR str)
		{
			MessageBox(hwnd, str, L"Notification", MB_OK | MB_ICONERROR);
			delete[] type;
			delete[] name;
			delete[] price;
			break;
		}

		Edit_SetText(GetDlgItem(hwnd, IDC_NAME_CHI), L"");
		Edit_SetText(GetDlgItem(hwnd, IDC_PRICE_CHI), L"");

		delete[] type;
		delete[] name;
		delete[] price;

		InvalidateRect(gHWndStatistic, 0, TRUE);
		OnColumnClick(NULL, gListView_ChiTieu->GetThisHandle());
	}
	break;
	case IDC_ADD_THU:
	{
		int length = -1;

		// Get type
		length = ComboBox_GetTextLength(GetDlgItem(hwnd, IDC_TYPE_THU));
		TCHAR *type = new TCHAR[length + 1];
		Edit_GetText(GetDlgItem(hwnd, IDC_TYPE_THU), type, length + 1);

		// Get name
		length = Edit_GetTextLength(GetDlgItem(hwnd, IDC_NAME_THU));

		if (length == 0)
		{
			MessageBox(hwnd, L"Phải có trường tên!\r\nVui lòng nhập tên!", L"Notification", MB_OK | MB_ICONWARNING);
			delete[] type;
			break;
		}

		TCHAR *name = new TCHAR[length + 1];
		Edit_GetText(GetDlgItem(hwnd, IDC_NAME_THU), name, length + 1);

		// Get price
		length = Edit_GetTextLength(GetDlgItem(hwnd, IDC_PRICE_THU));

		if (length == 0)
		{
			MessageBox(hwnd, L"Phải có trường số tiền!\r\nVui lòng nhập số tiền!", L"Notification", MB_OK | MB_ICONWARNING);
			delete[] type;
			delete[] name;
			break;
		}

		TCHAR *price = new TCHAR[length + 1];
		Edit_GetText(GetDlgItem(hwnd, IDC_PRICE_THU), price, length + 1);

		try
		{
			gListView_ThuNhap->AddItem(type, name, price);
		}
		catch (LPWSTR str)
		{
			MessageBox(hwnd, str, L"Notification", MB_OK | MB_ICONERROR);
			delete[] type;
			delete[] name;
			delete[] price;
			break;
		}

		Edit_SetText(GetDlgItem(hwnd, IDC_NAME_THU), L"");
		Edit_SetText(GetDlgItem(hwnd, IDC_PRICE_THU), L"");

		delete[] type;
		delete[] name;
		delete[] price;

		InvalidateRect(gHWndStatistic, 0, TRUE);
		OnColumnClick(NULL, gListView_ThuNhap->GetThisHandle());
	}
	break;

	case ID_STATISTICS_CHI_TIEU:
	case IDC_STATISTIC_CHI:
	{
		if (gHWndStatistic == NULL)
		{
			gHWndStatistic = CreateWindowW(L"Statistic", L"Statistics Chi Tiêu", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN,
				CW_USEDEFAULT, 0, 500, 800, nullptr, nullptr, hInst, nullptr);

			ShowWindow(gHWndStatistic, SW_SHOW);

			WINDOWPLACEMENT pos;
			GetWindowPlacement(hwnd, &pos);

			pos.rcNormalPosition.left = pos.rcNormalPosition.right - 15;
			pos.rcNormalPosition.right += 500;
			SetWindowPlacement(gHWndStatistic, &pos);
			gFlagStatChi = TRUE;
			SetWindowText(GetDlgItem(hwnd, IDC_STATISTIC_CHI), L"Thống kê <");
			CheckMenuItem(GetMenu(hwnd), ID_STATISTICS_CHI_TIEU, MF_CHECKED);
		}
		else
		{
			if (gFlagStatThu)
			{
				gFlagStatThu = FALSE;
				SetWindowText(GetDlgItem(hwnd, IDC_STATISTIC_THU), L"Thống kê >");
				CheckMenuItem(GetMenu(hwnd), ID_STATISTICS_THU_NHAP, MF_UNCHECKED);
			}

			if (gFlagStatChi)
			{
				ShowWindow(gHWndStatistic, SW_HIDE);
				gFlagStatChi = FALSE;
				SetWindowText(GetDlgItem(hwnd, IDC_STATISTIC_CHI), L"Thống kê >");
				CheckMenuItem(GetMenu(hwnd), ID_STATISTICS_CHI_TIEU, MF_UNCHECKED);
			}
			else
			{
				ShowWindow(gHWndStatistic, SW_SHOW);
				Support::NextTo(hwnd, gHWndStatistic);
				SetWindowText(gHWndStatistic, L"Statistics Chi Tiêu");
				gFlagStatChi = TRUE;
				SetWindowText(GetDlgItem(hwnd, IDC_STATISTIC_CHI), L"Thống kê <");
				CheckMenuItem(GetMenu(hwnd), ID_STATISTICS_CHI_TIEU, MF_CHECKED);
			}
		}

		InvalidateRect(gHWndStatistic, 0, TRUE);
	}
	break;

	case ID_STATISTICS_THU_NHAP:
	case IDC_STATISTIC_THU:
	{
		if (gHWndStatistic == NULL)
		{
			gHWndStatistic = CreateWindowW(L"Statistic", L"Statistics Thu Nhập", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN,
				CW_USEDEFAULT, 0, 500, 800, nullptr, nullptr, hInst, nullptr);

			ShowWindow(gHWndStatistic, SW_SHOW);

			WINDOWPLACEMENT pos;
			GetWindowPlacement(hwnd, &pos);

			pos.rcNormalPosition.left = pos.rcNormalPosition.right - 15;
			pos.rcNormalPosition.right += 500;
			SetWindowPlacement(gHWndStatistic, &pos);
			gFlagStatThu = TRUE;
			SetWindowText(GetDlgItem(hwnd, IDC_STATISTIC_THU), L"Thống kê <");
			CheckMenuItem(GetMenu(hwnd), ID_STATISTICS_THU_NHAP, MF_CHECKED);
		}
		else
		{
			if (gFlagStatChi)
			{
				gFlagStatChi = FALSE;
				SetWindowText(GetDlgItem(hwnd, IDC_STATISTIC_CHI), L"Thống kê >");
				CheckMenuItem(GetMenu(hwnd), ID_STATISTICS_CHI_TIEU, MF_UNCHECKED);
			}

			if (gFlagStatThu)
			{
				ShowWindow(gHWndStatistic, SW_HIDE);
				gFlagStatThu = FALSE;
				SetWindowText(GetDlgItem(hwnd, IDC_STATISTIC_THU), L"Thống kê >");
				CheckMenuItem(GetMenu(hwnd), ID_STATISTICS_THU_NHAP, MF_UNCHECKED);
			}
			else
			{
				ShowWindow(gHWndStatistic, SW_SHOW);
				Support::NextTo(hwnd, gHWndStatistic);
				SetWindowText(gHWndStatistic, L"Statistics Thu Nhập");
				gFlagStatThu = TRUE;
				SetWindowText(GetDlgItem(hwnd, IDC_STATISTIC_THU), L"Thống kê <");
				CheckMenuItem(GetMenu(hwnd), ID_STATISTICS_THU_NHAP, MF_CHECKED);
			}
		}

		InvalidateRect(gHWndStatistic, 0, TRUE);
	}
	break;

	case IDC_LIST_DELETE_ITEM:
	{
		int res = MessageBox(hwnd, L"Bạn có muốn xóa dữ liệu không?", L"Confirm", MB_YESNO | MB_ICONWARNING);
		if (res == IDNO) break;
		switch (gListPopup)
		{
		case CHI_LIST:
			gListView_ChiTieu->DeleteItem(giItemPopup);
			InvalidateRect(gHWndStatistic, 0, TRUE);
			OnColumnClick(NULL, gListView_ChiTieu->GetThisHandle());
			break;
		case THU_LIST:
			gListView_ThuNhap->DeleteItem(giItemPopup);
			InvalidateRect(gHWndStatistic, 0, TRUE);
			OnColumnClick(NULL, gListView_ThuNhap->GetThisHandle());
			break;
		}
	}
	break;

	case IDC_LIST_MODIFY_ITEM:
		switch (gListPopup)
		{
		case CHI_LIST:
			gOldItem = gListView_ChiTieu->GetItem(giItemPopup);
			DialogBox(hInst, MAKEINTRESOURCE(IDD_MODIFY), hwnd, WinProcModify);
			InvalidateRect(gHWndStatistic, 0, TRUE);
			OnColumnClick(NULL, gListView_ChiTieu->GetThisHandle());
			break;
		case THU_LIST:
			gOldItem = gListView_ThuNhap->GetItem(giItemPopup);
			DialogBox(hInst, MAKEINTRESOURCE(IDD_MODIFY), hwnd, WinProcModify);
			InvalidateRect(gHWndStatistic, 0, TRUE);
			OnColumnClick(NULL, gListView_ThuNhap->GetThisHandle());
			break;
		}
		break;

	case ID_FILE_SAVE:
		File::FileManager::SaveFileDialog(hwnd, gListView_ChiTieu, gListView_ThuNhap);
		break;

	case ID_FILE_OPEN:
	{
		if (!gListView_ChiTieu->IsEmpty() || !gListView_ThuNhap->IsEmpty())
		{
			int result = MessageBox(hwnd, L"Do you want to save data?", L"Warning", MB_YESNOCANCEL | MB_ICONWARNING);
			switch (result)
			{
			case IDNO:
				break;
			case IDYES:
				File::FileManager::SaveFileDialog(hwnd, gListView_ChiTieu, gListView_ThuNhap);
				return;
			case IDCANCEL:
				return;
			}
		}

		try
		{
			gListView_ChiTieu->ClearAllData();
			gListView_ThuNhap->ClearAllData();
			File::FileManager::OpenFileDialog(hwnd, gListView_ChiTieu, gListView_ThuNhap);
		}
		catch (LPCWSTR err)
		{
			MessageBox(hwnd, err, L"ERROR", MB_OK | MB_ICONERROR);
			gListView_ChiTieu->ClearAllData();
			gListView_ThuNhap->ClearAllData();
			break;
		}
		InvalidateRect(gHWndStatistic, 0, TRUE);
		OnColumnClick(NULL, gListView_ChiTieu->GetThisHandle());
		OnColumnClick(NULL, gListView_ThuNhap->GetThisHandle());
	}
	break;

	case ID_FILE_NEW:
	{
		if (!gListView_ChiTieu->IsEmpty() || !gListView_ThuNhap->IsEmpty())
		{
			int result = MessageBox(hwnd, L"Do you want to save data?", L"Warning", MB_YESNOCANCEL | MB_ICONWARNING);
			switch (result)
			{
			case IDNO:
				break;
			case IDYES:
				File::FileManager::SaveFileDialog(hwnd, gListView_ChiTieu, gListView_ThuNhap);
				break;
			case IDCANCEL:
				return;
			}
		}

		gListView_ChiTieu->ClearAllData();
		gListView_ThuNhap->ClearAllData();
		InvalidateRect(gHWndStatistic, 0, TRUE);
		OnColumnClick(NULL, gListView_ChiTieu->GetThisHandle());
		OnColumnClick(NULL, gListView_ThuNhap->GetThisHandle());
	}
	break;

	case ID_STATISTICS_SUMARY:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_SUMMARY), hwnd, WinProcSummary);
		break;

	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
		break;

	case IDM_EXIT:
		PostMessage(hwnd, WM_CLOSE, NULL, NULL);
		break;
	}
}

LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm)
{
	switch (pnm->code)
	{
	case LVN_COLUMNCLICK:
		// check for column click notification
		if (idFrom == IDC_LIST_CHI || idFrom == IDC_LIST_THU)
		{
			OnColumnClick((LPNMLISTVIEW)pnm);
		}
		break;
	case NM_RCLICK:
		if (idFrom == IDC_LIST_CHI || idFrom == IDC_LIST_THU)
		{
			LV_HITTESTINFO FAR* pinfo = new LVHITTESTINFO;
			ZeroMemory(pinfo, sizeof(LVHITTESTINFO));

			POINT pt;
			POINT popUpMenu;
			GetCursorPos(&pt);
			popUpMenu = pt;
			ScreenToClient(pnm->hwndFrom, &pt);
			pinfo->pt.x = pt.x;
			pinfo->pt.y = pt.y;

			int res = ListView_HitTest(pnm->hwndFrom, pinfo);

			if (pinfo->iItem == -1)
			{
			}
			else
			{
				giItemPopup = pinfo->iItem;
				gListPopup = (ListHandle)(idFrom - IDC_LIST_CHI + 1);

				HMENU hPopupMenu = CreatePopupMenu();
				InsertMenu(hPopupMenu, 0, MF_BYCOMMAND | MF_STRING | MF_ENABLED, IDC_LIST_DELETE_ITEM, L"Delete Item");
				InsertMenu(hPopupMenu, 1, MF_BYCOMMAND | MF_STRING | MF_ENABLED, IDC_LIST_MODIFY_ITEM, L"Modify Item");
				TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, popUpMenu.x, popUpMenu.y, 0, hwnd, NULL);
			}

			delete pinfo;
			//OnColumnClick((LPNMLISTVIEW)pnm);
		}
		break;
	}
	return NULL;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	// TODO: Add any drawing code that uses hdc here...
	EndPaint(hwnd, &ps);
}

void OnClose(HWND hwnd)
{
	if (!gListView_ChiTieu->IsEmpty() || !gListView_ThuNhap->IsEmpty())
	{
		int result = MessageBox(hwnd, L"Do you want to save data?", L"Warning", MB_YESNOCANCEL | MB_ICONWARNING);
		switch (result)
		{
		case IDNO:
			break;
		case IDYES:
			File::FileManager::SaveFileDialog(hwnd, gListView_ChiTieu, gListView_ThuNhap);
			break;
		case IDCANCEL:
			return;
		}
	}

	Midterm::GDIPlusSetup::GDIPlusDestroy();
	delete gListView_ChiTieu;
	delete gListView_ThuNhap;
	if (gHdcMem != NULL) DeleteDC(gHdcMem);
	DestroyWindow(hwnd);
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

void OnMove(HWND hwnd, int x, int y)
{
	if (gFlagStatChi || gFlagStatThu)
	{
		Support::NextTo(hwnd, gHWndStatistic);
	}
}

ATOM MyRegisterClass_Stat(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProcStatistic;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STAT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Statistic";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_STAT));

	return RegisterClassExW(&wcex);
}


LRESULT CALLBACK WndProcStatistic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	using namespace Gdiplus;
	switch (message)
	{
	case WM_PAINT:
	{
		RECT mainRect;
		GetWindowRect(hWnd, &mainRect);

		long width = mainRect.right - mainRect.left;
		long height = mainRect.bottom - mainRect.top;

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		if (gHdcMem != NULL) DeleteDC(gHdcMem);
		gHdcMem = Support::GetHDCParent(hWnd, { width, height });

		RECT rect = { 0,0,width, height };
		FillRect(gHdcMem, &rect, HBRUSH(RGB(255, 255, 255)));

		Gdiplus::Graphics *graphics = new Gdiplus::Graphics(gHdcMem);
		graphics->SetSmoothingMode(SmoothingModeHighQuality);
		if (gFlagStatChi) gListView_ChiTieu->DrawPieChart(graphics);
		if (gFlagStatThu) gListView_ThuNhap->DrawPieChart(graphics);

		BitBlt(hdc, 0, 0, width, height, gHdcMem, 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
		delete graphics;
	}
	break;
	case WM_MOVING:
	{
		WINDOWPLACEMENT pos;
		GetWindowPlacement(hWnd, &pos);

		pos.rcNormalPosition.right = pos.rcNormalPosition.left + 15;
		pos.rcNormalPosition.left -= 670;
		SetWindowPlacement(gHWndMain, &pos);
		BringWindowToTop(gHWndMain);
	}
	break;
	case WM_CLOSE:
		gFlagStatChi = gFlagStatThu = FALSE;
		SetWindowText(GetDlgItem(gHWndMain, IDC_STATISTIC_CHI), L"Thống kê >");
		CheckMenuItem(GetMenu(gHWndMain), ID_STATISTICS_CHI_TIEU, MF_UNCHECKED);

		SetWindowText(GetDlgItem(gHWndMain, IDC_STATISTIC_THU), L"Thống kê >");
		CheckMenuItem(GetMenu(gHWndMain), ID_STATISTICS_THU_NHAP, MF_UNCHECKED);
		DestroyWindow(hWnd);
		gHWndStatistic = NULL;
		break;
	case WM_DESTROY:
		DestroyWindow(hWnd);
		gHWndStatistic = NULL;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for modify box.
INT_PTR CALLBACK WinProcModify(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		if (gOldItem != NULL)
		{
			HWND cbox = GetDlgItem(hDlg, IDC_OLD_COMBO);
			ComboBox_SetText(cbox, gOldItem->GetType());

			HWND edtName = GetDlgItem(hDlg, IDC_OLD_NAME);
			SetWindowText(edtName, gOldItem->GetName());

			TCHAR buf[20];
			swprintf_s(buf, 20, L"%0.2f", gOldItem->GetPrice());
			HWND edtPrice = GetDlgItem(hDlg, IDC_OLD_PRICE);
			SetWindowText(edtPrice, buf);
		}

		switch (gListPopup)
		{
		case CHI_LIST:
		{
			HWND cboxChi = GetDlgItem(hDlg, IDC_NEW_COMBO);
			SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Ăn uống");
			SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Di chuyển");
			SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Nhà cửa");
			SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Xe cộ");
			SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Nhu yếu");
			SendMessage(cboxChi, CB_ADDSTRING, NULL, (LPARAM)L"Dịch vụ");

			ComboBox_SetText(cboxChi, gOldItem->GetType());
		}
		break;
		case THU_LIST:
		{
			HWND cboxThu = GetDlgItem(hDlg, IDC_NEW_COMBO);
			SendMessage(cboxThu, CB_ADDSTRING, NULL, (LPARAM)L"Part-time");
			SendMessage(cboxThu, CB_ADDSTRING, NULL, (LPARAM)L"Full-time");
			SendMessage(cboxThu, CB_ADDSTRING, NULL, (LPARAM)L"Over-time");

			ComboBox_SetText(cboxThu, gOldItem->GetType());
		}
		break;
		}

		HWND edtName = GetDlgItem(hDlg, IDC_NEW_NAME);
		SetWindowText(edtName, gOldItem->GetName());

		TCHAR buf[20];
		swprintf_s(buf, 20, L"%0.2f", gOldItem->GetPrice());
		HWND edtPrice = GetDlgItem(hDlg, IDC_NEW_PRICE);
		SetWindowText(edtPrice, buf);
	}
	return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			int length = -1;

			// Get type
			length = ComboBox_GetTextLength(GetDlgItem(hDlg, IDC_NEW_COMBO));
			TCHAR *type = new TCHAR[length + 1];
			Edit_GetText(GetDlgItem(hDlg, IDC_NEW_COMBO), type, length + 1);

			// Get name
			length = Edit_GetTextLength(GetDlgItem(hDlg, IDC_NEW_NAME));

			if (length == 0)
			{
				MessageBox(hDlg, L"Phải có trường tên!\r\nVui lòng nhập tên!", L"Notification", MB_OK | MB_ICONWARNING);
				delete[] type;
				break;
			}

			TCHAR *name = new TCHAR[length + 1];
			Edit_GetText(GetDlgItem(hDlg, IDC_NEW_NAME), name, length + 1);

			// Get price
			length = Edit_GetTextLength(GetDlgItem(hDlg, IDC_NEW_PRICE));

			if (length == 0)
			{
				MessageBox(hDlg, L"Phải có trường số tiền!\r\nVui lòng nhập số tiền!", L"Notification", MB_OK | MB_ICONWARNING);
				delete[] type;
				delete[] name;
				break;
			}

			TCHAR *price = new TCHAR[length + 1];
			Edit_GetText(GetDlgItem(hDlg, IDC_NEW_PRICE), price, length + 1);

			int res = MessageBox(hDlg, L"Bạn có muốn thay đổi dữ liệu không?", L"Confirm", MB_YESNO | MB_ICONWARNING);
			if (res == IDNO)
			{
				delete[] type;
				delete[] name;
				delete[] price;
				break;
			}

			try
			{
				switch (gListPopup)
				{
				case CHI_LIST:
					gListView_ChiTieu->ModifyItem(type, name, price, giItemPopup);
					break;
				case THU_LIST:
					gListView_ThuNhap->ModifyItem(type, name, price, giItemPopup);
					break;
				}
			}
			catch (LPWSTR str)
			{
				MessageBox(hDlg, str, L"Notification", MB_OK | MB_ICONERROR);
				delete[] type;
				delete[] name;
				delete[] price;
				break;
			}

			delete[] type;
			delete[] name;
			delete[] price;
		}
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
		case IDCANCEL:
			gNewItem = NULL;
			gOldItem = NULL;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// Message handler for modify box.
INT_PTR CALLBACK WinProcSummary(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_PAINT:
	{
		using namespace Gdiplus;
		RECT mainRect;
		GetWindowRect(hDlg, &mainRect);

		long width = mainRect.right - mainRect.left;
		long height = mainRect.bottom - mainRect.top;

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hDlg, &ps);

		if (gHdcMem != NULL) DeleteDC(gHdcMem);
		gHdcMem = Support::GetHDCParent(hDlg, { width, height });

		RECT rect = { 0,0,width, height };
		FillRect(gHdcMem, &rect, HBRUSH(RGB(255, 255, 255)));

		Gdiplus::Graphics *graphics = new Gdiplus::Graphics(gHdcMem);
		graphics->SetSmoothingMode(SmoothingModeHighQuality);
		
		Support::DrawPieChartSummary(graphics, gListView_ChiTieu, gListView_ThuNhap);

		BitBlt(hdc, 0, 0, width, height, gHdcMem, 0, 0, SRCCOPY);

		EndPaint(hDlg, &ps);
		ReleaseDC(hDlg, hdc);
		delete graphics;
	}
	break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}