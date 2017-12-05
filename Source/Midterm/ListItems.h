#pragma once
#include "FinanceItem.h"
#include <deque>
#include <unordered_map>

namespace PersonalFinance
{
	class ListItems
	{
	private:
		std::deque<FinanceItem*> listItems_;
		std::unordered_map<std::wstring, double> statGroup_;
	public:
		ListItems();
		~ListItems();

		// Kiểm tra xem list có trống hay không?
		bool IsEmpty();
	
		// Thêm một item
		void Add(FinanceItem* item);
		// Lấy ra một item
		FinanceItem* GetItem(int index);
		// Thay đổi một item
		void ModifyItem(FinanceItem* newItem, int index);
		// Xóa một item
		void DeleteItem(std::deque<FinanceItem*>::iterator it);

		// Size
		inline int Size() { return listItems_.size(); }
		// Xóa tất cả item
		void ClearAll();
		// Tính tổng
		double SumValue();
		// Lấy Size của Statistic list
		inline int SizeStatistic() { return statGroup_.size(); }

		// Iterator
		// Iterator begin của Statistic list
		inline auto StatBegin() { return statGroup_.begin(); }
		// Iterator end của Statistic list
		inline auto StatEnd() { return statGroup_.end(); }
		// Iterator begin của list items
		inline auto ListBegin() { return listItems_.begin(); }
		// Iterator end của list items
		inline auto ListEnd() { return listItems_.end(); }

		// Ghi dữ liệu list xuống file
		void Write(std::wofstream &output);
	};
}