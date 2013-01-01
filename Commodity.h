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
	inline double price();
	inline char* register_date();
	inline int sum();
	bool BindingParameter(); 
	bool InsertInfo(char no[9], char name[256], double price, char register_date[21], int sum);
	
private:
	char m_no_[9];				  /*商品编号*/
	char m_name_[256];			  /*商品名称*/
	double m_price_;			  /*商品单价*/
	char m_register_date_[20];    /*商品登记日期*/
    int m_sum_;          /*商品总数*/
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_name_;
	SQLINTEGER m_sql_price_;
	SQLINTEGER m_sql_register_date_;
	SQLINTEGER m_sql_sum_;

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
	return m_name_;
}

/*
 * 说明: 获取商品单价
 * 返回值: 商品单价
 **/
double CCommodity::price()
{
	return m_price_;
}

/*
 * 说明: 获取商品登记日期
 * 返回值: 商品登记日期字符串
 **/
char* CCommodity::register_date()
{
	return m_register_date_;
}


/*
 * 说明: 获取商品总数
 * 返回值: 商品总数
 **/
int CCommodity::sum()
{
	return m_sum_;
}
#endif 
