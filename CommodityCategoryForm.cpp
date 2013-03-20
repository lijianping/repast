// CommodityCategoryForm.cpp: implementation of the CCommodityCategoryForm class.
//
//////////////////////////////////////////////////////////////////////

#include "CommodityCategoryForm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommodityCategoryForm::CCommodityCategoryForm()
{
	 m_sql_no_ = SQL_NTS;
	 m_sql_name_ = SQL_NTS;
	 m_query_sql_ = "select * from CommodityCategory";

}

CCommodityCategoryForm::~CCommodityCategoryForm()
{

}

bool CCommodityCategoryForm::BindingParameter()
{
	SQLBindCol(m_hstmt_, 1, SQL_C_LONG, &m_no_, sizeof(m_no_), &m_sql_no_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	return true;
}