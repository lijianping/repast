#ifndef REPAST_CCUSTOMERMENUFORM_H_
#define REPAST_CCUSTOMERMENUFORM_H_

#include "DBForm.h"

class CCustomerMenuForm : public CDBForm  
{
public:
	CCustomerMenuForm();
	virtual ~CCustomerMenuForm();
	inline char* dish_name();
	inline float dish_price() const;
	inline int dish_quantity() const;
	void GetCustomerMenuSet(const char *customer_no);
	bool DeleteDish(const char *customer_no, const char *dish_name);
	bool DeleteAll(const char *customer_no);

protected:
	virtual bool BindingParameter();

private:
	char m_customer_no_[16];
	char m_dish_no_[4];
	char m_dish_name_[20];
	float m_dish_price_;
	int m_dish_quantity_;
	SQLINTEGER m_customer_no_len_;
	SQLINTEGER m_dish_no_len_;
	SQLINTEGER m_dish_name_len_;
	SQLINTEGER m_dish_price_len_;
	SQLINTEGER m_dish_quantity_len_;
};

/*
 * @ ˵��: ��ȡ����
 * @ ����ֵ:
 *           ����
 **/
char* CCustomerMenuForm::dish_name() {
	return m_dish_name_;
}

/*
 * @ ˵��: ��ȡ����
 * @ ����ֵ:
 *           ����--ÿ���˵ĵ���
 **/
float CCustomerMenuForm::dish_price() const {
	return m_dish_price_;
}

/*
 * @ ˵��: ��ȡ����
 * @ ����ֵ:
 *           ����--�û�����б��еĲ˵ķ���(������)
 **/
int CCustomerMenuForm::dish_quantity() const {
	return m_dish_quantity_;
}

#endif 
