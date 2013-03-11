// CStaffForm.cpp: implementation of the CStaffForm class.
//
//////////////////////////////////////////////////////////////////////

#include "StaffForm.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStaffForm::CStaffForm()
: m_age_(0),
  m_salary_(0),
  m_sql_id_(SQL_NTS),
  m_sql_name_(SQL_NTS),
  m_sql_sex_(SQL_NTS),
  m_sql_age_(SQL_NTS),
  m_sql_dept_name_(SQL_NTS),
  m_sql_mailbox_(SQL_NTS),
  m_sql_phone_num_(SQL_NTS),
  m_sql_address_(SQL_NTS)
{
    memset(m_id_, '\0', sizeof(m_id_));
    memset(m_name_, '\0', sizeof(m_name_));
    memset(m_sex_, '\0', sizeof(m_sex_));
    memset(m_dept_num_, '\0', sizeof(m_dept_num_));
    memset(m_dept_name_, '\0', sizeof(m_dept_name_));
	memset(m_mailbox_, '\0', sizeof(m_mailbox_));
	memset(m_phone_num_, '\0', sizeof(m_phone_num_));
	memset(m_address_, '\0', sizeof(m_address_));
    m_query_sql_ = "select Sno,Sname,Ssex,Sage,Ssalary,Dname,Smailbox,Sphoneno,Saddress from Staff,Dept where Sdeptno=Dno";
}

CStaffForm::~CStaffForm()
{

}

/*
 * 说明: 绑定记录集参数
 * 返回值: 执行成功返回true, 否则返回false
 */
bool CStaffForm::BindingParameter()
{
    /* 绑定列 *///TODO:尚未检测返回值
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_id_, sizeof(m_id_), &m_sql_id_);
    SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
    SQLBindCol(m_hstmt_, 3, SQL_C_CHAR, m_sex_, sizeof(m_sex_), &m_sql_sex_);
    SQLBindCol(m_hstmt_, 4, SQL_C_SSHORT, &m_age_, 0, &m_sql_age_);
    SQLBindCol(m_hstmt_, 5, SQL_C_DOUBLE, &m_salary_, 0, &m_sql_salary_);
    SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_dept_name_, sizeof(m_dept_name_), &m_sql_dept_name_);
   // SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_dept_num_, sizeof(m_dept_num_), &m_sql_dept_num_);
	SQLBindCol(m_hstmt_, 7, SQL_C_CHAR, m_mailbox_, sizeof(m_mailbox_), &m_sql_mailbox_);
	SQLBindCol(m_hstmt_, 8, SQL_C_CHAR, m_phone_num_, sizeof(m_phone_num_), &m_sql_phone_num_);
	SQLBindCol(m_hstmt_, 9, SQL_C_CHAR, m_address_, sizeof(m_address_), &m_sql_address_);
    return true;
}

/*
 * 说明: 绑定记录集参数,用于获取存储过程返回值
 * 返回值: 执行成功返回true, 否则返回false
 */
bool CStaffForm::BindingParameter(bool is_out)
{
	/*绑定存储过程返回值*/
	SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0,&m_pro_ret, 0, &m_sql_pro_ret);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		std::string information;
        information = "绑定返回值失败!";
		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
        return false;
    }
    /* 绑定列参数*/
    m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, sizeof(m_id_), 0, m_id_, 0, &m_sql_id_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		std::string information;
        information = "绑定参数1失败!";
		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, sizeof(m_name_), 0, m_name_, 0, &m_sql_name_);
   	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		std::string information;
        information = "绑定参数2失败!";
		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
        return false;
    }
