#ifndef REPAST_StaffForm_H_
#define REPAST_StaffForm_H_
#include "DBForm.h"

/* struct define */
typedef struct StaffInfo
{
	UINT menu_id;
	std::string old_id;/*����ԭ����ID�����޸�Ա����Ϣʱʹ��*/
    std::string id;
    std::string name;
    std::string sex;
    std::string age;
    std::string salary;
	std::string department;
	std::string email_address;
	std::string phone;
	std::string address;
	
}STAFFINFO;

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
    virtual bool BindingParameter(bool is_add, std::string &error_info);
	bool InsertInfo(STAFFINFO * staff_info, std::string &error_info);
	bool DeleteInfo(const char *user_id, std::string &error_info);
	bool UpdateInfo(STAFFINFO * staff_info,	std::string &error_info);
	int GetStaffSum();
	bool CheckStaff(STAFFINFO * staff_info, std::string &error_info);
	bool SetStaff(STAFFINFO * staff_info, std::string &error_info);
	bool GetStaffNo();

private:
	char m_old_id_[9];
    char m_id_[9];                /* staff's id */
    char m_name_[10];             /* staff's name */
    char m_sex_[3];               /* staff's sex */
    char m_dept_num_[3];          /* staff's department number */
    char m_dept_name_[10];        /* staff's department name */
    short m_age_;                 /* staff's age */
    float m_salary_;             /* staff's salary */
	char m_mailbox_[51];          /* staff's mailbox*/
	char m_phone_num_[21];        /* staff's phone number */
	char m_address_[1001];       /* staff's mailbox*/

    SQLINTEGER m_sql_old_id_;
    SQLINTEGER m_sql_id_;         /* the staff's id in database Staff form */
    SQLINTEGER m_sql_name_;       /* the staff's name in database Staff form */
    SQLINTEGER m_sql_sex_;        /* the staff's sex in database Staff form */
    SQLINTEGER m_sql_age_;        /* the staff's age in database Staff form */
    SQLINTEGER m_sql_salary_;     /* the staff's salary in database Staff form */
    SQLINTEGER m_sql_dept_num_;   /* the staff's department number in database Staff form */
	SQLINTEGER m_sql_dept_name_;  /* the staff's department name in database Dept form */
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
	DeleteSpace(m_id_, m_id_);
    return m_id_;
}

/*
 * ˵��: ��ȡԱ������
 * ����ֵ: Ա�������ַ���
 **/
char* CStaffForm::name()
{
	DeleteSpace(m_name_, m_name_);
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
	DeleteSpace(m_dept_name_, m_dept_name_);
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
	DeleteSpace(m_mailbox_, m_mailbox_);
    return m_mailbox_;
}

/*
 * ˵��: ��ȡԱ���绰����
 * ����ֵ: Ա���绰�����ַ���
 **/
char* CStaffForm::phone_num()
{
	DeleteSpace(m_phone_num_, m_phone_num_);
    return m_phone_num_;
}

/*
 * ˵��: ��ȡԱ��סַ
 * ����ֵ: Ա��סַ�ַ���
 **/
char* CStaffForm::address()
{
	DeleteSpace(m_address_, m_address_);
    return m_address_;
}

#endif /* end #define REPAST_CStaffForm_H_ */
