// ComMainCateForm.h: interface for the CComMainCateForm class.
//
//////////////////////////////////////////////////////////////////////

#ifndef REPAST_COMMAINCATEFORM_H_
#define REPAST_COMMAINCATEFORM_H_

#include "DBForm.h"

#define ADDMAINCATE    0
#define UPDATEMAINCATE 1
#define DELETEMAINCATE 2
struct COMMAINCATE 
{
	std::string old_no;
	std::string no;
	std::string name;
};
class ComMainCateForm : public CDBForm {
public:
	ComMainCateForm();
	~ComMainCateForm();
	inline short no() const;
	inline short old_no() const;
	inline char* name();
	bool GetMainCateName();
	bool GetMainCateByName(const char* name);
	void Initialize();
	bool Bind(unsigned int bind_type);
	bool CheckMainCate(COMMAINCATE *main_cate);
	void SetMainCate(COMMAINCATE *main_cate);
	bool AddMainCate(COMMAINCATE *main_cate);
	bool UpdateMainCate(COMMAINCATE *main_cate);
	bool DeleteMainCate(const char *main_cate_no);

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