// 	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, sizeof(m_sex_), 0, m_sex_, 0,  &m_sql_sex_);
//    	if ((m_return_code_ != SQL_SUCCESS) &&
//         (m_return_code_ != SQL_SUCCESS_WITH_INFO))
//     {
// 		std::string information;
//         information = "绑定参数3失败!";
// 		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
//         return false;
//     }
// 	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT, sizeof(m_age_), 0, &m_age_, 0, &m_sql_age_);
// 	if ((m_return_code_ != SQL_SUCCESS) &&
//         (m_return_code_ != SQL_SUCCESS_WITH_INFO))
//     {
// 		std::string information;
//         information = "绑定参数4失败!";
// 		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
//         return false;
//     }
// 	m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_REAL, sizeof(m_salary_), 0, &m_salary_, 0, &m_sql_salary_);
// 	if ((m_return_code_ != SQL_SUCCESS) &&
//         (m_return_code_ != SQL_SUCCESS_WITH_INFO))
//     {
// 		std::string information;
//         information = "绑定参数5失败!";
// 		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
//         return false;
//     }
// 	m_return_code_ = SQLBindParameter(m_hstmt_, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, sizeof(m_dept_name_), 0, m_dept_name_, 0, &m_sql_dept_name_);
//    // SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_dept_num_, sizeof(m_dept_num_), &m_sql_dept_num_);
// 	if ((m_return_code_ != SQL_SUCCESS) &&
//         (m_return_code_ != SQL_SUCCESS_WITH_INFO))
//     {
// 		std::string information;
//         information = "绑定参数6失败!";
// 		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
//         return false;
//     }
// 	m_return_code_ = SQLBindParameter(m_hstmt_, 7, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, sizeof(m_mailbox_), 0, m_mailbox_, 0, &m_sql_mailbox_);
// 	if ((m_return_code_ != SQL_SUCCESS) &&
//         (m_return_code_ != SQL_SUCCESS_WITH_INFO))
//     {
// 		std::string information;
//         information = "绑定参数7失败!";
// 		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
//         return false;
//     }
// 	m_return_code_ = SQLBindParameter(m_hstmt_, 8, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, sizeof(m_phone_num_), 0, m_phone_num_, 0, &m_sql_phone_num_);
// 	if ((m_return_code_ != SQL_SUCCESS) &&
//         (m_return_code_ != SQL_SUCCESS_WITH_INFO))
//     {
// 		std::string information;
//         information = "绑定参数8失败!";
// 		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
//         return false;
//     }
// 	m_return_code_ = SQLBindParameter(m_hstmt_, 9, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, sizeof(m_address_), 0, m_address_, 0, &m_sql_address_);
// 	if ((m_return_code_ != SQL_SUCCESS) &&
//         (m_return_code_ != SQL_SUCCESS_WITH_INFO))
//     {
// 		std::string information;
//         information = "绑定参数9失败!";
// 		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
//         return false;
//     }

	return true;
}

/*
 * 说明： 新增员工信息
 * 参数：
 *        user_id		     [in] 员工编号
 *        user_name			 [in] 员工姓名
 *        user_sex			 [in] 员工性别
 *        user_age           [in] 员工年龄
 *        user_salary        [in] 员工工资
 *        user_user_dept_num [in] 员工所属部门编号
 *        error_info		 [out] 错误信息
 * 返回值：
 *        执行成功返回true,否则返回false
 **/
