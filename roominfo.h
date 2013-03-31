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
	char room_no_[3];      // ������
	char floor_name_[17];  // ¥������
	char room_name_[33];   // ��������
	char old_room_no_[3];  // ԭ������
	SQLINTEGER sql_room_no_;    // ��Ӧ������
	SQLINTEGER sql_floor_name_; // ��Ӧ¥������
	SQLINTEGER sql_room_name_;  // ��Ӧ��������
	SQLINTEGER sql_old_room_no_;// ��Ӧԭ������
};

/*
 * @ brief: ��ȡ��������
 * @ return: ָ�򷿼����Ƶ��ַ�ָ��
 **/
char* RoomInfo::room_name() {
	DeleteSpace(room_name_, room_name_);
	return room_name_;
}

/*
 * @ brief: ��ȡ������
 * @ return: �������ַ���ָ��
 **/
char* RoomInfo::room_no() {
	DeleteSpace(room_no_, room_no_);
	return room_no_;
}
#endif