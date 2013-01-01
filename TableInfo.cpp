// TableInfo.cpp: implementation of the CTableInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "TableInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTableInfo::CTableInfo()
{
	m_query_sql_ = "select * from TableInfo";
}

CTableInfo::~CTableInfo()
{

}

bool CTableInfo::BindingParameter()
{
	/* °ó¶¨ÁÐ */
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR,   m_table_no_,      sizeof(m_table_no_),    &m_sql_table_no_);
	SQLBindCol(m_hstmt_, 2, SQL_C_SSHORT, &m_payable_num_,  sizeof(m_payable_num_), &m_sql_payable_num_);
	SQLBindCol(m_hstmt_, 3, SQL_C_SSHORT, &m_real_num_,     sizeof(m_real_num_),    &m_sql_real_num_);
	SQLBindCol(m_hstmt_, 4, SQL_C_SSHORT, &m_table_status_, sizeof(m_table_status_),&m_sql_table_status_);
	SQLBindCol(m_hstmt_, 5, SQL_C_CHAR,   m_datetime_,      sizeof(m_datetime_),    &m_sql_datetime);
	return true;
}