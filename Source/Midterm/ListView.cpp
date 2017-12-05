#include "stdafx.h"
#include "ListView.h"

namespace PersonalFinance
{
	//----------------------------------------------------------------------------------------------------------

	ListView::ListView()
	{
		this->hInst_ = NULL;
		this->hParent_ = NULL;
		this->hListView_ = NULL;
		this->ID_ = -1;
		this->nItems_ = -1;
	}

	ListView::~ListView()
	{
		if (this->hListView_) DestroyWindow(this->hListView_);
	}

	void ListView::Create(HWND parentWnd, long ID, HINSTANCE hParentInst,
		int Width, int Height, int x, int y,
		long lExtStyle, long lStyle)
	{
		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_LISTVIEW_CLASSES;
		InitCommonControlsEx(&icex);

		this->hInst_ = hParentInst;
		this->hParent_ = parentWnd;
		this->hListView_ = CreateWindowEx(lExtStyle, WC_LISTVIEW, L"List View",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | lStyle,
			x, y, Width, Height, this->hParent_, (HMENU)ID, this->hInst_, NULL);

		this->ID_ = ID;
		ListView_SetExtendedListViewStyle(this->hListView_, LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_DOUBLEBUFFER);

		this->nItems_ = 0;

		_InitColumn();
		ClearAll();
		LONG dNotView = ~(LVS_LIST | LVS_REPORT);
		SetWindowLong(this->hListView_, GWL_STYLE, GetWindowLong(this->hListView_, GWL_STYLE) & dNotView | LVS_REPORT);
	}

	//----------------------------------------------------------------------------------------------------------

	void ListView::_LoadToView(FinanceItem* item)
	{
		LV_ITEM lv;
		lv.mask = LVIF_TEXT | LVIF_PARAM;

		lv.iItem = item->GetID();
		lv.iSubItem = 0;

		TCHAR buffer[20];
		swprintf_s(buffer, 20, L"%d", item->GetID());
		lv.pszText = buffer;
		lv.lParam = (LPARAM)item;
		ListView_InsertItem(this->hListView_, &lv);

		lv.mask = LVIF_TEXT;
		lv.iSubItem = 1;
		lv.pszText = (LPWSTR)item->GetType();
		ListView_SetItem(this->hListView_, &lv);

		lv.mask = LVIF_TEXT;
		lv.iSubItem = 2;
		lv.pszText = (LPWSTR)item->GetName();
		ListView_SetItem(this->hListView_, &lv);

		swprintf_s(buffer, 20, L"%0.2f", item->GetPrice());
		lv.mask = LVIF_TEXT;
		lv.iSubItem = 3;
		lv.pszText = buffer;
		ListView_SetItem(this->hListView_, &lv);
	}

	void ListView::_InitColumn()
	{
		LVCOLUMN lvCol;

		lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

		lvCol.fmt = LVCFMT_LEFT;
		lvCol.cx = 50;
		lvCol.pszText = L"#id";
		lvCol.iSubItem = 0;
		ListView_InsertColumn(this->hListView_, 0, &lvCol);
		ListView_SetColumn(this->hListView_, 0, &lvCol);

		lvCol.fmt = LVCFMT_LEFT;
		lvCol.cx = 105;
		lvCol.pszText = L"Loại";
		lvCol.iSubItem = 1;
		ListView_InsertColumn(this->hListView_, 1, &lvCol);
		ListView_SetColumn(this->hListView_, 1, &lvCol);

		lvCol.fmt = LVCFMT_LEFT;
		lvCol.cx = 310;
		lvCol.pszText = L"Tên";
		lvCol.iSubItem = 2;
		ListView_InsertColumn(this->hListView_, 2, &lvCol);
		ListView_SetColumn(this->hListView_, 2, &lvCol);

		lvCol.fmt = LVCFMT_RIGHT;
		lvCol.pszText = L"Số tiền";
		lvCol.cx = 120;
		lvCol.iSubItem = 3;
		ListView_InsertColumn(this->hListView_, 3, &lvCol);
		ListView_SetColumn(this->hListView_, 3, &lvCol);
	}

	//----------------------------------------------------------------------------------------------------------

	bool ListView::IsEmpty()
	{
		return listItems_.IsEmpty();
	}

	void ListView::ClearAll()
	{
		ListView_DeleteAllItems(this->hListView_);
	}

	void ListView::ClearAllData()
	{
		ListView_DeleteAllItems(this->hListView_);
		listItems_.ClearAll();
		nItems_ = 0;
	}

	//----------------------------------------------------------------------------------------------------------

	void ListView::AddItem(LPWSTR type, LPWSTR name, LPWSTR price)
	{
		BOOL flagDot = false;
		int len = wcslen(price);
		for (int i = 0; i < len; i++)
		{
			if (!flagDot && price[i] == L'.')
			{
				flagDot = TRUE;
				if (i == len - 1)
				{
					throw L"Số tiền không hợp lệ!\r\nVui lòng nhập lại\r\n";
				}
			}
			else if (price[i] == L'.')
			{
				throw L"Số tiền không hợp lệ!\r\nChứa hơn 2 dấu chấm!\r\nVui lòng nhập lại\r\n";
			}

			if (IsCharAlpha(price[i]))
			{
				throw L"Số tiền không hợp lệ!\r\nChứa kí tự không hợp lệ!\r\nVui lòng nhập lại\r\n";
			}
		}

		double fPrice = _wtof(price);

		FinanceItem* newItem = new FinanceItem(nItems_, type, name, fPrice);
		listItems_.Add(newItem);

		_LoadToView(newItem);

		nItems_++;
	}

