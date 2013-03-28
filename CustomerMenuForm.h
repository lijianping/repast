#ifndef REPAST_CCUSTOMERMENUFORM_H_
#define REPAST_CCUSTOMERMENUFORM_H_

#include "DBForm.h"

class CCustomerMenuForm : public CDBForm  
{
public:
	CCustomerMenuForm();
	virtual ~CCustomerMenuForm();
	inline char* commodity_name();
	inline short quantity() const;
	inline float commodity_price() const;
	
	bool GetCustomerMenuSet(const char *customer_no);
	bool DeleteCustomerMenu(const char *customer_no);
	bool AddCustomerMenu(const char *customer_no, 
		                 const char *commodity_name,
						 int quantity);

protected:
	void Initialize();
	virtual bool BindingParameter();

private:
	char m_dish_no_[4];
	SQLINTEGER m_dish_no_len_;

	char customer_no_[16];          // �˿ͱ��
	char commodity_name_[64];       // ��Ʒ����
	short quantity_;                // ��Ʒ����
	float commodity_price_;         // ��Ʒ����
	SQLINTEGER sql_customer_no_;    // ��Ӧ�˿ͱ��
	SQLINTEGER sql_commodity_name_; // ��Ӧ��Ʒ����
	SQLINTEGER sql_quantity_;       // ��Ӧ��Ʒ����
	SQLINTEGER sql_commodity_price_;// ��Ӧ��Ʒ����
};

/*
 * @ brief: ��ȡ����
 * @ return: ����
 **/
char* CCustomerMenuForm::commodity_name() {
	DeleteSpace(commodity_name_, commodity_name_);
	return commodity_name_;
}

/*
 * @ brief: ��ȡ����
 * @ return: ����--�û�����б��еĲ˵ķ���(������)
 **/
short CCustomerMenuForm::quantity() const {
	return quantity_;
}

/*
 * @ brief: ��ȡ����
 * @ return: ����--ÿ���˵ĵ���
 **/
float CCustomerMenuForm::commodity_price() const {
	return commodity_price_;
}



#endif 
