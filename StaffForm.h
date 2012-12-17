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
    virtual bool BindingParameter();
    bool InsertInfo(char *user_id, char *user_name,
                    char *user_sex, short user_age,
                    double user_salary, char *user_dept_num);

private:
    char m_id_[9];                /* staff's id */
    char m_name_[10];             /* staff's name */
    char m_sex_[3];               /* staff's sex */
    char m_dept_num_[3];          /* staff's department number */
    char m_dept_name_[10];        /* staff's department name */
    short m_age_;                 /* staff's age */
    double m_salary_;             /* staff's salary */
    SQLINTEGER m_sql_id_;         /* the staff's id in database Staff form */
    SQLINTEGER m_sql_name_;       /* the staff's name in database Staff form */
    SQLINTEGER m_sql_sex_;        /* the staff's sex in database Staff form */
    SQLINTEGER m_sql_age_;        /* the staff's age in database Staff form */
    SQLINTEGER m_sql_salary_;     /* the staff's salary in database Staff form */
    SQLINTEGER m_sql_dept_num_;   /* the staff's department number in database Staff form */
//	SQLINTEGER m_sql_dept_name_;  /* the staff's department name in database Dept form */
};

/*
 * 说明: 获取员工编号
 * 返回值: 员工编号字符串
 **/
char* CStaffForm::id()
{
    return m_id_;
}

/*
 * 说明: 获取员工姓名
 * 返回值: 员工姓名字符串
 **/
char* CStaffForm::name()
{
    return m_name_;
}

/*
 * 说明: 获取员工性别
 * 返回值: 员工性别字符串
 **/
char* CStaffForm::sex()
{
    return m_sex_;
}

/*
 * 说明: 获取员工所在部门编号
 * 返回值: 员工所在部门编号字符串
 **/
char* CStaffForm::dept_num()
{
    return m_dept_num_;
}

/*
 * 说明: 获取员工所在部门名称
 * 返回值: 员工所在部门名称字符串
 **/
char* CStaffForm::dept_name()
{
    return m_dept_name_;
}

/*
 * 说明: 获取员工年龄
 * 返回值: 员工年龄
 **/
short CStaffForm::age() const
{
    return m_age_;
}

/*
 * 说明: 获取员工工资
 * 返回值: 员工工资
 **/
double CStaffForm::salary() const
{
    return m_salary_;
}


#endif /* end #define REPAST_CStaffForm_H_ */
