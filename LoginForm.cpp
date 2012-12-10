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
short CLoginForm::GetUserPermission(std::string name, 
                                    std::string password,
                                    std::string &information)
{
    std::string sql_statement = "select Lpermission from Login where Lname = '";
    sql_statement += name;
    sql_statement += "' and Lpassword = '";
    sql_statement += password;
    sql_statement += "'";
    this->ExecuteSQL((char *)sql_statement.c_str());
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