// Department.cpp: implementation of the CDepartment class.
//
//////////////////////////////////////////////////////////////////////

#include "Department.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDepartment::CDepartment()
{
	memset(m_name_, '\0', sizeof(m_name_));
}

CDepartment::~CDepartment()
{

}

bool CDepartment::BindingParameter()
{
	/* ���� */
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_id_, sizeof(m_id_), &m_sql_id_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	return true;
}

/*
 *˵������ȡ��������
 *����ֵ�����ز�������
 **/
int CDepartment:: GetDeptSum()
{
	int dept_sum;
	std::string error;
	char *sql_select_sum="select count(*) from Dept";
	SQLINTEGER sql_depat_sum;
	if (false == ExecuteSQL(sql_select_sum, error))
	{
		MessageBox(NULL, error.c_str(), TEXT("��ȡ������������"), MB_OK);
	}
	SQLBindCol(m_hstmt_, 1, SQL_C_SLONG, &dept_sum, sizeof(dept_sum), &sql_depat_sum);
	FetchData();
	return dept_sum;
}
