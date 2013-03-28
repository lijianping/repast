#include "consumer_table.h"


ConsumerTable::ConsumerTable(void)
{
}


ConsumerTable::~ConsumerTable(void)
{
}

/*
 * @ brief: 根据楼层获取顾客台号相关信息，开台管理
 * @ param: floor_name [in] 楼层名称
 * @ return: 成功返回true
 **/
bool ConsumerTable::GetConsumerTable(const char *floor_name) {
	Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	// 参数赋值
	strcpy(floor_name_, floor_name);
	std::string err_info;	
	// 执行存储过程
	ExecSQLProc("{? = call GetConsumerTableInfo(?)}", err_info);
	BindReturnSet();
	return true;
}

/*
 * @ brief: 初始化相关数据
 **/
void ConsumerTable::Initialize() {
	memset(consumer_no_, 0, sizeof(consumer_no_));
	memset(table_no_, 0, sizeof(table_no_));
	memset(room_name_, 0, sizeof(room_name_));
	table_status_ = -1;
	consumer_num_ = 0;
	memset(start_time_, 0, sizeof(start_time_));
	memset(floor_name_, 0, sizeof(floor_name_));
	sql_consumer_no_ = SQL_NTS;
	sql_table_no_ = SQL_NTS;
	sql_room_name_ = SQL_NTS;
	sql_table_status_ = SQL_NTS;
	sql_consumer_num_ = SQL_NTS;
	sql_start_time_ = SQL_NTS;
	sql_floor_name_ = SQL_NTS;
}

/*
 * @ brief: 绑定返回记录集
 * @ return: 成功返回true
 **/
bool ConsumerTable::BindReturnSet() {
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, consumer_no_, sizeof(consumer_no_), &sql_consumer_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, table_no_, sizeof(table_no_), &sql_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	m_return_code_ = SQLBindCol(m_hstmt_, 3, SQL_C_CHAR, room_name_, sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	m_return_code_ = SQLBindCol(m_hstmt_, 4, SQL_C_SSHORT, &table_status_, 0, &sql_table_status_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	m_return_code_ = SQLBindCol(m_hstmt_, 5, SQL_C_SSHORT, &consumer_num_, 0, &sql_consumer_num_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	m_return_code_ = SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, start_time_, sizeof(start_time_), &sql_start_time_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	return true;
}