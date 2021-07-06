
// LibraryMnagementProgramDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "LibraryMnagementProgram.h"
#include "LibraryMnagementProgramDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ODBC API 라이브러리

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLibraryMnagementProgramDlg 대화 상자

CLibraryMnagementProgramDlg::CLibraryMnagementProgramDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIBRARYMNAGEMENTPROGRAM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//자신이 설정해주었던 DSN 이름을 쓰고 id,pass를 입력
	db.OpenEx(_T("DSN=library;UID=mfc;PWD==r2BH+*hkU5yPtpz")); /* 일회용 비밀번호임*/
	get_all_data_from_member();
	get_all_data_from_book();
	
}

void CLibraryMnagementProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LIST_CTRL, list_ctrl);
	DDX_Control(pDX, ENTERED_MEMBER_NAME_TO_REGISTRATION, m_edit_member_name_registration);
	DDX_Control(pDX, ENTERED_MEMBER_NUMBER_TO_DELETE, m_edit_delete_member);
	DDX_Control(pDX, ENTERED_MEMBER_REGISTRATION_NUMBER_TO_BORROW, m_edit_rental_member_number);
	DDX_Control(pDX, ENTERED_BOOK_NUMBER_TO_BORROW, m_edit_rental_book_number);
	DDX_Control(pDX, ENTERED_MEMBER_REGISTRATION_NUMBER_TO_BORROW, m_edit_rental_member_number);
	DDX_Control(pDX, ENTERED_BOOK_NUMBER_TO_RETURN, m_edit_return);
	DDX_Control(pDX, ENTERED_BOOK_NAME_TO_REGISTRATION_BOOK, m_edit_book_registration);
	DDX_Control(pDX, ENTERED_BOOK_NAME_TO_SEARCH, m_edit_book_search);
	DDX_Control(pDX, ENTERED_BOOK_NUMBER_TO_DELETE, m_edit_button_number_to_delete);
	DDX_Control(pDX, INDIVIDUAL_MEMBER_INFORMATION, m_edit_search);
}

