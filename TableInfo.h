#ifndef REPAST_TABLEINFO_H_
#define REPAST_TABLEINFO_H_
#include "DBForm.h"

static const char *TableStatus[] = {
	"未开台",
	"已开台",
	"已预定"
};

struct TABLEINFO
{
	std::string new_floor_name;
	std::string new_room_name;
	std::string new_table_no;
	std::string new_table_payable;
	std::string old_floor_name;
	std::string old_room_name;
	std::string old_table_no;
};

class CTableInfo : public CDBForm
{
public:
	CTableInfo();
	virtual ~CTableInfo();
	
	bool UpdateForm(std::string sql, std::string &error);
	bool GetTableInfoSet(const char *floor_name);
	bool GetTableInfoSet(const char *floor_name, const char *room_name);
	bool GetStartTableSet(const char *floor_name, short status);
	bool AddTable(const char *floor_name, const char *room_name,
		          const char *table_no, short payable);
	bool DeleteTable(const char *floor_name, const char *room_name, const char *table_no);
	bool CheckTable(const TABLEINFO *table_info);
	void SetTable(const TABLEINFO *table_info);
	bool UpdateTable(const TABLEINFO *table_info);

	inline char* table_no();
	inline short status();
	inline short payable();
	inline char* room_name();

protected:
	void Initialize();
	virtual bool BindingParameter();

private:
	char table_no_[5];             // 台号
	char room_name_[33];              // 房间编号
	char floor_name_[33];             // 楼层编号
	short payable_;                // 台号可容纳人数
	short status_;                 // 台号状态
    char old_table_no_[5];
	char old_room_name_[33];
	char old_floor_name_[33];
	SQLINTEGER sql_table_no_;      // 对应台号
	SQLINTEGER sql_room_name_;       // 对应房间编号
	SQLINTEGER sql_floor_name_;      // 对应楼层编号 
	SQLINTEGER sql_payable_;       // 对应台号可容纳人数
	SQLINTEGER sql_status_;        // 对应台号状态
	SQLINTEGER sql_old_floor_name_;
	SQLINTEGER sql_old_room_name_;
	SQLINTEGER sql_old_table_no_;
};

/*
 * @ brief: 获取台号
 * @ return: 台号字符串指针
 **/
char* CTableInfo::table_no() {
	DeleteSpace(table_no_, table_no_);
	return table_no_;
}

/*
 * @ brief: 获取台号状态
 * @ return: 台号的状态信息 0 -- 未开台 1 -- 开台 2 -- 预订
 **/
short CTableInfo::status() {
	return status_;
}

/*
 * @ brief: 获取台号可容纳的人数
 * @ return: 可容纳的人数
 **/
short CTableInfo::payable() {
	return payable_;
}

/*
 * @ brief: 获取房间名称
 * @ return: 房间名称字符指针
 **/
char* CTableInfo::room_name() {
	DeleteSpace(room_name_, room_name_);
	return room_name_;
}
#endif 