	void ListView::DeleteItem(int index)
	{
		if (index < 0 || index >= nItems_) return;

		LVITEM pitem = { 0 };
		TCHAR bufID[20];
		pitem.mask = LVIF_TEXT;
		pitem.iItem = index;
		pitem.iSubItem = 0;
		pitem.cchTextMax = 20;
		pitem.pszText = bufID;
		ListView_GetItem(this->hListView_, &pitem);

		index = wcstol(bufID, NULL, 10);

		ClearAll();

		int i = 0;
		
		for (auto it = listItems_.ListBegin(); it != listItems_.ListEnd(); it++)
		{
			FinanceItem* temp = *it;
			
			if (temp->GetID() == index)
			{
				listItems_.DeleteItem(it);
				nItems_--;
				break;
			}
			
			_LoadToView(temp);
			i++;
		}

		for (; i < listItems_.Size(); i++)
		{
			FinanceItem* temp = listItems_.GetItem(i);
			temp->SetID(i);
			_LoadToView(temp);
		}
	}

	void ListView::ModifyItem(LPWSTR type, LPWSTR name, LPWSTR price, int index)
	{
		if (index < 0 || index >= nItems_) return;

		LVITEM pitem = { 0 };
		TCHAR bufID[20];
		pitem.mask = LVIF_TEXT;
		pitem.iItem = index;
		pitem.iSubItem = 0;
		pitem.cchTextMax = 20;
		pitem.pszText = bufID;
		ListView_GetItem(this->hListView_, &pitem);

		int id = wcstol(bufID, NULL, 10);

		BOOL flagDot = false;
		int len = wcslen(price);
		for (int i = 0; i < len; i++)
		{
			if (!flagDot && price[i] == L'.')
			{
				flagDot = TRUE;
				if (i == len - 1)
				{
					throw L"Số tiền không hợp lệ!\r\nVui lòng nhập lại\r\n";
				}
			}
			else if (price[i] == L'.')
			{
				throw L"Số tiền không hợp lệ!\r\nChứa hơn 2 dấu chấm!\r\nVui lòng nhập lại\r\n";
			}

			if (IsCharAlpha(price[i]))
			{
				throw L"Số tiền không hợp lệ!\r\nChứa kí tự không hợp lệ!\r\nVui lòng nhập lại\r\n";
			}
		}
		ListView_DeleteItem(this->hListView_, index);
		double fPrice = _wtof(price);

		FinanceItem* newItem = new FinanceItem(id, type, name, fPrice);
		listItems_.ModifyItem(newItem, id);

		_LoadToView(newItem);
	}

	FinanceItem* ListView::GetItem(int index)
	{
		if (index < 0 || index >= nItems_) return NULL;

		LVITEM pitem = { 0 };
		TCHAR bufID[20];
		pitem.mask = LVIF_TEXT;
		pitem.iItem = index;
		pitem.iSubItem = 0;
		pitem.cchTextMax = 20;
		pitem.pszText = bufID;
		ListView_GetItem(this->hListView_, &pitem);

		index = wcstol(bufID, NULL, 10);
		
		return listItems_.GetItem(index);
	}

	//----------------------------------------------------------------------------------------------------------

	void ListView::DrawPieChart(Gdiplus::Graphics *graphics)
	{
		using namespace Gdiplus;
		using namespace std;

		TCHAR *buffer = new TCHAR[512];

		Font font(L"Arial", 16, FontStyleBold);
		SolidBrush *black = new SolidBrush(Color(255, 0, 0, 0));
		Pen pen(Color(255, 0, 0, 0), 2);
		graphics->DrawEllipse(&pen, 24, 9, 452, 452);

		double sum = listItems_.SumValue();

		double *percent = new double[listItems_.SizeStatistic()];
		int i = 0;
		double degree = 0;
		double lastDegree = 0;
		PointF p; // for drawing string
		for (auto it = listItems_.StatBegin(); it != listItems_.StatEnd(); it++)
		{
			percent[i] = it->second / sum * 100;
			degree = it->second * 360 / sum;

			Color color_fill;
			color_fill.SetFromCOLORREF(LIST_COLOR[i]);

			SolidBrush *brush = new SolidBrush(color_fill);
			graphics->FillPie(brush, 25, 10, 450, 450, lastDegree, degree);
			graphics->FillRectangle(brush, 20, 500 + 30 * i, 20, 20);

			p.X = 50;
			p.Y = 500 + 30 * i;
			graphics->DrawString(const_cast<LPWSTR>(it->first.c_str()), -1, &font, p, black);

			Font font(L"Arial", 16, FontStyleItalic);
			swprintf_s(buffer, 512, L"(TC: %0.2f / %0.2f %%)", it->second, percent[i]);
			p.X = 200;
			graphics->DrawString(buffer, -1, &font, p, black);

			lastDegree += degree;

			i++;
			delete brush;
		}

		swprintf_s(buffer, 512, L"Tổng cộng: %0.2f", sum);
		p.X = 140;
		p.Y = 500 + 30 * (i + 1);
		graphics->DrawString(buffer, -1, &font, p, black);

		delete black;
		delete[] percent;
		delete[] buffer;
	}

