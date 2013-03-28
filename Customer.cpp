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
	return true;
}

/*
 * @ brief: 增加顾客信息
 * @ param: customer_no [in] 顾客编号
 * @ return: 若成功返回true
 **/
bool CCustomer::AddCustomer(const char *consumer_no) {
	Initialize();
	BindReturn();
	// 绑定输入参数
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(m_customer_no_) - 1, 0, m_customer_no_,\
		                              sizeof(m_customer_no_), &m_customer_no_len_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(m_customer_no_, consumer_no);
	std::string err_info;	
	// 执行存储过程
	ExecSQLProc("{? = call InsertCustomer(?)}", err_info);
	return true;
}

/*
 * @ brief: 初始化相关数据
 **/
void CCustomer::Initialize() {
	memset(m_customer_no_, 0, sizeof(m_customer_no_));
	m_customer_num_ = 0;
	memset(m_founding_time_, 0, sizeof(m_founding_time_));
	memset(m_end_time_, 0, sizeof(m_end_time_));
	m_money_ = 0;
	memset(m_clerk_, 0, sizeof(m_clerk_));
	memset(m_table_no_, 0, sizeof(m_table_no_));
	memset(m_floor_name_, 0, sizeof(m_floor_name_));
	memset(m_room_name_, 0, sizeof(m_room_name_));
	m_customer_no_len_ = SQL_NTS;
	m_customer_num_len_ = SQL_NTS;
	m_founding_time_len_ = SQL_NTS;
	m_end_time_len_ = SQL_NTS;
	m_money_len_ = SQL_NTS;
	m_clerk_len_ = SQL_NTS;
	m_sql_payablenum_len_ = SQL_NTS;
	m_table_no_len_ = SQL_NTS;
	m_table_state_len_ = SQL_NTS;
	m_floor_name_len_ = SQL_NTS;
	m_room_name_len_ = SQL_NTS;
}

bool CCustomer::AddCustomerTable(const char *customer_no, 
	                             const char *floor_name,
	                             const char *room_name, 
								 const char *table_no,
								 int real_num, int status) {
    Initialize();
	BindReturn();
	// 绑定输入参数
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(m_customer_no_) - 1, 0, m_customer_no_,\
		                              sizeof(m_customer_no_), &m_customer_no_len_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		// 绑定输入参数
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
	                                  sizeof(m_floor_name_) - 1, 0, m_floor_name_,\
									  sizeof(m_floor_name_), &m_floor_name_len_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
	         	                      sizeof(m_room_name_) - 1, 0, m_room_name_,\
		                              sizeof(m_room_name_), &m_room_name_len_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
	                                  sizeof(m_table_no_) - 1, 0, m_table_no_,\
		                              sizeof(m_table_no_), &m_table_no_len_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 6, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT,\
		                              0, 0, &m_payablenum_, 0, &m_sql_payablenum_len_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 7, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT,\
	                                  0, 0, &m_table_state_, 0, &m_table_state_len_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(m_customer_no_, customer_no);
	strcpy(m_floor_name_, floor_name);
	strcpy(m_room_name_, room_name);
	strcpy(m_table_no_, table_no);
	m_payablenum_ = real_num;
	m_table_state_ = status;
	std::string err_info;
	ExecSQLProc("{? = call AddConsumerTable(?,?,?,?,?,?)}", err_info); 
	return true;
}