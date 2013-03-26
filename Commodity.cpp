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
 * @ breif: ������Ʒ�������η������ƻ�ȡ��Ʒ����
 * @ param: main_name [in] ��������
 * @ param: child_name [in] �η�����
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool CCommodity::GetCommodityNameSet(const char* main_name) {
	Initialize();
	BindReturn();// �󶨷���ֵ
	// ���������
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
	BindReturn(); // �󶨷���ֵ
	// ���������
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
 * @ brief: ��ʼ������
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
 * @ brief: �󶨷��ؼ�¼��
 * @ return: �ɹ�����true
 **/
bool CCommodity::BindingParameter() {
	// ����Ʒ���
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_no_, sizeof(m_no_), &m_sql_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ����
	m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ����
	m_return_code_ = SQLBindCol(m_hstmt_, 3, SQL_C_FLOAT, &m_purchase_price_, 0, &m_sql_purchase_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ����
	m_return_code_ = SQLBindCol(m_hstmt_, 4, SQL_C_LONG, &m_quantity_, 0, &m_sql_quantity_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ�ӷ�����
	short child_no;   // ����
	m_return_code_ = SQLBindCol(m_hstmt_, 5, SQL_C_SHORT, &child_no, 0, &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ��λ
	m_return_code_ = SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_unit_, sizeof(m_unit_), &m_sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ�ۼ�
	m_return_code_ = SQLBindCol(m_hstmt_, 7, SQL_C_FLOAT, &m_sale_price_, 0, &m_sql_sale_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒע��ʱ��
	m_return_code_ = SQLBindCol(m_hstmt_, 8, SQL_C_CHAR, m_register_date_, sizeof(m_register_date_), &m_sql_register_date_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
		return true;
}