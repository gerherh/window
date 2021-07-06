#pragma once

// ODBC API 헤더
#include "pch.h"
#include "LibraryMember.h"
#include "Books.h"
#include <odbcinst.h>
#include <sqlext.h>
#include <vector>
#include <algorithm>
#include <atldbcli.h>
#include <afxdb.h>
// CLibraryMnagementProgramDlg 대화 상자
class CLibraryMnagementProgramDlg : public CDialogEx
{
	// 생성입니다.
public:
	CLibraryMnagementProgramDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIBRARYMNAGEMENTPROGRAM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// ODBC

public:
	CRect m_rcMinimumDialog;
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedMemberRegistrationButton();
	afx_msg void OnBnClickedMemberDeleteButton();
	afx_msg void OnBnClickedInformationButton();
	afx_msg void OnBnClickedRentalButton();
	afx_msg void OnBnClickedReturnButton();
	afx_msg void OnBnClickedBookRegistrationButton();
	afx_msg void OnBnClickedBookSearchButton();
	afx_msg void OnBnClickedBookListButton();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedMemberSearchButton();
	afx_msg void OnBnClickedBookDeleteButton();

	CDatabase db;
	CListCtrl list_ctrl;
	CEdit m_edit_rental_book_number;
	CEdit m_edit_rental_member_number;
	CEdit m_edit_return;
	CEdit m_edit_book_registration;
	CEdit m_edit_book_search;
	CEdit m_edit_member_name_registration;
	CEdit m_edit_delete_member;
	CEdit m_edit_button_number_to_delete;
	CEdit m_edit_search;

	vector<Member> member_vector;
	vector<Book> book_vector;

	void clear_list_ctrl();
	void get_all_data_from_member();
	void get_all_data_from_book();
	int get_last_member_num();
	int get_last_book_num();
	int get_book_vector_index_by_book_number(int book_number);
	int get_member_vector_index_by_member_number(int member_number);
	bool is_book_exist(int book_number);
	bool is_member_exist(int member_number);

	CString get_book_name_by_book_num(int book_number);
	CString get_a_list_of_books_on_loan_by_number(int member_num);
	CString get_the_numbers_of_the_books_on_loan_byn_umber(int member_num);

	void sort_book_vector(vector<Book>& v);
	void sort_member_vector(vector<Member>& v);



};



