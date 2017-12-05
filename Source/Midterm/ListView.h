#pragma once
#include "ListItems.h"
#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <gdiplus.h>
#pragma comment(lib, "comctl32.lib")

// List Color for drawing chart
const COLORREF LIST_COLOR[] = { RGB(131, 206, 183),		RGB(255, 0, 0),			RGB(0, 255, 0),
								RGB(255, 150, 0),		RGB(255, 150, 237),		RGB(128, 61, 237) };

namespace PersonalFinance
{
	class ListView
	{
	private:
		HINSTANCE		hInst_;			// Stored main HINSTANCE
		HWND			hParent_;		// Stored parent HWND
		HWND			hListView_;		// Stored HWND of this ListView
		long			ID_;			// Stored ID of this ListView
		long			nItems_;		// Amount of items in current ListView

		ListItems		listItems_;		// List of items data in current ListView

		void			_InitColumn();	// Initial columns in this ListView
		void			_LoadToView(FinanceItem* item); // Load item data to ListView
	public:
		ListView();
		~ListView();

		void			Create(HWND parentWnd, long ID, HINSTANCE hParentInst,
			int Width, int Height, int x = CW_USEDEFAULT, int y = 0,
			long lExtStyle = WS_EX_CLIENTEDGE, long lStyle = LVS_SHOWSELALWAYS);

		HWND			GetThisHandle();	// Get this ListView handle
		int				GetThisID();		// Get this ListView ID
		void			SetFocus();			// Set focus on this ListView

		// Check empty
		bool			IsEmpty();			// Check ListView is empty

		// Clear data
		void			ClearAll();			// Clear all items in show on ListView
		void			ClearAllData();		// Clear all items data and show on ListView

		// Add, Modify, Delete, Get - Item
		void			AddItem(LPWSTR type, LPWSTR name, LPWSTR price);
		void			ModifyItem(LPWSTR type, LPWSTR name, LPWSTR price, int index);
		void			DeleteItem(int index);
		FinanceItem*	GetItem(int index);

		// Drawing
		void			DrawPieChart(Gdiplus::Graphics *graphics);

		// Get Sum Price (Value)
		double			GetSumValue();
		
		// Read - Write - File
		void			Write(std::wofstream &output);
		void			Read(std::wifstream &input);
	};
}

/// Sort Item in column functions
typedef enum
{
	SHOW_NO_ARROW,
	SHOW_UP_ARROW,
	SHOW_DOWN_ARROW
} SHOW_ARROW;

// Show arrow in header column v ^ 
BOOL ListView_SetHeaderSortImage(HWND listView, int  columnIndex, SHOW_ARROW showArrow);
// Handle when user click on column header
void OnColumnClick(LPNMLISTVIEW pLVInfo, HWND hwndLV = NULL);
// Func for Compare Items in ListView in one column
int CALLBACK CompareListItems(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
///