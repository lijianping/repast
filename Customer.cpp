// Customer.cpp: implementation of the CCustomer class.
//
//////////////////////////////////////////////////////////////////////

#include "Customer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomer::CCustomer()
{
	m_query_sql_ = "exec SelectCustomer";
}

CCustomer::~CCustomer()
{

}

bool CCustomer::BindingParameter()
{

 	SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_customer_no_, sizeof(m_customer_no_), &m_table_state_len_);
    SQLBindCol(m_hstmt_, 2, SQL_C_SHORT, &m_customer_num_, 0, &m_customer_num_len_);
	SQLBindCol(m_hstmt_, 3, SQL_C_CHAR, m_founding_time_, sizeof(m_founding_time_), &m_founding_time_len_);
	SQLBindCol(m_hstmt_, 4, SQL_C_CHAR, m_end_time_, sizeof(m_end_time_), &m_end_time_len_);
	SQLBindCol(m_hstmt_, 5, SQL_C_FLOAT, &m_money_, 0, &m_money_len_);
	SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_clerk_, sizeof(m_clerk_), &m_clerk_len_);
	SQLBindCol(m_hstmt_, 7, SQL_C_SHORT, &m_payablenum_, 0, &m_sql_payablenum_len_);
	SQLBindCol(m_hstmt_, 8, SQL_C_CHAR, m_table_no_, sizeof(m_table_no_), &m_table_no_len_);
	SQLBindCol(m_hstmt_, 9, SQL_C_SHORT, &m_table_state_, sizeof(m_table_state_), &m_table_state_len_);
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

bool CCustomer::GetCustomerByName(const char *customer_no, const char* table_no, std::string &error)
{
	char query[128];
	sprintf(query,"exec SelectCustomerByName '%s', '%s'", customer_no, table_no);
	if (false == ExecuteSQL(query,error))
	{
		return false;
	}
	BindingParameter();
	MoveFirst();
	return true;
}