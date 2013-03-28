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
	inline char* table_no();
	inline short table_state() const;
	inline short payablenum() const;
	bool GetCustomerByName(const char *customer_no, const char* table_no, std::string &error);
	bool AddCustomer(const char *customer_no);
	void Initialize();
	bool AddCustomerTable(const char *customer_no, const char *floor_name,
		                  const char *room_name, const char *table_no, int real_num, int status);

protected:
	virtual bool BindingParameter();

private:
	char m_customer_no_[16];        /* �˿ͱ�� */
	short m_customer_num_;          /* �˿����� */
	char m_founding_time_[20];      /* ��̨/Ԥ��ʱ�� */
	char m_end_time_[20];           /*����ʱ��*/
	float m_money_;                 /*���ѽ��*/
	char m_clerk_[21];              /*ӪҵԱ*/
	short m_payablenum_;            /*Ӧ������*/
	
	char m_table_no_[7];            /* ̨�� */
	short m_table_state_;           /* ̨��״̬ */

	char m_floor_name_[33];          // ¥������
	char m_room_name_[33];           // ��������

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
};

char* CCustomer::customer_no() 
{
	return m_customer_no_;
}

short CCustomer::customer_num() const
{
	return m_customer_num_;
}

char* CCustomer::founding_time() 
{
	return m_founding_time_;
}

char* CCustomer::table_no()
{
	return m_table_no_;
}

short CCustomer::table_state() const
{
	return m_table_state_;
}
inline short CCustomer:: payablenum() const
{
	return m_payablenum_;
}
#endif 





















