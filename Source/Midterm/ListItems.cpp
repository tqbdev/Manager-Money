#include "stdafx.h"
#include "ListItems.h"

namespace PersonalFinance
{
	ListItems::ListItems()
	{
	}

	ListItems::~ListItems()
	{
		this->ClearAll();
	}

	// Xóa toàn bộ dữ liệu
	void ListItems::ClearAll()
	{
		while (!listItems_.empty())
		{
			FinanceItem* temp = listItems_.back();
			delete temp;
			listItems_.pop_back();
		}

		statGroup_.clear();
	}

	// Thêm một item
	void ListItems::Add(FinanceItem* item)
	{
		listItems_.push_back(item);
		statGroup_[item->GetType()] += item->GetPrice();
	}

	// Lấy ra một item
	FinanceItem* ListItems::GetItem(int index)
	{
		if (index < 0 || index >= listItems_.size()) return NULL;
		return listItems_.at(index);
	}

	// Thay đổi một item
	void ListItems::ModifyItem(FinanceItem* newItem, int index)
	{
		this->statGroup_[newItem->GetType()] += newItem->GetPrice();

		FinanceItem* oldItem = this->GetItem(index);
		this->statGroup_[oldItem->GetType()] -= oldItem->GetPrice();
		delete oldItem;
		this->listItems_[index] = newItem;
	}

	// Xóa một item
	void ListItems::DeleteItem(std::deque<FinanceItem*>::iterator it)
	{
		FinanceItem* temp = *it;
		statGroup_[temp->GetType()] -= temp->GetPrice();
		listItems_.erase(it);
	}

	// Get Sum
	double ListItems::SumValue()
	{
		double sum = 0;
		for (auto it = statGroup_.begin(); it != statGroup_.end(); it++)
		{
			sum += it->second;
		}

		return sum;
	}

	// Ghi dữ liệu list xuống file
	void ListItems::Write(std::wofstream &output)
	{
		for (int i = 0; i < listItems_.size(); i++)
		{
			if (i != 0) output << std::endl;
			listItems_[i]->Write(output);
		}
	}

	// Kiểm tra xem list có trống hay không
	bool ListItems::IsEmpty()
	{
		return listItems_.empty();
	}
}