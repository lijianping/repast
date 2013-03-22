// Permission.cpp: implementation of the CPermission class.
//
//////////////////////////////////////////////////////////////////////

#include "Permission.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPermission::CPermission()
{
	m_sql_no_ = SQL_NTS;
	m_sql_name_ = SQL_NTS;
	m_query_sql_ = "exec SelectPermissionAll";
}

CPermission::~CPermission()
{

}

bool CPermission::BindingParameter()
{
	//TODO:Œ¥ºÏ≤‚∑µªÿ÷µ
	SQLBindCol(m_hstmt_, 1, SQL_C_SHORT, &m_no_, 0, &m_sql_no_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, 0, &m_sql_name_);
	return true;
}
