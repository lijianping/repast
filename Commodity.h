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
	char m_no_[9];				  /*��Ʒ���*/
	char m_name_[256];			  /*��Ʒ����*/
	double m_price_;			  /*��Ʒ����*/
	char m_register_date_[20];    /*��Ʒ�Ǽ�����*/
    int m_sum_;          /*��Ʒ����*/
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_name_;
	SQLINTEGER m_sql_price_;
	SQLINTEGER m_sql_register_date_;
	SQLINTEGER m_sql_sum_;

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
	return m_name_;
}

/*
 * ˵��: ��ȡ��Ʒ����
 * ����ֵ: ��Ʒ����
 **/
double CCommodity::price()
{
	return m_price_;
}

/*
 * ˵��: ��ȡ��Ʒ�Ǽ�����
 * ����ֵ: ��Ʒ�Ǽ������ַ���
 **/
char* CCommodity::register_date()
{
	return m_register_date_;
}


/*
 * ˵��: ��ȡ��Ʒ����
 * ����ֵ: ��Ʒ����
 **/
int CCommodity::sum()
{
	return m_sum_;
}
#endif 