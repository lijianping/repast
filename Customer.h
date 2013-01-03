// Customer.h: interface for the CCustomer class.
//
//////////////////////////////////////////////////////////////////////
#ifndef REPAST_CUSTOMER_H_
#define REPAST_CUSTOMER_H_

#include "DBForm.h"

class CCustomer : public CDBForm  
{
public:
	CCustomer();
	virtual ~CCustomer();
	virtual bool BindingParameter();
	inline char* customer_no();
	inline short customer_num() const;
	inline char* founding_time();
	inline char* table_no();
	inline short table_state() const;

private:
	char m_customer_no_[15];        /* �˿ͱ�� */
	short m_customer_num_;          /* �˿����� */
	char m_founding_time_[20];      /* ��̨/Ԥ��ʱ�� */
	short m_table_state_;           /* ̨��״̬ */
	char m_table_no_[6];            /* ̨�� */
	SQLINTEGER m_length_;
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

#endif 
