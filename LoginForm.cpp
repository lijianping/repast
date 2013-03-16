// LoginForm.cpp: implementation of the CLoginForm class.
//
//////////////////////////////////////////////////////////////////////

#include "LoginForm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoginForm::CLoginForm()
{
  //  m_query_sql_ = "select * from Login";
	m_query_sql_ = "select Lname,Lpassword,Lpermission,LPname from Login,LoginPermission where Lpermission=LPpermission";
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
	SQLBindCol(m_hstmt_, 4, SQL_C_CHAR, m_permission_name_, 
		       sizeof(m_permission_name_), &m_sql_permission_name_);
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
	std::string password = Encrypt(user_password.c_str(), user_password.length() / 2, user_password.length());
    std::string sql_statement = "select Lpermission from Login where Lname = '";
    sql_statement += user_name;
    sql_statement += "' and Lpassword = '";
    sql_statement += password;
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

/*
 *  说明: 新增系统登录用户信息
 *  参数:
 *        user_name       [in] 用户姓名
 *        user_password   [in] 用户密码
 *        user_permission [in] 用户权限
 *        error_info      [out] 错误信息
 *  返回值: 若成功返回true，否则返回false
 **/
bool CLoginForm::InsertInfo(LoginUser *login_user, std::string &error_info)
{
	if (false == CheckLoginUser(login_user, error_info))
	{
		return false;
	}
	if (false == SetLoginUser(login_user, error_info))
	{
		return false;
	}
	if (false == BindingParameter(true, error_info))
	{
		return false;
	}
	if (false == ExecuteSQL("{? = call InsertLoginUser(?,?,?)}", error_info))
	{
		return false;
	}
	while ( ( m_return_code_ = SQLMoreResults(m_hstmt_) ) != SQL_NO_DATA )
	{
	}
	if (m_pro_ret != 0)
	{
		error_info="员工编号不能重复！";
		return false;
	}
	return true;
}

/*
 *  说明: 删除系统登录用户信息
 *  参数:
 *        user_name       [in] 用户姓名
 *        error_info      [out] 错误信息
 *  返回值: 若成功返回true，否则返回false
 **/
bool CLoginForm::DeleteInfo(std::string user_name, std::string &error_info)
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

/*
 *  说明: 更新系统登录用户信息
 *  参数:
 *        user_name       [in] 用户姓名
 *        user_password   [in] 用户密码
 *        user_permission [in] 用户权限
 *        error_info      [out] 错误信息
 *  返回值: 若成功返回true，否则返回false
 **/
bool CLoginForm::UpdateInfo(LoginUser *login_user, std::string &error_info)
{
	char update_sql[200];
// 	sprintf(update_sql, "update Login set Lpassword='%s', Lpermission='%d' where Lname='%s'",
// 		user_password, user_permission, user_name);
	/* 执行语句 */
    if (false == ExecuteSQL(update_sql, error_info))
    {
        return false;
    }

	return true;
}


/*
 * @ brief: caesar密码加密
 * @ param: src [in] 待加密的明文字符串
 * @ param: shift [in] 移动的位数，即密钥
 * @ param: len [in] 明文字符串长度
 * @ return: 加密后的密文
 */
std::string CLoginForm::Encrypt(const char *src, int shift, int len) {
    std::string des;
    for (int i = 0; i < len; ++i) {
        if (src[i] >= '!' && src[i] <= '~') {
            des += (src[i] + shift - '!' + 94) % 94 + '!';
        } else {
            des += src[i];
        }
    }
    return des;
}

/*
 * @ brief: 修改用户密码
 * @ param: password [in] 用户密码
 * @ return: 若成功返回true，否则返回false
 **/
bool CLoginForm::ModifyPasswd(std::string user_name, std::string password) {
	std::string encrypted = Encrypt(password.c_str(), password.length() / 2, password.length());
	char sql[64] = "\0";
	sprintf(sql, "Exec UpdatePassword %s, %s", user_name.c_str(), encrypted.c_str());
	std::string error_string;
	return ExecuteSQL(sql, error_string);
}


bool CLoginForm:: BindingParameter(bool is_add, std::string &error_info)
{
	m_sql_name_ = SQL_NTS;
	m_sql_password_ = SQL_NTS;
	m_sql_permission_name_ = SQL_NTS;
	m_sql_pro_ret = SQL_NTS;
	m_sql_old_name_ = SQL_NTS;

	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, \
		SQL_INTEGER,0, 0,&m_pro_ret, 0, &m_sql_pro_ret);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定返回值失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(m_name_)-1, 0, m_name_, 0, &m_sql_name_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定用户名失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(m_password_)-1, 0, m_password_, 0, &m_sql_password_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定用户密码失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(m_permission_name_)-1, 0, m_permission_name_, 0, &m_sql_permission_name_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定用户权限失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	if (!is_add)
	{
		m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_CHAR, \
			SQL_CHAR,sizeof(m_old_name_)-1, 0, m_old_name_, 0, &m_sql_old_name_);
		if ((m_return_code_ != SQL_SUCCESS) &&
			(m_return_code_ != SQL_SUCCESS_WITH_INFO))
		{
			error_info = "绑定旧用户名失败!";
			ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
			return false;
		}
	}
	return true;
}


bool CLoginForm::CheckLoginUser(LoginUser * login_user, std::string &error_info)
{
	unsigned int length=0;
	length = strlen(login_user->user_name.c_str());
	if (0 == length)
	{
		error_info = "用户名不能为空";
		return false;
	}
	if (length > sizeof(m_name_)-1)
	{
		error_info = "用户名太长，请适当减小后再试！";
		return false;
	}
	length = strlen(login_user->user_passwd.c_str());
	if ( 0 == length)
	{
		error_info = "用户密码不能为空";
		return false;
	}
	if (length > sizeof(m_password_)-1)
	{
		error_info = "用户密码太长，请适当减小后再试！";
		return false;
	}
	length = strlen(login_user->user_permission_name.c_str());
	if (length > sizeof(m_permission_name_)-1)
	{
		error_info = "用户权限太长，请适当减小后再试！";
		return false;
	}
	return true;
}
bool CLoginForm:: SetLoginUser(LoginUser * login_user, std::string &error_info)
{
	if (false == CheckLoginUser(login_user, error_info))
	{
		return false;
	}
	if (NULL == strcpy(m_name_, login_user->user_name.c_str()))
	{
		error_info = "用户名赋值失败！";
		return false;
	}
	if (NULL == strcpy(m_password_, login_user->user_passwd.c_str()))
	{
		error_info = "用户密码赋值失败！";
		return false;
	}
	if (NULL == strcpy(m_permission_name_, login_user->user_permission_name.c_str()))
	{
		error_info = "用户权限赋值失败！";
		return false;
	}
	if (NULL == strcpy(m_old_name_, login_user->user_old_name.c_str()))
	{
		error_info = "旧用户名赋值失败！";
		return false;
	}
	return true;
}