bool CStaffForm::InsertInfo(const char *user_id, 
							const char *user_name,
                            const char *user_sex, 
						    const char *user_age,
                            const char *user_salary,
						    const char *user_dept_name, 
					        const char *user_email, 
						    const char *user_phone,
						    const char *user_address, 
						    std::string &error_info)
{
	/*TODO :转化数据格式*/
    char insert_sql[1024];

	char test[100];
// 	if (false == SQLAllocHandleStmt(error_info))
// 	{
// 		return false;
// 	}
	/*填充员工数据*/
 
 
// 	strcpy(m_sex_, user_sex);
// 	m_age_ = atoi(user_age);
// 	m_salary_ = atoi(user_salary);
// 	strcpy(m_dept_name_, user_dept_name);
// 	strcpy(m_mailbox_, user_email);
// 	strcpy(m_phone_num_, user_phone);
// 	strcpy(m_address_, user_address); 


	/*绑定存储过程返回值和传入参数*/
	BindingParameter(true);
	strcpy(m_id_, user_id);
	strcpy(m_name_, user_name);

	m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char*)"{? = call InsertStaff (?,?)}", SQL_NTS);
	if ((m_return_code_ != SQL_SUCCESS) && 
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
	{
		sprintf(insert_sql,"eeeeeeee= %d", m_return_code_);
	MessageBox(NULL, insert_sql, "3333ddd", 0);
		std::string error_info;
		MessageBox(NULL, "exec procedure error", "sql",0);
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
		return false;
	}
	sprintf(insert_sql,"m_re= %d",  m_pro_ret);
	MessageBox(NULL, insert_sql, "insert", 0);
	while ( ( m_return_code_ = SQLMoreResults(m_hstmt_) ) != SQL_NO_DATA )
	{
		printf("eeeeeeeeeeeeeeeeeeeeeee\n");
	}
	sprintf(test,"m_re= %d", m_pro_ret);
	MessageBox(NULL, test, "insert", 0);
// 	sprintf(insert_sql,
// 		"%s, %s, %s, %d, %f, %s, %s, %s,%s ret= %d",
// 		user_id, user_name, user_sex, atoi(user_age), (float)atoi(user_salary), user_dept_name, user_email, 
// 		user_phone, user_address, m_pro_ret);
//	MessageBox(NULL, insert_sql, "insert", 0);
// 	if (false == ExecuteSQL(insert_sql, error_info))
// 	{
// 		return false;
// 	}
    return true;
}

/*
 * 说明： 删除员工信息
 * 参数：
 *        user_id [in] 员工编号
 *        error_info [out] 错误信息
 * 返回值：
 *        执行成功返回true,否则返回false
 **/
bool CStaffForm::DeleteInfo(const char *user_id, std::string &error_info)
{
	char delete_sql[500];
	sprintf (delete_sql, "execute DeleteStaff '%s'", user_id);/*格式化删除语句*/
	/* 执行语句 */
    if (false == ExecuteSQL(delete_sql, error_info))
    {
		/*TODO:是否弹出错误对话框？*/
        return false;
    }
	return true;
}


/*
 * 说明： 更新员工信息
 * 参数：
 *        user_id		     [in] 员工编号
 *        user_name			 [in] 员工姓名
 *        user_sex			 [in] 员工性别
 *        user_age           [in] 员工年龄
 *        user_salary        [in] 员工工资
 *        user_user_dept_num [in] 员工所属部门编号
 *        error_info		 [out] 错误信息
 *返回值：
 *        执行成功返回true,否则返回false
 **/
bool CStaffForm::UpdatetInfo(const char *old_id,
							 const char *user_id,
							 const char *user_name,
							 const char *user_sex,
							 const char *user_age,
							 const char *user_salary, 
							 const char *user_dept_name, 
							 const char *user_email, 
							 const char *user_phone,
                        	 const char *user_address,
							 std::string &error_info)
{
	char update_sql[1024];
	sprintf(update_sql, 
		"execute UpdateStaff '%s', '%s', '%s', '%s', '%d', '%f', '%s', '%s', '%s','%s'",
		old_id, user_id, user_name, user_sex, atoi(user_age), (float)atoi(user_salary), 
		user_dept_name, user_email, user_phone, user_address);
	/* 执行语句 */
    if (false == ExecuteSQL(update_sql, error_info))
    {
        return false;
    }


	return true;
}

int CStaffForm::GetStaffSum()
{
	int staff_sum=-1;
	SQLINTEGER sql_sum;
	std::string error;
	char *sql_select_sum="select count(*) from Staff";
	if (false == ExecuteSQL(sql_select_sum, error))
	{
		MessageBox(NULL, error.c_str(), TEXT("统计员工数量出错"), MB_OK);
		return staff_sum;
	}
	SQLBindCol(m_hstmt_, 1, SQL_C_SLONG, &staff_sum, sizeof(staff_sum), &sql_sum);
	MoveFirst();
	return staff_sum;
}
