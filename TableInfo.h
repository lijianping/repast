#ifndef REPAST_TABLEINFO_H_
#define REPAST_TABLEINFO_H_
#include "DBForm.h"

class CTableInfo : public CDBForm
{
public:
	CTableInfo();
	virtual ~CTableInfo();
	enum TableStatus {
		kFounding = 0,       // 未开台 
		kNotFounding = 1,    // 已开台 
		kBooked = 2          // 已预定 
	};
	inline char* table_no();
	inline short payable_num();
	inline short real_num();
	inline short table_status();
	inline char* datetime();
	bool UpdateForm(std::string sql, std::string &error);
	virtual bool BindingParameter();

	bool GetTableInfoSet(const char *floor_name);
	bool GetTableInfoSet(const char *floor_name, const char *room_name);
	void Initialize();

private:
	char m_table_no_[7];			 // 编号 
	short m_table_status_;			 // 状态 
	short m_payable_num_;			 // 应纳人数 
	SQLINTEGER m_sql_table_no_;    
	SQLINTEGER m_sql_table_status_;
	SQLINTEGER m_sql_payable_num_;

	// 新建,用于取代
	char table_no_[5];             // 台号
	char room_name_[33];              // 房间编号
	char floor_name_[33];             // 楼层编号
	short payable_;                // 台号可容纳人数
	short status_;                 // 台号状态
	SQLINTEGER sql_table_no_;      // 对应台号
	SQLINTEGER sql_room_name_;       // 对应房间编号
	SQLINTEGER sql_floor_name_;      // 对应楼层编号 
	SQLINTEGER sql_payable_;       // 对应台号可容纳人数
	SQLINTEGER sql_status_;        // 对应台号状态
};

/*
 * 说明: 获取台号
 * 返回值: 台号字符串
 **/
char* CTableInfo::table_no()
{
	return m_table_no_;
}

/*
 * 说明: 获取台号状态
 * 返回值: 	0, 已开台 
 *          1, 未开台 
 *          2, 已预定 
 **/
short CTableInfo::table_status()
{
	return m_table_status_;
}

/*
 * 说明: 获取应容人数
 * 返回值: 应容人数
**/
short CTableInfo::payable_num()
{
	return m_payable_num_;
}


#endif 
