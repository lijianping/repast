// Commodity.cpp: implementation of the CCommodity class.
//
//////////////////////////////////////////////////////////////////////

#include "Commodity.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommodity::CCommodity()
{   /*不可分行*/
	m_query_sql_ =  "select Commodity.Cno,Cname,Cprice,Cregisterdate,Csum from Commodity,	CommoditySum where Commodity.Cno=CommoditySum.Cno";
}

CCommodity::~CCommodity()
{

}

bool CCommodity::BindingParameter()
{
	/* 绑定列 */
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR,   m_no_,            sizeof(m_no_),           &m_sql_no_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR,   m_name_,          sizeof(m_name_),         &m_sql_name_);
	SQLBindCol(m_hstmt_, 3, SQL_C_DOUBLE, &m_price_,        sizeof(m_price_),        &m_sql_price_);
	SQLBindCol(m_hstmt_, 4, SQL_C_CHAR,   m_register_date_, sizeof(m_register_date_),&m_sql_register_date_);
	SQLBindCol(m_hstmt_, 5, SQL_C_LONG,   &m_sum_,          sizeof(m_sum_),          &m_sql_sum_);
	return true;
}

bool CCommodity::InsertInfo(char no[9], char name[256], double price, char register_date[21], int sum)
{
	char insert_sql[1024];
	/*TODO: ADD INSERT*/
	return true;
}