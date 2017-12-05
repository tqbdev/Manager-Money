#include "stdafx.h"
#include "resource.h"
#include "FileManager.h"

UINT_PTR CALLBACK OFNSaveHookProc(
	_In_ HWND   hdlg,
	_In_ UINT   uiMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	switch (uiMsg)
	{
	case WM_INITDIALOG:
	{
		SetWindowText(GetParent(hdlg), L"Save DB for Money Manager");
		// Get system font
		LOGFONT lf; // system font
		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFontTitle = CreateFont(12, lf.lfWidth, lf.lfEscapement, lf.lfOrientation, 400, lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, lf.lfPitchAndFamily, lf.lfFaceName);

		HWND temp;

		temp = CreateWindow(L"STATIC", L"Encoding: ",
			WS_CHILD | WS_VISIBLE,
			250, 396, 100, 20,
			GetParent(hdlg), NULL, GetModuleHandle(NULL), NULL);
		SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);

		temp = CreateWindow(L"COMBOBOX", L"",
			WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_SIMPLE | CBS_DROPDOWN | CBS_SORT | CBS_HASSTRINGS | WS_TABSTOP,
			310, 394, 140, 20,
			GetParent(hdlg), (HMENU)IDC_COMBO_ENCODE, GetModuleHandle(NULL) , NULL);
		SendMessage(temp, WM_SETFONT, WPARAM(hFontTitle), TRUE);
		SendMessage(temp, CB_ADDSTRING, NULL, (LPARAM)L"ANSI");
		//SendMessage(temp, CB_ADDSTRING, NULL, (LPARAM)L"Unicode");
		//SendMessage(temp, CB_ADDSTRING, NULL, (LPARAM)L"Unicode big endian");
		SendMessage(temp, CB_ADDSTRING, NULL, (LPARAM)L"UTF-8");
		SendMessage(temp, CB_SETCURSEL, (WPARAM)0, NULL);

		RECT rect;
		POINT p;

		GetWindowRect(GetDlgItem(GetParent(hdlg), lst1), &rect);
		p.x = rect.left;
		p.y = rect.top;
		ScreenToClient(GetParent(hdlg), &p);
		MoveWindow(GetDlgItem(GetParent(hdlg), lst1), p.x, p.y, rect.right - rect.left + 130, rect.bottom - rect.top, TRUE);

		GetWindowRect(GetDlgItem(GetParent(hdlg), cmb13), &rect);
		p.x = rect.left;
		p.y = rect.top;
		ScreenToClient(GetParent(hdlg), &p);
		MoveWindow(GetDlgItem(GetParent(hdlg), cmb13), p.x, p.y, rect.right - rect.left + 240, rect.bottom - rect.top, TRUE);

		GetWindowRect(GetDlgItem(GetParent(hdlg), cmb1), &rect);
		p.x = rect.left;
		p.y = rect.top;
		ScreenToClient(GetParent(hdlg), &p);
		MoveWindow(GetDlgItem(GetParent(hdlg), cmb1), p.x, p.y, rect.right - rect.left + 240, rect.bottom - rect.top, TRUE);

		GetWindowRect(GetDlgItem(GetParent(hdlg), IDOK), &rect);
		p.x = rect.left;
		p.y = rect.top;
		ScreenToClient(GetParent(hdlg), &p);
		MoveWindow(GetDlgItem(GetParent(hdlg), IDOK), p.x, p.y + 65, rect.right - rect.left, rect.bottom - rect.top, TRUE);

		GetWindowRect(GetDlgItem(GetParent(hdlg), IDCANCEL), &rect);
		p.x = rect.left;
		p.y = rect.top;
		ScreenToClient(GetParent(hdlg), &p);
		MoveWindow(GetDlgItem(GetParent(hdlg), IDCANCEL), p.x + 100, p.y + 39, rect.right - rect.left, rect.bottom - rect.top, TRUE);


		GetWindowRect(GetParent(hdlg), &rect);
		MoveWindow(GetParent(hdlg), rect.left, rect.top, rect.right - rect.left + 130, rect.bottom - rect.top + 40, TRUE);
	}
	break;
	default:
		break;
	}

	return TRUE;
}

