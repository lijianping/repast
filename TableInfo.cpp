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
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
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
	BindingParameter();
	return true;
}

bool CTableInfo::GetTableInfoSet(const char *floor_name, const char *room_name) {
	this->Initialize();
	BindReturn();
	// 绑定输入参数
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		sizeof(floor_name_) - 1, 0, floor_name_,\
		sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
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
    BindingParameter();
	return true;
}

/*
 * @ brief: 根据楼层名获取指定状态的房间台号
 * @ param: floor_name [in] 楼层名称
 * @ param: status [in] 状态
 * @ return: 若成功返回true,可获取台号,房间名及可容纳人数
 **/
bool CTableInfo::GetStartTableSet(const char *floor_name, short status) {
	Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT,\
	                                  0, 0, &status_, 0, &sql_status_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(floor_name_, floor_name);
	status_ = status;
	std::string err_info;
	ExecSQLProc("{? = call GetStartTableInfo(?,?)}", err_info);
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, table_no_, sizeof(table_no_), &sql_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, room_name_, sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	m_return_code_ = SQLBindCol(m_hstmt_, 3, SQL_C_SSHORT, &payable_, 0, &sql_payable_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	return true;
}

/*
 * @ brief: 添加台号信息
 * @ param: floor_name [in] 楼层名称
 * @ param: room_name [in] 房间名称
 * @ param: table_no [in] 台号
 * @ param: payable [in] 台号可容纳人数
 * @ return: 若成功返回true
 **/
bool CTableInfo::AddTable(const char *floor_name, const char *room_name, 
	                      const char *table_no, short payable) {
    Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(room_name_) - 1, 0, room_name_,\
		                              sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(table_no_) - 1, 0, table_no_,\
		                              sizeof(table_no_), &sql_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT,\
		                              0, 0, &payable_, 0, &sql_payable_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	strcpy(floor_name_, floor_name);
	strcpy(room_name_, room_name);
	strcpy(table_no_, table_no);
	payable_ = payable;
	ExecSQLProc("{? = call AddTable(?,?,?,?)}");
	return IsSQLProcRetRight();
}

/*
 * @ brief: 删除台号信息
 * @ param: floor_name [in] 楼层名称
 * @ param: room_name [in] 房间名称
 * @ param: table_no [in] 台号
 * @ return: 若成功返回true
 **/
bool CTableInfo::DeleteTable(const char *floor_name, const char *room_name, const char *table_no) {
	Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
	                                  sizeof(room_name_) - 1, 0, room_name_,\
		                              sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(table_no_) - 1, 0, table_no_,\
		                              sizeof(table_no_), &sql_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(floor_name_, floor_name);
	strcpy(room_name_, room_name);
	strcpy(table_no_, table_no);
	ExecSQLProc("{? = call DeleteTable(?,?,?)}");
	return IsSQLProcRetRight();
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
	this->sql_old_floor_name_ = SQL_NTS;
	this->sql_old_room_name_ = SQL_NTS;
	this->sql_old_table_no_ = SQL_NTS;
	memset(table_no_, 0, sizeof(table_no_));
	memset(floor_name_, 0, sizeof(floor_name_));
	memset(room_name_, 0, sizeof(room_name_));
	memset(old_floor_name_, 0, sizeof(old_floor_name_));
	memset(old_room_name_, 0, sizeof(old_room_name_));
	memset(old_table_no_, 0, sizeof(old_table_no_));
}

/*
 * @ brief: 绑定记录集
 * @ return: 成功返回true
 **/
bool CTableInfo::BindingParameter()
{
	// 绑定记录集
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
 * 说明：
 *    检查台号信息是否正确，主要是检查其字段的长度是否满足要求
 * 参数：
 *    table_info [in] 台号信息
 * 返回值：
 *     成功返回true
 */
bool CTableInfo::CheckTable(const TABLEINFO *table_info)
{
	if (table_info->new_floor_name.length()==0||
		table_info->new_room_name.length()==0||
		table_info->new_table_no.length()==0||
		table_info->new_table_payable.length()==0)
	{
		LTHROW(INPUT_NULL_ERROR)
	}
	if (table_info->new_floor_name.length()>(sizeof(floor_name_)-1)||
		table_info->new_room_name.length()>(sizeof(room_name_)-1)||
		table_info->new_table_no.length()>(sizeof(table_no_)-1)||
		table_info->new_table_payable.length()>(sizeof(payable_)))
	{
		LTHROW(INPUT_TOO_LONG_ERROR)
	}
	return true;
}

/*
 * 说明：
 *    台号信息赋值
 * 参数：
 *    table_info [in] 台号信息
 * 返回值：
 *     无
 */
void CTableInfo::SetTable(const TABLEINFO *table_info)
{
	strcpy(floor_name_,table_info->new_floor_name.c_str());
	strcpy(room_name_,table_info->new_room_name.c_str());
	strcpy(table_no_,table_info->new_table_no.c_str());
	payable_=atoi(table_info->new_table_payable.c_str());
	strcpy(old_floor_name_,table_info->old_floor_name.c_str());
	strcpy(old_room_name_,table_info->old_room_name.c_str());
	strcpy(old_table_no_,table_info->old_table_no.c_str());
}

/*
 * 说明：
 *    更新台号信息
 * 参数：
 *    table_info [in] 台号信息
 * 返回值：
 *     成功返回true
 */
bool CTableInfo::UpdateTable(const TABLEINFO *table_info)
{
	Initialize();
	CheckTable(table_info);
	BindReturn();
	    m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
											sizeof(floor_name_) - 1, 0, floor_name_,\
											sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
											sizeof(room_name_) - 1, 0, room_name_,\
											sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
											sizeof(table_no_) - 1, 0, table_no_,\
											sizeof(table_no_), &sql_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT,\
		0, 0, &payable_, 0, &sql_payable_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
		m_return_code_ = SQLBindParameter(m_hstmt_, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
											sizeof(old_floor_name_) - 1, 0, old_floor_name_,\
											sizeof(old_floor_name_), &sql_old_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		m_return_code_ = SQLBindParameter(m_hstmt_, 7, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
											sizeof(old_room_name_) - 1, 0, old_room_name_,\
											sizeof(old_room_name_), &sql_old_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		m_return_code_ = SQLBindParameter(m_hstmt_, 8, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
											sizeof(old_table_no_) - 1, 0, old_table_no_,\
											sizeof(old_table_no_), &sql_old_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	SetTable(table_info);
	ExecSQLProc("{?=call UpdateTable(?,?,?,?,?,?,?)}");
	IsSQLProcRetRight();
	return true;
}