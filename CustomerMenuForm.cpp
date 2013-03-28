// CustomerMenuForm.cpp: implementation of the CCustomerMenuForm class.
//
//////////////////////////////////////////////////////////////////////

#include "CustomerMenuForm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomerMenuForm::CCustomerMenuForm()
{

}

CCustomerMenuForm::~CCustomerMenuForm()
{

}

bool CCustomerMenuForm::BindingParameter()
{
	/* 菜名--单价--数量 */
	SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_dish_name_, sizeof(m_dish_name_), &m_dish_name_len_);
	SQLBindCol(m_hstmt_, 2, SQL_C_FLOAT, &m_dish_price_, 0, &m_dish_quantity_len_);
	SQLBindCol(m_hstmt_, 3, SQL_C_LONG, &m_dish_quantity_, 0, &m_dish_quantity_len_);
	return true;
}

/*
 * @ brief: 根据顾客编号获取顾客点菜信息
 * @ param: customer_no [in] 顾客编号
 **/
void CCustomerMenuForm::GetCustomerMenuSet(const char *customer_no) {
	char sql_statement[256] = {0};
	sprintf(sql_statement, "execute SelectCustomerMenu '%s'", customer_no);
	this->m_query_sql_ = std::string(sql_statement);
	this->GetRecordSet();	
}

/*
 * @ brief: 删除顾客点菜信息
 * @ param: customer_no [in] 顾客编号
 * @ param: dish_name [in] 商品名称
 * @ return: 成功返回true
 **/
bool CCustomerMenuForm::DeleteDish(const char *customer_no, 
								   const char *dish_name) {
	char sql_delete[128] = {0};
	sprintf(sql_delete, "execute DeleteCustomerMenu '%s', '%s'", customer_no, dish_name);
	std::string error;
	return this->ExecuteSQL(sql_delete, error);
}

bool CCustomerMenuForm::DeleteAll(const char *customer_no) {
	char sql_delete[128] = {0};
	sprintf(sql_delete, "execute DeleteCustomerMenuAll '%s'", customer_no);
	std::string error;
	return this->ExecuteSQL(sql_delete, error);
}
