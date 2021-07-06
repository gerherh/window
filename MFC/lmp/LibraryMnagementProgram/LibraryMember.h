#pragma once
#include "Books.h"
#include <string>
#include <map>
#include <vector>
using namespace std;
class Member
{
private:
	int member_number;
	CString member_name;
	vector<CString> book_num_vector;
	vector<CString> book_name_vector;
public:
	Member();
	Member(int _library_member_number, CString _name);
	Member(int _library_member_number, CString _name, CString _book_num, CString _book_name);
	
	void borrow_book(Book& book);
	void return_book(CString book_num);
	int get_member_number();
	CString get_member_name();
	vector<CString>& get_book_num_vector();
	vector<CString>& get_book_name_vector();
};



