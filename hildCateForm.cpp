// hildCateForm.cpp: implementation of the ChildCateForm class.
//
//////////////////////////////////////////////////////////////////////

#include "hildCateForm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ChildCateForm::ChildCateForm()
{

}

ChildCateForm::~ChildCateForm()
{

}

/*
 * @ brief: ��ʼ��sql��������
 **/
void ChildCateForm::Initialize()
{
	this->sql_cate_no_ = SQL_NTS;
	this->sql_main_cate_no_ = SQL_NTS;
	this->sql_cate_name_ = SQL_NTS;
}


/*
 * @ brief: ͨ�����������ƻ�ȡ�ӷ�������
 * @ param: main_cate_no [in] ����������
 * @ param: err_info [out] ������Ϣ
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool ChildCateForm::GetChildCateName(const char *name, std::string &err_info)
{
	this->Initialize(); // ��ʼ��sql����
	if (!BindReturn())  // �󶨷���ֵ
	{
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
	}
	//  �󶨲���
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(main_cate_name_)-1, 0, main_cate_name_, 0, &sql_main_cate_name_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        err_info = "��Ա�����ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
        return false;
    }
	strcpy(main_cate_name_, name);  // ������ֵ
	if (!this->ExecSQLProc("{? = call GetChildCateNameByMainCateName(?)}", err_info))
	{
		return false;
	}
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, cate_name_, sizeof(cate_name_), &sql_cate_name_);
	if ((m_return_code_ != SQL_SUCCESS) && (m_return_code_ != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
	}
	MoveFirst();
	return true;
}