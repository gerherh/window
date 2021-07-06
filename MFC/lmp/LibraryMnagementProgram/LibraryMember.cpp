#include "pch.h"
#include "LibraryMember.h"

Member::Member()
{
	member_number = 0;
	member_name = _T(" ");
}
Member::Member(int _library_member_number, CString _name)
{
	member_number = _library_member_number;
	member_name = _name;
}
Member::Member(int _library_member_number, CString _name, CString _book_num, CString _book_name)
{
	member_number = _library_member_number;
	member_name = _name;

	CString   resToken;
	int curPos = 0;
	resToken = _book_num.TrimRight(_T(" ")).Tokenize(_T(","), curPos);
	book_num_vector.push_back(resToken);
	while (resToken != "")
	{
		resToken = _book_num.Tokenize(_T(","), curPos);
		if (resToken == "")
		{
			break;
		}
		book_num_vector.push_back(resToken);
	};

	curPos = 0;
	resToken = _book_name.TrimRight(_T(" ")).Tokenize(_T(","), curPos);
	book_name_vector.push_back(resToken);
	while (resToken != "")
	{
		resToken = _book_name.Tokenize(_T(","), curPos);
		if (resToken == "")
		{
			break;
		}
		book_name_vector.push_back(resToken);
	};


}
void Member::borrow_book(Book& book)
{
	CString book_number_cstr;
	book_number_cstr.Format(_T("%d"), book.get_book_number());
	book_name_vector.push_back(book.get_book_name());
	book_num_vector.push_back(book_number_cstr);
}

void Member::return_book(CString book_num)
{
	for (int i = 0; i < get_book_num_vector().size(); i++)
	{
		if (book_num_vector[i] == book_num)
		{
			book_num_vector.erase(book_num_vector.begin()+i);
			book_name_vector.erase(book_name_vector.begin() + i);

		}
	}
}

int Member::get_member_number()
{
	return member_number;
}
CString Member::get_member_name()
{
	return member_name;
}


vector<CString>& Member::get_book_num_vector()
{
	return book_num_vector;
}

vector<CString>& Member::get_book_name_vector()
{
	return book_name_vector;
}

