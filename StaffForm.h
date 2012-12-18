#ifndef REPAST_StaffForm_H_
#define REPAST_StaffForm_H_
#include "DBForm.h"

class CStaffForm : public CDBForm
{
public:
	CStaffForm();
	virtual ~CStaffForm();
    inline char* id();
    inline char* name();
    inline char* sex();
    inline char* dept_num();
    inline char* dept_name();
    inline short age() const;
    inline double salary() const;
	inline char* mailbox();
	inline char* phone_num();
	inline char* address();
    virtual bool BindingParameter();
    bool InsertInfo(char *user_id, char *user_name,
                    char *user_sex, short user_age,
                    double user_salary, char *user_dept_num,
					std::string &error_info);
	bool DeleteInfo(char *user_id, std::string &error_info);

private:
    char m_id_[9];                /* staff's id */
    char m_name_[10];             /* staff's name */
    char m_sex_[3];               /* staff's sex */
    char m_dept_num_[3];          /* staff's department number */
    char m_dept_name_[10];        /* staff's department name */
    short m_age_;                 /* staff's age */
    double m_salary_;             /* staff's salary */
	char m_mailbox_[51];          /* staff's mailbox*/
	char m_phone_num_[21];        /* staff's phone number */
	char m_address_[10001];       /* staff's mailbox*/
    SQLINTEGER m_sql_id_;         /* the staff's id in database Staff form */
    SQLINTEGER m_sql_name_;       /* the staff's name in database Staff form */
    SQLINTEGER m_sql_sex_;        /* the staff's sex in database Staff form */
    SQLINTEGER m_sql_age_;        /* the staff's age in database Staff form */
    SQLINTEGER m_sql_salary_;     /* the staff's salary in database Staff form */
    SQLINTEGER m_sql_dept_num_;   /* the staff's department number in database Staff form */
//	SQLINTEGER m_sql_dept_name_;  /* the staff's department name in database Dept form */
	SQLINTEGER m_sql_mailbox_;    /* the staff's mailbox in database Dept form */
	SQLINTEGER m_sql_phone_num_;  /* the staff's phone number in database Dept form */
	SQLINTEGER m_sql_address_;    /* the staff's address in database Dept form */
};

/*
 * ˵��: ��ȡԱ�����
 * ����ֵ: Ա������ַ���
 **/
char* CStaffForm::id()
{
    return m_id_;
}

/*
 * ˵��: ��ȡԱ������
 * ����ֵ: Ա�������ַ���
 **/
char* CStaffForm::name()
{
    return m_name_;
}

/*
 * ˵��: ��ȡԱ���Ա�
 * ����ֵ: Ա���Ա��ַ���
 **/
char* CStaffForm::sex()
{
    return m_sex_;
}

/*
 * ˵��: ��ȡԱ�����ڲ��ű��
 * ����ֵ: Ա�����ڲ��ű���ַ���
 **/
char* CStaffForm::dept_num()
{
    return m_dept_num_;
}

/*
 * ˵��: ��ȡԱ�����ڲ�������
 * ����ֵ: Ա�����ڲ��������ַ���
 **/
char* CStaffForm::dept_name()
{
    return m_dept_name_;
}

/*
 * ˵��: ��ȡԱ������
 * ����ֵ: Ա������
 **/
short CStaffForm::age() const
{
    return m_age_;
}

/*
 * ˵��: ��ȡԱ������
 * ����ֵ: Ա������
 **/
double CStaffForm::salary() const
{
    return m_salary_;
}

/*
 * ˵��: ��ȡԱ������
 * ����ֵ: Ա�������ַ���
 **/
char* CStaffForm::mailbox()
{
    return m_mailbox_;
}

/*
 * ˵��: ��ȡԱ���绰����
 * ����ֵ: Ա���绰�����ַ���
 **/
char* CStaffForm::phone_num()
{
    return m_phone_num_;
}

/*
 * ˵��: ��ȡԱ��סַ
 * ����ֵ: Ա��סַ�ַ���
 **/
char* CStaffForm::address()
{
    return m_address_;
}

#endif /* end #define REPAST_CStaffForm_H_ */
