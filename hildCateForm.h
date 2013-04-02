// hildCateForm.h: interface for the ChildCateForm class.
//
//////////////////////////////////////////////////////////////////////

#ifndef REPAST_CHILDCATEFORM_H_
#define REPAST_CHILDCATEFORM_H_

#include "DBForm.h"

#define ADDCHILDCATE 1
#define UPDATECHILECATE 2
#define DELETECHILDCATE 3
struct COMCHILDCATE
{
	std::string child_no;
	std::string old_child_no;
	std::string child_name;
	std::string main_name;
};

// 商品类别子分类
class ChildCateForm : public CDBForm  
{
public:
	ChildCateForm();
	virtual ~ChildCateForm();
	void Initialize();
	bool GetChildCateName(const char *name, std::string &err_info);
	bool GetChildCateByDname(const char *parent_name, const char *child_name);
	inline short cate_no();
	inline short main_cate_no();
	inline char *main_cate_name();
	inline char *cate_name();
	bool CheckChildCate(COMCHILDCATE *child_cate);
	void SetChildCate(COMCHILDCATE *child_cate);
	bool Bind(int bind_type);
	bool AddChildCate(COMCHILDCATE *child_cate);
	bool UpdateChildCate(COMCHILDCATE *child_cate);
	bool DeleteChildCate(const char *child_no);


private:
	short cate_no_;      // 商品子分类编号
	short old_cate_no_;   // 原来的子分类编号
	short main_cate_no_; // 商品主分类编号
    char cate_name_[33]; // 商品子分类名称
    char main_cate_name_[33];      // 商品主分类名称
	SQLINTEGER sql_cate_no_;       // 对应cate_no_
	SQLINTEGER sql_old_cate_no_; 
	SQLINTEGER sql_main_cate_no_;  // 对应main_cate_no_
	SQLINTEGER sql_cate_name_;     // 对应cate_name_
	SQLINTEGER sql_main_cate_name_;// 对应main_cate_name_
};

char* ChildCateForm::cate_name()
{
	DeleteSpace(cate_name_, cate_name_);
	return cate_name_;
}
short ChildCateForm::cate_no()
{
	return cate_no_;
}

short ChildCateForm::main_cate_no()
{
	return main_cate_no_;
}

char * ChildCateForm::main_cate_name()
{
	DeleteSpace(main_cate_name_,main_cate_name_);
	return main_cate_name_;
}
#endif
