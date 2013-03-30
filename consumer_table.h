#ifndef REPAST_CONSUMER_TABLE_H_
#define REPAST_CONSUMER_TABLE_H_

#include "Err.h"
#include "dbform.h"
class ConsumerTable :
	public CDBForm
{
public:
	ConsumerTable(void);
	~ConsumerTable(void);
	bool GetConsumerTable(const char *floor_name);
	inline char* consumer_no();
	inline char* table_no();
	inline char* room_name();
	inline short table_status() const;
	inline short consumer_num() const;
	inline char* start_time();

protected:
	void Initialize();
	bool BindReturnSet();

private:
	char consumer_no_[17];             // 顾客编号
	char table_no_[5];                 // 台号
	char room_name_[33];               // 房间名称
	short table_status_;               // 台号状态
	short consumer_num_;               // 顾客人数
	char start_time_[20];              // 开台时间
	char floor_name_[17];              // 楼层名称
	SQLINTEGER sql_consumer_no_;
	SQLINTEGER sql_table_no_;
	SQLINTEGER sql_room_name_;
	SQLINTEGER sql_table_status_;
	SQLINTEGER sql_consumer_num_;
	SQLINTEGER sql_start_time_;
	SQLINTEGER sql_floor_name_;
};

/*
 * @ brief: 获取顾客编号
 * @ return: 顾客编号字符指针
 **/
char* ConsumerTable::consumer_no() {
	DeleteSpace(consumer_no_, consumer_no_);
	return consumer_no_;
}

/*
 * @ brief: 获取台号
 * @ return: 台号字符指针
 **/
char* ConsumerTable::table_no() {
	DeleteSpace(table_no_, table_no_);
	return table_no_;
}

/*
 * @ brief: 获取房间名
 * @ return: 房间名称字符指针
 **/
char* ConsumerTable::room_name() {
	DeleteSpace(room_name_, room_name_);
	return room_name_;
}

/*
 * @ brief: 获取台号状态
 * @ return: 台号状态标志
 **/
short ConsumerTable::table_status() const {
	return table_status_;
}

/*
 * @ brief: 获取顾客人数
 * @ return: 顾客人数
 **/
short ConsumerTable::consumer_num() const {
	return consumer_num_;
}

/*
 * @ brief: 获取开台时间
 * @ return: 开台时间字符指针
 **/
char* ConsumerTable::start_time() {
	return start_time_;
}

#endif