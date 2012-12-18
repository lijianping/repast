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
 * 说明: 绑定记录集参数
 * 返回值: 执行成功返回true, 否则返回false
 */
bool StaffForm::BindingParameter()
{
    /* 绑定列 */
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_id_, sizeof(m_id_), &m_sql_id_);
    SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
    SQLBindCol(m_hstmt_, 3, SQL_C_CHAR, m_sex_, sizeof(m_sex_), &m_sql_sex_);
    SQLBindCol(m_hstmt_, 4, SQL_C_SSHORT, &m_age_, 0, &m_sql_age_);
    SQLBindCol(m_hstmt_, 5, SQL_C_DOUBLE, &m_salary_, 0, &m_sql_salary_);
    SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_dept_num_, sizeof(m_dept_num_), &m_sql_dept_num_);
	SQLBindCol(m_hstmt_, 7, SQL_C_CHAR, m_mailbox_, sizeof(m_mailbox_), &m_sql_mailbox_);
	SQLBindCol(m_hstmt_, 8, SQL_C_CHAR, m_phone_num_, sizeof(m_phone_num_), &m_sql_phone_num_);
	SQLBindCol(m_hstmt_, 9, SQL_C_CHAR, m_address_, sizeof(m_address_), &m_sql_address_);
    return true;
}

bool StaffForm::InsertInfo(char *user_id, char *user_name,
                           char *user_sex, short user_age,
                           double user_salary, char *user_dept_num, std::string &error_info)
{
    char insert_sql[200];
    /* 格式化插入语句 */
    sprintf(insert_sql, 
            "insert into Staff values('%s', '%s', '%s', %d, %f, '%s')",
            user_id, user_name, user_sex, user_age,
            user_salary, user_dept_num);
	if (false == ExecuteSQL(insert_sql, error_info))
	{
		return false;
	}
    return true;
}

bool StaffForm::DeleteInfo(char *user_id, std::string &error_info)
{
	char delete_sql[500];
	char query_sql[500];
	sprintf (delete_sql, "delete from Staff where Sno='%s'", user_id);   /*格式化查询语句*/
	sprintf (query_sql, "select Sno from Staff where Sno='%s'", user_id);/*格式化删除语句*/
	/*先查询是否有此记录，若有，则删除*/
	if (false == ExecuteSQL(query_sql, error_info))
	{
		return false;
	}
	BindingParameter();
	MoveFirst();
	if (0 == strcmp("", id()))
	{
		error_info = "删除失败：无此记录";
		return false;
	}
	/* 执行语句 */
    if (false == ExecuteSQL(delete_sql, error_info))
    {
        return false;
    }
	return true;
}
