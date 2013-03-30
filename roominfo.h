#ifndef REPAST_ROOMINFO_H_
#define REPAST_ROOMINFO_H_

#include "Err.h"
#include "dbform.h"
class RoomInfo :
	public CDBForm
{
public:
	RoomInfo(void);
	~RoomInfo(void);
	void Initialize();
	bool GetRoomName(const char *floor_name);
	bool GetRoomInfo(const char *floor_name);
	bool AddRoom(const char *floor_name, const char *room_no, const char *room_name);
	bool DeleteRoom(const char *floor_name, const char *room_no);
	bool ModifyRoom(const char *floor_name, const char *old_room_no,
		            const char *new_room_no, const char *new_room_name);
	inline char* room_name();
	inline char* room_no();

private:
	char room_no_[3];      // 房间编号
	char floor_name_[17];  // 楼层名称
	char room_name_[33];   // 房间名称
	char old_room_no_[3];  // 原房间编号
	SQLINTEGER sql_room_no_;    // 对应房间编号
	SQLINTEGER sql_floor_name_; // 对应楼层名称
	SQLINTEGER sql_room_name_;  // 对应房间名称
	SQLINTEGER sql_old_room_no_;// 对应原房间编号
};

/*
 * @ brief: 获取房间名称
 * @ return: 指向房间名称的字符指针
 **/
char* RoomInfo::room_name() {
	DeleteSpace(room_name_, room_name_);
	return room_name_;
}

/*
 * @ brief: 获取房间编号
 * @ return: 房间编号字符串指针
 **/
char* RoomInfo::room_no() {
	DeleteSpace(room_no_, room_no_);
	return room_no_;
}
#endif