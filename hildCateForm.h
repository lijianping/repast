// hildCateForm.h: interface for the ChildCateForm class.
//
//////////////////////////////////////////////////////////////////////

#ifndef REPAST_CHILDCATEFORM_H_
#define REPAST_CHILDCATEFORM_H_

#include "DBForm.h"

// 商品类别子分类
class ChildCateForm : public CDBForm  
{
public:
	ChildCateForm();
	virtual ~ChildCateForm();
	void Initialize();
	bool GetChildCateName(const char *name, std::string &err_info);

private:
	short cate_no_;      // 商品子分类编号
	short main_cate_no_; // 商品主分类编号
    char cate_name_[33]; // 商品子分类名称
    char main_cate_name_[33];      // 商品主分类名称
	SQLINTEGER sql_cate_no_;       // 对应cate_no_
	SQLINTEGER sql_main_cate_no_;  // 对应main_cate_no_
	SQLINTEGER sql_cate_name_;     // 对应cate_name_
	SQLINTEGER sql_main_cate_name_;// 对应main_cate_name_
};

#endif
