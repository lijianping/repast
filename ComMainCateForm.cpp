// ComMainCateForm.cpp: implementation of the CComMainCateForm class.
//
//////////////////////////////////////////////////////////////////////

#include "ComMainCateForm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComMainCateForm::CComMainCateForm()
{

}

CComMainCateForm::~CComMainCateForm()
{

}


/*
 * 说明：
 *     绑定主商品分类的所有字段
 * 返回值：
 *     成功返回true，失败返回false
 */
bool CComMainCateForm::BindingParameter()
{
	SQLBindCol(m_hstmt_, 1, SQL_C_SHORT, &m_no_, sizeof(m_no_), &m_sql_no_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	return true;
}


/*
 * 说明：
 *     获取主商品分类名称
 * 返回值：
 *     成功返回true，失败返回false
 */
bool CComMainCateForm:: GetMainCategoryName(std::string &error)
{
	m_sql_name_ = SQL_NTS;
	m_sql_no_ = SQL_NTS;
	m_sql_pro_ret = SQL_NTS;
// 	 if(false == BindReturn())
// 	 {
// 		 ReportError(m_hstmt_, SQL_HANDLE_STMT,error);
// 		 return false;
// 	 }   
	//{? = call GetMainCategoryName}
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	if ((m_return_code_ != SQL_SUCCESS) && (m_return_code_ != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		return false;
	}
	if(false == ExecSQLProc("exec GetMainCategoryName", error))
	{
		return false;
	}

// 	if(false == MoveFirst())
// 	{
// 		return false;
// 	}
//    if (false == IsSQLProcRetRight(error))
//    {
// 	return false;
// 	}
	return true;
}