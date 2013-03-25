// ComMainCateForm.h: interface for the CComMainCateForm class.
//
//////////////////////////////////////////////////////////////////////

#ifndef REPAST_COMMAINCATEFORM_H_
#define REPAST_COMMAINCATEFORM_H_

#include "DBForm.h"

class ComMainCateForm : public CDBForm {
public:
	ComMainCateForm();
	~ComMainCateForm();
	inline short no() const;
	inline short old_no() const;
	inline char* name();
	bool GetMainCateName();
	void Initialize();

private:
	char name_[33];   // 主分类名称
	short no_;        // 主分类编号
	short old_no_;    // 主分类原编号
	SQLINTEGER sql_name_;  // 对应主分类名称
	SQLINTEGER sql_no_;    // 对应主分类编号
	SQLINTEGER sql_old_no_;// 对应主分类原编号
};

inline short ComMainCateForm::no() const {
	return no_;
}

inline short ComMainCateForm::old_no() const {
	return old_no_;
}

inline char* ComMainCateForm::name() {
	DeleteSpace(name_, name_);   // 删除空格
	return name_;
}
#endif 
