#include "stdafx.h"
#include "FinanceItem.h"

namespace PersonalFinance
{
	FinanceItem::FinanceItem()
	{
		this->price_ = -1;
		this->id_ = -1;
	}

	FinanceItem::FinanceItem(long id, std::wstring type, std::wstring name, double price)
	{
		this->id_ = id;
		this->type_ = type;
		this->name_ = name;
		this->price_ = price;
	}

	FinanceItem::~FinanceItem()
	{
	}

	bool FinanceItem::Read(std::wifstream &input)
	{
		std::wstring temp;
		std::getline(input, temp);
		if (temp.size() == 0) return false;
		int first = 0, last = 0;
		int len = temp.size();
		
		// Tìm vị trí dấu , thứ 1 trong file csv
		for (int i = 0; i < len; i++)
		{
			if (temp[i] == wchar_t(','))
			{
				first = i;
				break;
			}
		}

		// Tìm vị trí dấu , thứ 2 trong file csv
		for (int i = len - 1; i >= 0; i--)
		{
			if (temp[i] == wchar_t(','))
			{
				last = i;
				break;
			}
		}

		wchar_t t = '\"';

		// Loại là từ đầu cho tới vị trí dấu , thứ 1
		std::wstring& type = temp.substr(0, first);		
		if (type[0] == t) type.erase(0, 1);
		if (type[first - 2] == t) type.erase(first - 2, 1);
		if (type.length() == 0) return false;

		this->type_ = type;

		// Tên là từ dấu , thứ 1 cho tới dấu , thứ 2
		std::wstring& name = temp.substr(++first, last - first);
		if (name[0] == t) name.erase(0, 1);
		if (name[last - first - 2] == t) name.erase(last - first - 2, 1);
		if (name.length() == 0) return false;

		this->name_ = name;

		// Giá (value) là từ dấu , thứ 2 cho đến hết
		std::wstring& price = temp.substr(++last);
		if (price[0] == t) price.erase(0, 1);
		if (price[price.length() - 1] == t) price.erase(price.length() - 1, 1);
		if (price.length() == 0) return false;

		this->price_ = std::stod(price);
		
		//// Nếu còn dấu tab thì loại bỏ
		//if (input.peek() == wchar_t('\t')) input.get();
		return true;
	}

	void FinanceItem::Write(std::wofstream &output)
	{
		output << this->type_ << L",";

		if (this->name_.find(wchar_t(',')) != -1)
		{
			output << L"\"" << this->name_ << L"\",";
		}
		else
		{
			output << this->name_ << L",";
		}
		output << this->price_;
	}
}