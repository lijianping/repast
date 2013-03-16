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
 *  ˵��: ��ȡ�û�Ȩ��
 *  ����:
 *        name [in] �û�����
 *        password [in] �û�����
 *        information [out] ������Ϣ
 *  ����ֵ: ��ʧ�ܷ���0�����򷵻��û�Ȩ��
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
            information = "�û������������!";
        }
    }
    return permission;
}

/*
 *  ˵��: ����ϵͳ��¼�û���Ϣ
 *  ����:
 *        user_name       [in] �û�����
 *        user_password   [in] �û�����
 *        user_permission [in] �û�Ȩ��
 *        error_info      [out] ������Ϣ
 *  ����ֵ: ���ɹ�����true�����򷵻�false
 **/
bool CLoginForm::InsertInfo(std::string user_name,
							std::string user_password,
							short user_permission, 
							std::string error_info)
{
	char insert_sql[200];
    /* ��ʽ��������� */
    sprintf(insert_sql, "insert into Login values('%s', '%s', %d)",
		user_name, user_password, user_permission);
	if (false == ExecuteSQL(insert_sql, error_info))
	{
		return false;
	}
	return true;
}

/*
 *  ˵��: ɾ��ϵͳ��¼�û���Ϣ
 *  ����:
 *        user_name       [in] �û�����
 *        error_info      [out] ������Ϣ
 *  ����ֵ: ���ɹ�����true�����򷵻�false
 **/
bool CLoginForm::DeleteInfo(std::string user_name, std::string error_info)
{

	char delete_sql[500];
	char query_sql[500];
	sprintf (delete_sql, "delete from Login where Lname='%s'", user_name);	/*��ʽ����ѯ���*/
	sprintf (query_sql, "select Login from Staff where Lname='%s'", user_name);/*��ʽ��ɾ�����*/
	/*�Ȳ�ѯ�Ƿ��д˼�¼�����У���ɾ��*/
	if (false == ExecuteSQL(query_sql, error_info))
	{
		return false;
	}
	BindingParameter();
	MoveFirst();
	if (0 == strcmp("", name()))
	{
		error_info = "ɾ��ʧ�ܣ��޴˼�¼";
		return false;
	}
	/* ִ����� */
    if (false == ExecuteSQL(delete_sql, error_info))
    {
        return false;
    }
	return true;
}

/*
 *  ˵��: ����ϵͳ��¼�û���Ϣ
 *  ����:
 *        user_name       [in] �û�����
 *        user_password   [in] �û�����
 *        user_permission [in] �û�Ȩ��
 *        error_info      [out] ������Ϣ
 *  ����ֵ: ���ɹ�����true�����򷵻�false
 **/
bool CLoginForm::UpdateInfo(std::string user_name,
							std::string user_password,
							short user_permission, 
							std::string error_info)
{
	char update_sql[200];
	sprintf(update_sql, "update Login set Lpassword='%s', Lpermission='%d' where Lname='%s'",
		user_password, user_permission, user_name);
	/* ִ����� */
    if (false == ExecuteSQL(update_sql, error_info))
    {
        return false;
    }

	return true;
}


/*
 * @ brief: caesar�������
 * @ param: src [in] �����ܵ������ַ���
 * @ param: shift [in] �ƶ���λ��������Կ
 * @ param: len [in] �����ַ�������
 * @ return: ���ܺ������
 */
std::string CLoginForm::Encrypt(const char *src, int shift, int len) {
    std::string des;
	char key[] = "mykeyisbrief";
	int key_len = strlen(key);
    for (int i = 0, j = 0; i < len; ++i, ++j) {
        if (src[i] >= '!' && src[i] <= '~') {
            des += (src[i] + shift - '!' + 94) % 94 + '!';
        } else {
            des += src[i];
        }
		des[i] = des[i] ^ key[j % key_len];
    }
    return des;
}

/*
 * @ brief: �޸��û�����
 * @ param: password [in] �û�����
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool CLoginForm::ModifyPasswd(std::string user_name, std::string password) {
	std::string encrypted = Encrypt(password.c_str(), password.length() / 2, password.length());
	char sql[64] = "\0";
	sprintf(sql, "Exec UpdatePassword %s, %s", user_name.c_str(), encrypted.c_str());
	std::string error_string;
	return ExecuteSQL(sql, error_string);
}
