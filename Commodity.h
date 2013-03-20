// Commodity.h: interface for the CCommodity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMODITY_H__4B72C41F_AB35_424D_8BBF_B55CF8458A2E__INCLUDED_)
#define AFX_COMMODITY_H__4B72C41F_AB35_424D_8BBF_B55CF8458A2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBForm.h"

class CCommodity: public CDBForm
{
public:
	CCommodity();
	virtual ~CCommodity();
	inline char* no();
	inline char* name();
	inline double price();///TODO: 将不在使用了/////
	inline double purchase_price();
	inline int sum();
	inline char* category();
	inline char* unit();
	inline double sale_price();
	inline char* register_date();
	
	bool BindingParameter(); 
	bool SelectByName(char* name, std::string error);
	bool InsertInfo(char no[9], char name[256], double price, char register_date[21], int sum);
	
private:
	char m_no_[9];				  /*商品编号*/
	char m_name_[257];			  /*商品名称*/
	double m_price_;			  /*商品单价*///TODO: 将不在使用了/////
	double m_purchase_price_;     /*商品进价*/ 
	int m_sum_;                   /*商品总数*/
	char m_category_[33];         /*商品类别*/
	char m_unit_[9];              /*商品单位*/
	double m_sale_price_;         /*商品卖价*/
	char m_register_date_[20];    /*商品登记日期*/
   
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_name_;
	SQLINTEGER m_sql_price_;/////TODO: 将不在使用了//////////
	SQLINTEGER m_sql_purchase_price_;
	SQLINTEGER m_sql_sum_;
	SQLINTEGER m_sql_category_;
	SQLINTEGER m_sql_unit_;
	SQLINTEGER m_sql_sale_price_;
	SQLINTEGER m_sql_register_date_;

};


/*
 * 说明: 获取商品编号
 * 返回值: 商品编号字符串
 **/
char* CCommodity::no()
{
	return m_no_;
}

/*
 * 说明: 获取商品名称
 * 返回值: 商品名称字符串
 **/
char* CCommodity::name()
{
	DeleteSpace(m_name_, m_name_);
	return m_name_;
}

/*
 * 说明: 获取商品单价
 * 返回值: 商品单价
 **/
double CCommodity::price()/*TODO:将不在使用了*/
{
	return m_price_;
}



/*
 * 说明: 获取商品进价
 * 返回值: 商品进价
 **/
double CCommodity:: purchase_price()
{
	return m_purchase_price_;
}
/*
 * 说明: 获取商品总数
 * 返回值: 商品总数
 **/
int CCommodity::sum()
{
	return m_sum_;
}

/*
 * 说明: 获取商品类型
 * 返回值: 商品类型字符串
 **/
char* CCommodity::category()
{
	DeleteSpace(m_category_, m_category_);
	return m_category_;
}

/*
 * 说明: 获取商品的单位
 * 返回值: 商品单位字符串
 **/
char* CCommodity:: unit()
{
	DeleteSpace(m_unit_, m_unit_);
	return m_unit_;
}

/*
 * 说明: 获取商品卖价
 * 返回值: 商品卖价
 **/
double CCommodity::sale_price()
{
	return m_sale_price_;
}


/*
 * 说明: 获取商品登记日期
 * 返回值: 商品登记日期字符串
 **/
char* CCommodity::register_date()
{
	return m_register_date_;
}
#endif 
