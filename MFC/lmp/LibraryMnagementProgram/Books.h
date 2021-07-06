#pragma once
#include <string>
using namespace std;
class Book
{
protected:
	bool rental_status;
	CString book_name;
	int book_number;
	int borrower;
public:
	Book();
	Book(int _book_number, CString _book_name);
	Book(int _book_number, CString _book_name, bool _rental_status, int _borrower);
	void set_borrower(int _borrower);
	CString get_book_name();
	int get_book_number();
	bool get_rental_status();
	int get_borrower();
	void returned();
};

