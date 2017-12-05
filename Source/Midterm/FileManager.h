#pragma once
#include <Windows.h>
#include <fstream>
#include "ListView.h"

UINT_PTR CALLBACK OFNSaveHookProc(
	_In_ HWND   hdlg,
	_In_ UINT   uiMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);

UINT_PTR CALLBACK OFNOpenHookProc(
	_In_ HWND   hdlg,
	_In_ UINT   uiMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);

namespace File
{
	using namespace PersonalFinance;
	class FileManager
	{
	public:
		static void SaveFileDialog(HWND hwnd, ListView* listChiTieu, ListView* listThuNhap);
		static void OpenFileDialog(HWND hwnd, ListView* listChiTieu, ListView* listThuNhap);
	};
}