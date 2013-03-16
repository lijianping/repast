// CStaffForm.cpp: implementation of the CStaffForm class.
//
//////////////////////////////////////////////////////////////////////

#include "StaffForm.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStaffForm::CStaffForm()
: m_age_(0),
  m_salary_(0)
{
    memset(m_id_, '\0', sizeof(m_id_));
    memset(m_name_, '\0', sizeof(m_name_));
    memset(m_sex_, '\0', sizeof(m_sex_));
    memset(m_dept_num_, '\0', sizeof(m_dept_num_));
    memset(m_dept_name_, '\0', sizeof(m_dept_name_));
	memset(m_mailbox_, '\0', sizeof(m_mailbox_));
	memset(m_phone_num_, '\0', sizeof(m_phone_num_));
	memset(m_address_, '\0', sizeof(m_address_));

	m_sql_id_=SQL_NTS;         /* the staff's id in database Staff form */
	m_sql_name_=SQL_NTS;       /* the staff's name in database Staff form */
	m_sql_sex_=SQL_NTS;        /* the staff's sex in database Staff form */
	m_sql_age_=SQL_NTS;        /* the staff's age in database Staff form */
	m_sql_salary_=SQL_NTS;     /* the staff's salary in database Staff form */
	m_sql_dept_num_=SQL_NTS;   /* the staff's department number in database Staff form */
	m_sql_dept_name_=SQL_NTS;  /* the staff's department name in database Dept form */
	m_sql_mailbox_=SQL_NTS;    /* the staff's mailbox in database Dept form */
	m_sql_phone_num_=SQL_NTS;  /* the staff's phone number in database Dept form */
	m_sql_address_=SQL_NTS;    /* the staff's address in database Dept form */
	 m_sql_pro_ret =SQL_NTS;

    m_query_sql_ = "select Sno,Sname,Ssex,Sage,Ssalary,Dname,Smailbox,Sphoneno,Saddress from Staff,Dept where Sdeptno=Dno";
}

CStaffForm::~CStaffForm()
{

}

/*
 * ˵��: �󶨼�¼������
 * ����ֵ: ִ�гɹ�����true, ���򷵻�false
 */
bool CStaffForm::BindingParameter()
{
    /* ���� *//*TODO:��δ��鷵��ֵ */
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_id_, sizeof(m_id_), &m_sql_id_);
    SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
    SQLBindCol(m_hstmt_, 3, SQL_C_CHAR, m_sex_, sizeof(m_sex_), &m_sql_sex_);
    SQLBindCol(m_hstmt_, 4, SQL_C_SSHORT, &m_age_, 0, &m_sql_age_);
    SQLBindCol(m_hstmt_, 5, SQL_C_FLOAT, &m_salary_, 0, &m_sql_salary_);
    SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_dept_name_, sizeof(m_dept_name_), &m_sql_dept_name_);
   // SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_dept_num_, sizeof(m_dept_num_), &m_sql_dept_num_);
	SQLBindCol(m_hstmt_, 7, SQL_C_CHAR, m_mailbox_, sizeof(m_mailbox_), &m_sql_mailbox_);
	SQLBindCol(m_hstmt_, 8, SQL_C_CHAR, m_phone_num_, sizeof(m_phone_num_), &m_sql_phone_num_);
	SQLBindCol(m_hstmt_, 9, SQL_C_CHAR, m_address_, sizeof(m_address_), &m_sql_address_);
    return true;
}


/*
 * ˵��: 
 *       �󶨼�¼������,���ڻ�ȡ�洢���̷���ֵ
 * ������
 *       is_add       [in]  ��־�Ƿ������Ա�����ܵĲ����󶨺�������Ϊtrue,����Ϊfalse
 *       error_info   [out] ��ȡ������Ϣ
 * ����ֵ: 
 *       ִ�гɹ�����true, ���򷵻�false
 */
