// MenuForm.cpp: implementation of the CMenuForm class.
// 
// ////////////////////////////////////////////////////////////////////
// 
// #include "MenuForm.h"
// 
// ////////////////////////////////////////////////////////////////////
// Construction/Destruction
// ////////////////////////////////////////////////////////////////////
// 
// CMenuForm::CMenuForm()
// {
// 
// }
// 
// CMenuForm::~CMenuForm()
// {
// 
// }
// 
// /*
//  * @ 说明: 设置查询语句
//  * @ 参数:
//  *         statement [in] 待查询的语句
//  **/
// void CMenuForm::SetSQLStatement(const std::string statement)
// {
// 	m_query_sql_ = statement;
// }
// 
// /*
//  * @ 说明: 绑定参数
//  **/
// bool CMenuForm::BindingParameter()
// {
// 	SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_dish_no_, sizeof(m_dish_no_), &m_no_len_);
// 	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_dish_name_, sizeof(m_dish_name_), &m_name_len_);
// 	SQLBindCol(m_hstmt_, 3, SQL_C_FLOAT, &m_dish_price_, 0, &m_price_len_);
// 	return true;
// }
// 
// bool CMenuForm::InsertMenu(char *no, char *name, float price,std::string error)
// {
// 	char sql_insert[256]={0};
// 	sprintf(sql_insert, "execute InsertMenu '%s', '%s','%f'", no, name, price);
// 	if (false == ExecuteSQL(sql_insert,error))
// 	{
// 		return false;
// 	}
// 	return true;
// }
