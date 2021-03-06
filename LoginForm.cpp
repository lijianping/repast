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
	//TODO：尚未检查返回值
	SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_no_, sizeof(m_no_), &m_sql_no_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_staff_name_,sizeof(m_staff_name_), &m_sql_staff_name_);
    SQLBindCol(m_hstmt_, 3, SQL_C_CHAR, m_name_,sizeof(m_name_), &name_len_);
	SQLBindCol(m_hstmt_, 4, SQL_C_CHAR, m_permission_name_, sizeof(m_permission_name_), &permission_name_len_);
    return true;
}

/*
 * @ brief: 获取用户权限
 * @ param: name [in] 用户名
 * @ param: password [in] 用户密码,外部加密
 * @ param: information [out] 错误信息
 * @ return: 若失败返回-1，否则返回用户权限
 **/
short CLoginForm::GetUserPermission(std::string user_name, 
                                    std::string user_password,
                                    std::string &information)
{
	name_len_ = SQL_NTS;
	password_len_ = SQL_NTS;
	m_sql_pro_ret = SQL_NTS;
	m_sql_permission_ = SQL_NTS;

	/*绑定存储过程返回值*/
	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, \
		                              SQL_INTEGER,0, 0,&m_pro_ret, 0, &m_sql_pro_ret);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RETURN_ERROR)
	// 绑定列参数
    m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, \
		                              SQL_CHAR, sizeof(m_name_)-1, 0, m_name_,\
									  sizeof(m_name_), &name_len_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, \
		                              SQL_CHAR, sizeof(m_password_)-1, 0, m_password_,\
									  sizeof(m_password_), &password_len_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_PARAM_ERROR)
	//TODO: 添加检查用户信息长度
	strcpy(m_name_, user_name.c_str());
	strcpy(m_password_, user_password.c_str());

    if(false == ExecSQLProc("{?=call GetPermission(?,?)}", information))
	{
		return -1;
	}
    SQLBindCol(m_hstmt_, 1, SQL_C_SSHORT, &m_permission_, 0, &m_sql_permission_);
	m_return_code_ = SQLFetch(m_hstmt_);
    if (SQL_SUCCESS != m_return_code_ && SQL_SUCCESS_WITH_INFO != m_return_code_) {
        if (SQL_NO_DATA == m_return_code_) {
            information = "用户名或密码错误!";
        }
		return -1;
    }
	if (false == IsSQLProcRetRight(information)) {
		return -1;
	}
    return m_permission_;
}

/*
 * @ brief: 增加用户信息
 * @ param: login_user [in]  登陆用户信息
 * @ param: err_info [out] 错误信息
 * @ return: 若成功返回true，否则返回false
 **/
bool CLoginForm::AddUser(LoginUser *login_user, std::string &err_info) {
	if (!SetLoginUser(login_user, err_info)) {
		return false;
	}
	if (!BindingParameter(true, err_info)) {
		return false;
	}
	m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char *)"{? = call AddLoginUser(?,?,?,?)}", SQL_NTS);
	if ((m_return_code_ != SQL_SUCCESS) &&
		(m_return_code_ != SQL_SUCCESS_WITH_INFO))
	{
		err_info = "执行增加用户存储过程出错!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
    }
	while ((m_return_code_ = SQLMoreResults(m_hstmt_)) != SQL_NO_DATA)
	{
	}
	if (m_pro_ret != 0)
	{
		err_info="该用户已存在！";
		return false;
	}
	return true;
}

/*
 * @ brief: 修改用户信息
 * @ param: login_user [in]  登陆用户信息
 * @ param: err_info [out] 错误信息
 * @ return: 若成功返回true，否则返回false
 **/
bool CLoginForm::ModifyUser(LoginUser *login_user, std::string &err_info) {
	if (!SetLoginUser(login_user, err_info)) {
		return false;
	}
	if (!BindingParameter(true, err_info)) {
		return false;
	}
	m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char *)"{? = call ModifyLoginUser(?,?,?,?)}", SQL_NTS);
	if ((m_return_code_ != SQL_SUCCESS) &&
		(m_return_code_ != SQL_SUCCESS_WITH_INFO))
	{
		err_info = "执行修改用户存储过程出错!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
    }
	while ((m_return_code_ = SQLMoreResults(m_hstmt_)) != SQL_NO_DATA)
	{
	}
	if (m_pro_ret != 0)
	{
		err_info="修改用户信息失败！";
		return false;
	}
	return true;
}

/*
 * @ brief: 删除用户信息
 * @ param: staff_no [in]
 * @ return: 若成功返回true，否则返回false
 **/
bool CLoginForm::DeleteUser(const char *staff_no, std::string &err_info) {
	if (!staff_no) {
		err_info = "用户编号为空";
		return false;
	}
	this->Initialization();
	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, \
		SQL_INTEGER,0, 0,&m_pro_ret, 0, &m_sql_pro_ret);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        err_info = "绑定返回值失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
        return false;
    }
	// 员工编号绑定
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(m_staff_no_)-1, 0, m_staff_no_, 0, &staff_no_len_);
	strcpy(m_staff_no_, staff_no);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        err_info = "绑定员工编号失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
        return false;
    }
	m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char *)"{? = call DeleteLoginUser(?)}", SQL_NTS);
	if ((m_return_code_ != SQL_SUCCESS) &&
		(m_return_code_ != SQL_SUCCESS_WITH_INFO))
	{
		err_info = "执行删除用户存储过程出错!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
    }
	while ((m_return_code_ = SQLMoreResults(m_hstmt_)) != SQL_NO_DATA)
	{
	}
	if (m_pro_ret != 0)
	{
		err_info="删除用户信息失败！";
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
	sprintf (delete_sql, "delete from Login where Lname='%s'", user_name.c_str());	/*格式化删除语句*/
	/* 执行语句 */
    if (false == ExecuteSQL(delete_sql, error_info))
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
	std::string src_passwd(src);
	char key[] = "mykeyisbrief";
	int key_len = strlen(key);
    for (int i = 0, j = 0; i < len; ++i, ++j) {
        if (src_passwd[i] >= '!' && src_passwd[i] <= '~') {
            des += (src_passwd[i] + shift - '!' + 94) % 94 + '!';
        } else {
            des += src_passwd[i];
        }
		des[i] = des[i] ^ key[j % key_len];
    }
    return des;
}