bool CStaffForm::BindingParameter(bool is_add, std::string &error_info)
{
	m_sql_id_=SQL_NTS;         /* the staff's id in database Staff form */
	m_sql_name_=SQL_NTS;       /* the staff's name in database Staff form */
	m_sql_sex_=SQL_NTS;        /* the staff's sex in database Staff form */
	m_sql_age_=SQL_NTS;        /* the staff's age in database Staff form */
	m_sql_salary_=SQL_NTS;     /* the staff's salary in database Staff form */
	m_sql_dept_num_=SQL_NTS;   /* the staff's department number in database Staff form */
	m_sql_dept_name_=SQL_NTS;  /* the staff's department name in database Dept form */
	m_sql_mailbox_=SQL_NTS;    /* the staff's mailbox in database Dept form */
	m_sql_phone_num_=SQL_NTS;  /* the staff's phone number in database Dept form */
	m_sql_address_=SQL_NTS;    /* the staff's address in database Dept form */
	m_sql_pro_ret =SQL_NTS;
	m_sql_old_id_ =SQL_NTS;

	/*�󶨴洢���̷���ֵ*/
	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, \
		                              SQL_INTEGER,0, 0,&m_pro_ret, 0, &m_sql_pro_ret);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�󶨷���ֵʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
    /* ���в���*/
    m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, \
									SQL_CHAR, sizeof(m_id_)-1, 0, m_id_, sizeof(m_id_), &m_sql_id_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�󶨲���2ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, \
		                              SQL_CHAR, sizeof(m_name_)-1, 0, m_name_, sizeof(m_name_), &m_sql_name_);
   	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�󶨲���3ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, \
		                             SQL_CHAR, sizeof(m_sex_)-1, 0, m_sex_, sizeof(m_sex_),  &m_sql_sex_);
   	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�󶨲���4ʧ��!";
			ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_SSHORT,\
									 SQL_SMALLINT, 0, 0, &m_age_, 0, &m_sql_age_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�󶨲���5ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 6, SQL_PARAM_INPUT, SQL_C_FLOAT, \
		                              SQL_FLOAT, 0, 0, &m_salary_, 0, &m_sql_salary_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�󶨲���6ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 7, SQL_PARAM_INPUT, SQL_C_CHAR,\
		                             SQL_CHAR, sizeof(m_dept_name_)-1, 0, m_dept_name_, 0, &m_sql_dept_name_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�󶨲���7ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 8, SQL_PARAM_INPUT, SQL_C_CHAR,\
		                              SQL_CHAR, sizeof(m_mailbox_)-1, 0, m_mailbox_, 0, &m_sql_mailbox_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�󶨲���8ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 9, SQL_PARAM_INPUT, SQL_C_CHAR, \
		                              SQL_CHAR, sizeof(m_phone_num_)-1, 0, m_phone_num_, 0, &m_sql_phone_num_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�󶨲���9ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 10, SQL_PARAM_INPUT, SQL_C_CHAR, \
		                              SQL_CHAR, sizeof(m_address_)-1, 0, m_address_, 0, &m_sql_address_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�󶨲���10ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	/*��Ա���ľ�ID*/
	if (is_add == false)
	{
		m_return_code_ = SQLBindParameter(m_hstmt_, 11, SQL_PARAM_INPUT, \
			SQL_C_CHAR, SQL_CHAR, sizeof(m_old_id_)-1, 0, m_old_id_, 0, &m_sql_old_id_);
		if ((m_return_code_ != SQL_SUCCESS) &&
			(m_return_code_ != SQL_SUCCESS_WITH_INFO))
		{
			error_info = "�󶨲���11ʧ��!";
			ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
			return false;
		}
	}
	return true;
}

/*
 * ˵���� ����Ա����Ϣ
 * ������
 *        staff_info	     [in] Ա����Ϣ
 *         error_info		 [out] ������Ϣ
 * ����ֵ��
 *        ִ�гɹ�����true,���򷵻�false
 **/
bool CStaffForm::InsertInfo(STAFFINFO * staff_info,   std::string &error_info)
{
	/*��������Ƿ���ȷ*/
	if (false == CheckStaff(staff_info, error_info))
	{
		return false;
	}
	/*���Ա������*/
	if (false == SetStaff(staff_info, error_info))
	{
		return false;
	}
	/*�󶨴洢���̷���ֵ�ʹ������*/
	if(false ==BindingParameter(true, error_info))
	{
		return false;
	}
	/*ִ�д洢����*/
	if(false == ExecuteSQL("{? = call InsertStaff (?,?,?,?,?,?,?,?,?)}", error_info))
	{
		return false;
	}
	while ( ( m_return_code_ = SQLMoreResults(m_hstmt_) ) != SQL_NO_DATA )
	{
	}
	if (m_pro_ret != 0)
	{
		error_info="Ա����Ų����ظ���";
		return false;
	}
    return true;
}

/*
 * ˵���� ɾ��Ա����Ϣ
 * ������
 *        user_id [in] Ա�����
 *        error_info [out] ������Ϣ
 * ����ֵ��
 *        ִ�гɹ�����true,���򷵻�false
 **/
bool CStaffForm::DeleteInfo(const char *user_id, std::string &error_info)
{
	char delete_sql[500];
	sprintf (delete_sql, "execute DeleteStaff '%s'", user_id);/*��ʽ��ɾ�����*/
	/* ִ����� */
    if (false == ExecuteSQL(delete_sql, error_info))
    {
		error_info = "ɾ��Ա������ʧ�ܣ�";
        return false;
    }
	return true;
}


/*
 * ˵���� ����Ա����Ϣ
 * ������
 *        staff_info	     [in] Ա����Ϣ
 *        error_info		 [out] ������Ϣ
 *����ֵ��
 *        ִ�гɹ�����true,���򷵻�false
 **/
