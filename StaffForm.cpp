// StaffForm.cpp: implementation of the StaffForm class.
//
//////////////////////////////////////////////////////////////////////

#include "StaffForm.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StaffForm::StaffForm()
: m_age_(0),
  m_salary_(0)
{
    memset(m_id_, '\0', sizeof(m_id_));
    memset(m_name_, '\0', sizeof(m_name_));
    memset(m_sex_, '\0', sizeof(m_sex_));
    memset(m_dept_num_, '\0', sizeof(m_dept_num_));
    memset(m_dept_name_, '\0', sizeof(m_dept_name_));
    m_query_sql_ = "select * from Staff";
}

StaffForm::~StaffForm()
{

}

/*
 * ˵��: �󶨼�¼������
 * ����ֵ: ִ�гɹ�����true, ���򷵻�false
 */
bool StaffForm::BindingParameter()
{
    /* ���� */
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_id_, sizeof(m_id_), &m_sql_id_);
    SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
    SQLBindCol(m_hstmt_, 3, SQL_C_CHAR, m_sex_, sizeof(m_sex_), &m_sql_sex_);
    SQLBindCol(m_hstmt_, 4, SQL_C_SSHORT, &m_age_, 0, &m_sql_age_);
    SQLBindCol(m_hstmt_, 5, SQL_C_DOUBLE, &m_salary_, 0, &m_sql_salary_);
    SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_dept_num_, sizeof(m_dept_num_), &m_sql_dept_num_);
    return true;
}

bool StaffForm::InsertInfo(char *user_id, char *user_name,
                           char *user_sex, short user_age,
                           double user_salary, char *user_dept_num)
{
    char insert_sql[200];
    /* ��ʽ��������� */
    sprintf(insert_sql, 
            "insert into Staff values('%s', '%s', '%s', %d, %f, '%s')",
            user_id, user_name, user_sex, user_age,
            user_salary, user_dept_num);
    if (NULL == m_hdbc_)
    {
        MessageBox(NULL, "�����������ݿ�", "����", MB_OK | MB_ICONERROR);
        return false;
    }
    /* ��������� */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc_, &m_hstmt_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        MessageBox(NULL, "���������ʧ��", "����", MB_OK | MB_ICONERROR);
        SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt_);
        m_hstmt_ = NULL;
        return false;
    }
    /* ִ����� */
    m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char *)insert_sql, SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        ReportError(m_hstmt_, SQL_HANDLE_STMT, "ִ��SQL���ʧ�ܣ�����ִ��");
        SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt_);
        m_hstmt_ = NULL;
        return false;
    }
    return true;
}