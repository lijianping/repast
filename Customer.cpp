// Customer.cpp: implementation of the CCustomer class.
//
//////////////////////////////////////////////////////////////////////

#include "Customer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomer::CCustomer()
{

}

CCustomer::~CCustomer()
{

}

bool CCustomer::BindingParameter()
{
	SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_table_no_, sizeof(m_table_no_), &m_table_no_len_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_customer_no_, sizeof(m_customer_no_), &m_table_state_len_);
	SQLBindCol(m_hstmt_, 3, SQL_C_SHORT, &m_table_state_, 0, &m_customer_no_len_);
	SQLBindCol(m_hstmt_, 4, SQL_C_CHAR, m_founding_time_, sizeof(m_founding_time_), &m_time_len_);
	return true;
}

bool CCustomer::InsertCustomerMenu(const char *customer_no, const char *menu_name, int quantity)
{
	std::string error;
	char sql_insert[256]={0};
	sprintf(sql_insert, "execute InsertCustomerMenu '%s', '%s','%d'",customer_no, menu_name, quantity);
	if (false == ExecuteSQL(sql_insert,error))
	{
		return false;
	}
	return true;
}
