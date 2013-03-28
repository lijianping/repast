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

	char customer_no_[16];          // 顾客编号
	char commodity_name_[64];       // 商品名称
	short quantity_;                // 商品数量
	float commodity_price_;         // 商品单价
	SQLINTEGER sql_customer_no_;    // 对应顾客编号
	SQLINTEGER sql_commodity_name_; // 对应商品名称
	SQLINTEGER sql_quantity_;       // 对应商品数量
	SQLINTEGER sql_commodity_price_;// 对应商品单价
};

/*
 * @ brief: 获取菜名
 * @ return: 菜名
 **/
char* CCustomerMenuForm::commodity_name() {
	DeleteSpace(commodity_name_, commodity_name_);
	return commodity_name_;
}

/*
 * @ brief: 获取数量
 * @ return: 数量--用户点菜列表中的菜的份数(单个菜)
 **/
short CCustomerMenuForm::quantity() const {
	return quantity_;
}

/*
 * @ brief: 获取单价
 * @ return: 单价--每个菜的单价
 **/
float CCustomerMenuForm::commodity_price() const {
	return commodity_price_;
}



#endif 
