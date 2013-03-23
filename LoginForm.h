#ifndef REPAST_LOGINFORM_H_
#define REPAST_LOGINFORM_H_

#include "DBForm.h"

// 登录用户信息 -- 用户管理 增加修改功能使用 
struct LoginUser
{
	UINT menu_id;            // 选项按钮id
	std::string staff_no;    // 员工编号
//	std::string login_name;  // 用户登录名
	std::string new_login_name; // 修改后的用户登录名
	std::string login_permission; // 用户登录权限
	std::string password1;     // 用户密码
};

class CLoginForm : public CDBForm  
{
public:
	CLoginForm();
	virtual ~CLoginForm();
    inline short permission() const;
    inline char* password();
    inline char* name();
	inline char* staff_name();
	inline char* no();
	inline char* permission_name();
    virtual bool BindingParameter();
    short GetUserPermission(std::string user_name,
                            std::string user_password,
                            std::string &information);
	bool AddUser(LoginUser *login_user, std::string &err_info);
	bool ModifyUser(LoginUser *login_user, std::string &err_info);
	bool DeleteUser(const char *staff_no, std::string &err_info);
	bool DeleteInfo(std::string user_name, std::string &error_info);
	bool ModifyPasswd(std::string user_name, std::string password);
	std::string Encrypt(const char *src, int shift, int len);
protected:
	void Initialization();
    virtual	bool BindingParameter(bool is_add, std::string &error_info);
	bool CheckLoginUser(LoginUser * login_user, std::string &error_info);
	bool SetLoginUser(LoginUser * login_user, std::string &error_info);

private:
	char m_no_[9];                 /* 登录用户编号，与员工编号相同*/
	char m_staff_no_[9];           /* 员工编号 */
	char m_staff_name_[33];        /* 员工姓名*/
    char m_name_[21];              /* 用户登录名 */
    char m_password_[31];          /* 用户密码 */
    short m_permission_;           /* 用户权限 */
	char m_permission_name_[33];       /* 用户权限名称 */
	char m_old_name_[21];

	SQLINTEGER staff_no_len_;   // 对应员工编号
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_staff_name_;
    SQLINTEGER name_len_;        // 对应用户登录名
    SQLINTEGER password_len_;    // 对应用户密码
    SQLINTEGER m_sql_permission_;  /* sql type staff's permission */
	SQLINTEGER permission_name_len_; // 对应用户权限名称
	SQLINTEGER m_sql_old_name_;
};

/*
 * 说明: 获取用户权限
 * 返回值: 用户权限标识
 **/
short CLoginForm::permission() const
{
    return m_permission_;
}

/*
 * 说明: 获取用户密码
 * 返回值: 用户密码字符串
 **/
char* CLoginForm::password()
{
    return m_password_;
}


/*
 * 说明: 获取用户编号
 * 返回值: 用户编号
 **/
char*  CLoginForm::no()
{
	return m_no_;
}

/*
 * 说明: 获取用户姓名
 * 返回值: 用户姓名字符串
 **/
char* CLoginForm::name()
{
	DeleteSpace(m_name_, m_name_);
    return m_name_;
}

/*
 * 说明: 获取员工姓名
 * 返回值: 员工姓名字符串
 **/
char* CLoginForm::staff_name()
{
	DeleteSpace(m_staff_name_, m_staff_name_);
    return m_staff_name_;
}


/*
 * 说明: 获取用户权限的具体内容
 * 返回值: 用户权限的具体内容
 **/
char* CLoginForm::permission_name()
{
	DeleteSpace(m_permission_name_, m_permission_name_);
	return m_permission_name_;
}
#endif /* end #define REPAST_LOGINFORM_H_ */
