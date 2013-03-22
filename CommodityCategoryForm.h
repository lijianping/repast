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
	virtual bool BindingParameter();
   virtual bool BindingParameter(bool is_add, std::string &error_info);
    bool InsertCategory(std::string id, std::string name,std::string &error);
    bool UpdateCategory(std::string old_id, std::string id, std::string name,std::string &error);
	bool DeleteCategory(std::string id,std::string &error);
	inline int no();
	inline char* name();
	bool CheckCategory(std::string id, std::string name, std::string &error);
private:
	int m_no_;        /*��Ʒ������*/
	char m_name_[33]; /*��Ʒ��������*/
	int m_old_no_;    /*��Ʒ����ľɱ��*/
	
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_name_;
	SQLINTEGER m_sql_old_no;

};


/*
 * ˵����
 *      ��ȡ��Ʒ�����ID
 * ����ֵ��
 *      ������Ʒ�����ID��
 **/
int CCommodityCategoryForm:: no()
{
	return m_no_;
}

/*
 * ˵����
 *      ��ȡ��Ʒ���������
 * ����ֵ��
 *      ������Ʒ��������Ƶ��ַ���
 **/
char* CCommodityCategoryForm:: name()
{
	DeleteSpace(m_name_, m_name_);
	return m_name_;
}

#endif // !defined(AFX_COMMODITYCATEGORYFORM_H__8DA5006F_F846_43FC_9B86_FB9C968A92B8__INCLUDED_)