	double ListView::GetSumValue()
	{
		return listItems_.SumValue();
	}

	//----------------------------------------------------------------------------------------------------------

	void ListView::Write(std::wofstream &output)
	{
		listItems_.Write(output);
	}

	void ListView::Read(std::wifstream &input)
	{
		ClearAllData();

		while (!input.eof() && input.peek() != wchar_t(','))
		{
			FinanceItem* res = new FinanceItem();
			bool ret = res->Read(input);
			if (ret == false)
			{
				delete res;
				continue;
			}
			res->SetID(nItems_++);
			listItems_.Add(res);
			_LoadToView(res);
		}
	}

	//----------------------------------------------------------------------------------------------------------

	HWND ListView::GetThisHandle()
	{
		return this->hListView_;
	}

	int	ListView::GetThisID()
	{
		return this->ID_;
	}

	void ListView::SetFocus()
	{
		::SetFocus(this->hListView_);
	}

	//----------------------------------------------------------------------------------------------------------
}

//----------------------------------------------------------------------------------------------------------

BOOL ListView_SetHeaderSortImage(HWND listView, int  columnIndex, SHOW_ARROW showArrow)
{
	HWND    hHeader = NULL;
	HDITEM  hdrItem = { 0 };

	hHeader = ListView_GetHeader(listView);

	if (hHeader)
	{
		hdrItem.mask = HDI_FORMAT;

		if (Header_GetItem(hHeader, columnIndex, &hdrItem))
		{
			if (showArrow == SHOW_UP_ARROW)
			{
				hdrItem.fmt = (hdrItem.fmt & ~HDF_SORTDOWN) | HDF_SORTUP;
			}
			else if (showArrow == SHOW_DOWN_ARROW)
			{
				hdrItem.fmt = (hdrItem.fmt & ~HDF_SORTUP) | HDF_SORTDOWN;
			}
			else
			{
				hdrItem.fmt = hdrItem.fmt & ~(HDF_SORTDOWN | HDF_SORTUP);
			}

			return Header_SetItem(hHeader, columnIndex, &hdrItem);
		}
	}

	return FALSE;
}

void OnColumnClick(LPNMLISTVIEW pLVInfo, HWND hwndLV)
{
	static int nSortColumn = 0;
	//static int lastSortedCol = 0;
	static BOOL bSortAscending = TRUE;
	LPARAM lParamSort;
	HWND hwndFrom = hwndLV;

	// get new sort parameters
	if (pLVInfo != NULL)
	{
		if (pLVInfo->iSubItem == nSortColumn)
			bSortAscending = !bSortAscending;
		else
		{
			nSortColumn = pLVInfo->iSubItem;
			bSortAscending = TRUE;
		}

		hwndFrom = pLVInfo->hdr.hwndFrom;
	}

	// Show arrow on column header
	BOOL ret;
	for (int i = 0; i < 4; i++)
	{
		ret = ListView_SetHeaderSortImage(hwndFrom, i, SHOW_NO_ARROW);
	}

	if (bSortAscending)
	{
		ret = ListView_SetHeaderSortImage(hwndFrom, nSortColumn, SHOW_UP_ARROW);
	}
	else
	{
		ret = ListView_SetHeaderSortImage(hwndFrom, nSortColumn, SHOW_DOWN_ARROW);
	}

	// combine sort info into a single value we can send to our sort function
	lParamSort = 1 + nSortColumn;
	if (!bSortAscending)
		lParamSort = -lParamSort;

	// sort list
	ListView_SortItems(hwndFrom, CompareListItems, lParamSort);
}

int CALLBACK CompareListItems(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	BOOL bSortAscending = (lParamSort > 0);
	int nColumn = abs(lParamSort) - 1;

	using namespace PersonalFinance;
	FinanceItem* item1 = (FinanceItem*)lParam1;
	FinanceItem* item2 = (FinanceItem*)lParam2;

	switch (nColumn)
	{
	case 0: // Column ID
		return bSortAscending ? (item1->GetID() - item2->GetID()) : (item2->GetID() - item1->GetID());
	case 1: // Column Type
		return bSortAscending ? wcscmp(item1->GetType(), item2->GetType()) : wcscmp(item2->GetType(), item1->GetType());
	case 2: // Column Name
		return bSortAscending ? wcscmp(item1->GetName(), item2->GetName()) : wcscmp(item2->GetName(), item1->GetName());
	case 3: // Column Price (Value)
		return bSortAscending ? (item1->GetPrice() - item2->GetPrice()) : (item2->GetPrice() - item1->GetPrice());
	}
}

//----------------------------------------------------------------------------------------------------------