UINT_PTR CALLBACK OFNOpenHookProc(
	_In_ HWND   hdlg,
	_In_ UINT   uiMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	switch (uiMsg)
	{
	case WM_INITDIALOG:
	{
		SetWindowText(GetParent(hdlg), L"Open DB for Money Manager");

		RECT rect;
		POINT p;

		GetWindowRect(GetDlgItem(GetParent(hdlg), lst1), &rect);
		p.x = rect.left;
		p.y = rect.top;
		ScreenToClient(GetParent(hdlg), &p);
		MoveWindow(GetDlgItem(GetParent(hdlg), lst1), p.x, p.y, rect.right - rect.left + 130, rect.bottom - rect.top, TRUE);

		GetWindowRect(GetDlgItem(GetParent(hdlg), cmb13), &rect);
		p.x = rect.left;
		p.y = rect.top;
		ScreenToClient(GetParent(hdlg), &p);
		MoveWindow(GetDlgItem(GetParent(hdlg), cmb13), p.x, p.y, rect.right - rect.left + 240, rect.bottom - rect.top, TRUE);

		GetWindowRect(GetDlgItem(GetParent(hdlg), cmb1), &rect);
		p.x = rect.left;
		p.y = rect.top;
		ScreenToClient(GetParent(hdlg), &p);
		MoveWindow(GetDlgItem(GetParent(hdlg), cmb1), p.x, p.y, rect.right - rect.left + 240, rect.bottom - rect.top, TRUE);

		GetWindowRect(GetDlgItem(GetParent(hdlg), IDOK), &rect);
		p.x = rect.left;
		p.y = rect.top;
		ScreenToClient(GetParent(hdlg), &p);
		MoveWindow(GetDlgItem(GetParent(hdlg), IDOK), p.x, p.y + 65, rect.right - rect.left, rect.bottom - rect.top, TRUE);

		GetWindowRect(GetDlgItem(GetParent(hdlg), IDCANCEL), &rect);
		p.x = rect.left;
		p.y = rect.top;
		ScreenToClient(GetParent(hdlg), &p);
		MoveWindow(GetDlgItem(GetParent(hdlg), IDCANCEL), p.x + 100, p.y + 39, rect.right - rect.left, rect.bottom - rect.top, TRUE);

		GetWindowRect(GetParent(hdlg), &rect);
		MoveWindow(GetParent(hdlg), rect.left, rect.top, rect.right - rect.left + 130, rect.bottom - rect.top + 40, TRUE);
	}
	break;
	default:
		break;
	}

	return TRUE;
}

namespace File
{
	void FileManager::SaveFileDialog(HWND hwnd, ListView* listChiTieu, ListView* listThuNhap)
	{
		OPENFILENAME ofn;
		WCHAR *szFile = new WCHAR[10260];
		ZeroMemory(szFile, sizeof(szFile));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.nMaxFile = 10260;
		ofn.lpstrFile = szFile;
		ofn.lpfnHook = OFNSaveHookProc; // custom with hook
		ofn.lpstrFilter = L"CSV (*.csv)\0*.csv\0"; // only csv file
		ofn.nFilterIndex = 1;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLEHOOK;

		if (GetSaveFileName(&ofn) == TRUE)
		{
			using namespace std;
			wstring buffer = ofn.lpstrFile;

			switch (ofn.nFilterIndex)
			{
			case 1:
			{
				if (ofn.nFileExtension == 0) buffer += L".csv";

				std::wofstream output;
				output.open(buffer);
				output.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 1114111UL, std::generate_header>));

				output << L"Chi tiêu,," << endl;
				output << L"Type,Name,Price" << endl;
				listChiTieu->Write(output);
				output << endl << L",," << endl;
				output << L"Thu nhập,," << endl;
				output << L"Type,Name,Price" << endl;
				listThuNhap->Write(output);
				output << endl;
			}
			break;
			}
		}

		delete[] szFile;
	}
	void FileManager::OpenFileDialog(HWND hwnd, ListView* listChiTieu, ListView* listThuNhap)
	{
		OPENFILENAME ofn;
		WCHAR *szFile = new WCHAR[10260];
		ZeroMemory(szFile, sizeof(szFile));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.nMaxFile = 10260;
		ofn.lpstrFile = szFile;
		ofn.lpfnHook = OFNOpenHookProc; // custom with hook
		ofn.lpstrFilter = L"CSV (*.csv)\0*.csv\0"; // only csv file
		ofn.nFilterIndex = 1;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLEHOOK;

		if (GetOpenFileName(&ofn) == TRUE)
		{
			using namespace std;
			wstring buffer = ofn.lpstrFile;

			switch (ofn.nFilterIndex)
			{
			case 1:
			{
				// Checking BOM file - UTF-8
				char* buf = new char[4];
				std::ifstream binary;
				binary.open(buffer, ios::binary);
				binary.read(buf, 4);
				int b1 = buf[0] & 0xFF;
				int b2 = buf[1] & 0xFF;
				int b3 = buf[2] & 0xFF;
				int b4 = buf[3] & 0xFF;

				if (b1 == 0xEF && b2 == 0xBB && b3 == 0xBF)
				{
					// utf-8
					delete[] buf;
					binary.close();
				}
				else
				{
					delete[] buf;
					throw L"Error! File not in UTF-8 format!";
				}
				//

				// if correct UTF-8 BOM continue to reading
				std::wifstream input;
				input.open(buffer);
				input.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 1114111UL, std::generate_header>));

				wstring temp;
				input.get();
				getline(input, temp);
				if (temp.find(L"Chi tiêu,,") == -1)
				{
					throw L"Error! File invalid!";
				}

				getline(input, temp);
				if (temp != L"Type,Name,Price")
				{
					throw L"Error! File invalid!";
				}
				
				try
				{
					listChiTieu->Read(input);
				}
				catch (...)
				{
					throw L"Error! File invalid!";
				}

				getline(input, temp);
				if (temp != L",,")
				{
					throw L"Error! File invalid!";
				}

				getline(input, temp);
				if (temp.find(L"Thu nhập,,") == -1)
				{
					throw L"Error! File invalid!";
				}

				getline(input, temp);
				if (temp != L"Type,Name,Price")
				{
					throw L"Error! File invalid!";
				}

				try
				{
					listThuNhap->Read(input);
				}
				catch (...)
				{
					throw L"Error! File invalid!";
				}
			}
			}
		}
		delete[] szFile;
	}
}