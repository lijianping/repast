// Commodity.cpp: implementation of the CCommodity class.
//
//////////////////////////////////////////////////////////////////////

#include "Commodity.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommodity::CCommodity()
{  
	
}

CCommodity::~CCommodity()
{

}

/*
 * @ breif: 根据商品的主，次分类名称获取商品名称
 * @ param: main_name [in] 主分类名
 * @ param: child_name [in] 次分类名
 * @ parem: err_info [out] 错误信息
 * @ return: 若成功返回true，否则返回false
 **/
bool CCommodity::GetCommodityNameSet(const char* main_name,
	                                 const char *child_name,
	                                 std::string &err_info)
{
	Initialize();
	SQLRETURN m_return_code_;   // sql 返回类型
	// 绑定返回值
	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER,\
		                       0, 0, &m_pro_ret, 0, &m_sql_pro_ret);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RETURN_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, sizeof(m_main_name_) - 1,\
		                       0, m_main_name_, sizeof(m_main_name_), &m_sql_main_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, sizeof(m_child_name_) - 1,\
		                       0, m_child_name_, sizeof(m_child_name_), &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(m_main_name_, main_name);
	strcpy(m_child_name_, child_name);
	ExecSQLProc("{? = call GetCommodityName(?,?)}", err_info);
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	return true;
}

/*
 * @ brief: 初始化数据
 **/
void CCommodity::Initialize() {
	m_sql_no_ = SQL_NTS;
	m_sql_name_ = SQL_NTS;
	
	m_sql_main_name_ = SQL_NTS;
	m_sql_child_name_ = SQL_NTS;
	m_sql_pro_ret = SQL_NTS;
	memset(m_name_, 0, sizeof(m_name_));
	memset(m_main_name_, 0, sizeof(m_main_name_));
	memset(m_child_name_, 0, sizeof(m_child_name_));
}