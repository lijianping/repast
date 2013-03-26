// TableInfo.cpp: implementation of the CTableInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "TableInfo.h"
#include "Err.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTableInfo::CTableInfo()
{
//	m_query_sql_ = "select * from TableInfo";
	m_query_sql_ = "execute selecttable";
}

CTableInfo::~CTableInfo()
{

}

/*
 *  说明: 更新台号信息表
 *  参数:
 *        sql [in] 更新的sql语句
 *        error [out] 出错时的错误信息
 *  返回值: 若成功返回true，否则返回false
 */
bool CTableInfo::UpdateForm(std::string sql, std::string &error)
{
	return this->ExecuteSQL(sql.c_str(), error);
}

bool CTableInfo::BindingParameter()
{
	/* 绑定列 */
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR,   m_table_no_,      sizeof(m_table_no_),    &m_sql_table_no_);	
	SQLBindCol(m_hstmt_, 2, SQL_C_SSHORT, &m_table_status_, sizeof(m_table_status_),&m_sql_table_status_);
	SQLBindCol(m_hstmt_, 3, SQL_C_SSHORT, &m_payable_num_,  sizeof(m_payable_num_), &m_sql_payable_num_);
	return true;
}

/*
 * @ brief: 获取台号相关信息
 * @ param: floor_name [in] 台号所处楼层名称
 * @ param: room_name [in] 台号所在房间名称
 * @ return: 成功获取台号信息记录集返回true
 **/
bool CTableInfo::GetTableInfoSet(const char *floor_name) {
	this->Initialize();
	BindReturn();
	// 绑定输入参数
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	// 参数赋值
	strcpy(floor_name_, floor_name);
	std::string err_info;	
	// 执行存储过程
	ExecSQLProc("{? = call GetTableInfoByFloor(?)}", err_info);
	// 记录集绑定
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, table_no_, sizeof(table_no_), &sql_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_SSHORT, &status_, 0, &sql_status_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	m_return_code_ = SQLBindCol(m_hstmt_, 3, SQL_C_SSHORT, &payable_, 0, &sql_payable_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	return true;
}

bool CTableInfo::GetTableInfoSet(const char *floor_name, const char *room_name) {
	this->Initialize();
	BindReturn();
	// 绑定输入参数
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR,\
		sizeof(floor_name_) - 1, 0, floor_name_,\
		sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR,\
	                              	  sizeof(room_name_) - 1, 0, room_name_,\
		                              sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		// 参数赋值
	strcpy(floor_name_, floor_name);
	strcpy(room_name_, room_name);
	std::string err_info;	
	// 执行存储过程
	ExecSQLProc("{? = call GetTableInfoByFloorRoom(?,?)}", err_info);
	// 记录集绑定
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, table_no_, sizeof(table_no_), &sql_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_SSHORT, &status_, 0, &sql_status_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	m_return_code_ = SQLBindCol(m_hstmt_, 3, SQL_C_SSHORT, &payable_, 0, &sql_payable_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	return true;
}

/*
 * @ brief: 初始化相关数据
 **/
void CTableInfo::Initialize() {
	this->sql_table_no_ = SQL_NTS;
	this->sql_floor_name_ = SQL_NTS;
	this->sql_room_name_ = SQL_NTS;
	this->sql_payable_ = SQL_NTS;
	this->sql_status_ = SQL_NTS;
	memset(table_no_, 0, sizeof(table_no_));
	memset(floor_name_, 0, sizeof(floor_name_));
	memset(room_name_, 0, sizeof(room_name_));
}