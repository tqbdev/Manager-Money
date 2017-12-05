#include "stdafx.h"
#include "Support.h"

void Support::NextTo(HWND main, HWND nextTo)
{
	WINDOWPLACEMENT pos;
	GetWindowPlacement(main, &pos);

	pos.rcNormalPosition.left = pos.rcNormalPosition.right - 15;
	pos.rcNormalPosition.right += 500;
	SetWindowPlacement(nextTo, &pos);
	BringWindowToTop(nextTo);
}

HDC	Support::GetHDCParent(HWND hwnd, SIZE size)
{
	HDC resHDC = NULL;
	HBITMAP hBitmap = NULL;

	HDC hdc = GetDC(hwnd);

	resHDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, size.cx, size.cy);

	SelectObject(resHDC, hBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hdc);

	return resHDC;
}

void	Support::DrawPieChartSummary(Gdiplus::Graphics *graphics,
	PersonalFinance::ListView* listChiTieu,
	PersonalFinance::ListView* listThuNhap)
{
	using namespace Gdiplus;
	using namespace std;

	TCHAR *buffer = new TCHAR[512];

	Font font(L"Arial", 12, FontStyleBold);
	SolidBrush *black = new SolidBrush(Color(255, 0, 0, 0));
	Pen pen(Color(255, 0, 0, 0), 2);
	graphics->DrawEllipse(&pen, 24, 9, 302, 302);

	double sumChiTieu = listChiTieu->GetSumValue();
	double sumThuNhap = listThuNhap->GetSumValue();
	double total = sumChiTieu + sumThuNhap;

	double value[2] = { sumChiTieu , sumThuNhap };

	double percent[2] = { 0 };
	percent[0] = sumChiTieu / total * 100;
	percent[1] = sumThuNhap / total * 100;

	const wchar_t* title[2] = { L"Chi Tiêu", L"Thu Nhập" };

	double degree = 0;
	double lastDegree = 0;
	PointF p; // for drawing string

	if (total != 0)
	{
		for (int i = 0; i < 2; i++)
		{
			degree = percent[i] / 100 * 360;

			Color color_fill;
			color_fill.SetFromCOLORREF(LIST_COLOR[i]);

			SolidBrush *brush = new SolidBrush(color_fill);
			graphics->FillPie(brush, 25, 10, 300, 300, lastDegree, degree);
			graphics->FillRectangle(brush, 20, 350 + 30 * i, 20, 20);

			p.X = 50;
			p.Y = 350 + 30 * i;
			graphics->DrawString(title[i], -1, &font, p, black);

			Font font(L"Arial", 12, FontStyleItalic);
			swprintf_s(buffer, 512, L"(TC: %0.2f / %0.2f %%)", value[i], percent[i]);
			p.X = 150;
			graphics->DrawString(buffer, -1, &font, p, black);

			lastDegree += degree;
			delete brush;
		}
	}

	swprintf_s(buffer, 512, L"Tiết kiệm: %0.2f", sumThuNhap - sumChiTieu);
	p.X = 100;
	p.Y = 350 + 30 * 2;
	graphics->DrawString(buffer, -1, &font, p, black);

	delete black;
	delete[] buffer;
}