BEGIN_MESSAGE_MAP(CLibraryMnagementProgramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(MEMBER_REGISTRATION_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedMemberRegistrationButton)
	ON_BN_CLICKED(MEMBER_DELETE_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedMemberDeleteButton)
	ON_BN_CLICKED(MEMBER_INFORMATION_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedInformationButton)
	ON_BN_CLICKED(BOOK_RENTAL_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedRentalButton)
	ON_BN_CLICKED(BOOK_RETURN_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedReturnButton)
	ON_BN_CLICKED(BOOK_REGISTRATION_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedBookRegistrationButton)
	ON_BN_CLICKED(BOOK_SEARCH_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedBookSearchButton)
	ON_BN_CLICKED(BOOK_LIST_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedBookListButton)
	ON_WM_DESTROY()
	ON_BN_CLICKED(DELETE_BOOK_BUTTON, &CLibraryMnagementProgramDlg::OnBnClickedBookDeleteButton)
	ON_BN_CLICKED(IDC_BUTTON1, &CLibraryMnagementProgramDlg::OnBnClickedMemberSearchButton)
END_MESSAGE_MAP()


// CLibraryMnagementProgramDlg 메시지 처리기

BOOL CLibraryMnagementProgramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	/*처음 창 크기를 얻는 부분*/
	GetClientRect(&m_rcMinimumDialog);
	CalcWindowRect(m_rcMinimumDialog);
	
	GetDlgItem(ENTERED_MEMBER_NAME_TO_REGISTRATION)->SetWindowText(_T("이름 입력"));
	GetDlgItem(ENTERED_MEMBER_NUMBER_TO_DELETE)->SetWindowText(_T("회원 번호 입력"));
	GetDlgItem(INDIVIDUAL_MEMBER_INFORMATION)->SetWindowText(_T("회원 이름 입력"));
	GetDlgItem(ENTERED_MEMBER_REGISTRATION_NUMBER_TO_BORROW)->SetWindowText(_T("회원 번호"));
	GetDlgItem(ENTERED_BOOK_NUMBER_TO_BORROW)->SetWindowText(_T("책 번호"));
	GetDlgItem(ENTERED_BOOK_NUMBER_TO_RETURN)->SetWindowText(_T("책 번호"));
	GetDlgItem(ENTERED_BOOK_NAME_TO_REGISTRATION_BOOK)->SetWindowText(_T("책 이름"));
	GetDlgItem(ENTERED_BOOK_NAME_TO_SEARCH)->SetWindowText(_T("책 이름"));
	GetDlgItem(ENTERED_BOOK_NUMBER_TO_DELETE)->SetWindowText(_T("책 번호"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CLibraryMnagementProgramDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CLibraryMnagementProgramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CLibraryMnagementProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLibraryMnagementProgramDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CDialogEx::OnGetMinMaxInfo(lpMMI);
	/*처음 크기 이상으로 줄어들지는 않게 하는 부분*/
	lpMMI->ptMinTrackSize.x = m_rcMinimumDialog.Width();
	lpMMI->ptMinTrackSize.y = m_rcMinimumDialog.Height();
}

/*회원 등록*/
void CLibraryMnagementProgramDlg::OnBnClickedMemberRegistrationButton()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString member_name_cstr;
	int new_member_num;
	sort_member_vector(member_vector);
	
	if (member_vector.size() == 0)
	{
		new_member_num = 1;
	}
	else
	{
		new_member_num = member_vector[member_vector.size() - 1].get_member_number() + 1;
	}
	
	CString cquery;
	m_edit_member_name_registration.GetWindowTextW(member_name_cstr);
	cquery.Format(_T("INSERT INTO [dbo].[member]([member_number], [member_name])VALUES(%d, '%s')"), new_member_num,member_name_cstr);

	/*입력 쿼리 실행*/
	try
	{
		db.ExecuteSQL(cquery);
	}
	catch (CDBException* e) //에러 확인.
	{
		int errCode = e->ReportError();
	}
	GetDlgItem(ENTERED_MEMBER_NAME_TO_REGISTRATION)->SetWindowText(_T("이름 입력"));
	
	member_vector.push_back(Member(new_member_num, member_name_cstr));

}


void CLibraryMnagementProgramDlg::OnBnClickedMemberDeleteButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int member_vector_index;
	CString member_number_cstr;
	CString cquery;
	m_edit_delete_member.GetWindowTextW(member_number_cstr);
	if (member_vector[get_member_vector_index_by_member_number(_ttoi(member_number_cstr))].get_book_num_vector()[0] != _T(""))
	{
		
		MessageBox(_T("책을 반납해야 삭제할수 있습니다"));
		GetDlgItem(ENTERED_MEMBER_NUMBER_TO_DELETE)->SetWindowText(_T("회원 번호 입력"));
		return;
	}

	cquery.Format(_T("DELETE FROM [dbo].[member]WHERE member_number = %d"), _ttoi(member_number_cstr));

	/*삭제 쿼리 실행*/
	try
	{
		db.ExecuteSQL(cquery);
	}
	catch (CDBException* e) //에러 확인.
	{
		int errCode = e->ReportError();
	}
	GetDlgItem(ENTERED_MEMBER_NUMBER_TO_DELETE)->SetWindowText(_T("회원 번호 입력"));

	member_vector_index = get_member_vector_index_by_member_number(_ttoi(member_number_cstr));
	member_vector.erase(member_vector.begin() + member_vector_index);
}

