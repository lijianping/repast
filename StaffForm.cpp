// CStaffForm.cpp: implementation of the CStaffForm class.
//
//////////////////////////////////////////////////////////////////////

#include "StaffForm.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStaffForm::CStaffForm()
: m_age_(0),
  m_salary_(0)
{
    memset(m_id_, '\0', sizeof(m_id_));
    memset(m_name_, '\0', sizeof(m_name_));
    memset(m_sex_, '\0', sizeof(m_sex_));
    memset(m_dept_num_, '\0', sizeof(m_dept_num_));
    memset(m_dept_name_, '\0', sizeof(m_dept_name_));
    m_query_sql_ = "select Sno,Sname,Ssex,Sage,Ssalary,Dname,Smailbox,Sphoneno,Saddress from Staff,Dept where Sdeptno=Dno";
}

CStaffForm::~CStaffForm()
{

}

/*
 * ˵��: �󶨼�¼������
 * ����ֵ: ִ�гɹ�����true, ���򷵻�false
 */
bool CStaffForm::BindingParameter()
{
    /* ���� */
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_id_, sizeof(m_id_), &m_sql_id_);
    SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
    SQLBindCol(m_hstmt_, 3, SQL_C_CHAR, m_sex_, sizeof(m_sex_), &m_sql_sex_);
    SQLBindCol(m_hstmt_, 4, SQL_C_SSHORT, &m_age_, 0, &m_sql_age_);
    SQLBindCol(m_hstmt_, 5, SQL_C_DOUBLE, &m_salary_, 0, &m_sql_salary_);
    SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_dept_name_, sizeof(m_dept_name_), &m_sql_dept_name_);
   // SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_dept_num_, sizeof(m_dept_num_), &m_sql_dept_num_);
	SQLBindCol(m_hstmt_, 7, SQL_C_CHAR, m_mailbox_, sizeof(m_mailbox_), &m_sql_mailbox_);
	SQLBindCol(m_hstmt_, 8, SQL_C_CHAR, m_phone_num_, sizeof(m_phone_num_), &m_sql_phone_num_);
	SQLBindCol(m_hstmt_, 9, SQL_C_CHAR, m_address_, sizeof(m_address_), &m_sql_address_);
    return true;
}

/*
 * ˵���� ����Ա����Ϣ
 * ������
 *        user_id		     [in] Ա�����
 *        user_name			 [in] Ա������
 *        user_sex			 [in] Ա���Ա�
 *        user_age           [in] Ա������
 *        user_salary        [in] Ա������
 *        user_user_dept_num [in] Ա���������ű��
 *        error_info		 [out] ������Ϣ
 * ����ֵ��
 *        ִ�гɹ�����true,���򷵻�false
 **/
bool CStaffForm::InsertInfo(char *user_id, char *user_name,
                           char *user_sex, short user_age,
                           double user_salary, char *user_dept_num, 
						   std::string &error_info)
{
    char insert_sql[200];
    /* ��ʽ��������� */
    sprintf(insert_sql, 
            "insert into Staff values('%s', '%s', '%s', %d, %f, '%s')",
            user_id, user_name, user_sex, user_age,
            user_salary, user_dept_num);
	/*���������*/
    if (false == SQLAllocHandleStmt(error_info))
	{
		return false;
	}
	if (false == ExecuteSQL(insert_sql, error_info))
	{
		return false;
	}
    return true;
}

/*
 * ˵���� ɾ��Ա����Ϣ
 * ������
 *        user_id [in] Ա�����
 *        error_info [out] ������Ϣ
 * ����ֵ��
 *        ִ�гɹ�����true,���򷵻�false
 **/
bool CStaffForm::DeleteInfo(char *user_id, std::string &error_info)
{
	char delete_sql[500];
	char query_sql[500];
	sprintf (query_sql, "select Sno from Staff where Sno='%s'", user_id);/*��ʽ��ɾ�����*/
	/* ִ����� */
    if (false == ExecuteSQL(delete_sql, error_info))
    {
        return false;
    }
	return true;
}


/*
 * ˵���� ����Ա����Ϣ
 * ������
 *        user_id		     [in] Ա�����
 *        user_name			 [in] Ա������
 *        user_sex			 [in] Ա���Ա�
 *        user_age           [in] Ա������
 *        user_salary        [in] Ա������
 *        user_user_dept_num [in] Ա���������ű��
 *        error_info		 [out] ������Ϣ
 *����ֵ��
 *        ִ�гɹ�����true,���򷵻�false
 **/
bool CStaffForm::UpdatetInfo(char *user_id, char *user_name,
                           char *user_sex, short user_age,
                           double user_salary, char *user_dept_num, 
						   std::string &error_info)
{
	char update_sql[500];
	sprintf(update_sql, 
		"update Staff set Sname='%s', Ssex='%s', Sage='%s', Ssalary='%0.2lf', Sdeptno='%s' where Sid='%s'",
		user_name, user_sex, user_age, user_salary, user_dept_num, user_id);
	/* ִ����� */
    if (false == ExecuteSQL(update_sql, error_info))
    {
        return false;
    }


	return true;
}

int CStaffForm::GetStaffSum()
{
	int staff_sum=-1;
	SQLINTEGER sql_sum;
	std::string error;
	char *sql_select_sum="select count(*) from Staff";
	if (false == ExecuteSQL(sql_select_sum, error))
	{
		MessageBox(NULL, error.c_str(), TEXT("ͳ��Ա����������"), MB_OK);
		return staff_sum;
	}
	SQLBindCol(m_hstmt_, 1, SQL_C_SLONG, &staff_sum, sizeof(staff_sum), &sql_sum);
	MoveFirst();
	return staff_sum;
}
