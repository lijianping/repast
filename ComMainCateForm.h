// ComMainCateForm.h: interface for the CComMainCateForm class.
//
//////////////////////////////////////////////////////////////////////

#ifndef REPAST_COMMAINCATEFORM_H_
#define REPAST_COMMAINCATEFORM_H_

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
	void Initialize(); 
private: 
	short m_no_;             //����Ʒ������
	short m_old_no_;         //ԭ��������Ʒ�����ţ������޸�����Ʒ������Ϣ
	char m_name_[33];        //����Ʒ��������

	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_old_no_;
	SQLINTEGER m_sql_name_;

};


short CComMainCateForm::no()
{
	return m_no_;
}
char* CComMainCateForm::name()
{
	this->DeleteSpace(m_name_, m_name_);
	return m_name_;
}

#endif 