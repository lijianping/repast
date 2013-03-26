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
	char room_no_[3];      // ������
	char floor_name_[33];  // ¥������
	char room_name_[33];   // ��������
	SQLINTEGER sql_room_no_;    // ��Ӧ������
	SQLINTEGER sql_floor_name_; // ��Ӧ¥������
	SQLINTEGER sql_room_name_;  // ��Ӧ��������
};

/*
 * @ brief: ��ȡ��������
 * @ return: ָ�򷿼����Ƶ��ַ�ָ��
 **/
char* RoomInfo::room_name() {
	DeleteSpace(room_name_, room_name_);
	return room_name_;
}
#endif