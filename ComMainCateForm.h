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
	char name_[33];   // ����������
	short no_;        // ��������
	short old_no_;    // ������ԭ���
	SQLINTEGER sql_name_;  // ��Ӧ����������
	SQLINTEGER sql_no_;    // ��Ӧ��������
	SQLINTEGER sql_old_no_;// ��Ӧ������ԭ���
};

inline short ComMainCateForm::no() const {
	return no_;
}

inline short ComMainCateForm::old_no() const {
	return old_no_;
}

inline char* ComMainCateForm::name() {
	DeleteSpace(name_, name_);   // ɾ���ո�
	return name_;
}
#endif 
