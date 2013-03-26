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
	inline char* room_name();

private:
	char room_no_[3];      // 房间编号
	char floor_name_[33];  // 楼层名称
	char room_name_[33];   // 房间名称
	SQLINTEGER sql_room_no_;    // 对应房间编号
	SQLINTEGER sql_floor_name_; // 对应楼层名称
	SQLINTEGER sql_room_name_;  // 对应房间名称
};

/*
 * @ brief: 获取房间名称
 * @ return: 指向房间名称的字符指针
 **/
char* RoomInfo::room_name() {
	DeleteSpace(room_name_, room_name_);
	return room_name_;
}
#endif