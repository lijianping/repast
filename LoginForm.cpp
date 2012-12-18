// LoginForm.cpp: implementation of the CLoginForm class.
//
//////////////////////////////////////////////////////////////////////

#include "LoginForm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoginForm::CLoginForm()
{
    m_query_sql_ = "select * from Login";
}

CLoginForm::~CLoginForm()
{

}

bool CLoginForm::BindingParameter()
{
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_name_,
               sizeof(m_name_), &m_sql_name_);
    SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_password_,
               sizeof(m_password_), &m_sql_password_);
    SQLBindCol(m_hstmt_, 3, SQL_C_SSHORT, &m_permission_,
               0, &m_sql_permission_);
    return true;
}

/*
 *  说明: 获取用户权限
 *  参数:
 *        name [in] 用户姓名
 *        password [in] 用户密码
 *        information [out] 错误信息
 *  返回值: 若失败返回0，否则返回用户权限
 **/
short CLoginForm::GetUserPermission(std::string user_name, 
                                    std::string user_password,
                                    std::string &information)
{
    std::string sql_statement = "select Lpermission from Login where Lname = '";
    sql_statement += user_name;
    sql_statement += "' and Lpassword = '";
    sql_statement += user_password;
    sql_statement += "'";
    this->ExecuteSQL((char *)sql_statement.c_str(), information);
    short permission = 0;
    SQLINTEGER sql_permission;
    SQLBindCol(m_hstmt_, 1, SQL_C_SSHORT, &permission, 0, &sql_permission);
    m_return_code_ = SQLFetch(m_hstmt_);
    if ((SQL_SUCCESS != m_return_code_) &&
        (SQL_SUCCESS_WITH_INFO != m_return_code_))
    {
        if (SQL_NO_DATA == m_return_code_)
        {
            information = "用户名或密码错误!";
        }
    }
    return permission;
}

bool CLoginForm::InsertInfo(std::string user_name,
							std::string user_password,
							short user_permission, 
							std::string error_info)
{
	char insert_sql[200];
    /* 格式化插入语句 */
    sprintf(insert_sql, "insert into Login values('%s', '%s', %d)",
		user_name, user_password, user_permission);
	if (false == ExecuteSQL(insert_sql, error_info))
	{
		return false;
	}
	return true;
}

bool CLoginForm::DeleteInfo(std::string user_name, std::string error_info)
{

	char delete_sql[500];
	char query_sql[500];
	sprintf (delete_sql, "delete from Login where Lname='%s'", user_name);	/*格式化查询语句*/
	sprintf (query_sql, "select Login from Staff where Lname='%s'", user_name);/*格式化删除语句*/
	/*先查询是否有此记录，若有，则删除*/
	if (false == ExecuteSQL(query_sql, error_info))
	{
		return false;
	}
	BindingParameter();
	MoveFirst();
	if (0 == strcmp("", name()))
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