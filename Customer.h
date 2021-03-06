// Customer.h: interface for the CCustomer class.
//
//////////////////////////////////////////////////////////////////////
#ifndef REPAST_CUSTOMER_H_
#define REPAST_CUSTOMER_H_

#include "DBForm.h"

class CCustomer : public CDBForm  
{
public:
	bool InsertCustomerMenu(const char *coustmer_no, const char* menu_name, int quantity);
	CCustomer();
	virtual ~CCustomer();
	inline char* customer_no();
	inline short customer_num() const;
	inline char* founding_time();
	inline char* end_time();
	inline char* table_no();
	inline short table_state() const;
	inline short payablenum() const;
	inline float money() const;
	inline char* clerk();
        inline char* commodity_name();
        inline short quantity() const;
	bool GetCustomerByName(const char *customer_no, const char* table_no, std::string &error);
	bool AddCustomer(const char *customer_no);
	
	bool AddCustomerTable(const char *customer_no, const char *floor_name,
		                  const char *room_name, const char *table_no, int real_num, int status);
	bool CheckOut(const char *customer_no, const char *clerk,float totle_cash);
	bool ChangeTable(const char *old_floor_name, const char *old_room_name, const char *old_table_no,
		             const char *new_floor_name, const char *new_room_name, const char *new_table_no,
					 const char *consumer_no, short people_num, short table_state);
	bool GetConsumerRecord(const char *start_time, const char *end_time);
        bool GetConsumerMenuRecord(const char *consumer_no);
        bool GetConsumerRecordBackup(const char *consumer_no);

protected:
	void Initialize();
	virtual bool BindingParameter();

private:
	char m_customer_no_[16];        /* 顾客编号 */
	short m_customer_num_;          /* 顾客人数 */
	char m_founding_time_[20];      /* 开台/预定时间 */
	char m_end_time_[20];           /*结账时间*/
	float m_money_;                 /*消费金额*/
	char m_clerk_[21];              /*营业员*/
	short m_payablenum_;            /*应纳人数*/
	
	char m_table_no_[7];            /* 台号 */
	short m_table_state_;           /* 台号状态 */

	char m_floor_name_[17];          // 楼层名称
	char m_room_name_[33];           // 房间名称
	char m_old_floor_name_[17];      // 原楼层信息
	char m_old_room_name_[33];       // 原房间信息
	char m_old_table_no_[5];         // 原台号信息
	char m_query_start_time_[20];    // 查询开始时间
	char m_query_end_time_[20];      // 查询结束时间
        char m_commodity_name_[257];     // 商品名称
        short m_quantity_;

	SQLINTEGER m_customer_no_len_;
	SQLINTEGER m_customer_num_len_;
	SQLINTEGER m_founding_time_len_;
	SQLINTEGER m_end_time_len_;
	SQLINTEGER m_money_len_;
	SQLINTEGER m_clerk_len_;
	SQLINTEGER m_sql_payablenum_len_;
	
	SQLINTEGER m_table_no_len_;
	SQLINTEGER m_table_state_len_;
	SQLINTEGER m_floor_name_len_;
	SQLINTEGER m_room_name_len_;
	SQLINTEGER m_old_floor_name_len_;
	SQLINTEGER m_old_room_name_len_;
	SQLINTEGER m_old_table_no_len_;
	SQLINTEGER m_query_start_time_len_;
	SQLINTEGER m_query_end_time_len_;
        SQLINTEGER m_commodity_name_len_;
        SQLINTEGER m_quantity_len_;
};

char* CCustomer::customer_no() 
{
	DeleteSpace(m_customer_no_, m_customer_no_);
	return m_customer_no_;
}

short CCustomer::customer_num() const
{
	return m_customer_num_;
}

char* CCustomer::founding_time() 
{
	DeleteSpace(m_founding_time_, m_founding_time_);
	return m_founding_time_;
}

char* CCustomer::end_time() 
{
	DeleteSpace(m_end_time_, m_end_time_);
	return m_end_time_;
}
char* CCustomer::table_no()
{
	DeleteSpace(m_table_no_, m_table_no_);
	return m_table_no_;
}

short CCustomer::table_state() const
{
	return m_table_state_;
}
short CCustomer:: payablenum() const
{
	return m_payablenum_;
}

float CCustomer::money() const 
{
	return m_money_;
}

char* CCustomer::clerk() 
{
	DeleteSpace(m_clerk_, m_clerk_);
	return m_clerk_;
}

/*
 * @ brief: 获取顾客所点商品名称
 * @ return: 商品名称
 **/
char* CCustomer::commodity_name() 
{
    DeleteSpace(m_commodity_name_, m_commodity_name_);
    return m_commodity_name_;
}

/*
 * @ brief: 获取顾客所点商品数量
 * @ return: 商品数量
 **/
short CCustomer::quantity() const
{
    return m_quantity_;
}
#endif 





















