#ifndef REPAST_LOGINFORM_H_
#define REPAST_LOGINFORM_H_

#include "DBForm.h"

// ��¼�û���Ϣ -- �û����� �����޸Ĺ���ʹ�� 
struct LoginUser
{
	UINT menu_id;            // ѡ�ťid
	std::string staff_no;    // Ա�����
//	std::string login_name;  // �û���¼��
	std::string new_login_name; // �޸ĺ���û���¼��
	std::string login_permission; // �û���¼Ȩ��
	std::string password1;     // �û�����
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
	char m_no_[9];                 /* ��¼�û���ţ���Ա�������ͬ*/
	char m_staff_no_[9];           /* Ա����� */
	char m_staff_name_[33];        /* Ա������*/
    char m_name_[21];              /* �û���¼�� */
    char m_password_[31];          /* �û����� */
    short m_permission_;           /* �û�Ȩ�� */
	char m_permission_name_[33];       /* �û�Ȩ������ */
	char m_old_name_[21];

	SQLINTEGER staff_no_len_;   // ��ӦԱ�����
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_staff_name_;
    SQLINTEGER name_len_;        // ��Ӧ�û���¼��
    SQLINTEGER password_len_;    // ��Ӧ�û�����
    SQLINTEGER m_sql_permission_;  /* sql type staff's permission */
	SQLINTEGER permission_name_len_; // ��Ӧ�û�Ȩ������
	SQLINTEGER m_sql_old_name_;
};

/*
 * ˵��: ��ȡ�û�Ȩ��
 * ����ֵ: �û�Ȩ�ޱ�ʶ
 **/
short CLoginForm::permission() const
{
    return m_permission_;
}

/*
 * ˵��: ��ȡ�û�����
 * ����ֵ: �û������ַ���
 **/
char* CLoginForm::password()
{
    return m_password_;
}


/*
 * ˵��: ��ȡ�û����
 * ����ֵ: �û����
 **/
char*  CLoginForm::no()
{
	return m_no_;
}

/*
 * ˵��: ��ȡ�û�����
 * ����ֵ: �û������ַ���
 **/
char* CLoginForm::name()
{
	DeleteSpace(m_name_, m_name_);
    return m_name_;
}

/*
 * ˵��: ��ȡԱ������
 * ����ֵ: Ա�������ַ���
 **/
char* CLoginForm::staff_name()
{
	DeleteSpace(m_staff_name_, m_staff_name_);
    return m_staff_name_;
}


/*
 * ˵��: ��ȡ�û�Ȩ�޵ľ�������
 * ����ֵ: �û�Ȩ�޵ľ�������
 **/
char* CLoginForm::permission_name()
{
	DeleteSpace(m_permission_name_, m_permission_name_);
	return m_permission_name_;
}
#endif /* end #define REPAST_LOGINFORM_H_ */
