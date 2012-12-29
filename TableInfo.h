#ifndef REPAST_TABLEINFO_H_
#define REPAST_TABLEINFO_H_
#include "DBForm.h"

class CTableInfo : public CDBForm
{
public:
	CTableInfo();
	virtual ~CTableInfo();
	enum TableStatu {
		kFounding = 0,       /* 已开台 */
		kNotFounding = 1,    /* 未开台 */
		kBooked = 2          /* 已预定 */
	};
	 inline char* table_no();
	 inline short payable_num();
	 inline short real_num();
	 inline short table_status();
	virtual bool BindingParameter();
private:
	char m_table_no_[7];     /* 编号 */
	short m_payable_num_;    /* 应纳人数 */
	short m_real_num_;       /* 实纳人数 */
	short m_table_status_;   /* 状态 */
    SQLINTEGER m_sql_table_no_;
	SQLINTEGER m_sql_payable_num_;
	SQLINTEGER m_sql_real_num_;
	SQLINTEGER m_sql_table_status_;
};

/*
 * 说明: 获取台号
 * 返回值: 台号字符串
 **/
char* CTableInfo:: table_no()
{
	return m_table_no_;
}

/*
 * 说明: 获取应容人数
 * 返回值: 应容人数
 **/
short CTableInfo::payable_num()
{
	return m_payable_num_;
}

/*
 * 说明: 获取实容人数
 * 返回值: 实容人数
 **/
short CTableInfo:: real_num()
{
	return m_real_num_;
}

/*
 * 说明: 获取台号状态
 * 返回值: 	0, 已开台 
 *          1, 未开台 
 *          2, 已预定 
 **/
short CTableInfo:: table_status()
{
	return m_table_status_;
}

#endif 
