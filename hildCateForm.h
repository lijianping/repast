// hildCateForm.h: interface for the ChildCateForm class.
//
//////////////////////////////////////////////////////////////////////

#ifndef REPAST_CHILDCATEFORM_H_
#define REPAST_CHILDCATEFORM_H_

#include "DBForm.h"

// ��Ʒ����ӷ���
class ChildCateForm : public CDBForm  
{
public:
	ChildCateForm();
	virtual ~ChildCateForm();
	void Initialize();
	bool GetChildCateName(const char *name, std::string &err_info);
	inline char *cate_name();

private:
	short cate_no_;      // ��Ʒ�ӷ�����
	short main_cate_no_; // ��Ʒ��������
    char cate_name_[33]; // ��Ʒ�ӷ�������
    char main_cate_name_[33];      // ��Ʒ����������
	SQLINTEGER sql_cate_no_;       // ��Ӧcate_no_
	SQLINTEGER sql_main_cate_no_;  // ��Ӧmain_cate_no_
	SQLINTEGER sql_cate_name_;     // ��Ӧcate_name_
	SQLINTEGER sql_main_cate_name_;// ��Ӧmain_cate_name_
};

char* ChildCateForm::cate_name()
{
	DeleteSpace(cate_name_, cate_name_);
	return cate_name_;
}
#endif
