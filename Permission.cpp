// Permission.cpp: implementation of the CPermission class.
//
//////////////////////////////////////////////////////////////////////

#include "Permission.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPermission::CPermission()
{
	m_sql_old_no_ = SQL_NTS;
	m_sql_no_ = SQL_NTS;
	m_sql_name_ = SQL_NTS;
	m_query_sql_ = "exec SelectPermissionAll";
}

CPermission::~CPermission()
{

}

bool CPermission::BindingParameter()
{
	//TODO:δ��ⷵ��ֵ
	SQLBindCol(m_hstmt_, 1, SQL_C_SHORT, &m_no_, 0, &m_sql_no_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	return true;
}

/*
 * ˵����
 *    ��ִ�д洢���̵Ĳ���
 * ������
 *       bind_type  [in]    �����ͣ�ADD, MODIFY, DELETE
 *       error      [out]   ��Ŵ�����Ϣ
 * ����ֵ��
 *      �ɹ�����true, ���򷵻�false
 **/
bool CPermission::BindingParameter(int bind_type, std::string error)
{
	m_sql_no_ = SQL_NTS;
	m_sql_old_no_ = SQL_NTS;
	m_sql_name_ = SQL_NTS;

	//�󶨴洢���̷���ֵ
	if(!this->BindReturn())
	{
		error="�󶨴洢���̷���ֵʧ��";
		return false;
	}
	/* ���в���*/
    m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_SHORT, \
		SQL_SMALLINT, 0, 0, &m_no_, 0, &m_sql_no_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error = "�󶨲���2ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
        return false;
    }
	if (bind_type == DELETEPERMISSION)//������Ϊdelete,��ֻ��Ҫ�󶨷���ֵ�������ID
	{
		return true;
	}
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR, sizeof(m_name_)-1, 0, m_name_, sizeof(m_name_), &m_sql_name_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error = "�󶨲���3ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
        return false;
    }
	if (bind_type == ADDPERMISSION)//������Ϊadd,��ֻ��Ҫ�󶨷���ֵ�������ID,name
	{
		return true;
	}
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_SHORT, \
		SQL_SMALLINT, 0, 0, &m_old_no_, 0, &m_sql_old_no_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error = "�󶨲���4ʧ��!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
        return false;
    }
	return true;
}

/*
 * ˵����
 *    ���Ȩ�޵ĸ����ֶ��Ƿ���ȷ
 * ������
 *       permission  [in]    Ȩ����Ϣ�ṹ��
 *       error       [out]   ��Ŵ�����Ϣ
 * ����ֵ��
 *      �ɹ�����true, ���򷵻�false
 **/
bool CPermission::CheckPermission(PERMISSION *permission, std::string &error)
{
	if (0 == permission->no.length())
	{
		error = "��Ų���Ϊ�գ�";
		return false;
	}
	if (permission->no.length() > sizeof(m_name_)-1)
	{
		error = "�û���ų��ȳ�������ķ�Χ�����ʵ����̺����ԣ�";
		return false;
	}
	if (0 == permission->name.length())
	{
		error = "�û�������Ϊ�գ�";
		return false;
	}
	if (permission->name.length() > sizeof(m_name_)-1)
	{
		error = "�û������ȳ�������ķ�Χ�����ʵ����̺����ԣ�";
		return false;
	}
	return true;
}

/*
 * ˵����
 *    ΪȨ�޵ĸ����ֶθ�ֵ
 * ������
 *       permission  [in]    Ȩ����Ϣ�ṹ��
 **/
void CPermission::SetPermission(PERMISSION *permission)
{
	m_no_ = atoi(permission->no.c_str());
	m_old_no_ = atoi(permission->old_no.c_str());
	strcpy(m_name_ , permission->name.c_str());
}

/*
 * ˵����
 *    �����û�Ȩ��
 * ������
 *       permission  [in]    Ȩ����Ϣ�ṹ��
 *       error       [out]   ���������Ϣ
 * ����ֵ��
 *       ���ӳɹ�����true, ���򷵻�false
 */
bool CPermission::InsertPermission(PERMISSION *permission, std::string &error)
{
	if (!CheckPermission(permission,error))
	{
		return false;
	}
	SetPermission(permission);
	if (!BindingParameter(ADDPERMISSION, error))
	{
		return false;
	}
	if (!ExecSQLProc("{? = call InsertPermission(?,?)}",error))
	{
		return false;
	}
	if(!IsSQLProcRetRight(error))
	{
		return false;
	}
	return true;
}


/*
 * ˵����
 *    �޸��û�Ȩ��
 * ������
 *       permission  [in]    Ȩ����Ϣ�ṹ��
 *       error       [out]   ���������Ϣ
 * ����ֵ��
 *       =�޸ĳɹ�����true, ���򷵻�false
 */
bool CPermission::UpdatePermission(PERMISSION *permission, std::string &error)
{
	if (!CheckPermission(permission,error))
	{
		return false;
	}
	SetPermission(permission);
	if (!BindingParameter(UPDATEPERMISSION, error))
	{
		return false;
	}
	if (!ExecSQLProc("{? = call UpdatePermission(?,?,?)}",error))
	{
		return false;
	}
	if(!IsSQLProcRetRight(error))
	{
		return false;
	}
	return true;
}

/*
 * ˵����
 *    ɾ���û�Ȩ��
 * ������
 *       permission  [in]    Ȩ����Ϣ�ṹ��
 *       error       [out]   ���������Ϣ
 * ����ֵ��
 *       ɾ���ɹ�����true, ���򷵻�false
 */
bool CPermission:: DeletePermission(PERMISSION *permission, std::string &error)
{
	SetPermission(permission);
	if (!BindingParameter(DELETEPERMISSION, error))
	{
		return false;
	}
	if (!ExecSQLProc("{? = call DeletePermission(?)}",error))
	{
		return false;
	}
	if(!IsSQLProcRetRight(error))
	{
		return false;
	}
	return true;
}
