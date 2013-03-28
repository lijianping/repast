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
 * @ return: 若成功返回true，否则返回false
 **/
bool CCommodity::GetCommodityNameSet(const char* main_name) {
	Initialize();
	BindReturn();// 绑定返回值
	// 绑定输入参数
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR,\
		                              sizeof(m_main_name_) - 1, 0, m_main_name_, \
									  sizeof(m_main_name_), &m_sql_main_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(m_main_name_, main_name);
	std::string err_info;
	ExecSQLProc("{? = call GetCommodityByMainName(?)}", err_info);
	BindingParameter();
	return true;
}
bool CCommodity::GetCommodityNameSet(const char* main_name, const char *child_name) {
	Initialize();
	BindReturn(); // 绑定返回值
	// 绑定输入参数
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
	std::string err_info;
	ExecSQLProc("{? = call GetCommodityByDBName(?,?)}", err_info);
	BindingParameter();
	return true;
}

/*
 * @ brief: 初始化数据
 **/
void CCommodity::Initialize() {
	m_sql_no_ = SQL_NTS;
	m_sql_name_ = SQL_NTS;
	m_sql_purchase_price_ = SQL_NTS;
	m_sql_quantity_ = SQL_NTS;
	m_sql_child_name_ = SQL_NTS;
	m_sql_main_name_ = SQL_NTS;
	m_sql_unit_ = SQL_NTS;
	m_sql_sale_price_ = SQL_NTS;
	m_sql_register_date_ = SQL_NTS;
	m_sql_pro_ret = SQL_NTS;
	memset(m_no_, 0, sizeof(m_no_));
	memset(m_name_, 0, sizeof(m_name_));
	memset(m_main_name_, 0, sizeof(m_main_name_));
	memset(m_child_name_, 0, sizeof(m_child_name_));
	memset(m_unit_, 0, sizeof(m_unit_));
	memset(m_register_date_, 0, sizeof(m_register_date_));
}

/*
 * @ brief: 绑定返回记录集
 * @ return: 成功返回true
 **/
bool CCommodity::BindingParameter() {
	// 绑定商品编号
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_no_, sizeof(m_no_), &m_sql_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品名称
	m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品进价
	m_return_code_ = SQLBindCol(m_hstmt_, 3, SQL_C_FLOAT, &m_purchase_price_, 0, &m_sql_purchase_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品数量
	m_return_code_ = SQLBindCol(m_hstmt_, 4, SQL_C_LONG, &m_quantity_, 0, &m_sql_quantity_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品子分类编号
	short child_no;   // 不用
	m_return_code_ = SQLBindCol(m_hstmt_, 5, SQL_C_SHORT, &child_no, 0, &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品单位
	m_return_code_ = SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_unit_, sizeof(m_unit_), &m_sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品售价
	m_return_code_ = SQLBindCol(m_hstmt_, 7, SQL_C_FLOAT, &m_sale_price_, 0, &m_sql_sale_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品注册时间
	m_return_code_ = SQLBindCol(m_hstmt_, 8, SQL_C_CHAR, m_register_date_, sizeof(m_register_date_), &m_sql_register_date_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
		return true;
}