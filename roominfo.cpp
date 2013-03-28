#include "roominfo.h"


RoomInfo::RoomInfo(void)
{
}


RoomInfo::~RoomInfo(void)
{
}

/*
 * @ brief: ��ʼ������
 **/
void RoomInfo::Initialize() {
	memset(room_no_, 0, sizeof(room_no_));
	memset(room_name_, 0, sizeof(room_name_));
	memset(floor_name_, 0, sizeof(floor_name_));
	sql_room_name_ = SQL_NTS;
	sql_room_no_ = SQL_NTS;
	sql_floor_name_ = SQL_NTS;
}

bool RoomInfo::GetRoomName(const char *floor_name) {
	Initialize();  // ��ʼ��
	BindReturn();  // �󶨷���ֵ
	// ���������
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
									  sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	// ������ֵ
	strcpy(floor_name_, floor_name);
	std::string err_info;	
	// ִ�д洢����
	ExecSQLProc("{? = call GetRoomByFloorName(?)}", err_info);
	// ��¼����
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, room_name_, sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	return true;
}