/*회원정보 출력*/
void CLibraryMnagementProgramDlg::OnBnClickedInformationButton()
{

	member_vector.clear();
	book_vector.clear();
	get_all_data_from_member();
	get_all_data_from_book();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	clear_list_ctrl();
	// member 테이블에서 회원 번호와 이름만 가져와서 뿌려줄거임
	list_ctrl.InsertColumn(0, _T("회원 번호"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(1, _T("이름"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(2, _T("대여중인 책 번호"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(3, _T("대여중인 책 이름"), LVCFMT_CENTER, 200, -1);
	/*리스트에 값을 다 넣고 실행해야한다고 함*/
	list_ctrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	/* members == db에서 읽어온 member들을 저장해놓은 벡터*/
	CString cstr_member_num;
	CString book_nums_on_loan, book_names_on_loan, tmp;
	vector<CString> bnumv;
	vector<CString> bnamev;
	sort_member_vector(member_vector);
	for (int row = 0; row < member_vector.size(); row++)
	{
		/*행의 첫번째 열에 InsertItem을 해야 그 행의 나머지 열에도 입력할수 있음*/
		list_ctrl.InsertItem(row, _T(""));
		for (int col = 0; col < 4; col++)
		{
			switch (col)
			{

			case 0:
				/*member_number*/
				cstr_member_num.Format(_T("%d"), member_vector[row].get_member_number());
				list_ctrl.SetItem(row, col, LVIF_TEXT, cstr_member_num.TrimRight(_T(" ")), 0, 0, 0, NULL);
				break;
				/*member_name*/
			case 1:
				
				list_ctrl.SetItem(row, col, LVIF_TEXT, member_vector[row].get_member_name().TrimRight(_T(" ")), 0, 0, 0, NULL);
				break;
				/*book_number*/
			case 2:
				bnumv = member_vector[row].get_book_num_vector();
				for (int i = 0; i < bnumv.size(); i++)
				{
					if (i == 0)
					{
						if (bnumv[0] == _T("-"))
						{
							book_nums_on_loan = _T("없음");
						}
						else
						{
							book_nums_on_loan = bnumv[i];
						}
					}
					else
					{
						book_nums_on_loan += _T(",") + bnumv[i];
					}
				}
				list_ctrl.SetItem(row, col, LVIF_TEXT, book_nums_on_loan.TrimRight(_T(" ")), 0, 0, 0, NULL);
				break;
				/*book_name*/
			case 3:
				bnamev = member_vector[row].get_book_name_vector();
		
				for (int i = 0; i < bnamev.size(); i++)
				{
					if (i == 0)
					{
						if (bnamev[0] == _T("-"))
						{
							book_names_on_loan = _T("없음");
						}
						else
						{
							book_names_on_loan = bnamev[i];
						}

					}
					else
					{
						book_names_on_loan += _T(",") + bnamev[i];
					}
				}
				
				list_ctrl.SetItem(row, col, LVIF_TEXT, book_names_on_loan.TrimRight(_T(" ")), 0, 0, 0, NULL);
				break;
			}
		}
	}

}

void CLibraryMnagementProgramDlg::OnBnClickedRentalButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString member_number_cstr, book_number_cstr, book_name, book_num, books_on_loan, new_books_on_loan, book_nums_on_loan, new_book_num_on_loan;
	CString cquery, cquery1;
	int book_vector_index;
	
	m_edit_rental_member_number.GetWindowTextW(member_number_cstr);
	m_edit_rental_book_number.GetWindowTextW(book_number_cstr);
	
	/*책 번호로 책 이름을 찾아야함*/
	
	if (!is_book_exist(_ttoi(book_number_cstr)))
	{
		MessageBox(_T("책 번호를 잘못 입력했습니다."));
		return;
	}
	else
	{
		book_vector_index = get_book_vector_index_by_book_number(_ttoi(book_number_cstr));
		book_name = book_vector[book_vector_index].get_book_name();
		book_num .Format(_T("%d"), book_vector[book_vector_index].get_book_number());
	}
	/*대여중인 책인지 확인*/
	if (book_vector[book_vector_index].get_rental_status() == TRUE)
	{
		MessageBox(_T("대여중인 책입니다"));
		GetDlgItem(ENTERED_MEMBER_REGISTRATION_NUMBER_TO_BORROW)->SetWindowText(_T("회원 번호"));
		GetDlgItem(ENTERED_BOOK_NUMBER_TO_BORROW)->SetWindowText(_T("책 번호"));
		return;
	}
	/*회원 번호 존재 확인*/
	if (!is_member_exist(_ttoi(member_number_cstr)))
	{
		MessageBox(_T("회원 번호를 잘못 입력했습니다."));
		GetDlgItem(ENTERED_MEMBER_REGISTRATION_NUMBER_TO_BORROW)->SetWindowText(_T("회원 번호"));
		GetDlgItem(ENTERED_BOOK_NUMBER_TO_BORROW)->SetWindowText(_T("책 번호"));
		return;
	}
	if (member_vector[get_member_vector_index_by_member_number(_ttoi(member_number_cstr))].get_book_num_vector().size() == 5)
	{
		GetDlgItem(ENTERED_MEMBER_REGISTRATION_NUMBER_TO_BORROW)->SetWindowText(_T("회원 번호"));
		GetDlgItem(ENTERED_BOOK_NUMBER_TO_BORROW)->SetWindowText(_T("책 번호"));
		MessageBox(_T("5권까지만 빌릴수 있습니다."));
		GetDlgItem(ENTERED_MEMBER_REGISTRATION_NUMBER_TO_BORROW)->SetWindowText(_T("회원 번호"));
		GetDlgItem(ENTERED_BOOK_NUMBER_TO_BORROW)->SetWindowText(_T("책 번호"));
		return;
	}

	books_on_loan = get_a_list_of_books_on_loan_by_number(_ttoi(member_number_cstr));
	if (books_on_loan == "")
	{
		new_books_on_loan = _T('\'') + book_name.TrimRight(_T(" ")) + _T('\'');
	}
	else
	{
		new_books_on_loan = _T('\'') + books_on_loan + _T(',') + book_name.TrimRight(_T(" ")) + _T('\'');
	}

	book_nums_on_loan = get_the_numbers_of_the_books_on_loan_byn_umber(_ttoi(member_number_cstr));
	if (book_nums_on_loan == "")
	{
		new_book_num_on_loan = _T('\'') + book_num.TrimRight(_T(" ")) + _T('\'');
	}
	else
	{
		new_book_num_on_loan = _T('\'') + book_nums_on_loan + _T(',') + book_num.TrimRight(_T(" ")) + _T('\'');
	}

	cquery.Format(_T("UPDATE [dbo].[member]SET[book_number] = %s, [book_name] = %s WHERE[member_number] = %d"),
		new_book_num_on_loan,
		new_books_on_loan,
		_ttoi(member_number_cstr)
		);
	cquery1.Format(_T("UPDATE [dbo].[book]SET [rental_status] = %d ,[borrower] = %d WHERE [book_number] = %d"),
		1, 
		_ttoi(member_number_cstr),
		_ttoi(book_number_cstr));
	/*입력 쿼리 실행*/
	try
	{
		db.ExecuteSQL(cquery);
		db.ExecuteSQL(cquery1);
	}
	catch (CDBException* e) 
	{
		int errCode = e->ReportError();
	}
	member_vector[_ttoi(member_number_cstr)].borrow_book(book_vector[book_vector_index]);
	book_vector[book_vector_index].set_borrower(_ttoi(member_number_cstr));

	GetDlgItem(ENTERED_MEMBER_REGISTRATION_NUMBER_TO_BORROW)->SetWindowText(_T("회원 번호"));
	GetDlgItem(ENTERED_BOOK_NUMBER_TO_BORROW)->SetWindowText(_T("책 번호"));
}


void CLibraryMnagementProgramDlg::OnBnClickedReturnButton()
{
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString book_number_to_return, cquery, cquery1;;
	int member_number, member_vector_index, book_vector_index;
	m_edit_return.GetWindowTextW(book_number_to_return);
	book_vector_index = get_book_vector_index_by_book_number(_ttoi(book_number_to_return));
	member_number = book_vector[book_vector_index].get_borrower();
	member_vector_index = get_member_vector_index_by_member_number(member_number);

	if (book_vector[book_vector_index].get_rental_status() == false)
	{
		MessageBox(_T("빌린적 없는 책입니다"));
		return;
	}
	else
	{
		member_vector[member_vector_index].return_book(book_number_to_return);
		book_vector[book_vector_index].returned();
	}
	CString book_number = _T("");
	CString	book_name = _T("");
	CString tmp = _T("");
	
	for (int i = 0; i < member_vector[member_vector_index].get_book_num_vector().size(); i++)
	{
		if (i == 0)
		{
			tmp = member_vector[member_vector_index].get_book_num_vector()[0];
			book_number = tmp;
			tmp = member_vector[member_vector_index].get_book_name_vector()[0];
			book_name = tmp;
		}
		else
		{
			tmp = member_vector[member_vector_index].get_book_num_vector()[i];
			book_number += _T(",") + tmp;
			tmp = member_vector[member_vector_index].get_book_name_vector()[i];
			book_name += _T(",") + tmp;
		}
	}

	if (book_number == _T(""))
	{
		cquery.Format(_T("UPDATE [dbo].[member]SET [book_number] = '%s',[book_name] = '%s' WHERE [member_number] = %d"), _T(""), _T(""), member_number);
	}
	else
	{
		cquery.Format(_T("UPDATE [dbo].[member]SET [book_number] = '%s',[book_name] = '%s' WHERE [member_number] = %d"), book_number, book_name, member_number);
	}
	
	cquery1.Format(_T("UPDATE [dbo].[book]SET [rental_status] = %d,[borrower] = %d WHERE [book_number] = %d"),0,0,_ttoi(book_number_to_return));

	/*입력 쿼리 실행*/
	try
	{
		db.ExecuteSQL(cquery);
		db.ExecuteSQL(cquery1);
		MessageBox(_T("반납 완료"));
	}
	catch (CDBException* e) 
	{
		int errCode = e->ReportError();
	}
	
	GetDlgItem(ENTERED_BOOK_NUMBER_TO_RETURN)->SetWindowText(_T("책 번호"));
}


void CLibraryMnagementProgramDlg::OnBnClickedBookRegistrationButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString book_name_cstr;
	int new_book_num;

	sort_book_vector(book_vector);
	if (book_vector.size() == 0)
	{
		new_book_num = 1;
	}
	else
	{
		new_book_num = book_vector[book_vector.size() - 1].get_book_number() + 1;
	}
	
	CString cquery;
	m_edit_book_registration.GetWindowTextW(book_name_cstr);;
	cquery.Format(_T("INSERT INTO [dbo].[book]([book_number], [book_name])VALUES(%d, '%s')"), new_book_num, book_name_cstr);

	/*입력 쿼리 실행*/
	try
	{
		db.ExecuteSQL(cquery);
	}
	catch (CDBException* e) //에러 확인.
	{
		int errCode = e->ReportError();
	}
	GetDlgItem(ENTERED_BOOK_NAME_TO_REGISTRATION_BOOK)->SetWindowText(_T("책 이름"));

	book_vector.push_back(Book(new_book_num, book_name_cstr));
}


void CLibraryMnagementProgramDlg::OnBnClickedBookSearchButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString book_search_name;
	m_edit_book_search.GetWindowTextW(book_search_name);
	vector<int> index_of_searched_names;
	member_vector.clear();
	book_vector.clear();
	get_all_data_from_member();
	get_all_data_from_book();
	// 리스트컨트롤 초기화
	clear_list_ctrl();
	// 책 리스트 => 컬럽 4개
	list_ctrl.InsertColumn(0, _T("책 번호"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(1, _T("책 이름"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(2, _T("대여 상태"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(3, _T("대여중인 사람의 회원 번호"), LVCFMT_CENTER, 200, -1);

	list_ctrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	/*
	for (int i = 0; i < list_ctrl.GetHeaderCtrl()->GetItemCount(); ++i)
		list_ctrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	*/

	sort_book_vector(book_vector);
	CString cstr_book_num, cstr_book_rental_status, borrower;



	for (int i = 0; i < book_vector.size(); i++)
	{
		if (book_vector[i].get_book_name().TrimRight(_T(" ")) == book_search_name)
		{
			index_of_searched_names.push_back(i);
		}
	}
	
	for (int row = 0; row < index_of_searched_names.size(); row++)
	{
		/*행의 첫번째 열에 InsertItem을 해야 그 행의 나머지 열에도 입력할수 있음*/
		list_ctrl.InsertItem(row, _T(""));
		for (int col = 0; col < 4; col++)
		{
			switch (col)
			{
			case 0:
				/*book_number*/
				cstr_book_num.Format(_T("%d"), book_vector[index_of_searched_names[row]].get_book_number());
				list_ctrl.SetItem(row, col, LVIF_TEXT, cstr_book_num, 0, 0, 0, NULL);
				break;
				/*book_name*/
			case 1:
				list_ctrl.SetItem(row, col, LVIF_TEXT, book_vector[index_of_searched_names[row]].get_book_name(), 0, 0, 0, NULL);
				break;
				/*rental_status*/
			case 2:
				if (book_vector[index_of_searched_names[row]].get_rental_status() == 0)
				{
					cstr_book_rental_status = _T("대여 가능");
				}
				else
				{
					cstr_book_rental_status = _T("대여 불가");
				}
				list_ctrl.SetItem(row, col, LVIF_TEXT, cstr_book_rental_status, 0, 0, 0, NULL);
				break;
				/*borrower*/
			case 3:
				if (book_vector[index_of_searched_names[row]].get_borrower() == 0)
				{
					list_ctrl.SetItem(row, col, LVIF_TEXT, _T("-"), 0, 0, 0, NULL);
				}
				else
				{
					borrower.Format(_T("%d"), book_vector[index_of_searched_names[row]].get_borrower());
					list_ctrl.SetItem(row, col, LVIF_TEXT, borrower, 0, 0, 0, NULL);
				}
				break;
			}
		}
	}
	GetDlgItem(ENTERED_BOOK_NAME_TO_SEARCH)->SetWindowText(_T("책 이름"));
}


void CLibraryMnagementProgramDlg::OnBnClickedBookListButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	member_vector.clear();
	book_vector.clear();
	get_all_data_from_member();
	get_all_data_from_book();
	// 리스트컨트롤 초기화
	clear_list_ctrl();
	// 책 리스트 => 컬럽 4개
	list_ctrl.InsertColumn(0, _T("책 번호"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(1, _T("책 이름"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(2, _T("대여 상태"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(3, _T("대여중인 사람의 회원 번호"), LVCFMT_CENTER, 200, -1);

	list_ctrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	/*
	for (int i = 0; i < list_ctrl.GetHeaderCtrl()->GetItemCount(); ++i)
		list_ctrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	*/

	sort_book_vector(book_vector);
	
	CString cstr_book_num, cstr_book_rental_status, borrower;
	
	for (int row = 0; row < book_vector.size(); row++)
	{
		/*행의 첫번째 열에 InsertItem을 해야 그 행의 나머지 열에도 입력할수 있음*/
		list_ctrl.InsertItem(row, _T(""));
		for (int col = 0; col < 4; col++)
		{
			switch (col)
			{

			case 0:
				/*book_number*/
				cstr_book_num.Format(_T("%d"), book_vector[row].get_book_number());
				list_ctrl.SetItem(row, col, LVIF_TEXT, cstr_book_num, 0, 0, 0, NULL);
				break;
				/*book_name*/
			case 1:
				list_ctrl.SetItem(row, col, LVIF_TEXT, book_vector[row].get_book_name(), 0, 0, 0, NULL);
				break;
				/*rental_status*/
			case 2:
				if (book_vector[row].get_rental_status() == 0)
				{
					cstr_book_rental_status = _T("대여 가능");
				}
				else
				{
					cstr_book_rental_status = _T("대여 불가");
				}
				list_ctrl.SetItem(row, col, LVIF_TEXT, cstr_book_rental_status, 0, 0, 0, NULL);
				break;
				/*borrower*/
			case 3:
				if (book_vector[row].get_borrower() == 0)
				{
					list_ctrl.SetItem(row, col, LVIF_TEXT, _T("-"), 0, 0, 0, NULL);
				}
				else
				{
					borrower.Format(_T("%d"), book_vector[row].get_borrower());
					list_ctrl.SetItem(row, col, LVIF_TEXT, borrower, 0, 0, 0, NULL);
				}

				break;
			}
		}
	}
}


void CLibraryMnagementProgramDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	/*db 연결 종료*/
	db.Close();


}

void CLibraryMnagementProgramDlg::clear_list_ctrl()
{
	list_ctrl.DeleteAllItems();
	for (int i = 0; i < 6; i++)
	{
		list_ctrl.DeleteColumn(0);
	}
}

int CLibraryMnagementProgramDlg::get_last_member_num()
{

	CString tmp;
	CRecordset rs(&db);
	try
	{
		rs.Open(CRecordset::dynaset, _T("SELECT [member_number] FROM member"));        //테이블의모든내용선택
	}
	catch (CDBException* e)
	{
		e->ReportError();      //디폴트는 오류시에 메시지 박스를 띄워준다
	}
	//GetODBCFieldCount 함수는 필드수(열의수) 를 알려줌
	short col = rs.GetODBCFieldCount();
	//행
	while (!rs.IsEOF())
	{
		//열
		for (short i = 0; i < col; i++)
		{
			rs.GetFieldValue(i, tmp);

		}
		//다음 행으로 이동
		rs.MoveNext();
	}

	return _ttoi(tmp);
}
int CLibraryMnagementProgramDlg::get_last_book_num()
{

	CString tmp;
	CRecordset rs(&db);
	try
	{
		rs.Open(CRecordset::dynaset, _T("SELECT [book_number] FROM book"));        //테이블의모든내용선택
	}
	catch (CDBException* e)
	{
		e->ReportError();      //디폴트는 오류시에 메시지 박스를 띄워준다
	}
	//GetODBCFieldCount 함수는 필드수(열의수) 를 알려줌
	short col = rs.GetODBCFieldCount();
	//행
	while (!rs.IsEOF())
	{
		//열
		for (short i = 0; i < col; i++)
		{
			rs.GetFieldValue(i, tmp);

		}
		//다음 행으로 이동
		rs.MoveNext();
	}
	return _ttoi(tmp);
}

void CLibraryMnagementProgramDlg::get_all_data_from_member()
{
	CString tmp[4];
	CRecordset rs(&db);
	try
	{
		rs.Open(CRecordset::dynaset, _T("SELECT * FROM member"));        //테이블의모든내용선택
	}
	catch (CDBException* e)
	{
		e->ReportError();      //디폴트는 오류시에 메시지 박스를 띄워준다
	}

	//GetODBCFieldCount 함수는 필드수(열의수) 를 알려줌
	short col = rs.GetODBCFieldCount();
	
	//행
	while (!rs.IsEOF())
	{
		//열
		for (short i = 0; i < col; i++)
		{
			rs.GetFieldValue(i, tmp[i]);
			
		}
		Member library_member(_ttoi(tmp[0]), tmp[1], tmp[2], tmp[3]);
		member_vector.push_back(library_member);
		//다음 행으로 이동
		rs.MoveNext();
	}
}
void CLibraryMnagementProgramDlg::get_all_data_from_book()
{
	CString tmp[4];
	CRecordset rs(&db);
	try
	{
		rs.Open(CRecordset::dynaset, _T("SELECT * FROM book"));        //테이블의모든내용선택
	}
	catch (CDBException* e)
	{
		e->ReportError();      //디폴트는 오류시에 메시지 박스를 띄워준다
	}

	//GetODBCFieldCount 함수는 필드수(열의수) 를 알려줌
	short col = rs.GetODBCFieldCount();

	//행
	while (!rs.IsEOF())
	{
		//열
		for (short i = 0; i < col; i++)
		{
			rs.GetFieldValue(i, tmp[i]);
		}
		Book book(_ttoi(tmp[0]),tmp[1], _ttoi(tmp[2]), _ttoi(tmp[3]));
		book_vector.push_back(book);
		//다음 행으로 이동
		rs.MoveNext();
	}
}

CString CLibraryMnagementProgramDlg::get_book_name_by_book_num(int book_number)
{

	CString ret;
	int book_vector_index = is_book_exist(book_number);
	if (book_vector_index == 0)
	{
		ret = _T("-");
		return ret;
	}
	else 
	{
		ret = book_vector[book_vector_index].get_book_name();
		return ret;
	}


}

bool CLibraryMnagementProgramDlg::is_book_exist(int book_number)
{
	for (int i = 0; i < book_vector.size(); i++)
	{
		if (book_vector[i].get_book_number() == book_number)
		{
			return true;
		}
	}
	return false;
}
int CLibraryMnagementProgramDlg::get_book_vector_index_by_book_number(int book_number)
{
	for (int i = 0; i < book_vector.size(); i++)
	{
		if (book_vector[i].get_book_number() == book_number)
		{
			return i;
		}
	}
	return 0;
}
int CLibraryMnagementProgramDlg::get_member_vector_index_by_member_number(int member_number)
{
	for (int i = 0; i < member_vector.size(); i++)
	{
		if (member_vector[i].get_member_name() == member_number)
		{
			return i;
		}
	}
	return 0;
}

bool CLibraryMnagementProgramDlg::is_member_exist(int member_number)
{
	for (int i = 0; i < member_vector.size(); i++)
	{
		if (member_vector[i].get_member_number() == member_number)
		{
			return true;
		}
	}
	return false;
}

CString CLibraryMnagementProgramDlg::get_a_list_of_books_on_loan_by_number(int member_num)
{
	CString cquery, books_on_loan;
	cquery.Format(_T("SELECT [book_name]FROM [Library].[dbo].[member] WHERE [member_number] = %d"),member_num);
	
	CRecordset rs(&db);
	try
	{
		rs.Open(CRecordset::dynaset, cquery);        //테이블의모든내용선택
	}
	catch (CDBException* e)
	{
		e->ReportError();      //디폴트는 오류시에 메시지 박스를 띄워준다
	}

	//GetODBCFieldCount 함수는 필드수(열의수) 를 알려줌
	short col = rs.GetODBCFieldCount();

	while (!rs.IsEOF())
	{
		//열
		for (short i = 0; i < col; i++)
		{
			rs.GetFieldValue(i, books_on_loan);
		}
		//다음 행으로 이동
		rs.MoveNext();
	}

	return books_on_loan;
}

CString CLibraryMnagementProgramDlg::get_the_numbers_of_the_books_on_loan_byn_umber(int member_num)
{
	CString cquery, book_numbers_on_loan;
	cquery.Format(_T("SELECT [book_number]FROM [Library].[dbo].[member] WHERE [member_number] = %d"), member_num);

	CRecordset rs(&db);
	try
	{
		rs.Open(CRecordset::dynaset, cquery);        //테이블의모든내용선택
	}
	catch (CDBException* e)
	{
		e->ReportError();      //디폴트는 오류시에 메시지 박스를 띄워준다
	}

	//GetODBCFieldCount 함수는 필드수(열의수) 를 알려줌
	short col = rs.GetODBCFieldCount();

	while (!rs.IsEOF())
	{
		//열
		for (short i = 0; i < col; i++)
		{
			rs.GetFieldValue(i, book_numbers_on_loan);
		}
		//다음 행으로 이동
		rs.MoveNext();
	}

	return book_numbers_on_loan;
}






void CLibraryMnagementProgramDlg::OnBnClickedBookDeleteButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int book_vector_index;
	CString book_number_cstr;
	CString cquery;
	m_edit_button_number_to_delete.GetWindowTextW(book_number_cstr);
	book_vector_index = get_book_vector_index_by_book_number(_ttoi(book_number_cstr));
	if (book_vector[book_vector_index].get_rental_status() == TRUE)
	{
		MessageBox(_T("아직 반납되지 않은 책은 삭제할수 없습니다"));
		GetDlgItem(ENTERED_BOOK_NUMBER_TO_DELETE)->SetWindowText(_T("책 번호"));
		return;
	}
	cquery.Format(_T("DELETE FROM [dbo].[book]WHERE [book_number] = %d"), _ttoi(book_number_cstr));

	/*삭제 쿼리 실행*/
	try
	{
		db.ExecuteSQL(cquery);
	}
	catch (CDBException* e) //에러 확인.
	{
		int errCode = e->ReportError();
	}
	GetDlgItem(ENTERED_BOOK_NUMBER_TO_DELETE)->SetWindowText(_T("책 번호"));
	book_vector.erase(book_vector.begin() + book_vector_index);
}
void CLibraryMnagementProgramDlg::sort_book_vector(vector<Book>& v)
{
	Book temp;
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = i + 1; j < v.size(); j++)
		{
			if (v[i].get_book_number() > v[j].get_book_number())
			{
				temp = v[j];
				v[j] = v[i];
				v[i] = temp;
			}
		}
	}
}

void CLibraryMnagementProgramDlg::sort_member_vector(vector<Member>& v)
{
	Member temp;
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = i + 1; j < v.size(); j++)
		{
			if (v[i].get_member_number() > v[j].get_member_number())
			{
				temp = v[j];
				v[j] = v[i];
				v[i] = temp;
			}
		}
	}
}

void CLibraryMnagementProgramDlg::OnBnClickedMemberSearchButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString search_name;
	CString member_num, book_nums, book_names;
	vector<CString> bnumv;
	vector<CString> bnamev;
	m_edit_search.GetWindowTextW(search_name);
	vector<int> index_of_searched_names;
	clear_list_ctrl();
	// member 테이블에서 회원 번호와 이름만 가져와서 뿌려줄거임
	list_ctrl.InsertColumn(0, _T("회원 번호"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(1, _T("이름"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(2, _T("대여중인 책 번호"), LVCFMT_CENTER, 200, -1);
	list_ctrl.InsertColumn(3, _T("대여중인 책 이름"), LVCFMT_CENTER, 200, -1);
	/*리스트에 값을 다 넣고 실행해야한다고 함*/
	list_ctrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	for (int i = 0; i < member_vector.size(); i++)
	{
		if (member_vector[i].get_member_name().TrimRight(_T(" ")) == search_name)
		{
			index_of_searched_names.push_back(i);
		}
	}
	for (int row = 0; row < index_of_searched_names.size(); row++)
	{
		list_ctrl.InsertItem(row, _T(""));
		for (int col = 0; col < 4; col++)
		{
			switch (col)
			{
			case 0:
				member_num.Format(_T("%d"), member_vector[index_of_searched_names[row]].get_member_number());
				list_ctrl.SetItem(row, col, LVIF_TEXT, member_num, 0, 0, 0, NULL);
				break;
			case 1:
				list_ctrl.SetItem(row, col, LVIF_TEXT, member_vector[index_of_searched_names[row]].get_member_name(), 0, 0, 0, NULL);
				break;
			case 2:
				bnumv = member_vector[row].get_book_num_vector();
				for (int i = 0; i < bnumv.size(); i++)
				{
					if (i == 0)
					{
						if (bnumv[0] == _T("-"))
						{
							book_nums = _T("없음");
						}
						else
						{
							book_nums = bnumv[i];
						}
					}
					else
					{
						book_nums += _T(",") + bnumv[i];
					}
				}
				list_ctrl.SetItem(row, col, LVIF_TEXT, book_nums, 0, 0, 0, NULL);
				break;
			case 3:
				bnamev = member_vector[row].get_book_name_vector();
				for (int i = 0; i < bnamev.size(); i++)
				{
					if (i == 0)
					{
						if (bnamev[0] == _T("-"))
						{
							book_names = _T("없음");
						}
						else
						{
							book_names = bnamev[i];
						}
					}
					else
					{
						book_names += _T(",") + bnamev[i];
					}
				}
				list_ctrl.SetItem(row, col, LVIF_TEXT, book_names, 0, 0, 0, NULL);
				break;
			}
		}
	}
	GetDlgItem(INDIVIDUAL_MEMBER_INFORMATION)->SetWindowText(_T("회원 이름"));
}
