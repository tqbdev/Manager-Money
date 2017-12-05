#pragma once
#include <gdiplus.h>

extern Gdiplus::GdiplusStartupInput	gdiplusStartupInput;
extern ULONG_PTR					gdiplusToken;

namespace Midterm
{
	class GDIPlusSetup
	{
	public:
		static void GDIPlusInit();
		static void GDIPlusDestroy();
	};
}