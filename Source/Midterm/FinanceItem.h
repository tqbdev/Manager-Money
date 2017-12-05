#pragma once
#include <string>

namespace PersonalFinance
{
	class FinanceItem
	{
	private:
		std::wstring type_;
		std::wstring name_;
		double price_;
		long id_;
	public:
		FinanceItem();
		FinanceItem(long id, std::wstring type, std::wstring name, double price);
		~FinanceItem();

		inline void			SetID(long id)    { this->id_ = id; }
		inline long			GetID()		const { return id_; }

		inline LPCWSTR		GetType()	const { return const_cast<LPCWSTR>(type_.c_str()); }
		inline LPCWSTR		GetName()	const { return const_cast<LPCWSTR>(name_.c_str()); }
		inline double		GetPrice()	const { return price_; }

		// Đọc một item từ file
		bool				Read(std::wifstream &input);
		// Ghi nội dung một item xuống file
		void				Write(std::wofstream &output);
	};
}