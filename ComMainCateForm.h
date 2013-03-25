// ComMainCateForm.h: interface for the CComMainCateForm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMAINCATEFORM_H__6D9BE542_105F_4C36_A967_C0B39FCCC376__INCLUDED_)
#define AFX_COMMAINCATEFORM_H__6D9BE542_105F_4C36_A967_C0B39FCCC376__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBForm.h"

class CComMainCateForm  :public CDBForm
{
public:
	CComMainCateForm();
	virtual ~CComMainCateForm();
	inline short no();
	inline char* name();
	virtual bool BindingParameter();//������Ʒ����������ֶ�
	bool GetMainCategoryName(std::string &error);//��ȡ����Ʒ��������
	virtual bool BindingParameter(bool is_add, std::string &error_info);
    bool InsertCategory(std::string id, std::string name,std::string &error);
    bool UpdateCategory(std::string old_id, std::string id, std::string name,std::string &error);
	bool DeleteCategory(std::string id,std::string &error);
	bool CheckCategory(std::string id, std::string name, std::string &error);
private: 
	short m_no_;             //����Ʒ������
	short m_old_no_;         //ԭ��������Ʒ�����ţ������޸�����Ʒ������Ϣ
	char m_name_[33];        //����Ʒ��������

	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_old_no_;
	SQLINTEGER m_sql_name_;

};


short CComMainCateForm:: no()
{
	return m_no_;
}
char* CComMainCateForm:: name()
{
	return m_name_;
}

#endif // !defined(AFX_COMMAINCATEFORM_H__6D9BE542_105F_4C36_A967_C0B39FCCC376__INCLUDED_)
