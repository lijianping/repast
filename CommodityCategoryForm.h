// CommodityCategoryForm.h: interface for the CCommodityCategoryForm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMODITYCATEGORYFORM_H__8DA5006F_F846_43FC_9B86_FB9C968A92B8__INCLUDED_)
#define AFX_COMMODITYCATEGORYFORM_H__8DA5006F_F846_43FC_9B86_FB9C968A92B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBForm.h"

class CCommodityCategoryForm  : public CDBForm
{
public:
	CCommodityCategoryForm();
	virtual ~CCommodityCategoryForm();
	bool BindingParameter();
	inline int no();
	inline char* name();
private:
	int m_no_;        /*商品分类编号*/
	char m_name_[33]; /*商品分类名称*/
	
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_name_;

};


/*
 * 说明：
 *      获取商品分类的ID
 * 返回值：
 *      返回商品分类的ID号
 **/
int CCommodityCategoryForm:: no()
{
	return m_no_;
}

/*
 * 说明：
 *      获取商品分类的名称
 * 返回值：
 *      返回商品分类的名称的字符串
 **/
char* CCommodityCategoryForm:: name()
{
	DeleteSpace(m_name_, m_name_);
	return m_name_;
}

#endif // !defined(AFX_COMMODITYCATEGORYFORM_H__8DA5006F_F846_43FC_9B86_FB9C968A92B8__INCLUDED_)