bool CStaffForm::UpdateInfo(STAFFINFO * staff_info,	 std::string &error_info)
{
	if (false == CheckStaff(staff_info,error_info))
	{
		return false;
	}
	if (false == SetStaff(staff_info, error_info))
	{
		return false;
	}
	if (false == BindingParameter(false, error_info))
	{
		return false;
	}
	/* ִ����� */
    if (false == ExecuteSQL("{? = call UpdateStaff (?,?,?,?,?,?,?,?,?,?)}", error_info))
    {
        return false;
    }
	/*TDDO:��Ӵ�����*/
	while ( ( m_return_code_ = SQLMoreResults(m_hstmt_) ) != SQL_NO_DATA )
	{
	}
	if (m_pro_ret != 0)
	{
		error_info="Ա����Ų����ظ���";
		return false;
	}
	return true;
}


/* ˵����
 *    ͳ��Ա������
 * ����ֵ
 *       �ɹ�����Ա��������ʧ�ܷ���-1
 */
int CStaffForm::GetStaffSum()
{
	int staff_sum=-1;
	SQLINTEGER sql_sum;
	std::string error;
	char *sql_select_sum="select count(*) from Staff";
	if (false == ExecuteSQL(sql_select_sum, error))
	{
		MessageBox(NULL, error.c_str(), TEXT("ͳ��Ա����������"), MB_OK);
		return staff_sum;
	}
	SQLBindCol(m_hstmt_, 1, SQL_C_SLONG, &staff_sum, sizeof(staff_sum), &sql_sum);
	MoveFirst();
	return staff_sum;
}

/*
 * ˵����
 *      ���Ա�������Ƿ���ȷ
 * ������
 *      staff_info    [in]  Ա����Ϣ
 *      error_info    [out]  ������Ϣ
 * ����ֵ��
 *       �ɹ�����true,���򷵻�false
 */
bool CStaffForm::CheckStaff(STAFFINFO * staff_info,std::string &error_info)
{
	if (strlen(staff_info->id.c_str())>sizeof(m_id_)-1)
	{
		error_info ="Ա�����̫����  �涨Ա������Ϊ8��Ӣ�Ļ�����";
		return false;
	}
	if (strlen(staff_info->name.c_str())>sizeof(m_name_)-1)
	{
		error_info = "Ա������̫�� �� �涨Ա�������Ϊ9��Ӣ���ַ���4������";
		return false;
	}
	if (atoi(staff_info->age.c_str())<16||atoi(staff_info->age.c_str())>150)
	{
		error_info = "Ա�����䲻��ȷ������ϸ��飡";
		return false;
	}
	if (atof(staff_info->salary.c_str())<0||atof(staff_info->salary.c_str())>12345678)
	{
		error_info = "Ա�����ʲ���ȷ������ϸ��飡";
		return false;
	}
	if (NULL == strchr(staff_info->email_address.c_str(), '@'))
	{
		error_info = "Ա�������ʽ����ȷ������ϸ���";
		return false;
	}
	if (strlen(staff_info->email_address.c_str())>sizeof(m_mailbox_)-1)
	{
		error_info = "Ա�������ַ̫������ȷ����";
		return false;
	}
	if (strlen(staff_info->phone.c_str())>sizeof(m_phone_num_)-1)
	{
		error_info = "Ա���ĵ绰����̫�������ʵ���������";
		return false;
	}
	if (strlen(staff_info->address.c_str())>sizeof(m_address_)-1)
	{
		error_info = "Ա����ַ����̫�������ʵ���������";
		return false;
	}
	return true;
}



/*
 * ˵����
 *      ���Ա����Ϣ
 * ������
 *      staff_info    [in]  Ա����Ϣ
 *      error_info    [out]  ������Ϣ  
 * ����ֵ��
 *       �ɹ�����true,���򷵻�false
 */
bool CStaffForm::SetStaff(STAFFINFO * staff_info,std::string &error_info)
{
	if (NULL == strcpy(m_old_id_, staff_info->old_id.c_str()))
	{
		return false;
	}
	if (NULL == strcpy(m_id_, staff_info->id.c_str()))
	{
		return false;
	}
	if (NULL == strcpy(m_name_, staff_info->name.c_str()))
	{
		return false;
	}
	if (NULL == strcpy(m_sex_, staff_info->sex.c_str()))
	{
		return false;
	}
	m_age_ = (short)atoi(staff_info->age.c_str());
	m_salary_ = atof(staff_info->salary.c_str());
	char department[41];
	DeleteSpace(staff_info->department.c_str(), department);
	if (NULL == strcpy(m_dept_name_, department))
	{
		return false;
	}
	if (NULL == strcpy(m_mailbox_, staff_info->email_address.c_str()))
	{
		return false;
	}
	if (NULL == strcpy(m_phone_num_, staff_info->phone.c_str()))
	{
		return false;
	}
 	if (NULL ==  strcpy(m_address_, staff_info->address.c_str()))
	{
		return false;
	}
	return true;
}