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
	//TODO����δ��鷵��ֵ
	SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_no_, sizeof(m_no_), &m_sql_no_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_staff_name_,sizeof(m_staff_name_), &m_sql_staff_name_);
    SQLBindCol(m_hstmt_, 3, SQL_C_CHAR, m_name_,sizeof(m_name_), &name_len_);
	SQLBindCol(m_hstmt_, 4, SQL_C_CHAR, m_permission_name_, sizeof(m_permission_name_), &permission_name_len_);
    return true;
}

/*
 *  ˵��: ��ȡ�û�Ȩ��
 *  ����:
 *        name [in] �û�����
 *        password [in] �û�����
 *        information [out] ������Ϣ
 *  ����ֵ: ��ʧ�ܷ���-1�����򷵻��û�Ȩ��
 **/
short CLoginForm::GetUserPermission(std::string user_name, 
                                    std::string user_password,
                                    std::string &information)
{
//	std::string password = Encrypt(user_password.c_str(), user_password.length() / 2, user_password.length());

	name_len_ = SQL_NTS;
	password_len_ = SQL_NTS;
	m_sql_pro_ret = SQL_NTS;
	m_sql_permission_ = SQL_NTS;
	/*�󶨴洢���̷���ֵ*/
	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, \
		SQL_INTEGER,0, 0,&m_pro_ret, 0, &m_sql_pro_ret);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "�󶨷���ֵʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, information);
        return -1;
    }
	// ���в���
    m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR, sizeof(m_name_)-1, 0, m_name_, sizeof(m_name_), &name_len_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "�󶨲���1ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, information);
        return -1;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR, sizeof(m_password_)-1, 0, m_password_, sizeof(m_password_), &password_len_);
   	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "�󶨲���2ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, information);
        return -1;
    }
	//TODO: ��Ӽ���û���Ϣ����
	strcpy(m_name_, user_name.c_str());
	strcpy(m_password_, user_password.c_str());

    if(false == ExecSQLProc("{?=call GetPermission(?,?)}", information))
	{
		return -1;
	}

//     short permission = 0;
//     SQLINTEGER sql_permission=SQL_NTS;
    SQLBindCol(m_hstmt_, 1, SQL_C_SSHORT, &m_permission_, 0, &m_sql_permission_);
	m_return_code_ = SQLFetch(m_hstmt_);
    if ((SQL_SUCCESS != m_return_code_) &&
        (SQL_SUCCESS_WITH_INFO != m_return_code_))
    {
        if (SQL_NO_DATA == m_return_code_)
        {
            information = "�û������������!";
        }
		return -1;
    }
	if (false == IsSQLProcRetRight(information))
	{
		return -1;
	}
    return m_permission_;
}

/*
 * @ brief: �����û���Ϣ
 * @ param: login_user [in]  ��½�û���Ϣ
 * @ param: err_info [out] ������Ϣ
 * @ return: ���ɹ�����true�����򷵻�false
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
		err_info = "ִ�������û��洢���̳���!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
    }
	while ((m_return_code_ = SQLMoreResults(m_hstmt_)) != SQL_NO_DATA)
	{
	}
	if (m_pro_ret != 0)
	{
		err_info="���û��Ѵ��ڣ�";
		return false;
	}
	return true;
}

/*
 * @ brief: �޸��û���Ϣ
 * @ param: login_user [in]  ��½�û���Ϣ
 * @ param: err_info [out] ������Ϣ
 * @ return: ���ɹ�����true�����򷵻�false
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
		err_info = "ִ���޸��û��洢���̳���!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
    }
	while ((m_return_code_ = SQLMoreResults(m_hstmt_)) != SQL_NO_DATA)
	{
	}
	if (m_pro_ret != 0)
	{
		err_info="�޸��û���Ϣʧ�ܣ�";
		return false;
	}
	return true;
}

/*
 * @ brief: ɾ���û���Ϣ
 * @ param: staff_no [in]
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool CLoginForm::DeleteUser(const char *staff_no, std::string &err_info) {
	if (!staff_no) {
		err_info = "�û����Ϊ��";
		return false;
	}
	this->Initialization();
	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, \
		SQL_INTEGER,0, 0,&m_pro_ret, 0, &m_sql_pro_ret);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        err_info = "�󶨷���ֵʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
        return false;
    }
	// Ա����Ű�
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(m_staff_no_)-1, 0, m_staff_no_, 0, &staff_no_len_);
	strcpy(m_staff_no_, staff_no);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        err_info = "��Ա�����ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
        return false;
    }
	m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char *)"{? = call DeleteLoginUser(?)}", SQL_NTS);
	if ((m_return_code_ != SQL_SUCCESS) &&
		(m_return_code_ != SQL_SUCCESS_WITH_INFO))
	{
		err_info = "ִ��ɾ���û��洢���̳���!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
    }
	while ((m_return_code_ = SQLMoreResults(m_hstmt_)) != SQL_NO_DATA)
	{
	}
	if (m_pro_ret != 0)
	{
		err_info="ɾ���û���Ϣʧ�ܣ�";
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
bool CLoginForm::DeleteInfo(std::string user_name, std::string &error_info)
{
	char delete_sql[500];
	sprintf (delete_sql, "delete from Login where Lname='%s'", user_name.c_str());	/*��ʽ��ɾ�����*/
	/* ִ����� */
    if (false == ExecuteSQL(delete_sql, error_info))
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
 * @ brief: �޸��û�����
 * @ param: password [in] �û�����
 * @ return: ���ɹ�����true�����򷵻�false
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
        error_info = "�󶨷���ֵʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	// Ա����Ű�
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(m_staff_no_)-1, 0, m_staff_no_, 0, &staff_no_len_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "��Ա�����ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(m_name_)-1, 0, m_name_, 0, &name_len_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "���û���ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(m_password_)-1, 0, m_password_, 0, &password_len_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "���û�����ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
    m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_CHAR, \
	                          		  SQL_CHAR,sizeof(m_permission_name_)-1, 0,\
									  m_permission_name_, 0, &permission_name_len_);
		if ((m_return_code_ != SQL_SUCCESS) &&
			(m_return_code_ != SQL_SUCCESS_WITH_INFO))
		{
			error_info = "���û�Ȩ����ʧ��!";
			ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
			return false;
		}
	return true;
}

