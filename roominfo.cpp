#include "roominfo.h"


RoomInfo::RoomInfo(void)
{
}


RoomInfo::~RoomInfo(void)
{
}

/*
 * @ brief: 初始化数据
 **/
void RoomInfo::Initialize() {
	memset(room_no_, 0, sizeof(room_no_));
	memset(room_name_, 0, sizeof(room_name_));
	memset(floor_name_, 0, sizeof(floor_name_));
	memset(old_room_no_, 0, sizeof(old_room_no_));
	sql_room_name_ = SQL_NTS;
	sql_room_no_ = SQL_NTS;
	sql_floor_name_ = SQL_NTS;
	sql_old_room_no_ = SQL_NTS;
}

bool RoomInfo::GetRoomName(const char *floor_name) {
	Initialize();  // 初始化
	BindReturn();  // 绑定返回值
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
	ExecSQLProc("{? = call GetRoomByFloorName(?)}", err_info);
	// 记录集绑定
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, room_name_, sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	return true;
}

/*
 * @ brief: 根据楼层名称获取房间信息
 * @ param: floor_name [in] 楼层名称
 * @ return: 成功返回true
 **/
bool RoomInfo::GetRoomInfo(const char *floor_name) {
	Initialize();  // 初始化
	BindReturn();  // 绑定返回值
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
	ExecSQLProc("{? = call GetRoomInfoSet(?)}", err_info);
	// 记录集绑定
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, room_no_, sizeof(room_no_), &sql_room_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, room_name_, sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	return true;
}

/*
 * @ brief: 增加房间信息
 * @ param: floor_name [in] 楼层名称
 * @ param: room_no [in] 房间编号
 * @ param: room_name [in] 房间名称
 * @ return: 成功返回true
 **/
bool RoomInfo::AddRoom(const char *floor_name, const char *room_no, const char *room_name) {
	Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
	                          	      sizeof(room_no_) - 1, 0, room_no_,\
		                              sizeof(room_no_), &sql_room_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(room_name_) - 1, 0, room_name_,\
		                              sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(floor_name_, floor_name);
	strcpy(room_no_, room_no);
	strcpy(room_name_, room_name);
	std::string err_info;	
	// 执行存储过程
	ExecSQLProc("{? = call AddRoom(?,?,?)}");
	return IsSQLProcRetRight();
}

/*
 * @ brief: 删除房间信息
 * @ param: floor_name [in] 楼层名称
 * @ param: room_no [in] 房间编号
 * @ return: 成功返回true
 **/
bool RoomInfo::DeleteRoom(const char *floor_name, const char *room_no) {
	Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(room_no_) - 1, 0, room_no_,\
		                              sizeof(room_no_), &sql_room_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(floor_name_, floor_name);
	strcpy(room_no_, room_no);
	ExecSQLProc("{? = call DeleteRoom(?,?)}");
	return IsSQLProcRetRight();
}

/*
 * @ brief: 修改房间信息
 * @ param: floor_name [in] 楼层名称 
 * @ param: old_room_no [in] 修改前的房间编号
 * @ param: new_room_no [in] 修改后的房间编号
 * @ param: new_room_name [in] 修改后的房间名称
 * @ return: 若成功返回true
 **/
bool RoomInfo::ModifyRoom(const char *floor_name, const char *old_room_no, 
	                      const char *new_room_no, const char *new_room_name) {
    Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(old_room_no_) - 1, 0, old_room_no_,\
		                              sizeof(old_room_no_), &sql_old_room_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
    // room_no_代替new_room_no
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(room_no_) - 1, 0, room_no_,\
		                              sizeof(room_no_), &sql_room_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	// room_name_代替new_room_name
	m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                                  sizeof(room_name_) - 1, 0, room_name_,\
		                                  sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(floor_name_, floor_name);
	strcpy(old_room_no_, old_room_no);
	strcpy(room_no_, new_room_no);
	strcpy(room_name_, new_room_name);
	ExecSQLProc("{? = call ModifyRoom(?,?,?,?)}");
	return IsSQLProcRetRight();
}