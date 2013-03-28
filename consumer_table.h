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
	char consumer_no_[17];             // �˿ͱ��
	char table_no_[5];                 // ̨��
	char room_name_[33];               // ��������
	short table_status_;               // ̨��״̬
	short consumer_num_;               // �˿�����
	char start_time_[33];              // ��̨ʱ��
	char floor_name_[17];              // ¥������
	SQLINTEGER sql_consumer_no_;
	SQLINTEGER sql_table_no_;
	SQLINTEGER sql_room_name_;
	SQLINTEGER sql_table_status_;
	SQLINTEGER sql_consumer_num_;
	SQLINTEGER sql_start_time_;
	SQLINTEGER sql_floor_name_;
};

/*
 * @ brief: ��ȡ�˿ͱ��
 * @ return: �˿ͱ���ַ�ָ��
 **/
char* ConsumerTable::consumer_no() {
	DeleteSpace(consumer_no_, consumer_no_);
	return consumer_no_;
}

/*
 * @ brief: ��ȡ̨��
 * @ return: ̨���ַ�ָ��
 **/
char* ConsumerTable::table_no() {
	DeleteSpace(table_no_, table_no_);
	return table_no_;
}

/*
 * @ brief: ��ȡ������
 * @ return: ���������ַ�ָ��
 **/
char* ConsumerTable::room_name() {
	DeleteSpace(room_name_, room_name_);
	return room_name_;
}

/*
 * @ brief: ��ȡ̨��״̬
 * @ return: ̨��״̬��־
 **/
short ConsumerTable::table_status() const {
	return table_status_;
}

/*
 * @ brief: ��ȡ�˿�����
 * @ return: �˿�����
 **/
short ConsumerTable::consumer_num() const {
	return consumer_num_;
}

/*
 * @ brief: ��ȡ��̨ʱ��
 * @ return: ��̨ʱ���ַ�ָ��
 **/
char* ConsumerTable::start_time() {
	return start_time_;
}

#endif