/*
 * @ brief: ��¼�û���Ϣ���
 * @ param: login_user [in] �������û���Ϣ
 * @ param: error_info [out] ������Ϣ
 * @ return: ���ɹ�����ture�����򷵻�false
 **/
bool CLoginForm::CheckLoginUser(LoginUser * login_user, std::string &error_info)
{
	unsigned int length=0;
	length = login_user->staff_no.length();
	if (0 == length) {  // ���Ա�����
		error_info = "Ա����Ų���Ϊ��";
		return false;
	}
	length = login_user->new_login_name.length();
	if (length == 0) {  // ����û���
		error_info = "�û�������Ϊ��";
		return false;
	}
	if (length > sizeof(m_name_)-1)
	{
		error_info = "�û���̫�������ʵ���С�����ԣ�";
		return false;
	}
	length = login_user->password1.length();
	if ( 0 == length)  // �������
	{
		error_info = "�û����벻��Ϊ��";
		return false;
	}
	if (length > sizeof(m_password_)-1)
	{
		error_info = "�û�����̫�������ʵ���С�����ԣ�";
		return false;
	}
	length = login_user->login_permission.length();
	if (0 == length)  // ���Ȩ��
	{
		error_info = "�������û�Ȩ�ޣ�";
		return false;
	}
	return true;
}

/*
 * @ brief: �Խ�Ҫִ�еĴ洢���̸�ֵ���Σ����ü�麯��
 * @ param: login_user [in] ��¼�û���Ϣ
 * @ param: error_info [out] ������Ϣ
 * @ return: ���ɹ�����ture�����򷵻�false
 **/
bool CLoginForm::SetLoginUser(LoginUser * login_user, std::string &error_info)
{
	// �û���Ϣ���
	if (false == CheckLoginUser(login_user, error_info))
	{
		return false;
	}
	// Ա�����
	if (NULL == strcpy(m_staff_no_, login_user->staff_no.c_str())) {
		error_info = "Ա����Ÿ�ֵʧ�ܣ�";
		return false;
	}
	// �û���¼��
	if (NULL == strcpy(m_name_, login_user->new_login_name.c_str()))
	{
		error_info = "�û�����ֵʧ�ܣ�";
		return false;
	}
	// �û�����
	if (NULL == strcpy(m_password_, login_user->password1.c_str()))
	{
		error_info = "�û����븳ֵʧ�ܣ�";
		return false;
	}
	// �û�Ȩ��
	if (NULL == strcpy(m_permission_name_, login_user->login_permission.c_str()))
	{
		error_info = "�û�Ȩ�޸�ֵʧ�ܣ�";
		return false;
	}
	return true;
}

/*
 * @ brief: ��ʼ��SQL�����������
 **/
void CLoginForm::Initialization() {
	m_sql_pro_ret = SQL_NTS;   
	this->staff_no_len_ = SQL_NTS;
	this->name_len_ = SQL_NTS;
	this->password_len_ = SQL_NTS;
	this->permission_name_len_ = SQL_NTS;
}
