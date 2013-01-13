// MenuForm.cpp: implementation of the CMenuForm class.
//
//////////////////////////////////////////////////////////////////////

#include "MenuForm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenuForm::CMenuForm()
{

}

CMenuForm::~CMenuForm()
{

}

/*
 * @ ˵��: ���ò�ѯ���
 * @ ����:
 *         statement [in] ����ѯ�����
 **/
void CMenuForm::SetSQLStatement(const std::string statement)
{
	m_query_sql_ = statement;
}

/*
 * @ ˵��: �󶨲���
 **/
bool CMenuForm::BindingParameter()
{
	SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_dish_no_, sizeof(m_dish_no_), &m_no_len_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_dish_name_, sizeof(m_dish_name_), &m_name_len_);
	SQLBindCol(m_hstmt_, 3, SQL_C_FLOAT, &m_dish_price_, 0, &m_price_len_);
	return true;
}
