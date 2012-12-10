#ifndef REPAST_LOGINFORM_H_
#define REPAST_LOGINFORM_H_

#include "DBForm.h"

class CLoginForm : public CDBForm  
{
public:
	CLoginForm();
	virtual ~CLoginForm();
    inline short permission() const;
    inline char* password();
    inline char* name();
    virtual bool BindingParameter();
    short GetUserPermission(std::string name,
                            std::string password,
                            std::string &information);

private:
    char m_name_[20];              /* staff's name in login form */
    char m_password_[30];          /* staff's password */
    short m_permission_;           /* staff's permission */
    SQLINTEGER m_sql_name_;        /* sql type staff's name */
    SQLINTEGER m_sql_password_;    /* sql type staff's password */
    SQLINTEGER m_sql_permission_;  /* sql type staff's permission */
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
 * 说明: 获取用户姓名
 * 返回值: 用户姓名字符串
 **/
char* CLoginForm::name()
{
    return m_name_;
}

#endif /* end #define REPAST_LOGINFORM_H_ */