/*
 * @ brief: 修改用户密码
 * @ param: password [in] 用户密码
 * @ return: 若成功返回true，否则返回false
 **/
bool CLoginForm::ModifyPasswd(std::string user_name, std::string password) {
	char sql[64] = "\0";
	sprintf(sql, "Exec UpdatePassword '%s', '%s'", user_name.c_str(), password.c_str());
	std::string error_string;
	return ExecuteSQL(sql, error_string);
}


bool CLoginForm::BindingParameter(bool is_add, std::string &error_info)
{
	this->Initialization();

	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, \
		SQL_INTEGER,0, 0,&m_pro_ret, 0, &m_sql_pro_ret);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定返回值失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	// 员工编号绑定
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(m_staff_no_)-1, 0, m_staff_no_, 0, &staff_no_len_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定员工编号失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(m_name_)-1, 0, m_name_, 0, &name_len_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定用户名失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(m_password_)-1, 0, m_password_, 0, &password_len_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定用户密码失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
    m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_CHAR, \
	                          		  SQL_CHAR,sizeof(m_permission_name_)-1, 0,\
									  m_permission_name_, 0, &permission_name_len_);
		if ((m_return_code_ != SQL_SUCCESS) &&
			(m_return_code_ != SQL_SUCCESS_WITH_INFO))
		{
			error_info = "绑定用户权限名失败!";
			ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
			return false;
		}
	return true;
}

/*
 * @ brief: 登录用户信息检查
 * @ param: login_user [in] 待检查的用户信息
 * @ param: error_info [out] 错误信息
 * @ return: 若成功返回ture，否则返回false
 **/
bool CLoginForm::CheckLoginUser(LoginUser * login_user, std::string &error_info)
{
	unsigned int length=0;
	length = login_user->staff_no.length();
	if (0 == length) {  // 检查员工编号
		LTHROW(INPUT_NULL_ERROR)
		return false;
	}
	length = login_user->new_login_name.length();
	if (length == 0) {  // 检查用户名
	LTHROW(INPUT_TOO_LONG_ERROR)
		return false;
	}
	if (length > sizeof(m_name_)-1)
	{
		LTHROW(INPUT_TOO_LONG_ERROR)
		return false;
	}
	length = login_user->password1.length();
	if ( 0 == length)  // 检查密码
	{
		LTHROW(INPUT_NULL_ERROR)
		return false;
	}
	if (length > sizeof(m_password_)-1)
	{
		LTHROW(INPUT_TOO_LONG_ERROR)
		return false;
	}
	length = login_user->login_permission.length();
	if (0 == length)  // 检查权限
	{
		LTHROW(INPUT_NULL_ERROR)
		return false;
	}
	return true;
}

/*
 * 说明：
 *     检查登录时输入是否正确
 * 参数：
 *     name   [in] 输入的名称
 *     passwd [in] 输入的密码
 * 返回值：
 *     输入正确返回true,否则返回false 
 */
bool CLoginForm::CheckInputRight(char* name,char* passwd)
{
	if (strlen(name) > sizeof(m_name_)-1){  // 检查用户名
	LTHROW(INPUT_TOO_LONG_ERROR)
		return false;
	}
	if (strlen(passwd) > sizeof(m_password_)-1){  // 检查密码
	LTHROW(INPUT_TOO_LONG_ERROR)
		return false;
	}
	return true;
}

/*
 * @ brief: 对将要执行的存储过程赋值传参，内置检查函数
 * @ param: login_user [in] 登录用户信息
 * @ param: error_info [out] 错误信息
 * @ return: 若成功返回ture，否则返回false
 **/
bool CLoginForm::SetLoginUser(LoginUser * login_user, std::string &error_info)
{
	// 用户信息检查
	if (false == CheckLoginUser(login_user, error_info))
	{
		return false;
	}
	// 员工编号
	if (NULL == strcpy(m_staff_no_, login_user->staff_no.c_str())) {
		error_info = "员工编号赋值失败！";
		return false;
	}
	// 用户登录名
	if (NULL == strcpy(m_name_, login_user->new_login_name.c_str()))
	{
		error_info = "用户名赋值失败！";
		return false;
	}
	// 用户密码
	if (NULL == strcpy(m_password_, login_user->password1.c_str()))
	{
		error_info = "用户密码赋值失败！";
		return false;
	}
	// 用户权限
	if (NULL == strcpy(m_permission_name_, login_user->login_permission.c_str()))
	{
		error_info = "用户权限赋值失败！";
		return false;
	}
	return true;
}

/*
 * @ brief: 初始化SQL相关类型数据
 **/
void CLoginForm::Initialization() {
	m_sql_pro_ret = SQL_NTS;   
	this->staff_no_len_ = SQL_NTS;
	this->name_len_ = SQL_NTS;
	this->password_len_ = SQL_NTS;
	this->permission_name_len_ = SQL_NTS;
}
