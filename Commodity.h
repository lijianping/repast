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
	inline double price();///TODO: ������ʹ����/////
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
	char m_no_[9];				  /*��Ʒ���*/
	char m_name_[257];			  /*��Ʒ����*/
	double m_price_;			  /*��Ʒ����*///TODO: ������ʹ����/////
	double m_purchase_price_;     /*��Ʒ����*/ 
	int m_sum_;                   /*��Ʒ����*/
	char m_category_[33];         /*��Ʒ���*/
	char m_unit_[9];              /*��Ʒ��λ*/
	double m_sale_price_;         /*��Ʒ����*/
	char m_register_date_[20];    /*��Ʒ�Ǽ�����*/
   
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_name_;
	SQLINTEGER m_sql_price_;/////TODO: ������ʹ����//////////
	SQLINTEGER m_sql_purchase_price_;
	SQLINTEGER m_sql_sum_;
	SQLINTEGER m_sql_category_;
	SQLINTEGER m_sql_unit_;
	SQLINTEGER m_sql_sale_price_;
	SQLINTEGER m_sql_register_date_;

};


/*
 * ˵��: ��ȡ��Ʒ���
 * ����ֵ: ��Ʒ����ַ���
 **/
char* CCommodity::no()
{
	return m_no_;
}

/*
 * ˵��: ��ȡ��Ʒ����
 * ����ֵ: ��Ʒ�����ַ���
 **/
char* CCommodity::name()
{
	DeleteSpace(m_name_, m_name_);
	return m_name_;
}

/*
 * ˵��: ��ȡ��Ʒ����
 * ����ֵ: ��Ʒ����
 **/
double CCommodity::price()/*TODO:������ʹ����*/
{
	return m_price_;
}



/*
 * ˵��: ��ȡ��Ʒ����
 * ����ֵ: ��Ʒ����
 **/
double CCommodity:: purchase_price()
{
	return m_purchase_price_;
}
/*
 * ˵��: ��ȡ��Ʒ����
 * ����ֵ: ��Ʒ����
 **/
int CCommodity::sum()
{
	return m_sum_;
}

/*
 * ˵��: ��ȡ��Ʒ����
 * ����ֵ: ��Ʒ�����ַ���
 **/
char* CCommodity::category()
{
	DeleteSpace(m_category_, m_category_);
	return m_category_;
}

/*
 * ˵��: ��ȡ��Ʒ�ĵ�λ
 * ����ֵ: ��Ʒ��λ�ַ���
 **/
char* CCommodity:: unit()
{
	DeleteSpace(m_unit_, m_unit_);
	return m_unit_;
}

/*
 * ˵��: ��ȡ��Ʒ����
 * ����ֵ: ��Ʒ����
 **/
double CCommodity::sale_price()
{
	return m_sale_price_;
}


/*
 * ˵��: ��ȡ��Ʒ�Ǽ�����
 * ����ֵ: ��Ʒ�Ǽ������ַ���
 **/
char* CCommodity::register_date()
{
	return m_register_date_;
}
#endif 
